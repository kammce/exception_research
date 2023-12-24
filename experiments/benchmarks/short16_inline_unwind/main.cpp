
#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <limits>
#include <span>
#include <string_view>

#include <unwind.h>

/// Structure type to access the Data Watch point and Trace Register (DWT).
struct dwt_register_t
{
  /// Offset: 0x000 (R/W)  Control Register
  volatile uint32_t ctrl;
  /// Offset: 0x004 (R/W)  Cycle Count Register
  volatile uint32_t cyccnt;
  /// Offset: 0x008 (R/W)  CPI Count Register
  volatile uint32_t cpicnt;
  /// Offset: 0x00C (R/W)  Exception Overhead Count Register
  volatile uint32_t exccnt;
  /// Offset: 0x010 (R/W)  Sleep Count Register
  volatile uint32_t sleepcnt;
  /// Offset: 0x014 (R/W)  LSU Count Register
  volatile uint32_t lsucnt;
  /// Offset: 0x018 (R/W)  Folded-instruction Count Register
  volatile uint32_t foldcnt;
  /// Offset: 0x01C (R/ )  Program Counter Sample Register
  volatile const uint32_t pcsr;
  /// Offset: 0x020 (R/W)  Comparator Register 0
  volatile uint32_t comp0;
  /// Offset: 0x024 (R/W)  Mask Register 0
  volatile uint32_t mask0;
  /// Offset: 0x028 (R/W)  Function Register 0
  volatile uint32_t function0;
  /// Reserved 0
  std::array<uint32_t, 1> reserved0;
  /// Offset: 0x030 (R/W)  Comparator Register 1
  volatile uint32_t comp1;
  /// Offset: 0x034 (R/W)  Mask Register 1
  volatile uint32_t mask1;
  /// Offset: 0x038 (R/W)  Function Register 1
  volatile uint32_t function1;
  /// Reserved 1
  std::array<uint32_t, 1> reserved1;
  /// Offset: 0x040 (R/W)  Comparator Register 2
  volatile uint32_t comp2;
  /// Offset: 0x044 (R/W)  Mask Register 2
  volatile uint32_t mask2;
  /// Offset: 0x048 (R/W)  Function Register 2
  volatile uint32_t function2;
  /// Reserved 2
  std::array<uint32_t, 1> reserved2;
  /// Offset: 0x050 (R/W)  Comparator Register 3
  volatile uint32_t comp3;
  /// Offset: 0x054 (R/W)  Mask Register 3
  volatile uint32_t mask3;
  /// Offset: 0x058 (R/W)  Function Register 3
  volatile uint32_t function3;
};

/// Structure type to access the Core Debug Register (CoreDebug)
struct core_debug_registers_t
{
  /// Offset: 0x000 (R/W)  Debug Halting Control and Status Register
  volatile uint32_t dhcsr;
  /// Offset: 0x004 ( /W)  Debug Core Register Selector Register
  volatile uint32_t dcrsr;
  /// Offset: 0x008 (R/W)  Debug Core Register Data Register
  volatile uint32_t dcrdr;
  /// Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register
  volatile uint32_t demcr;
};

/// Address of the hardware DWT registers
constexpr intptr_t dwt_address = 0xE0001000UL;

/// Address of the Cortex M CoreDebug module
constexpr intptr_t core_debug_address = 0xE000EDF0UL;

// NOLINTNEXTLINE
auto* dwt = reinterpret_cast<dwt_register_t*>(dwt_address);

// NOLINTNEXTLINE
auto* core = reinterpret_cast<core_debug_registers_t*>(core_debug_address);

void dwt_counter_enable()
{
  /**
   * @brief This bit must be set to 1 to enable use of the trace and debug
   * blocks:
   *
   *   - Data Watchpoint and Trace (DWT)
   *   - Instrumentation Trace Macrocell (ITM)
   *   - Embedded Trace Macrocell (ETM)
   *   - Trace Port Interface Unit (TPIU).
   */
  constexpr unsigned core_trace_enable = 1 << 24U;

  /// Mask for turning on cycle counter.
  constexpr unsigned enable_cycle_count = 1 << 0;

  // Enable trace core
  core->demcr = (core->demcr | core_trace_enable);

  // Reset cycle count
  dwt->cyccnt = 0;

  // Start cycle count
  dwt->ctrl = (dwt->ctrl | enable_cycle_count);
}

std::uint32_t uptime()
{
  return dwt->cyccnt;
}

[[noreturn]] void terminate() noexcept
{
  while (true) {
    continue;
  }
}

namespace __cxxabiv1 {                                   // NOLINT
std::terminate_handler __terminate_handler = terminate;  // NOLINT
}

