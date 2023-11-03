from pathlib import Path
import struct

arm_ex_idx_file = Path("except2.bin")
ex_idx_data = arm_ex_idx_file.read_bytes()
_IDX_TABLE_ENTRY_FORMAT = "<II"
_IDX_TABLE_ENTRY_SIZE = struct.calcsize(_IDX_TABLE_ENTRY_FORMAT)
_IDX_TABLE_ADDRESS = 0x0000a268
entry_count = len(ex_idx_data) / _IDX_TABLE_ENTRY_SIZE

def selfrel_offset31(offset):
  # Sign extend to 32 bits.
  if offset & (1 << 30):
    offset |= 1 << 31
  else:
    offset &= ~(1 << 31)
  return offset

def signed_32bit(value):
  return struct.unpack('i', struct.pack('=I', value & 0xffffffff))[0]


one_content = 0

for i in range(int(entry_count)):
  start = i * _IDX_TABLE_ENTRY_SIZE
  end = start + _IDX_TABLE_ENTRY_SIZE
  entry_position = _IDX_TABLE_ADDRESS + start
  entry = struct.unpack(_IDX_TABLE_ENTRY_FORMAT, ex_idx_data[start:end])
  offset = selfrel_offset31(entry[0])
  signed_offset = signed_32bit(offset)
  if entry[1] == 1:
    one_content += 1
  print("{:03d}".format(i), ")", hex(entry[0]), "0x{:08x}".format(entry[1]),
        "offset:", signed_offset, hex(offset), hex(entry_position),
        "fun_addr:", hex(signed_offset + entry_position))

print("================ Stats ================")
print("Entries with 1 as 'content':", one_content)
print("Total entry count:", entry_count)