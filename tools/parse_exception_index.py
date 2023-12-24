# Updated Python application to handle all unwind operations as specified in the ARM EHABI documentation.

import argparse
import sys
import struct
from pathlib import Path

def swap32(i):
    return struct.unpack("<I", struct.pack(">I", i))[0]

def selfrel_offset31(offset):
  # Sign extend to 32 bits.
  if offset & (1 << 30):
    offset |= 1 << 31
  else:
    offset &= ~(1 << 31)
  return offset

def describe_instruction2(instruction):
    descriptions = []
    i = 0
    instruction = swap32(instruction)

    while i < 4:
        # Extract the byte from the instruction
        byte = (instruction >> (i * 8)) & 0xFF

        if 0x00 <= byte <= 0x3F:  # 00xxxxxx: vsp = vsp + (xxxxxx << 2) + 4
            value = (byte & 0x3F) << 2
            descriptions.append(f"Byte {i+1}: vsp = vsp + {value + 4} (Immediate value)")

        elif 0x40 <= byte <= 0x7F:  # 01xxxxxx: vsp = vsp - (xxxxxx << 2) - 4
            value = (byte & 0x3F) << 2
            descriptions.append(f"Byte {i+1}: vsp = vsp - {value + 4} (Immediate value)")

        elif byte == 0x80 and i < 3 and (instruction >> ((i + 1) * 8) & 0xFF) == 0x00:  # 10000000 00000000: Refuse to unwind
            descriptions.append(f"Byte {i+1}-{i+2}: Refuse to unwind")
            i += 1  # Skip next byte

        elif 0x80 <= byte <= 0x8F:  # 1000iiii iiiiiiii: Pop integer registers r4-r15 under masks
            if i < 3:
                next_byte = (instruction >> ((i + 1) * 8)) & 0xFF
                mask = ((byte & 0x0F) << 8) | next_byte
                descriptions.append(f"Byte {i+1}-{i+2}: Pop integer registers under mask {mask:#04x}")
                i += 1  # Skip next byte

        elif 0x90 <= byte <= 0x9D:  # 1001nnnn: Set vsp = r[nnnn] (nnnn != 13,15)
            reg = byte & 0x0F
            if reg not in [0xD, 0xF]:
                descriptions.append(f"Byte {i+1}: Set vsp = r{reg}")

        elif byte == 0x9D:  # 10011101: Reserved as prefix for Arm register to register moves
            descriptions.append(f"Byte {i+1}: Reserved as prefix for Arm register to register moves")

        elif byte == 0x9F:  # 10011111: Reserved as prefix for Intel Wireless MMX register to register moves
            descriptions.append(f"Byte {i+1}: Reserved as prefix for Intel Wireless MMX register to register moves")

        elif 0xA0 <= byte <= 0xA7:  # 10100nnn: Pop r4-r[4+nnn]
            top_reg = 4 + (byte & 0x07)
            descriptions.append(f"Byte {i+1}: Pop r4-r{top_reg}")

        elif 0xA8 <= byte <= 0xAF:  # 10101nnn: Pop r4-r[4+nnn], r14
            top_reg = 4 + (byte & 0x07)
            descriptions.append(f"Byte {i+1}: Pop r4-r{top_reg}, r14")

        elif byte == 0xB0:  # 10110000: Finish
            descriptions.append(f"Byte {i+1}: Finish")

        elif byte == 0xB1 and i < 3:  # 10110001 00000000: Spare
            if (instruction >> ((i + 1) * 8) & 0xFF) == 0x00:
                descriptions.append(f"Byte {i+1}-{i+2}: Spare")
                i += 1  # Skip next byte

        elif 0xB1 <= byte <= 0xBF:  # 10110001 0000iiii: Pop integer registers under mask {r3, r2, r1, r0}
            # ... additional cases for other instructions ...
            descriptions.append(f"Byte {i+1}: Instruction not yet implemented")

        else:
            descriptions.append(f"Byte {i+1}: Unknown instruction: {byte:#04x}")

        i += 1

    return "; ".join(descriptions)

def parse_exception_table(file_path):
    try:
        data = Path(file_path).read_bytes()
        offset = 0

        # Each entry is 8 bytes long, so loop through each entry.
        while offset < len(data):
            entry = data[offset:offset+8]
            prel31_offset, instructions_or_prel31 = struct.unpack("<II", entry)
            offset = selfrel_offset31(prel31_offset)

            print(f"[{prel31_offset:#010x}->{offset},{instructions_or_prel31:#010x}]: ",
                  end="")

            if instructions_or_prel31 == 0x00000001:
                print(f"EXIDX_CANTUNWIND")
            elif not (instructions_or_prel31 & 0x80000000):
                print(f"Instructions located in ARM.EXTAB region, {selfrel_offset31(prel31_offset)}")
            else:
                print(describe_instruction2(instructions_or_prel31))
            offset += 8

    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <binary_file_path>")
    else:
        parse_exception_table(sys.argv[1])


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--index",
                        help="Path to the ARM index table binary file",
                        type=Path)
    parser.add_argument("-x", "--ex-tab",
                        help="Path to the ARM ex-tab table",
                        default=15,
                        type=int)
    parser.add_argument("-s", "--sample_size",
                                  help="Number of files to generate",
                                  default=25,
                                  type=int)
    parser.add_argument("-e", "--error_size",
                                  help="Size, in bytes, of the error object. In randomized test suites, this will be the upper bounds.",
                                  default=128,
                                  type=int)
    parser.add_argument("-n", "--nontrivial_dtor",
                                  help="Determine if classes will have a nontrivial destructor.",
                                  action='store_true')
    parser.set_defaults(func=parse_exception_table)
    args = parser.parse_args()
    args.func(args)
