#include <unwind.h>

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <limits>
#include <span>

volatile std::int32_t side_effect = 0;
std::uint32_t start_cycles = 0;
std::uint32_t end_cycles = 0;

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

void
dwt_counter_enable()
{
#if __arm__
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
#endif
}

void
enable_flash_accelerator()
{
#if __arm__
  // Set flash accelerator to 1 CPU cycle per instruction
  *reinterpret_cast<std::uint32_t*>(0x400F'C000) = 0xA;
#endif
}

std::uint32_t
uptime()
{
#if __arm__
  return dwt->cyccnt;
#else
  return 0;
#endif
}

struct my_error_t
{
  std::array<std::uint8_t, 4> data;
};

[[noreturn]] void
terminate() noexcept
{
  while (true) {
    continue;
  }
}

namespace __cxxabiv1 {                                  // NOLINT
std::terminate_handler __terminate_handler = terminate; // NOLINT
}

std::uint64_t iterate_time = 0;
std::uint64_t relative_iterate_time = 0;
std::uint64_t call_latency = 0;

template<size_t SizeBytes>
class fake_stack
{
public:
  bool allocate_memory_and_push_sp_and_pc(size_t p_amount, std::intptr_t p_pc)
  {
    if (m_sp_index + p_amount > m_stack.size()) {
      return false;
    }
    auto old_sp_index = m_sp_index;
    m_sp_index += p_amount;
    m_sp_index += 1;
    m_stack[m_sp_index] =
      reinterpret_cast<std::intptr_t>(&m_stack[old_sp_index]);
    m_sp_index += 1;
    m_stack[m_sp_index] = p_pc;

    return true;
  }

  std::intptr_t* sp() { return &m_stack[m_sp_index]; }

  std::array<std::intptr_t, SizeBytes / sizeof(std::intptr_t)> m_stack{};
  std::intptr_t m_sp_index = 0;
};

template<size_t SizeBytes>
class fake_stack_with_relative_frame_pointer
{
public:
  bool allocate_memory_and_push_sp_and_pc(
    std::intptr_t p_number_of_registers_pushed,
    std::intptr_t p_pc,
    size_t p_local_variable_word_size)
  {

    if (m_sp_index + p_local_variable_word_size + p_number_of_registers_pushed +
          1 >
        m_stack.size()) {
      return false;
    }
    auto old_sp_index = m_sp_index;

    // Inject pushed registers
    for (std::intptr_t i = 0; i < p_number_of_registers_pushed; i++) {
      // 0xABCD MSB is used to mark that this is a register entry in the data
      // The LSB bytes will indicate the count.
      m_stack[m_sp_index] = 0xABCD'0000 + i;
      m_sp_index += 1;
    }

    // Inject PC
    m_stack[m_sp_index] = p_pc;
    m_sp_index++;

    // Allocate local variables plus the space for the tail frame pointer
    m_sp_index += p_local_variable_word_size + 1;

    // Set tail frame pointer
    std::uint32_t trivial_unwind_data = 0;
    const auto frame_pointer_distance = m_sp_index - (old_sp_index + 1);
    const auto link_register_distance =
      frame_pointer_distance - (p_number_of_registers_pushed - 1);

    m_stack[m_sp_index - 1] =
      link_register_distance << 16 | frame_pointer_distance;

    return true;
  }

  std::intptr_t* sp() { return &m_stack[m_sp_index]; }

  std::array<std::intptr_t, SizeBytes / sizeof(std::intptr_t)> m_stack{};
  std::intptr_t m_sp_index = 0;
};

fake_stack<10'000> my_stack{};
fake_stack_with_relative_frame_pointer<10'000> relative_stack{};
volatile std::intptr_t final_pc = 0;
volatile std::intptr_t* final_sp = nullptr;

int
main()
{
  dwt_counter_enable();
  enable_flash_accelerator();

  start_cycles = uptime();
  end_cycles = uptime();
  call_latency = end_cycles - start_cycles;

  my_stack.allocate_memory_and_push_sp_and_pc(2, 1001);
  // Create stack
  for (int i = 0; i < 96; i++) {
    my_stack.allocate_memory_and_push_sp_and_pc(2, i);
  }

  std::intptr_t pc = 0x0;
  std::intptr_t* sp = my_stack.sp();

  // Search Stack
  start_cycles = uptime();
  do {
    pc = *sp;
    sp = reinterpret_cast<std::intptr_t*>(*(sp - 1));
  } while (!(1000 <= pc && pc <= 2000));
  end_cycles = uptime();

  final_pc = pc;
  final_sp = sp;

  iterate_time = (end_cycles - start_cycles) - call_latency;

  // Create relative stack
  relative_stack.allocate_memory_and_push_sp_and_pc(4, 1001, 4);
  for (int i = 0; i < 10; i++) {
    relative_stack.allocate_memory_and_push_sp_and_pc(4, i, 4);
  }

  pc = 0x0;
  sp = relative_stack.sp();

  // Search Stack
  start_cycles = uptime();
  do {
    auto offsets = reinterpret_cast<std::intptr_t>(*(sp - 1));
    auto sp_diff = offsets & 0xFFFF;
    auto pc_diff = offsets >> 16;
    pc = *(sp - pc_diff);
    sp = sp - sp_diff;
  } while (!(1000 <= pc && pc <= 2000));
  end_cycles = uptime();

  final_pc = pc;
  final_sp = sp;

  relative_iterate_time = (end_cycles - start_cycles) - call_latency;

  while (true) {
    continue;
  }

  return side_effect;
}