extern "C"
{
  void _exit([[maybe_unused]] int rc)
  {
    while (true) {
      continue;
    }
  }
  int kill(int, int)
  {
    return -1;
  }
  struct _reent* _impure_ptr = nullptr;  // NOLINT
  int getpid()
  {
    return 1;
  }

  std::array<std::uint8_t, 1024> storage;
  std::span<std::uint8_t> storage_left(storage);
  void* __wrap___cxa_allocate_exception(unsigned int p_size)  // NOLINT
  {
    // I only know this needs to be 128 because of the disassembly. I cannot
    // figure out why its needed yet, but maybe the answer is in the
    // libunwind-arm.cpp file.
    static constexpr size_t offset = 128;
    if (p_size + offset > storage_left.size()) {
      return nullptr;
    }
    auto* memory = &storage_left[offset];
    storage_left = storage_left.subspan(p_size + offset);
    return memory;
  }
  void __wrap___cxa_free_exception(void*)  // NOLINT
  {
    storage_left = std::span<std::uint8_t>(storage);
  }
  void __wrap___cxa_call_unexpected(void*)  // NOLINT
  {
    std::terminate();
  }
}  // extern "C"

int start();

int main()
{
  dwt_counter_enable();
  // Set flash accelerator to 1 CPU cycle per instruction
  *reinterpret_cast<std::uint32_t*>(0x400F'C000) = 0xA;
  volatile int return_code = 0;
  try {
    return_code = start();
  } catch (...) {
    return_code = -1;
  }
  std::terminate();
  return return_code;
}

std::uint64_t call_latency = 0;
std::uint64_t cycle_cost = 0;

namespace cortex {
struct m4_core
{
  std::array<std::uint32_t, 16> r{};
  volatile std::uint32_t& ip()
  {
    return r[12];
  }
  volatile std::uint32_t& sp()
  {
    return r[13];
  }
  volatile std::uint32_t* sp_ptr()
  {
    return reinterpret_cast<std::uint32_t*>(r[13]);
  }
  volatile std::uint32_t* sp_ptr2()
  {
    return reinterpret_cast<std::uint32_t*>(r[13]);
  }
  volatile std::uint32_t& lr()
  {
    return r[14];
  }
  volatile std::uint32_t& pc()
  {
    return r[15];
  }
};

struct m4_virtual_cpu
{
  m4_core core;
};
}  // namespace cortex

template<size_t N_words>
class stack
{
public:
  void push(std::uint32_t p_word) noexcept
  {
    m_stack[m_index--] = p_word;
  }

  std::uint8_t allocate_local_space(std::uint32_t p_word_count) noexcept
  {
    m_index -= p_word_count;
    return p_word_count;
  }

  auto index() const noexcept
  {
    return m_index;
  }

  std::uint32_t stack_address() const noexcept
  {
    return reinterpret_cast<std::uint32_t>(&m_stack[m_index]);
  }

  const std::uint32_t* stack_pointer() const noexcept
  {
    return &m_stack[m_index];
  }

private:
  std::array<std::uint32_t, N_words> m_stack{};
  std::uint32_t m_index = (N_words - 1);
};

stack<16> my_stack{};

struct short16_entry_t
{
  std::array<std::uint8_t, 3> instructions{};
  std::uint8_t personality_select = 0b1'000'0000;
};

enum class instruction_class
{
  add_vsp = 0b00 << 6,
  sub_vsp = 0b01 << 6,
  basic_unwind = 0b10 << 6,
  advanced_unwind = 0b11 << 6,
};

cortex::m4_virtual_cpu virtual_cpu{};
short16_entry_t personality_info{};
std::uint64_t temp_cycles = 0;

[[gnu::noinline]] void execute_unwind(cortex::m4_virtual_cpu& p_virtual_cpu,
                                      short16_entry_t& p_personality_info)
{
  // Perform "short16_inline_unwind"
  auto start = uptime();
  bool set_pc = false;
  for (auto index = 0; index < 3; index++) {
    auto instruction = p_personality_info.instructions.crbegin()[index];
    if (instruction == 0xb0) {
      // "10110000"
      // Finish (see remark c)
      goto exit_loop;
    }
    // Extract the first 4 bits
    int main_bits = (instruction & 0b11110000) >> 4;

    switch (main_bits) {
      case 0b0000:
      case 0b0001:
      case 0b0010:
      case 0b0011: {
        // vsp = vsp + (xxxxxx << 2) + 4. Covers range 0x04-0x100 inclusive
        int shift_amount = instruction & 0b111111;
        p_virtual_cpu.core.sp() =
          p_virtual_cpu.core.sp() + ((shift_amount << 2) + 4);
        break;
      }
      case 0b0100:
      case 0b0101:
      case 0b0110:
      case 0b0111: {
        // vsp = vsp - (xxxxxx << 2) + 4. Covers range 0x04-0x100 inclusive
        int shift_amount = instruction & 0b111111;
        p_virtual_cpu.core.sp() =
          p_virtual_cpu.core.sp() - ((shift_amount << 2) + 4);
        break;
      }
      case 0b1001: {
        // Handle "1001nnnn"
        int nnnn = instruction & 0xF;  // Extract the last 4 bits
        if (nnnn != 13 && nnnn != 15) {
          // Set vsp = r[nnnn]
          p_virtual_cpu.core.sp() = p_virtual_cpu.core.r[nnnn];
        } else {
          // Handle "10011101" or "10011111"
          // Reserved as prefix for Arm register to register moves
          // Reserved as prefix for Intel Wireless MMX register to register
          // moves
          std::terminate();
        }
        break;
      }
      case 0b1010: {
        // Handle "10100nnn" (Pop r4-r[4+nnn]), and "10101nnn" (Pop r4-r[4+nnn],
        // r14)
        volatile std::uint32_t* sp_ptr = p_virtual_cpu.core.sp_ptr();
        if (instruction & 0b1000) {
          p_virtual_cpu.core.lr() = (*sp_ptr++);
        }
#if 1
        int nnn = instruction & 0b111;  // Extract the last 3 bits
        switch (nnn) {
          case 7:
            p_virtual_cpu.core.r[11] = (*sp_ptr++);
            [[fallthrough]];
          case 6:
            p_virtual_cpu.core.r[10] = (*sp_ptr++);
            [[fallthrough]];
          case 5:
            p_virtual_cpu.core.r[9] = (*sp_ptr++);
            [[fallthrough]];
          case 4:
            p_virtual_cpu.core.r[8] = (*sp_ptr++);
            [[fallthrough]];
          case 3:
            p_virtual_cpu.core.r[7] = (*sp_ptr++);
            [[fallthrough]];
          case 2:
            p_virtual_cpu.core.r[6] = (*sp_ptr++);
            [[fallthrough]];
          case 1:
            p_virtual_cpu.core.r[5] = (*sp_ptr++);
            [[fallthrough]];
          case 0:
            p_virtual_cpu.core.r[4] = (*sp_ptr++);
        }
#else
        int nnn = 4 + (instruction & 0x7);  // Extract the last 3 bits
        for (int i = nnn - 1; i >= 4; i--) {
          p_virtual_cpu.core.r[i] = (*sp_ptr++);
        }
#endif
        p_virtual_cpu.core.sp() = reinterpret_cast<std::uint32_t>(sp_ptr);
        break;
      }
      case 0b1011: {
        // Handle "10110000", and "1011011n"
        if (instruction == 0xb0) {
          // "10110000"
          // Finish (see remark c)
          goto exit_loop;
        } else if ((instruction & 0b1100) == 0b1100) {
          // "1011011n"
          // Spare (was Pop FPA)
          std::terminate();
        }
        break;
      }
      // No additional groupings are left as all provided instructions are
      // covered
      default:
        // Handle unknown or undefined instruction
        std::terminate();
        break;
    }
  }
exit_loop:
  if (!set_pc) {
    p_virtual_cpu.core.pc() = p_virtual_cpu.core.lr();
  }
  cycle_cost = uptime() - start;
}

int start()
{
  auto call_latency_test_start = uptime();
  auto call_latency_test_end = uptime();
  call_latency = call_latency_test_end - call_latency_test_start;

  // Setup
  constexpr std::uint32_t starting_r4 = 0x1234;
  constexpr std::uint32_t starting_r5 = 0x5678;
  constexpr std::uint32_t starting_r6 = 0x9ABC;
  constexpr std::uint32_t starting_r7 = 0xDEF0;
  constexpr std::uint32_t starting_lr = 0xDEAD;
  constexpr std::uint32_t starting_pc = 0xabc0;

  constexpr std::uint32_t ending_r4 = 0x4444;
  constexpr std::uint32_t ending_r5 = 0x5555;
  constexpr std::uint32_t ending_r6 = 0x6666;
  constexpr std::uint32_t ending_r7 = 0x7777;
  constexpr std::uint32_t ending_lr = 0xBEEF;

  my_stack.push(ending_r4);
  my_stack.push(ending_r5);
  my_stack.push(ending_r6);
  my_stack.push(ending_r7);
  my_stack.push(ending_lr);
  const auto deallocate_instruction = my_stack.allocate_local_space(8);

  virtual_cpu.core.r[4] = starting_r4;
  virtual_cpu.core.r[5] = starting_r5;
  virtual_cpu.core.r[6] = starting_r6;
  virtual_cpu.core.r[7] = starting_r7;
  virtual_cpu.core.lr() = starting_lr;
  virtual_cpu.core.pc() = starting_pc;
  virtual_cpu.core.sp() = my_stack.stack_address();
  // 00xxxxxx = vsp = vsp + (xxxxxx << 2) + 4. Covers range 0x04-0x100
  // inclusive
  // 10101nnn = Pop r4-r[4+nnn], r14
  personality_info.instructions.rbegin()[0] = deallocate_instruction;
  personality_info.instructions.rbegin()[1] = 0b10101'011;
  personality_info.instructions.rbegin()[2] = 0xB0;

  execute_unwind(virtual_cpu, personality_info);

  // Breakpoint
  while (true) {
    asm volatile("BKPT #0");
    continue;
  }
}
