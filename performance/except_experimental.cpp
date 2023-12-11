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
#include <string_view>

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

std::uint32_t
uptime()
{
  return dwt->cyccnt;
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
  struct _reent* _impure_ptr = nullptr; // NOLINT
  int getpid()
  {
    return 1;
  }

  std::array<std::uint8_t, 1024> storage;
  std::span<std::uint8_t> storage_left(storage);
  void* __wrap___cxa_allocate_exception(unsigned int p_size) // NOLINT
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
  void __wrap___cxa_free_exception(void*) // NOLINT
  {
    storage_left = std::span<std::uint8_t>(storage);
  }
  void __wrap___cxa_call_unexpected(void*) // NOLINT
  {
    std::terminate();
  }
#define USE_KHALIL_EXCEPTIONS 1

#if USE_KHALIL_EXCEPTIONS == 1
  typedef struct __EIT_entry
  {
    std::uint32_t fnoffset;
    std::uint32_t content;
  } __EIT_entry;

  std::uint32_t selfrel_offset31(const std::uint32_t* p)
  {
    std::uint32_t offset;

    offset = *p;
    /* Sign extend to 32 bits.  */
    if (offset & (1 << 30))
      offset |= 1u << 31;
    else
      offset &= ~(1u << 31);

    return offset + (std::uint32_t)p;
  }

  extern std::uint32_t __trivial_handle_start;
  extern std::uint32_t __trivial_handle_end;
  extern std::uint32_t __text_start;
  extern std::uint32_t __text_end;

  [[gnu::always_inline]] inline bool is_trivial_function(
    std::uint32_t return_address)
  {
    // NOLINTNEXTLINE
    std::uint32_t* check = reinterpret_cast<std::uint32_t*>(return_address);
    return &__trivial_handle_start <= check && check <= &__trivial_handle_end;
  }

  struct eit_entry_less_than
  {
    [[gnu::always_inline]] static std::uint32_t to_prel31_offset(
      const __EIT_entry& entry,
      std::uint32_t address)
    {
      std::uint32_t entry_addr = reinterpret_cast<std::uint32_t>(&entry);
      std::uint32_t final_address = (address - entry_addr) & ~(1 << 31);
      return final_address;
    }

    bool operator()(const __EIT_entry& left, const __EIT_entry& right)
    {
      return left.fnoffset < right.fnoffset;
    }
    bool operator()(const __EIT_entry& left, std::uint32_t right)
    {
      std::uint32_t final_address = to_prel31_offset(left, right);
      return left.fnoffset < final_address;
    }
    bool operator()(std::uint32_t left, const __EIT_entry& right)
    {
      std::uint32_t final_address = to_prel31_offset(right, left);
      return final_address < right.fnoffset;
    }
  };

  // NOLINTNEXTLINE
  const __EIT_entry* search_EIT_table(const __EIT_entry* table,
                                      int nrec, // NOLINT
                                      std::uint32_t return_address)
  {
    if (nrec == 0) {
      return nullptr;
    }

    if (is_trivial_function(return_address)) {
      return &table[nrec - 2];
    }

#define SEARCH_ALGORITHM 2
#if SEARCH_ALGORITHM == 0
    int left = 0;
    int right = nrec - 1;
    while (true) {
      int n = (left + right) / 2;
      std::uint32_t next_fn = std::numeric_limits<std::uint32_t>::max();
      std::uint32_t this_fn = selfrel_offset31(&table[n].fnoffset);

      if (n != nrec - 1) {
        next_fn = selfrel_offset31(&table[n + 1].fnoffset) - 1;
      }

      if (return_address < this_fn) {
        if (n == left) {
          return nullptr;
        }
        right = n - 1;
      } else if (return_address <= next_fn) {
        return &table[n];
      } else {
        left = n + 1;
      }
    }
#elif SEARCH_ALGORITHM == 1
    int left = 0;
    int right = nrec - 1;

    while (true) {
      int n = (left + right) / 2;
      std::uint32_t next_fn = std::numeric_limits<std::uint32_t>::max();
      std::uint32_t this_fn = table[n].fnoffset;

      if (n != nrec - 1) {
        next_fn = table[n + 1].fnoffset - 1;
      }

      std::uint32_t prel31 =
        return_address - reinterpret_cast<std::uint32_t>(&table[n]);
      // clear MSB to conform to the prel31 fnoffset format
      prel31 = prel31 & ~(1 << 31);

      if (prel31 < this_fn) {
        if (n == left) {
          return nullptr;
        }
        right = n - 1;
      } else if (prel31 <= next_fn) {
        return &table[n];
      } else {
        left = n + 1;
      }
    }
#elif SEARCH_ALGORITHM == 2
    std::span<const __EIT_entry> table_span(table, nrec);
    const auto& entry = std::upper_bound(table_span.begin(),
                                         table_span.end(),
                                         return_address,
                                         eit_entry_less_than{});
    return &(*(entry - 1));
#endif
  }

/* Misc constants.  */
#define R_IP 12
#define R_SP 13
#define R_LR 14
#define R_PC 15

  struct core_regs
  {
    std::uint32_t r[16];
  };

  /* We use normal integer types here to avoid the compiler generating
     coprocessor instructions.  */
  struct vfp_regs
  {
    std::uint64_t d[16];
    std::uint32_t pad;
  };

  struct vfpv3_regs
  {
    /* Always populated via VSTM, so no need for the "pad" field from
       vfp_regs (which is used to store the format word for FSTMX).  */
    std::uint64_t d[16];
  };

  struct wmmxd_regs
  {
    std::uint64_t wd[16];
  };

  struct wmmxc_regs
  {
    std::uint32_t wc[4];
  };

  /* The ABI specifies that the unwind routines may only use core registers,
     except when actually manipulating coprocessor state.  This allows
     us to write one implementation that works on all platforms by
     demand-saving coprocessor registers.

     During unwinding we hold the coprocessor state in the actual hardware
     registers and allocate demand-save areas for use during phase1
     unwinding.  */

  struct phase1_vrs
  {
    /* The first fields must be the same as a phase2_vrs.  */
    std::uint32_t demand_save_flags;
    struct core_regs core;
    std::uint32_t prev_sp; /* Only valid during forced unwinding.  */
    struct vfp_regs vfp;
    struct vfpv3_regs vfp_regs_16_to_31;
    struct wmmxd_regs wmmxd;
    struct wmmxc_regs wmmxc;
  };

  /* This must match the structure created by the assembly wrappers.  */
  struct phase2_vrs
  {
    std::uint32_t demand_save_flags;
    struct core_regs core;
  };

  static volatile int vfp_show_up = 0;

  [[gnu::always_inline]] _Unwind_VRS_Result _Unwind_VRS_Pop(
    _Unwind_Context* context,
    _Unwind_VRS_RegClass regclass,
    _uw discriminator,
    _Unwind_VRS_DataRepresentation representation)
  {
    auto* vrs = reinterpret_cast<phase1_vrs*>(context);

    switch (regclass) {
      case _UVRSC_CORE: {
        std::uint32_t mask = discriminator & 0xffff;
        // The mask may not demand that the stack pointer be popped, but the
        // stack pointer will still need to be popped anyway, so this check
        // determines if the mask handles this or not.
        bool set_stack_pointer_afterwards = (mask & R_SP) == 0x0;

        std::uint32_t* ptr = // NOTLINTNEXTLINE
          reinterpret_cast<std::uint32_t*>(vrs->core.r[R_SP]);
        /* Pop the requested registers.  */
        while (mask) {
          auto reg_to_restore = std::countr_zero(mask);
          mask &= ~(1 << reg_to_restore);
          vrs->core.r[reg_to_restore] = *(ptr++);
        }
        if (set_stack_pointer_afterwards) {
          vrs->core.r[R_SP] = reinterpret_cast<std::uint32_t>(ptr);
        }
      }
        return _UVRSR_OK;
      case _UVRSC_VFP:
        return _UVRSR_OK;
      case _UVRSC_WMMXD:
        return _UVRSR_OK;
      case _UVRSC_WMMXC:
        return _UVRSR_OK;
      default:
        return _UVRSR_FAILED;
    }
  }

  /* Return the next byte of unwinding information, or CODE_FINISH if there is
     no data remaining.  */
  [[gnu::always_inline]] _uw8 next_unwind_byte(__gnu_unwind_state* uws)
  {
    _uw8 b;

    if (uws->bytes_left == 0) {
      /* Load another word */
      if (uws->words_left == 0)
        return 0xB0; /* Nothing left.  */
      uws->words_left--;
      uws->data = *(uws->next++);
      uws->bytes_left = 3;
    } else
      uws->bytes_left--;

    /* Extract the most significant byte.  */
    b = (uws->data >> 24) & 0xff;
    uws->data <<= 8;
    return b;
  }

  [[gnu::always_inline]] _Unwind_VRS_Result _My_Unwind_VRS_Get(
    _Unwind_Context* context,
    _Unwind_VRS_RegClass regclass,
    _uw regno,
    _Unwind_VRS_DataRepresentation representation,
    void* valuep)
  {
    auto* vrs = reinterpret_cast<phase1_vrs*>(context);
    *(_uw*)valuep = vrs->core.r[regno];
    return _UVRSR_OK;
  }

  /* ABI defined function to load a virtual register from memory.  */

  [[gnu::always_inline]] _Unwind_VRS_Result _My_Unwind_VRS_Set(
    _Unwind_Context* context,
    _Unwind_VRS_RegClass regclass,
    _uw regno,
    _Unwind_VRS_DataRepresentation representation,
    void* valuep)
  {
    auto* vrs = reinterpret_cast<phase1_vrs*>(context);
    vrs->core.r[regno] = *(_uw*)valuep;
    return _UVRSR_OK;
  }

  extern std::intptr_t __fit_sw_start;
  extern std::intptr_t __fit_sw_end;

  /* Execute the unwinding instructions described by UWS.  */
  _Unwind_Reason_Code __gnu_unwind_execute(_Unwind_Context* context,
                                           __gnu_unwind_state* uws)
  {
    _uw op;
    int set_pc;
    _uw reg;

    auto* vrs = reinterpret_cast<phase1_vrs*>(context);
    std::uint32_t pc = reinterpret_cast<std::uint32_t>(vrs->core.r[R_PC]);
    std::uint32_t* sp = reinterpret_cast<std::uint32_t*>(vrs->core.r[R_SP]);

    if (pc > reinterpret_cast<std::uint32_t>(&__fit_sw_start)) {
      do {
        pc = *sp;
        sp = reinterpret_cast<std::uint32_t*>(*(sp - 1));
      } while (pc > reinterpret_cast<std::uint32_t>(&__fit_sw_start));

      vrs->core.r[R_PC] = pc;
      vrs->core.r[R_SP] = reinterpret_cast<std::uint32_t>(sp);
      return _URC_OK;
    }

    set_pc = 0;
    for (;;) {
      op = next_unwind_byte(uws);
      if (op == 0xb0) {
        /* If we haven't already set pc then copy it from lr.  */
        if (!set_pc) {
          _My_Unwind_VRS_Get(context, _UVRSC_CORE, R_LR, _UVRSD_UINT32, &reg);
          _My_Unwind_VRS_Set(context, _UVRSC_CORE, R_PC, _UVRSD_UINT32, &reg);
          set_pc = 1;
        }
        /* Drop out of the loop.  */
        break;
      }
      if ((op & 0x80) == 0) {
        /* vsp = vsp +- (imm6 << 2 + 4).  */
        _uw offset;

        offset = ((op & 0x3f) << 2) + 4;
        _My_Unwind_VRS_Get(context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
        if (op & 0x40)
          reg -= offset;
        else
          reg += offset;
        _My_Unwind_VRS_Set(context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
        continue;
      }

      if ((op & 0xf0) == 0x80) {
        op = (op << 8) | next_unwind_byte(uws);
        if (op == 0x8000) {
          /* Refuse to unwind.  */
          return _URC_FAILURE;
        }
        /* Pop r4-r15 under mask.  */
        op = (op << 4) & 0xfff0;
        if (_Unwind_VRS_Pop(context, _UVRSC_CORE, op, _UVRSD_UINT32) !=
            _UVRSR_OK)
          return _URC_FAILURE;
        if (op & (1 << R_PC))
          set_pc = 1;
        continue;
      }
      if ((op & 0xf0) == 0x90) {
        op &= 0xf;
        if (op == 13 || op == 15)
          /* Reserved.  */
          return _URC_FAILURE;
        /* vsp = r[nnnn].  */
        _My_Unwind_VRS_Get(context, _UVRSC_CORE, op, _UVRSD_UINT32, &reg);
        _My_Unwind_VRS_Set(context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
        continue;
      }
      if ((op & 0xf0) == 0xa0) {
        /* Pop r4-r[4+nnn], [lr].  */
        _uw mask;

        mask = (0xff0 >> (7 - (op & 7))) & 0xff0;
        if (op & 8)
          mask |= (1 << R_LR);
        if (_Unwind_VRS_Pop(context, _UVRSC_CORE, mask, _UVRSD_UINT32) !=
            _UVRSR_OK)
          return _URC_FAILURE;
        continue;
      }
      if ((op & 0xf0) == 0xb0) {
        /* op == 0xb0 already handled.  */
        if (op == 0xb1) {
          op = next_unwind_byte(uws);
          if (op == 0 || ((op & 0xf0) != 0))
            /* Spare.  */
            return _URC_FAILURE;
          /* Pop r0-r4 under mask.  */
          if (_Unwind_VRS_Pop(context, _UVRSC_CORE, op, _UVRSD_UINT32) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        if (op == 0xb2) {
          /* vsp = vsp + 0x204 + (uleb128 << 2).  */
          int shift;

          _My_Unwind_VRS_Get(context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
          op = next_unwind_byte(uws);
          shift = 2;
          while (op & 0x80) {
            reg += ((op & 0x7f) << shift);
            shift += 7;
            op = next_unwind_byte(uws);
          }
          reg += ((op & 0x7f) << shift) + 0x204;
          _My_Unwind_VRS_Set(context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
          continue;
        }
        if (op == 0xb3) {
          /* Pop VFP registers with fldmx.  */
          op = next_unwind_byte(uws);
          op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
          if (_Unwind_VRS_Pop(context, _UVRSC_VFP, op, _UVRSD_VFPX) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        if ((op & 0xfc) == 0xb4) /* Obsolete FPA.  */
          return _URC_FAILURE;

        /* op & 0xf8 == 0xb8.  */
        /* Pop VFP D[8]-D[8+nnn] with fldmx.  */
        op = 0x80000 | ((op & 7) + 1);
        if (_Unwind_VRS_Pop(context, _UVRSC_VFP, op, _UVRSD_VFPX) != _UVRSR_OK)
          return _URC_FAILURE;
        continue;
      }
      if ((op & 0xf0) == 0xc0) {
        if (op == 0xc6) {
          /* Pop iWMMXt D registers.  */
          op = next_unwind_byte(uws);
          op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
          if (_Unwind_VRS_Pop(context, _UVRSC_WMMXD, op, _UVRSD_UINT64) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        if (op == 0xc7) {
          op = next_unwind_byte(uws);
          if (op == 0 || (op & 0xf0) != 0)
            /* Spare.  */
            return _URC_FAILURE;
          /* Pop iWMMXt wCGR{3,2,1,0} under mask.  */
          if (_Unwind_VRS_Pop(context, _UVRSC_WMMXC, op, _UVRSD_UINT32) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        if ((op & 0xf8) == 0xc0) {
          /* Pop iWMMXt wR[10]-wR[10+nnn].  */
          op = 0xa0000 | ((op & 0xf) + 1);
          if (_Unwind_VRS_Pop(context, _UVRSC_WMMXD, op, _UVRSD_UINT64) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        if (op == 0xc8) {
          /* Pop VFPv3 registers D[16+ssss]-D[16+ssss+cccc] with vldm.  */
          op = next_unwind_byte(uws);
          op = (((op & 0xf0) + 16) << 12) | ((op & 0xf) + 1);
          if (_Unwind_VRS_Pop(context, _UVRSC_VFP, op, _UVRSD_DOUBLE) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        if (op == 0xc9) {
          /* Pop VFP registers with fldmd.  */
          op = next_unwind_byte(uws);
          op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
          if (_Unwind_VRS_Pop(context, _UVRSC_VFP, op, _UVRSD_DOUBLE) !=
              _UVRSR_OK)
            return _URC_FAILURE;
          continue;
        }
        /* Spare.  */
        return _URC_FAILURE;
      }
      if ((op & 0xf8) == 0xd0) {
        /* Pop VFP D[8]-D[8+nnn] with fldmd.  */
        op = 0x80000 | ((op & 7) + 1);
        if (_Unwind_VRS_Pop(context, _UVRSC_VFP, op, _UVRSD_DOUBLE) !=
            _UVRSR_OK)
          return _URC_FAILURE;
        continue;
      }
      /* Spare.  */
      return _URC_FAILURE;
    }
    return _URC_OK;
  }
#endif
} // extern "C"

int
start();

int
main()
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

std::array<std::uint64_t, 25> cycle_map{};
std::array<std::uint64_t, 25> happy_cycle_map{};

int
funct_group0_0();
int
funct_group1_0();
int
funct_group2_0();
int
funct_group3_0();
int
funct_group4_0();
int
funct_group5_0();
int
funct_group6_0();
int
funct_group7_0();
int
funct_group8_0();
int
funct_group9_0();
int
funct_group10_0();
int
funct_group11_0();
int
funct_group12_0();
int
funct_group13_0();
int
funct_group14_0();
int
funct_group15_0();
int
funct_group16_0();
int
funct_group17_0();
int
funct_group18_0();
int
funct_group19_0();
int
funct_group20_0();
int
funct_group21_0();
int
funct_group22_0();
int
funct_group23_0();
int
funct_group24_0();

using signature = int(void);

std::array<signature*, 25> functions = {
  funct_group0_0,  funct_group1_0,  funct_group2_0,  funct_group3_0,
  funct_group4_0,  funct_group5_0,  funct_group6_0,  funct_group7_0,
  funct_group8_0,  funct_group9_0,  funct_group10_0, funct_group11_0,
  funct_group12_0, funct_group13_0, funct_group14_0, funct_group15_0,
  funct_group16_0, funct_group17_0, funct_group18_0, funct_group19_0,
  funct_group20_0, funct_group21_0, funct_group22_0, funct_group23_0,
  funct_group24_0
};

int
start()
{
  cycle_map.fill(0);
  happy_cycle_map.fill(std::numeric_limits<std::int32_t>::max());
  std::uint32_t index = 0;
  for (auto& funct : functions) {
    try {
      start_cycles = uptime();
      funct();
    } catch ([[maybe_unused]] const my_error_t& p_error) {
      end_cycles = uptime();
      cycle_map[index++] = end_cycles - start_cycles;
    }
  }
  index = 0;
  for (auto& funct : functions) {
    bool was_caught = false;
    try {
      // should prevent throw from executing
      side_effect = -1'000'000'000;
      start_cycles = uptime();
      funct();
    } catch ([[maybe_unused]] const my_error_t& p_error) {
      was_caught = true;
    }
    if (!was_caught) {
      end_cycles = uptime();
      happy_cycle_map[index++] = end_cycles - start_cycles;
    }
  }
  return side_effect;
}

class class_0
{
public:
  class_0(std::int32_t p_channel)
    : m_channel(p_channel)
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

  class_0(class_0&) = delete;
  class_0& operator=(class_0&) = delete;
  class_0(class_0&&) noexcept = default;
  class_0& operator=(class_0&&) noexcept = default;
  ~class_0() = default;
  void trigger()
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

private:
  std::int32_t m_channel = 0;
};

class class_1
{
public:
  class_1(std::int32_t p_channel)
    : m_channel(p_channel)
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

  class_1(class_1&) = delete;
  class_1& operator=(class_1&) = delete;
  class_1(class_1&&) noexcept = default;
  class_1& operator=(class_1&&) noexcept = default;
  ~class_1() { side_effect = side_effect & ~(1 << m_channel); }

  void trigger()
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

private:
  std::int32_t m_channel = 0;
};

int
funct_group0_1();

[[gnu::section(".fit_sw")]] int
funct_group0_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group0_1();
  return side_effect;
}

int
funct_group0_2();

[[gnu::section(".fit_sw")]] int
funct_group0_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group0_2();
  return side_effect;
}

int
funct_group0_3();

[[gnu::section(".fit_sw")]] int
funct_group0_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group0_3();
  return side_effect;
}

int
funct_group0_4();

[[gnu::section(".fit_sw")]] int
funct_group0_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group0_4();
  return side_effect;
}

int
funct_group0_5();

[[gnu::section(".fit_sw")]] int
funct_group0_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  volatile static float my_float = 0.0f;
  my_float = my_float + 5.5f;
  instance_0.trigger();
  side_effect = side_effect + funct_group0_5();
  return side_effect;
}

[[gnu::section(".fit_sw")]] int
funct_group0_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group1_1();

[[gnu::section(".trivial_handle")]] int
funct_group1_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_1();
  return side_effect;
}

int
funct_group1_2();

[[gnu::section(".trivial_handle")]] int
funct_group1_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_2();
  return side_effect;
}

int
funct_group1_3();

[[gnu::section(".trivial_handle")]] int
funct_group1_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_3();
  return side_effect;
}

int
funct_group1_4();

[[gnu::section(".trivial_handle")]] int
funct_group1_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_4();
  return side_effect;
}

int
funct_group1_5();

[[gnu::section(".trivial_handle")]] int
funct_group1_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_5();
  return side_effect;
}

int
funct_group1_6();

[[gnu::section(".trivial_handle")]] int
funct_group1_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_6();
  return side_effect;
}

int
funct_group1_7();

[[gnu::section(".trivial_handle")]] int
funct_group1_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_7();
  return side_effect;
}

int
funct_group1_8();

[[gnu::section(".trivial_handle")]] int
funct_group1_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_8();
  return side_effect;
}

int
funct_group1_9();

[[gnu::section(".trivial_handle")]] int
funct_group1_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_9();
  return side_effect;
}

int
funct_group1_10();

[[gnu::section(".trivial_handle")]] int
funct_group1_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_10();
  return side_effect;
}

int
funct_group1_11();

[[gnu::section(".trivial_handle")]] int
funct_group1_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group1_11();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group1_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group2_1();

[[gnu::section(".trivial_handle")]] int
funct_group2_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_1();
  return side_effect;
}

int
funct_group2_2();

[[gnu::section(".trivial_handle")]] int
funct_group2_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_2();
  return side_effect;
}

int
funct_group2_3();

[[gnu::section(".trivial_handle")]] int
funct_group2_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_3();
  return side_effect;
}

int
funct_group2_4();

[[gnu::section(".trivial_handle")]] int
funct_group2_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_4();
  return side_effect;
}

int
funct_group2_5();

[[gnu::section(".trivial_handle")]] int
funct_group2_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_5();
  return side_effect;
}

int
funct_group2_6();

[[gnu::section(".trivial_handle")]] int
funct_group2_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_6();
  return side_effect;
}

int
funct_group2_7();

[[gnu::section(".trivial_handle")]] int
funct_group2_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_7();
  return side_effect;
}

int
funct_group2_8();

[[gnu::section(".trivial_handle")]] int
funct_group2_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_8();
  return side_effect;
}

int
funct_group2_9();

[[gnu::section(".trivial_handle")]] int
funct_group2_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_9();
  return side_effect;
}

int
funct_group2_10();

[[gnu::section(".trivial_handle")]] int
funct_group2_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_10();
  return side_effect;
}

int
funct_group2_11();

[[gnu::section(".trivial_handle")]] int
funct_group2_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_11();
  return side_effect;
}

int
funct_group2_12();

[[gnu::section(".trivial_handle")]] int
funct_group2_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_12();
  return side_effect;
}

int
funct_group2_13();

[[gnu::section(".trivial_handle")]] int
funct_group2_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_13();
  return side_effect;
}

int
funct_group2_14();

[[gnu::section(".trivial_handle")]] int
funct_group2_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_14();
  return side_effect;
}

int
funct_group2_15();

[[gnu::section(".trivial_handle")]] int
funct_group2_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_15();
  return side_effect;
}

int
funct_group2_16();

[[gnu::section(".trivial_handle")]] int
funct_group2_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_16();
  return side_effect;
}

int
funct_group2_17();

[[gnu::section(".trivial_handle")]] int
funct_group2_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_17();
  return side_effect;
}

int
funct_group2_18();

[[gnu::section(".trivial_handle")]] int
funct_group2_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_18();
  return side_effect;
}

int
funct_group2_19();

[[gnu::section(".trivial_handle")]] int
funct_group2_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_19();
  return side_effect;
}

int
funct_group2_20();

[[gnu::section(".trivial_handle")]] int
funct_group2_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_20();
  return side_effect;
}

int
funct_group2_21();

[[gnu::section(".trivial_handle")]] int
funct_group2_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_21();
  return side_effect;
}

int
funct_group2_22();

[[gnu::section(".trivial_handle")]] int
funct_group2_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_22();
  return side_effect;
}

int
funct_group2_23();

[[gnu::section(".trivial_handle")]] int
funct_group2_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group2_23();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group2_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group3_1();

[[gnu::section(".trivial_handle")]] int
funct_group3_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_1();
  return side_effect;
}

int
funct_group3_2();

[[gnu::section(".trivial_handle")]] int
funct_group3_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_2();
  return side_effect;
}

int
funct_group3_3();

[[gnu::section(".trivial_handle")]] int
funct_group3_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_3();
  return side_effect;
}

int
funct_group3_4();

[[gnu::section(".trivial_handle")]] int
funct_group3_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_4();
  return side_effect;
}

int
funct_group3_5();

[[gnu::section(".trivial_handle")]] int
funct_group3_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_5();
  return side_effect;
}

int
funct_group3_6();

[[gnu::section(".trivial_handle")]] int
funct_group3_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_6();
  return side_effect;
}

int
funct_group3_7();

[[gnu::section(".trivial_handle")]] int
funct_group3_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_7();
  return side_effect;
}

int
funct_group3_8();

[[gnu::section(".trivial_handle")]] int
funct_group3_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_8();
  return side_effect;
}

int
funct_group3_9();

[[gnu::section(".trivial_handle")]] int
funct_group3_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_9();
  return side_effect;
}

int
funct_group3_10();

[[gnu::section(".trivial_handle")]] int
funct_group3_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_10();
  return side_effect;
}

int
funct_group3_11();

[[gnu::section(".trivial_handle")]] int
funct_group3_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_11();
  return side_effect;
}

int
funct_group3_12();

[[gnu::section(".trivial_handle")]] int
funct_group3_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_12();
  return side_effect;
}

int
funct_group3_13();

[[gnu::section(".trivial_handle")]] int
funct_group3_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_13();
  return side_effect;
}

int
funct_group3_14();

[[gnu::section(".trivial_handle")]] int
funct_group3_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_14();
  return side_effect;
}

int
funct_group3_15();

[[gnu::section(".trivial_handle")]] int
funct_group3_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_15();
  return side_effect;
}

int
funct_group3_16();

[[gnu::section(".trivial_handle")]] int
funct_group3_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_16();
  return side_effect;
}

int
funct_group3_17();

[[gnu::section(".trivial_handle")]] int
funct_group3_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_17();
  return side_effect;
}

int
funct_group3_18();

[[gnu::section(".trivial_handle")]] int
funct_group3_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_18();
  return side_effect;
}

int
funct_group3_19();

[[gnu::section(".trivial_handle")]] int
funct_group3_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_19();
  return side_effect;
}

int
funct_group3_20();

[[gnu::section(".trivial_handle")]] int
funct_group3_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_20();
  return side_effect;
}

int
funct_group3_21();

[[gnu::section(".trivial_handle")]] int
funct_group3_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_21();
  return side_effect;
}

int
funct_group3_22();

[[gnu::section(".trivial_handle")]] int
funct_group3_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_22();
  return side_effect;
}

int
funct_group3_23();

[[gnu::section(".trivial_handle")]] int
funct_group3_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_23();
  return side_effect;
}

int
funct_group3_24();

[[gnu::section(".trivial_handle")]] int
funct_group3_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_24();
  return side_effect;
}

int
funct_group3_25();

[[gnu::section(".trivial_handle")]] int
funct_group3_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_25();
  return side_effect;
}

int
funct_group3_26();

[[gnu::section(".trivial_handle")]] int
funct_group3_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_26();
  return side_effect;
}

int
funct_group3_27();

[[gnu::section(".trivial_handle")]] int
funct_group3_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_27();
  return side_effect;
}

int
funct_group3_28();

[[gnu::section(".trivial_handle")]] int
funct_group3_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_28();
  return side_effect;
}

int
funct_group3_29();

[[gnu::section(".trivial_handle")]] int
funct_group3_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_29();
  return side_effect;
}

int
funct_group3_30();

[[gnu::section(".trivial_handle")]] int
funct_group3_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_30();
  return side_effect;
}

int
funct_group3_31();

[[gnu::section(".trivial_handle")]] int
funct_group3_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_31();
  return side_effect;
}

int
funct_group3_32();

[[gnu::section(".trivial_handle")]] int
funct_group3_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_32();
  return side_effect;
}

int
funct_group3_33();

[[gnu::section(".trivial_handle")]] int
funct_group3_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_33();
  return side_effect;
}

int
funct_group3_34();

[[gnu::section(".trivial_handle")]] int
funct_group3_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_34();
  return side_effect;
}

int
funct_group3_35();

[[gnu::section(".trivial_handle")]] int
funct_group3_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_35();
  return side_effect;
}

int
funct_group3_36();

[[gnu::section(".trivial_handle")]] int
funct_group3_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_36();
  return side_effect;
}

int
funct_group3_37();

[[gnu::section(".trivial_handle")]] int
funct_group3_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_37();
  return side_effect;
}

int
funct_group3_38();

[[gnu::section(".trivial_handle")]] int
funct_group3_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_38();
  return side_effect;
}

int
funct_group3_39();

[[gnu::section(".trivial_handle")]] int
funct_group3_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_39();
  return side_effect;
}

int
funct_group3_40();

[[gnu::section(".trivial_handle")]] int
funct_group3_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_40();
  return side_effect;
}

int
funct_group3_41();

[[gnu::section(".trivial_handle")]] int
funct_group3_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_41();
  return side_effect;
}

int
funct_group3_42();

[[gnu::section(".trivial_handle")]] int
funct_group3_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_42();
  return side_effect;
}

int
funct_group3_43();

[[gnu::section(".trivial_handle")]] int
funct_group3_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_43();
  return side_effect;
}

int
funct_group3_44();

[[gnu::section(".trivial_handle")]] int
funct_group3_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_44();
  return side_effect;
}

int
funct_group3_45();

[[gnu::section(".trivial_handle")]] int
funct_group3_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_45();
  return side_effect;
}

int
funct_group3_46();

[[gnu::section(".trivial_handle")]] int
funct_group3_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_46();
  return side_effect;
}

int
funct_group3_47();

[[gnu::section(".trivial_handle")]] int
funct_group3_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group3_47();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group3_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group4_1();

[[gnu::section(".trivial_handle")]] int
funct_group4_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_1();
  return side_effect;
}

int
funct_group4_2();

[[gnu::section(".trivial_handle")]] int
funct_group4_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_2();
  return side_effect;
}

int
funct_group4_3();

[[gnu::section(".trivial_handle")]] int
funct_group4_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_3();
  return side_effect;
}

int
funct_group4_4();

[[gnu::section(".trivial_handle")]] int
funct_group4_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_4();
  return side_effect;
}

int
funct_group4_5();

[[gnu::section(".trivial_handle")]] int
funct_group4_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_5();
  return side_effect;
}

int
funct_group4_6();

[[gnu::section(".trivial_handle")]] int
funct_group4_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_6();
  return side_effect;
}

int
funct_group4_7();

[[gnu::section(".trivial_handle")]] int
funct_group4_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_7();
  return side_effect;
}

int
funct_group4_8();

[[gnu::section(".trivial_handle")]] int
funct_group4_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_8();
  return side_effect;
}

int
funct_group4_9();

[[gnu::section(".trivial_handle")]] int
funct_group4_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_9();
  return side_effect;
}

int
funct_group4_10();

[[gnu::section(".trivial_handle")]] int
funct_group4_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_10();
  return side_effect;
}

int
funct_group4_11();

[[gnu::section(".trivial_handle")]] int
funct_group4_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_11();
  return side_effect;
}

int
funct_group4_12();

[[gnu::section(".trivial_handle")]] int
funct_group4_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_12();
  return side_effect;
}

int
funct_group4_13();

[[gnu::section(".trivial_handle")]] int
funct_group4_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_13();
  return side_effect;
}

int
funct_group4_14();

[[gnu::section(".trivial_handle")]] int
funct_group4_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_14();
  return side_effect;
}

int
funct_group4_15();

[[gnu::section(".trivial_handle")]] int
funct_group4_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_15();
  return side_effect;
}

int
funct_group4_16();

[[gnu::section(".trivial_handle")]] int
funct_group4_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_16();
  return side_effect;
}

int
funct_group4_17();

[[gnu::section(".trivial_handle")]] int
funct_group4_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_17();
  return side_effect;
}

int
funct_group4_18();

[[gnu::section(".trivial_handle")]] int
funct_group4_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_18();
  return side_effect;
}

int
funct_group4_19();

[[gnu::section(".trivial_handle")]] int
funct_group4_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_19();
  return side_effect;
}

int
funct_group4_20();

[[gnu::section(".trivial_handle")]] int
funct_group4_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_20();
  return side_effect;
}

int
funct_group4_21();

[[gnu::section(".trivial_handle")]] int
funct_group4_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_21();
  return side_effect;
}

int
funct_group4_22();

[[gnu::section(".trivial_handle")]] int
funct_group4_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_22();
  return side_effect;
}

int
funct_group4_23();

[[gnu::section(".trivial_handle")]] int
funct_group4_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_23();
  return side_effect;
}

int
funct_group4_24();

[[gnu::section(".trivial_handle")]] int
funct_group4_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_24();
  return side_effect;
}

int
funct_group4_25();

[[gnu::section(".trivial_handle")]] int
funct_group4_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_25();
  return side_effect;
}

int
funct_group4_26();

[[gnu::section(".trivial_handle")]] int
funct_group4_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_26();
  return side_effect;
}

int
funct_group4_27();

[[gnu::section(".trivial_handle")]] int
funct_group4_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_27();
  return side_effect;
}

int
funct_group4_28();

[[gnu::section(".trivial_handle")]] int
funct_group4_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_28();
  return side_effect;
}

int
funct_group4_29();

[[gnu::section(".trivial_handle")]] int
funct_group4_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_29();
  return side_effect;
}

int
funct_group4_30();

[[gnu::section(".trivial_handle")]] int
funct_group4_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_30();
  return side_effect;
}

int
funct_group4_31();

[[gnu::section(".trivial_handle")]] int
funct_group4_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_31();
  return side_effect;
}

int
funct_group4_32();

[[gnu::section(".trivial_handle")]] int
funct_group4_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_32();
  return side_effect;
}

int
funct_group4_33();

[[gnu::section(".trivial_handle")]] int
funct_group4_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_33();
  return side_effect;
}

int
funct_group4_34();

[[gnu::section(".trivial_handle")]] int
funct_group4_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_34();
  return side_effect;
}

int
funct_group4_35();

[[gnu::section(".trivial_handle")]] int
funct_group4_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_35();
  return side_effect;
}

int
funct_group4_36();

[[gnu::section(".trivial_handle")]] int
funct_group4_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_36();
  return side_effect;
}

int
funct_group4_37();

[[gnu::section(".trivial_handle")]] int
funct_group4_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_37();
  return side_effect;
}

int
funct_group4_38();

[[gnu::section(".trivial_handle")]] int
funct_group4_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_38();
  return side_effect;
}

int
funct_group4_39();

[[gnu::section(".trivial_handle")]] int
funct_group4_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_39();
  return side_effect;
}

int
funct_group4_40();

[[gnu::section(".trivial_handle")]] int
funct_group4_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_40();
  return side_effect;
}

int
funct_group4_41();

[[gnu::section(".trivial_handle")]] int
funct_group4_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_41();
  return side_effect;
}

int
funct_group4_42();

[[gnu::section(".trivial_handle")]] int
funct_group4_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_42();
  return side_effect;
}

int
funct_group4_43();

[[gnu::section(".trivial_handle")]] int
funct_group4_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_43();
  return side_effect;
}

int
funct_group4_44();

[[gnu::section(".trivial_handle")]] int
funct_group4_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_44();
  return side_effect;
}

int
funct_group4_45();

[[gnu::section(".trivial_handle")]] int
funct_group4_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_45();
  return side_effect;
}

int
funct_group4_46();

[[gnu::section(".trivial_handle")]] int
funct_group4_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_46();
  return side_effect;
}

int
funct_group4_47();

[[gnu::section(".trivial_handle")]] int
funct_group4_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_47();
  return side_effect;
}

int
funct_group4_48();

[[gnu::section(".trivial_handle")]] int
funct_group4_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_48();
  return side_effect;
}

int
funct_group4_49();

[[gnu::section(".trivial_handle")]] int
funct_group4_48()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_49();
  return side_effect;
}

int
funct_group4_50();

[[gnu::section(".trivial_handle")]] int
funct_group4_49()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_50();
  return side_effect;
}

int
funct_group4_51();

[[gnu::section(".trivial_handle")]] int
funct_group4_50()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_51();
  return side_effect;
}

int
funct_group4_52();

[[gnu::section(".trivial_handle")]] int
funct_group4_51()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_52();
  return side_effect;
}

int
funct_group4_53();

[[gnu::section(".trivial_handle")]] int
funct_group4_52()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_53();
  return side_effect;
}

int
funct_group4_54();

[[gnu::section(".trivial_handle")]] int
funct_group4_53()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_54();
  return side_effect;
}

int
funct_group4_55();

[[gnu::section(".trivial_handle")]] int
funct_group4_54()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_55();
  return side_effect;
}

int
funct_group4_56();

[[gnu::section(".trivial_handle")]] int
funct_group4_55()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_56();
  return side_effect;
}

int
funct_group4_57();

[[gnu::section(".trivial_handle")]] int
funct_group4_56()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_57();
  return side_effect;
}

int
funct_group4_58();

[[gnu::section(".trivial_handle")]] int
funct_group4_57()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_58();
  return side_effect;
}

int
funct_group4_59();

[[gnu::section(".trivial_handle")]] int
funct_group4_58()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_59();
  return side_effect;
}

int
funct_group4_60();

[[gnu::section(".trivial_handle")]] int
funct_group4_59()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_60();
  return side_effect;
}

int
funct_group4_61();

[[gnu::section(".trivial_handle")]] int
funct_group4_60()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_61();
  return side_effect;
}

int
funct_group4_62();

[[gnu::section(".trivial_handle")]] int
funct_group4_61()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_62();
  return side_effect;
}

int
funct_group4_63();

[[gnu::section(".trivial_handle")]] int
funct_group4_62()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_63();
  return side_effect;
}

int
funct_group4_64();

[[gnu::section(".trivial_handle")]] int
funct_group4_63()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_64();
  return side_effect;
}

int
funct_group4_65();

[[gnu::section(".trivial_handle")]] int
funct_group4_64()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_65();
  return side_effect;
}

int
funct_group4_66();

[[gnu::section(".trivial_handle")]] int
funct_group4_65()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_66();
  return side_effect;
}

int
funct_group4_67();

[[gnu::section(".trivial_handle")]] int
funct_group4_66()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_67();
  return side_effect;
}

int
funct_group4_68();

[[gnu::section(".trivial_handle")]] int
funct_group4_67()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_68();
  return side_effect;
}

int
funct_group4_69();

[[gnu::section(".trivial_handle")]] int
funct_group4_68()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_69();
  return side_effect;
}

int
funct_group4_70();

[[gnu::section(".trivial_handle")]] int
funct_group4_69()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_70();
  return side_effect;
}

int
funct_group4_71();

[[gnu::section(".trivial_handle")]] int
funct_group4_70()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_71();
  return side_effect;
}

int
funct_group4_72();

[[gnu::section(".trivial_handle")]] int
funct_group4_71()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_72();
  return side_effect;
}

int
funct_group4_73();

[[gnu::section(".trivial_handle")]] int
funct_group4_72()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_73();
  return side_effect;
}

int
funct_group4_74();

[[gnu::section(".trivial_handle")]] int
funct_group4_73()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_74();
  return side_effect;
}

int
funct_group4_75();

[[gnu::section(".trivial_handle")]] int
funct_group4_74()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_75();
  return side_effect;
}

int
funct_group4_76();

[[gnu::section(".trivial_handle")]] int
funct_group4_75()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_76();
  return side_effect;
}

int
funct_group4_77();

[[gnu::section(".trivial_handle")]] int
funct_group4_76()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_77();
  return side_effect;
}

int
funct_group4_78();

[[gnu::section(".trivial_handle")]] int
funct_group4_77()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_78();
  return side_effect;
}

int
funct_group4_79();

[[gnu::section(".trivial_handle")]] int
funct_group4_78()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_79();
  return side_effect;
}

int
funct_group4_80();

[[gnu::section(".trivial_handle")]] int
funct_group4_79()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_80();
  return side_effect;
}

int
funct_group4_81();

[[gnu::section(".trivial_handle")]] int
funct_group4_80()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_81();
  return side_effect;
}

int
funct_group4_82();

[[gnu::section(".trivial_handle")]] int
funct_group4_81()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_82();
  return side_effect;
}

int
funct_group4_83();

[[gnu::section(".trivial_handle")]] int
funct_group4_82()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_83();
  return side_effect;
}

int
funct_group4_84();

[[gnu::section(".trivial_handle")]] int
funct_group4_83()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_84();
  return side_effect;
}

int
funct_group4_85();

[[gnu::section(".trivial_handle")]] int
funct_group4_84()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_85();
  return side_effect;
}

int
funct_group4_86();

[[gnu::section(".trivial_handle")]] int
funct_group4_85()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_86();
  return side_effect;
}

int
funct_group4_87();

[[gnu::section(".trivial_handle")]] int
funct_group4_86()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_87();
  return side_effect;
}

int
funct_group4_88();

[[gnu::section(".trivial_handle")]] int
funct_group4_87()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_88();
  return side_effect;
}

int
funct_group4_89();

[[gnu::section(".trivial_handle")]] int
funct_group4_88()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_89();
  return side_effect;
}

int
funct_group4_90();

[[gnu::section(".trivial_handle")]] int
funct_group4_89()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_90();
  return side_effect;
}

int
funct_group4_91();

[[gnu::section(".trivial_handle")]] int
funct_group4_90()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_91();
  return side_effect;
}

int
funct_group4_92();

[[gnu::section(".trivial_handle")]] int
funct_group4_91()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_92();
  return side_effect;
}

int
funct_group4_93();

[[gnu::section(".trivial_handle")]] int
funct_group4_92()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_93();
  return side_effect;
}

int
funct_group4_94();

[[gnu::section(".trivial_handle")]] int
funct_group4_93()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_94();
  return side_effect;
}

int
funct_group4_95();

[[gnu::section(".trivial_handle")]] int
funct_group4_94()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group4_95();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group4_95()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group5_1();

[[gnu::section(".trivial_handle")]] int
funct_group5_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group5_1();
  return side_effect;
}

int
funct_group5_2();

[[gnu::section(".trivial_handle")]] int
funct_group5_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group5_2();
  return side_effect;
}

int
funct_group5_3();

[[gnu::section(".trivial_handle")]] int
funct_group5_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group5_3();
  return side_effect;
}

int
funct_group5_4();

[[gnu::section(".trivial_handle")]] int
funct_group5_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group5_4();
  return side_effect;
}

int
funct_group5_5();

[[gnu::section(".trivial_handle")]] int
funct_group5_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group5_5();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group5_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group6_1();

[[gnu::section(".trivial_handle")]] int
funct_group6_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_1();
  return side_effect;
}

int
funct_group6_2();

[[gnu::section(".trivial_handle")]] int
funct_group6_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_2();
  return side_effect;
}

int
funct_group6_3();

[[gnu::section(".trivial_handle")]] int
funct_group6_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_3();
  return side_effect;
}

int
funct_group6_4();

[[gnu::section(".trivial_handle")]] int
funct_group6_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_4();
  return side_effect;
}

int
funct_group6_5();

[[gnu::section(".trivial_handle")]] int
funct_group6_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_5();
  return side_effect;
}

int
funct_group6_6();

[[gnu::section(".trivial_handle")]] int
funct_group6_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_6();
  return side_effect;
}

int
funct_group6_7();

[[gnu::section(".trivial_handle")]] int
funct_group6_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_7();
  return side_effect;
}

int
funct_group6_8();

[[gnu::section(".trivial_handle")]] int
funct_group6_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_8();
  return side_effect;
}

int
funct_group6_9();

[[gnu::section(".trivial_handle")]] int
funct_group6_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_9();
  return side_effect;
}

int
funct_group6_10();

int
funct_group6_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_10();
  return side_effect;
}

int
funct_group6_11();

[[gnu::section(".trivial_handle")]] int
funct_group6_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group6_11();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group6_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group7_1();

[[gnu::section(".trivial_handle")]] int
funct_group7_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_1();
  return side_effect;
}

int
funct_group7_2();

[[gnu::section(".trivial_handle")]] int
funct_group7_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_2();
  return side_effect;
}

int
funct_group7_3();

[[gnu::section(".trivial_handle")]] int
funct_group7_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_3();
  return side_effect;
}

int
funct_group7_4();

[[gnu::section(".trivial_handle")]] int
funct_group7_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_4();
  return side_effect;
}

int
funct_group7_5();

[[gnu::section(".trivial_handle")]] int
funct_group7_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_5();
  return side_effect;
}

int
funct_group7_6();

[[gnu::section(".trivial_handle")]] int
funct_group7_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_6();
  return side_effect;
}

int
funct_group7_7();

[[gnu::section(".trivial_handle")]] int
funct_group7_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_7();
  return side_effect;
}

int
funct_group7_8();

[[gnu::section(".trivial_handle")]] int
funct_group7_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_8();
  return side_effect;
}

int
funct_group7_9();

[[gnu::section(".trivial_handle")]] int
funct_group7_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_9();
  return side_effect;
}

int
funct_group7_10();

int
funct_group7_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_10();
  return side_effect;
}

int
funct_group7_11();

[[gnu::section(".trivial_handle")]] int
funct_group7_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_11();
  return side_effect;
}

int
funct_group7_12();

[[gnu::section(".trivial_handle")]] int
funct_group7_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_12();
  return side_effect;
}

int
funct_group7_13();

[[gnu::section(".trivial_handle")]] int
funct_group7_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_13();
  return side_effect;
}

int
funct_group7_14();

[[gnu::section(".trivial_handle")]] int
funct_group7_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_14();
  return side_effect;
}

int
funct_group7_15();

[[gnu::section(".trivial_handle")]] int
funct_group7_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_15();
  return side_effect;
}

int
funct_group7_16();

[[gnu::section(".trivial_handle")]] int
funct_group7_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_16();
  return side_effect;
}

int
funct_group7_17();

[[gnu::section(".trivial_handle")]] int
funct_group7_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_17();
  return side_effect;
}

int
funct_group7_18();

[[gnu::section(".trivial_handle")]] int
funct_group7_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_18();
  return side_effect;
}

int
funct_group7_19();

[[gnu::section(".trivial_handle")]] int
funct_group7_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_19();
  return side_effect;
}

int
funct_group7_20();

int
funct_group7_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_20();
  return side_effect;
}

int
funct_group7_21();

[[gnu::section(".trivial_handle")]] int
funct_group7_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_21();
  return side_effect;
}

int
funct_group7_22();

[[gnu::section(".trivial_handle")]] int
funct_group7_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_22();
  return side_effect;
}

int
funct_group7_23();

[[gnu::section(".trivial_handle")]] int
funct_group7_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group7_23();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group7_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group8_1();

[[gnu::section(".trivial_handle")]] int
funct_group8_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_1();
  return side_effect;
}

int
funct_group8_2();

[[gnu::section(".trivial_handle")]] int
funct_group8_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_2();
  return side_effect;
}

int
funct_group8_3();

[[gnu::section(".trivial_handle")]] int
funct_group8_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_3();
  return side_effect;
}

int
funct_group8_4();

[[gnu::section(".trivial_handle")]] int
funct_group8_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_4();
  return side_effect;
}

int
funct_group8_5();

[[gnu::section(".trivial_handle")]] int
funct_group8_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_5();
  return side_effect;
}

int
funct_group8_6();

[[gnu::section(".trivial_handle")]] int
funct_group8_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_6();
  return side_effect;
}

int
funct_group8_7();

[[gnu::section(".trivial_handle")]] int
funct_group8_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_7();
  return side_effect;
}

int
funct_group8_8();

[[gnu::section(".trivial_handle")]] int
funct_group8_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_8();
  return side_effect;
}

int
funct_group8_9();

[[gnu::section(".trivial_handle")]] int
funct_group8_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_9();
  return side_effect;
}

int
funct_group8_10();

int
funct_group8_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_10();
  return side_effect;
}

int
funct_group8_11();

[[gnu::section(".trivial_handle")]] int
funct_group8_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_11();
  return side_effect;
}

int
funct_group8_12();

[[gnu::section(".trivial_handle")]] int
funct_group8_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_12();
  return side_effect;
}

int
funct_group8_13();

[[gnu::section(".trivial_handle")]] int
funct_group8_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_13();
  return side_effect;
}

int
funct_group8_14();

[[gnu::section(".trivial_handle")]] int
funct_group8_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_14();
  return side_effect;
}

int
funct_group8_15();

[[gnu::section(".trivial_handle")]] int
funct_group8_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_15();
  return side_effect;
}

int
funct_group8_16();

[[gnu::section(".trivial_handle")]] int
funct_group8_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_16();
  return side_effect;
}

int
funct_group8_17();

[[gnu::section(".trivial_handle")]] int
funct_group8_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_17();
  return side_effect;
}

int
funct_group8_18();

[[gnu::section(".trivial_handle")]] int
funct_group8_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_18();
  return side_effect;
}

int
funct_group8_19();

[[gnu::section(".trivial_handle")]] int
funct_group8_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_19();
  return side_effect;
}

int
funct_group8_20();

int
funct_group8_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_20();
  return side_effect;
}

int
funct_group8_21();

[[gnu::section(".trivial_handle")]] int
funct_group8_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_21();
  return side_effect;
}

int
funct_group8_22();

[[gnu::section(".trivial_handle")]] int
funct_group8_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_22();
  return side_effect;
}

int
funct_group8_23();

[[gnu::section(".trivial_handle")]] int
funct_group8_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_23();
  return side_effect;
}

int
funct_group8_24();

[[gnu::section(".trivial_handle")]] int
funct_group8_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_24();
  return side_effect;
}

int
funct_group8_25();

[[gnu::section(".trivial_handle")]] int
funct_group8_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_25();
  return side_effect;
}

int
funct_group8_26();

[[gnu::section(".trivial_handle")]] int
funct_group8_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_26();
  return side_effect;
}

int
funct_group8_27();

[[gnu::section(".trivial_handle")]] int
funct_group8_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_27();
  return side_effect;
}

int
funct_group8_28();

[[gnu::section(".trivial_handle")]] int
funct_group8_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_28();
  return side_effect;
}

int
funct_group8_29();

[[gnu::section(".trivial_handle")]] int
funct_group8_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_29();
  return side_effect;
}

int
funct_group8_30();

int
funct_group8_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_30();
  return side_effect;
}

int
funct_group8_31();

[[gnu::section(".trivial_handle")]] int
funct_group8_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_31();
  return side_effect;
}

int
funct_group8_32();

[[gnu::section(".trivial_handle")]] int
funct_group8_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_32();
  return side_effect;
}

int
funct_group8_33();

[[gnu::section(".trivial_handle")]] int
funct_group8_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_33();
  return side_effect;
}

int
funct_group8_34();

[[gnu::section(".trivial_handle")]] int
funct_group8_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_34();
  return side_effect;
}

int
funct_group8_35();

[[gnu::section(".trivial_handle")]] int
funct_group8_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_35();
  return side_effect;
}

int
funct_group8_36();

[[gnu::section(".trivial_handle")]] int
funct_group8_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_36();
  return side_effect;
}

int
funct_group8_37();

[[gnu::section(".trivial_handle")]] int
funct_group8_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_37();
  return side_effect;
}

int
funct_group8_38();

[[gnu::section(".trivial_handle")]] int
funct_group8_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_38();
  return side_effect;
}

int
funct_group8_39();

[[gnu::section(".trivial_handle")]] int
funct_group8_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_39();
  return side_effect;
}

int
funct_group8_40();

int
funct_group8_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_40();
  return side_effect;
}

int
funct_group8_41();

[[gnu::section(".trivial_handle")]] int
funct_group8_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_41();
  return side_effect;
}

int
funct_group8_42();

[[gnu::section(".trivial_handle")]] int
funct_group8_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_42();
  return side_effect;
}

int
funct_group8_43();

[[gnu::section(".trivial_handle")]] int
funct_group8_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_43();
  return side_effect;
}

int
funct_group8_44();

[[gnu::section(".trivial_handle")]] int
funct_group8_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_44();
  return side_effect;
}

int
funct_group8_45();

[[gnu::section(".trivial_handle")]] int
funct_group8_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_45();
  return side_effect;
}

int
funct_group8_46();

[[gnu::section(".trivial_handle")]] int
funct_group8_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_46();
  return side_effect;
}

int
funct_group8_47();

[[gnu::section(".trivial_handle")]] int
funct_group8_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group8_47();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group8_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group9_1();

[[gnu::section(".trivial_handle")]] int
funct_group9_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_1();
  return side_effect;
}

int
funct_group9_2();

[[gnu::section(".trivial_handle")]] int
funct_group9_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_2();
  return side_effect;
}

int
funct_group9_3();

[[gnu::section(".trivial_handle")]] int
funct_group9_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_3();
  return side_effect;
}

int
funct_group9_4();

[[gnu::section(".trivial_handle")]] int
funct_group9_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_4();
  return side_effect;
}

int
funct_group9_5();

[[gnu::section(".trivial_handle")]] int
funct_group9_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_5();
  return side_effect;
}

int
funct_group9_6();

[[gnu::section(".trivial_handle")]] int
funct_group9_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_6();
  return side_effect;
}

int
funct_group9_7();

[[gnu::section(".trivial_handle")]] int
funct_group9_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_7();
  return side_effect;
}

int
funct_group9_8();

[[gnu::section(".trivial_handle")]] int
funct_group9_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_8();
  return side_effect;
}

int
funct_group9_9();

[[gnu::section(".trivial_handle")]] int
funct_group9_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_9();
  return side_effect;
}

int
funct_group9_10();

int
funct_group9_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_10();
  return side_effect;
}

int
funct_group9_11();

[[gnu::section(".trivial_handle")]] int
funct_group9_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_11();
  return side_effect;
}

int
funct_group9_12();

[[gnu::section(".trivial_handle")]] int
funct_group9_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_12();
  return side_effect;
}

int
funct_group9_13();

[[gnu::section(".trivial_handle")]] int
funct_group9_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_13();
  return side_effect;
}

int
funct_group9_14();

[[gnu::section(".trivial_handle")]] int
funct_group9_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_14();
  return side_effect;
}

int
funct_group9_15();

[[gnu::section(".trivial_handle")]] int
funct_group9_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_15();
  return side_effect;
}

int
funct_group9_16();

[[gnu::section(".trivial_handle")]] int
funct_group9_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_16();
  return side_effect;
}

int
funct_group9_17();

[[gnu::section(".trivial_handle")]] int
funct_group9_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_17();
  return side_effect;
}

int
funct_group9_18();

[[gnu::section(".trivial_handle")]] int
funct_group9_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_18();
  return side_effect;
}

int
funct_group9_19();

[[gnu::section(".trivial_handle")]] int
funct_group9_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_19();
  return side_effect;
}

int
funct_group9_20();

int
funct_group9_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_20();
  return side_effect;
}

int
funct_group9_21();

[[gnu::section(".trivial_handle")]] int
funct_group9_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_21();
  return side_effect;
}

int
funct_group9_22();

[[gnu::section(".trivial_handle")]] int
funct_group9_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_22();
  return side_effect;
}

int
funct_group9_23();

[[gnu::section(".trivial_handle")]] int
funct_group9_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_23();
  return side_effect;
}

int
funct_group9_24();

[[gnu::section(".trivial_handle")]] int
funct_group9_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_24();
  return side_effect;
}

int
funct_group9_25();

[[gnu::section(".trivial_handle")]] int
funct_group9_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_25();
  return side_effect;
}

int
funct_group9_26();

[[gnu::section(".trivial_handle")]] int
funct_group9_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_26();
  return side_effect;
}

int
funct_group9_27();

[[gnu::section(".trivial_handle")]] int
funct_group9_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_27();
  return side_effect;
}

int
funct_group9_28();

[[gnu::section(".trivial_handle")]] int
funct_group9_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_28();
  return side_effect;
}

int
funct_group9_29();

[[gnu::section(".trivial_handle")]] int
funct_group9_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_29();
  return side_effect;
}

int
funct_group9_30();

int
funct_group9_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_30();
  return side_effect;
}

int
funct_group9_31();

[[gnu::section(".trivial_handle")]] int
funct_group9_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_31();
  return side_effect;
}

int
funct_group9_32();

[[gnu::section(".trivial_handle")]] int
funct_group9_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_32();
  return side_effect;
}

int
funct_group9_33();

[[gnu::section(".trivial_handle")]] int
funct_group9_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_33();
  return side_effect;
}

int
funct_group9_34();

[[gnu::section(".trivial_handle")]] int
funct_group9_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_34();
  return side_effect;
}

int
funct_group9_35();

[[gnu::section(".trivial_handle")]] int
funct_group9_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_35();
  return side_effect;
}

int
funct_group9_36();

[[gnu::section(".trivial_handle")]] int
funct_group9_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_36();
  return side_effect;
}

int
funct_group9_37();

[[gnu::section(".trivial_handle")]] int
funct_group9_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_37();
  return side_effect;
}

int
funct_group9_38();

[[gnu::section(".trivial_handle")]] int
funct_group9_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_38();
  return side_effect;
}

int
funct_group9_39();

[[gnu::section(".trivial_handle")]] int
funct_group9_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_39();
  return side_effect;
}

int
funct_group9_40();

int
funct_group9_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_40();
  return side_effect;
}

int
funct_group9_41();

[[gnu::section(".trivial_handle")]] int
funct_group9_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_41();
  return side_effect;
}

int
funct_group9_42();

[[gnu::section(".trivial_handle")]] int
funct_group9_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_42();
  return side_effect;
}

int
funct_group9_43();

[[gnu::section(".trivial_handle")]] int
funct_group9_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_43();
  return side_effect;
}

int
funct_group9_44();

[[gnu::section(".trivial_handle")]] int
funct_group9_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_44();
  return side_effect;
}

int
funct_group9_45();

[[gnu::section(".trivial_handle")]] int
funct_group9_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_45();
  return side_effect;
}

int
funct_group9_46();

[[gnu::section(".trivial_handle")]] int
funct_group9_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_46();
  return side_effect;
}

int
funct_group9_47();

[[gnu::section(".trivial_handle")]] int
funct_group9_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_47();
  return side_effect;
}

int
funct_group9_48();

[[gnu::section(".trivial_handle")]] int
funct_group9_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_48();
  return side_effect;
}

int
funct_group9_49();

[[gnu::section(".trivial_handle")]] int
funct_group9_48()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_49();
  return side_effect;
}

int
funct_group9_50();

int
funct_group9_49()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_50();
  return side_effect;
}

int
funct_group9_51();

[[gnu::section(".trivial_handle")]] int
funct_group9_50()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_51();
  return side_effect;
}

int
funct_group9_52();

[[gnu::section(".trivial_handle")]] int
funct_group9_51()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_52();
  return side_effect;
}

int
funct_group9_53();

[[gnu::section(".trivial_handle")]] int
funct_group9_52()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_53();
  return side_effect;
}

int
funct_group9_54();

[[gnu::section(".trivial_handle")]] int
funct_group9_53()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_54();
  return side_effect;
}

int
funct_group9_55();

[[gnu::section(".trivial_handle")]] int
funct_group9_54()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_55();
  return side_effect;
}

int
funct_group9_56();

[[gnu::section(".trivial_handle")]] int
funct_group9_55()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_56();
  return side_effect;
}

int
funct_group9_57();

[[gnu::section(".trivial_handle")]] int
funct_group9_56()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_57();
  return side_effect;
}

int
funct_group9_58();

[[gnu::section(".trivial_handle")]] int
funct_group9_57()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_58();
  return side_effect;
}

int
funct_group9_59();

[[gnu::section(".trivial_handle")]] int
funct_group9_58()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_59();
  return side_effect;
}

int
funct_group9_60();

int
funct_group9_59()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_60();
  return side_effect;
}

int
funct_group9_61();

[[gnu::section(".trivial_handle")]] int
funct_group9_60()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_61();
  return side_effect;
}

int
funct_group9_62();

[[gnu::section(".trivial_handle")]] int
funct_group9_61()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_62();
  return side_effect;
}

int
funct_group9_63();

[[gnu::section(".trivial_handle")]] int
funct_group9_62()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_63();
  return side_effect;
}

int
funct_group9_64();

[[gnu::section(".trivial_handle")]] int
funct_group9_63()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_64();
  return side_effect;
}

int
funct_group9_65();

[[gnu::section(".trivial_handle")]] int
funct_group9_64()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_65();
  return side_effect;
}

int
funct_group9_66();

[[gnu::section(".trivial_handle")]] int
funct_group9_65()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_66();
  return side_effect;
}

int
funct_group9_67();

[[gnu::section(".trivial_handle")]] int
funct_group9_66()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_67();
  return side_effect;
}

int
funct_group9_68();

[[gnu::section(".trivial_handle")]] int
funct_group9_67()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_68();
  return side_effect;
}

int
funct_group9_69();

[[gnu::section(".trivial_handle")]] int
funct_group9_68()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_69();
  return side_effect;
}

int
funct_group9_70();

int
funct_group9_69()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_70();
  return side_effect;
}

int
funct_group9_71();

[[gnu::section(".trivial_handle")]] int
funct_group9_70()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_71();
  return side_effect;
}

int
funct_group9_72();

[[gnu::section(".trivial_handle")]] int
funct_group9_71()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_72();
  return side_effect;
}

int
funct_group9_73();

[[gnu::section(".trivial_handle")]] int
funct_group9_72()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_73();
  return side_effect;
}

int
funct_group9_74();

[[gnu::section(".trivial_handle")]] int
funct_group9_73()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_74();
  return side_effect;
}

int
funct_group9_75();

[[gnu::section(".trivial_handle")]] int
funct_group9_74()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_75();
  return side_effect;
}

int
funct_group9_76();

[[gnu::section(".trivial_handle")]] int
funct_group9_75()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_76();
  return side_effect;
}

int
funct_group9_77();

[[gnu::section(".trivial_handle")]] int
funct_group9_76()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_77();
  return side_effect;
}

int
funct_group9_78();

[[gnu::section(".trivial_handle")]] int
funct_group9_77()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_78();
  return side_effect;
}

int
funct_group9_79();

[[gnu::section(".trivial_handle")]] int
funct_group9_78()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_79();
  return side_effect;
}

int
funct_group9_80();

int
funct_group9_79()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_80();
  return side_effect;
}

int
funct_group9_81();

[[gnu::section(".trivial_handle")]] int
funct_group9_80()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_81();
  return side_effect;
}

int
funct_group9_82();

[[gnu::section(".trivial_handle")]] int
funct_group9_81()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_82();
  return side_effect;
}

int
funct_group9_83();

[[gnu::section(".trivial_handle")]] int
funct_group9_82()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_83();
  return side_effect;
}

int
funct_group9_84();

[[gnu::section(".trivial_handle")]] int
funct_group9_83()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_84();
  return side_effect;
}

int
funct_group9_85();

[[gnu::section(".trivial_handle")]] int
funct_group9_84()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_85();
  return side_effect;
}

int
funct_group9_86();

[[gnu::section(".trivial_handle")]] int
funct_group9_85()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_86();
  return side_effect;
}

int
funct_group9_87();

[[gnu::section(".trivial_handle")]] int
funct_group9_86()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_87();
  return side_effect;
}

int
funct_group9_88();

[[gnu::section(".trivial_handle")]] int
funct_group9_87()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_88();
  return side_effect;
}

int
funct_group9_89();

[[gnu::section(".trivial_handle")]] int
funct_group9_88()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_89();
  return side_effect;
}

int
funct_group9_90();

int
funct_group9_89()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_90();
  return side_effect;
}

int
funct_group9_91();

[[gnu::section(".trivial_handle")]] int
funct_group9_90()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_91();
  return side_effect;
}

int
funct_group9_92();

[[gnu::section(".trivial_handle")]] int
funct_group9_91()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_92();
  return side_effect;
}

int
funct_group9_93();

[[gnu::section(".trivial_handle")]] int
funct_group9_92()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_93();
  return side_effect;
}

int
funct_group9_94();

[[gnu::section(".trivial_handle")]] int
funct_group9_93()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_94();
  return side_effect;
}

int
funct_group9_95();

[[gnu::section(".trivial_handle")]] int
funct_group9_94()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group9_95();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group9_95()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group10_1();

[[gnu::section(".trivial_handle")]] int
funct_group10_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group10_1();
  return side_effect;
}

int
funct_group10_2();

[[gnu::section(".trivial_handle")]] int
funct_group10_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group10_2();
  return side_effect;
}

int
funct_group10_3();

[[gnu::section(".trivial_handle")]] int
funct_group10_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group10_3();
  return side_effect;
}

int
funct_group10_4();

int
funct_group10_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group10_4();
  return side_effect;
}

int
funct_group10_5();

[[gnu::section(".trivial_handle")]] int
funct_group10_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group10_5();
  return side_effect;
}

[[gnu::section(".trivial_handle")]] int
funct_group10_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group11_1();

[[gnu::section(".trivial_handle")]] int
funct_group11_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_1();
  return side_effect;
}

int
funct_group11_2();

[[gnu::section(".trivial_handle")]] int
funct_group11_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_2();
  return side_effect;
}

int
funct_group11_3();

[[gnu::section(".trivial_handle")]] int
funct_group11_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_3();
  return side_effect;
}

int
funct_group11_4();

int
funct_group11_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_4();
  return side_effect;
}

int
funct_group11_5();

[[gnu::section(".trivial_handle")]] int
funct_group11_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_5();
  return side_effect;
}

int
funct_group11_6();

[[gnu::section(".trivial_handle")]] int
funct_group11_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_6();
  return side_effect;
}

int
funct_group11_7();

[[gnu::section(".trivial_handle")]] int
funct_group11_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_7();
  return side_effect;
}

int
funct_group11_8();

int
funct_group11_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_8();
  return side_effect;
}

int
funct_group11_9();

[[gnu::section(".trivial_handle")]] int
funct_group11_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_9();
  return side_effect;
}

int
funct_group11_10();

[[gnu::section(".trivial_handle")]] int
funct_group11_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_10();
  return side_effect;
}

int
funct_group11_11();

[[gnu::section(".trivial_handle")]] int
funct_group11_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group11_11();
  return side_effect;
}

int
funct_group11_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group12_1();

[[gnu::section(".trivial_handle")]] int
funct_group12_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_1();
  return side_effect;
}

int
funct_group12_2();

[[gnu::section(".trivial_handle")]] int
funct_group12_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_2();
  return side_effect;
}

int
funct_group12_3();

[[gnu::section(".trivial_handle")]] int
funct_group12_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_3();
  return side_effect;
}

int
funct_group12_4();

int
funct_group12_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_4();
  return side_effect;
}

int
funct_group12_5();

[[gnu::section(".trivial_handle")]] int
funct_group12_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_5();
  return side_effect;
}

int
funct_group12_6();

[[gnu::section(".trivial_handle")]] int
funct_group12_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_6();
  return side_effect;
}

int
funct_group12_7();

[[gnu::section(".trivial_handle")]] int
funct_group12_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_7();
  return side_effect;
}

int
funct_group12_8();

int
funct_group12_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_8();
  return side_effect;
}

int
funct_group12_9();

[[gnu::section(".trivial_handle")]] int
funct_group12_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_9();
  return side_effect;
}

int
funct_group12_10();

[[gnu::section(".trivial_handle")]] int
funct_group12_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_10();
  return side_effect;
}

int
funct_group12_11();

[[gnu::section(".trivial_handle")]] int
funct_group12_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_11();
  return side_effect;
}

int
funct_group12_12();

int
funct_group12_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_12();
  return side_effect;
}

int
funct_group12_13();

[[gnu::section(".trivial_handle")]] int
funct_group12_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_13();
  return side_effect;
}

int
funct_group12_14();

[[gnu::section(".trivial_handle")]] int
funct_group12_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_14();
  return side_effect;
}

int
funct_group12_15();

[[gnu::section(".trivial_handle")]] int
funct_group12_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_15();
  return side_effect;
}

int
funct_group12_16();

int
funct_group12_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_16();
  return side_effect;
}

int
funct_group12_17();

[[gnu::section(".trivial_handle")]] int
funct_group12_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_17();
  return side_effect;
}

int
funct_group12_18();

[[gnu::section(".trivial_handle")]] int
funct_group12_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_18();
  return side_effect;
}

int
funct_group12_19();

[[gnu::section(".trivial_handle")]] int
funct_group12_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_19();
  return side_effect;
}

int
funct_group12_20();

int
funct_group12_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_20();
  return side_effect;
}

int
funct_group12_21();

[[gnu::section(".trivial_handle")]] int
funct_group12_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_21();
  return side_effect;
}

int
funct_group12_22();

[[gnu::section(".trivial_handle")]] int
funct_group12_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_22();
  return side_effect;
}

int
funct_group12_23();

[[gnu::section(".trivial_handle")]] int
funct_group12_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group12_23();
  return side_effect;
}

int
funct_group12_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group13_1();

[[gnu::section(".trivial_handle")]] int
funct_group13_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_1();
  return side_effect;
}

int
funct_group13_2();

[[gnu::section(".trivial_handle")]] int
funct_group13_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_2();
  return side_effect;
}

int
funct_group13_3();

[[gnu::section(".trivial_handle")]] int
funct_group13_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_3();
  return side_effect;
}

int
funct_group13_4();

int
funct_group13_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_4();
  return side_effect;
}

int
funct_group13_5();

[[gnu::section(".trivial_handle")]] int
funct_group13_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_5();
  return side_effect;
}

int
funct_group13_6();

[[gnu::section(".trivial_handle")]] int
funct_group13_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_6();
  return side_effect;
}

int
funct_group13_7();

[[gnu::section(".trivial_handle")]] int
funct_group13_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_7();
  return side_effect;
}

int
funct_group13_8();

int
funct_group13_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_8();
  return side_effect;
}

int
funct_group13_9();

[[gnu::section(".trivial_handle")]] int
funct_group13_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_9();
  return side_effect;
}

int
funct_group13_10();

[[gnu::section(".trivial_handle")]] int
funct_group13_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_10();
  return side_effect;
}

int
funct_group13_11();

[[gnu::section(".trivial_handle")]] int
funct_group13_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_11();
  return side_effect;
}

int
funct_group13_12();

int
funct_group13_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_12();
  return side_effect;
}

int
funct_group13_13();

[[gnu::section(".trivial_handle")]] int
funct_group13_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_13();
  return side_effect;
}

int
funct_group13_14();

[[gnu::section(".trivial_handle")]] int
funct_group13_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_14();
  return side_effect;
}

int
funct_group13_15();

[[gnu::section(".trivial_handle")]] int
funct_group13_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_15();
  return side_effect;
}

int
funct_group13_16();

int
funct_group13_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_16();
  return side_effect;
}

int
funct_group13_17();

[[gnu::section(".trivial_handle")]] int
funct_group13_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_17();
  return side_effect;
}

int
funct_group13_18();

[[gnu::section(".trivial_handle")]] int
funct_group13_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_18();
  return side_effect;
}

int
funct_group13_19();

[[gnu::section(".trivial_handle")]] int
funct_group13_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_19();
  return side_effect;
}

int
funct_group13_20();

int
funct_group13_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_20();
  return side_effect;
}

int
funct_group13_21();

[[gnu::section(".trivial_handle")]] int
funct_group13_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_21();
  return side_effect;
}

int
funct_group13_22();

[[gnu::section(".trivial_handle")]] int
funct_group13_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_22();
  return side_effect;
}

int
funct_group13_23();

[[gnu::section(".trivial_handle")]] int
funct_group13_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_23();
  return side_effect;
}

int
funct_group13_24();

int
funct_group13_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_24();
  return side_effect;
}

int
funct_group13_25();

[[gnu::section(".trivial_handle")]] int
funct_group13_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_25();
  return side_effect;
}

int
funct_group13_26();

[[gnu::section(".trivial_handle")]] int
funct_group13_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_26();
  return side_effect;
}

int
funct_group13_27();

[[gnu::section(".trivial_handle")]] int
funct_group13_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_27();
  return side_effect;
}

int
funct_group13_28();

int
funct_group13_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_28();
  return side_effect;
}

int
funct_group13_29();

[[gnu::section(".trivial_handle")]] int
funct_group13_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_29();
  return side_effect;
}

int
funct_group13_30();

[[gnu::section(".trivial_handle")]] int
funct_group13_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_30();
  return side_effect;
}

int
funct_group13_31();

[[gnu::section(".trivial_handle")]] int
funct_group13_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_31();
  return side_effect;
}

int
funct_group13_32();

int
funct_group13_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_32();
  return side_effect;
}

int
funct_group13_33();

[[gnu::section(".trivial_handle")]] int
funct_group13_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_33();
  return side_effect;
}

int
funct_group13_34();

[[gnu::section(".trivial_handle")]] int
funct_group13_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_34();
  return side_effect;
}

int
funct_group13_35();

[[gnu::section(".trivial_handle")]] int
funct_group13_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_35();
  return side_effect;
}

int
funct_group13_36();

int
funct_group13_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_36();
  return side_effect;
}

int
funct_group13_37();

[[gnu::section(".trivial_handle")]] int
funct_group13_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_37();
  return side_effect;
}

int
funct_group13_38();

[[gnu::section(".trivial_handle")]] int
funct_group13_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_38();
  return side_effect;
}

int
funct_group13_39();

[[gnu::section(".trivial_handle")]] int
funct_group13_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_39();
  return side_effect;
}

int
funct_group13_40();

int
funct_group13_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_40();
  return side_effect;
}

int
funct_group13_41();

[[gnu::section(".trivial_handle")]] int
funct_group13_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_41();
  return side_effect;
}

int
funct_group13_42();

[[gnu::section(".trivial_handle")]] int
funct_group13_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_42();
  return side_effect;
}

int
funct_group13_43();

[[gnu::section(".trivial_handle")]] int
funct_group13_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_43();
  return side_effect;
}

int
funct_group13_44();

int
funct_group13_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_44();
  return side_effect;
}

int
funct_group13_45();

[[gnu::section(".trivial_handle")]] int
funct_group13_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_45();
  return side_effect;
}

int
funct_group13_46();

[[gnu::section(".trivial_handle")]] int
funct_group13_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_46();
  return side_effect;
}

int
funct_group13_47();

[[gnu::section(".trivial_handle")]] int
funct_group13_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group13_47();
  return side_effect;
}

int
funct_group13_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group14_1();

[[gnu::section(".trivial_handle")]] int
funct_group14_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_1();
  return side_effect;
}

int
funct_group14_2();

[[gnu::section(".trivial_handle")]] int
funct_group14_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_2();
  return side_effect;
}

int
funct_group14_3();

[[gnu::section(".trivial_handle")]] int
funct_group14_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_3();
  return side_effect;
}

int
funct_group14_4();

int
funct_group14_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_4();
  return side_effect;
}

int
funct_group14_5();

[[gnu::section(".trivial_handle")]] int
funct_group14_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_5();
  return side_effect;
}

int
funct_group14_6();

[[gnu::section(".trivial_handle")]] int
funct_group14_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_6();
  return side_effect;
}

int
funct_group14_7();

[[gnu::section(".trivial_handle")]] int
funct_group14_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_7();
  return side_effect;
}

int
funct_group14_8();

int
funct_group14_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_8();
  return side_effect;
}

int
funct_group14_9();

[[gnu::section(".trivial_handle")]] int
funct_group14_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_9();
  return side_effect;
}

int
funct_group14_10();

[[gnu::section(".trivial_handle")]] int
funct_group14_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_10();
  return side_effect;
}

int
funct_group14_11();

[[gnu::section(".trivial_handle")]] int
funct_group14_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_11();
  return side_effect;
}

int
funct_group14_12();

int
funct_group14_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_12();
  return side_effect;
}

int
funct_group14_13();

[[gnu::section(".trivial_handle")]] int
funct_group14_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_13();
  return side_effect;
}

int
funct_group14_14();

[[gnu::section(".trivial_handle")]] int
funct_group14_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_14();
  return side_effect;
}

int
funct_group14_15();

[[gnu::section(".trivial_handle")]] int
funct_group14_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_15();
  return side_effect;
}

int
funct_group14_16();

int
funct_group14_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_16();
  return side_effect;
}

int
funct_group14_17();

[[gnu::section(".trivial_handle")]] int
funct_group14_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_17();
  return side_effect;
}

int
funct_group14_18();

[[gnu::section(".trivial_handle")]] int
funct_group14_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_18();
  return side_effect;
}

int
funct_group14_19();

[[gnu::section(".trivial_handle")]] int
funct_group14_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_19();
  return side_effect;
}

int
funct_group14_20();

int
funct_group14_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_20();
  return side_effect;
}

int
funct_group14_21();

[[gnu::section(".trivial_handle")]] int
funct_group14_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_21();
  return side_effect;
}

int
funct_group14_22();

[[gnu::section(".trivial_handle")]] int
funct_group14_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_22();
  return side_effect;
}

int
funct_group14_23();

[[gnu::section(".trivial_handle")]] int
funct_group14_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_23();
  return side_effect;
}

int
funct_group14_24();

int
funct_group14_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_24();
  return side_effect;
}

int
funct_group14_25();

[[gnu::section(".trivial_handle")]] int
funct_group14_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_25();
  return side_effect;
}

int
funct_group14_26();

[[gnu::section(".trivial_handle")]] int
funct_group14_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_26();
  return side_effect;
}

int
funct_group14_27();

[[gnu::section(".trivial_handle")]] int
funct_group14_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_27();
  return side_effect;
}

int
funct_group14_28();

int
funct_group14_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_28();
  return side_effect;
}

int
funct_group14_29();

[[gnu::section(".trivial_handle")]] int
funct_group14_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_29();
  return side_effect;
}

int
funct_group14_30();

[[gnu::section(".trivial_handle")]] int
funct_group14_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_30();
  return side_effect;
}

int
funct_group14_31();

[[gnu::section(".trivial_handle")]] int
funct_group14_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_31();
  return side_effect;
}

int
funct_group14_32();

int
funct_group14_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_32();
  return side_effect;
}

int
funct_group14_33();

[[gnu::section(".trivial_handle")]] int
funct_group14_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_33();
  return side_effect;
}

int
funct_group14_34();

[[gnu::section(".trivial_handle")]] int
funct_group14_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_34();
  return side_effect;
}

int
funct_group14_35();

[[gnu::section(".trivial_handle")]] int
funct_group14_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_35();
  return side_effect;
}

int
funct_group14_36();

int
funct_group14_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_36();
  return side_effect;
}

int
funct_group14_37();

[[gnu::section(".trivial_handle")]] int
funct_group14_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_37();
  return side_effect;
}

int
funct_group14_38();

[[gnu::section(".trivial_handle")]] int
funct_group14_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_38();
  return side_effect;
}

int
funct_group14_39();

[[gnu::section(".trivial_handle")]] int
funct_group14_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_39();
  return side_effect;
}

int
funct_group14_40();

int
funct_group14_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_40();
  return side_effect;
}

int
funct_group14_41();

[[gnu::section(".trivial_handle")]] int
funct_group14_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_41();
  return side_effect;
}

int
funct_group14_42();

[[gnu::section(".trivial_handle")]] int
funct_group14_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_42();
  return side_effect;
}

int
funct_group14_43();

[[gnu::section(".trivial_handle")]] int
funct_group14_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_43();
  return side_effect;
}

int
funct_group14_44();

int
funct_group14_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_44();
  return side_effect;
}

int
funct_group14_45();

[[gnu::section(".trivial_handle")]] int
funct_group14_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_45();
  return side_effect;
}

int
funct_group14_46();

[[gnu::section(".trivial_handle")]] int
funct_group14_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_46();
  return side_effect;
}

int
funct_group14_47();

[[gnu::section(".trivial_handle")]] int
funct_group14_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_47();
  return side_effect;
}

int
funct_group14_48();

int
funct_group14_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_48();
  return side_effect;
}

int
funct_group14_49();

[[gnu::section(".trivial_handle")]] int
funct_group14_48()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_49();
  return side_effect;
}

int
funct_group14_50();

[[gnu::section(".trivial_handle")]] int
funct_group14_49()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_50();
  return side_effect;
}

int
funct_group14_51();

[[gnu::section(".trivial_handle")]] int
funct_group14_50()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_51();
  return side_effect;
}

int
funct_group14_52();

int
funct_group14_51()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_52();
  return side_effect;
}

int
funct_group14_53();

[[gnu::section(".trivial_handle")]] int
funct_group14_52()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_53();
  return side_effect;
}

int
funct_group14_54();

[[gnu::section(".trivial_handle")]] int
funct_group14_53()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_54();
  return side_effect;
}

int
funct_group14_55();

[[gnu::section(".trivial_handle")]] int
funct_group14_54()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_55();
  return side_effect;
}

int
funct_group14_56();

int
funct_group14_55()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_56();
  return side_effect;
}

int
funct_group14_57();

[[gnu::section(".trivial_handle")]] int
funct_group14_56()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_57();
  return side_effect;
}

int
funct_group14_58();

[[gnu::section(".trivial_handle")]] int
funct_group14_57()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_58();
  return side_effect;
}

int
funct_group14_59();

[[gnu::section(".trivial_handle")]] int
funct_group14_58()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_59();
  return side_effect;
}

int
funct_group14_60();

int
funct_group14_59()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_60();
  return side_effect;
}

int
funct_group14_61();

[[gnu::section(".trivial_handle")]] int
funct_group14_60()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_61();
  return side_effect;
}

int
funct_group14_62();

[[gnu::section(".trivial_handle")]] int
funct_group14_61()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_62();
  return side_effect;
}

int
funct_group14_63();

[[gnu::section(".trivial_handle")]] int
funct_group14_62()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_63();
  return side_effect;
}

int
funct_group14_64();

int
funct_group14_63()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_64();
  return side_effect;
}

int
funct_group14_65();

[[gnu::section(".trivial_handle")]] int
funct_group14_64()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_65();
  return side_effect;
}

int
funct_group14_66();

[[gnu::section(".trivial_handle")]] int
funct_group14_65()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_66();
  return side_effect;
}

int
funct_group14_67();

[[gnu::section(".trivial_handle")]] int
funct_group14_66()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_67();
  return side_effect;
}

int
funct_group14_68();

int
funct_group14_67()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_68();
  return side_effect;
}

int
funct_group14_69();

[[gnu::section(".trivial_handle")]] int
funct_group14_68()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_69();
  return side_effect;
}

int
funct_group14_70();

[[gnu::section(".trivial_handle")]] int
funct_group14_69()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_70();
  return side_effect;
}

int
funct_group14_71();

[[gnu::section(".trivial_handle")]] int
funct_group14_70()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_71();
  return side_effect;
}

int
funct_group14_72();

int
funct_group14_71()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_72();
  return side_effect;
}

int
funct_group14_73();

[[gnu::section(".trivial_handle")]] int
funct_group14_72()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_73();
  return side_effect;
}

int
funct_group14_74();

[[gnu::section(".trivial_handle")]] int
funct_group14_73()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_74();
  return side_effect;
}

int
funct_group14_75();

[[gnu::section(".trivial_handle")]] int
funct_group14_74()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_75();
  return side_effect;
}

int
funct_group14_76();

int
funct_group14_75()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_76();
  return side_effect;
}

int
funct_group14_77();

[[gnu::section(".trivial_handle")]] int
funct_group14_76()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_77();
  return side_effect;
}

int
funct_group14_78();

[[gnu::section(".trivial_handle")]] int
funct_group14_77()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_78();
  return side_effect;
}

int
funct_group14_79();

[[gnu::section(".trivial_handle")]] int
funct_group14_78()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_79();
  return side_effect;
}

int
funct_group14_80();

int
funct_group14_79()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_80();
  return side_effect;
}

int
funct_group14_81();

[[gnu::section(".trivial_handle")]] int
funct_group14_80()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_81();
  return side_effect;
}

int
funct_group14_82();

[[gnu::section(".trivial_handle")]] int
funct_group14_81()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_82();
  return side_effect;
}

int
funct_group14_83();

[[gnu::section(".trivial_handle")]] int
funct_group14_82()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_83();
  return side_effect;
}

int
funct_group14_84();

int
funct_group14_83()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_84();
  return side_effect;
}

int
funct_group14_85();

[[gnu::section(".trivial_handle")]] int
funct_group14_84()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_85();
  return side_effect;
}

int
funct_group14_86();

[[gnu::section(".trivial_handle")]] int
funct_group14_85()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_86();
  return side_effect;
}

int
funct_group14_87();

[[gnu::section(".trivial_handle")]] int
funct_group14_86()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_87();
  return side_effect;
}

int
funct_group14_88();

int
funct_group14_87()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_88();
  return side_effect;
}

int
funct_group14_89();

[[gnu::section(".trivial_handle")]] int
funct_group14_88()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_89();
  return side_effect;
}

int
funct_group14_90();

[[gnu::section(".trivial_handle")]] int
funct_group14_89()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_90();
  return side_effect;
}

int
funct_group14_91();

[[gnu::section(".trivial_handle")]] int
funct_group14_90()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_91();
  return side_effect;
}

int
funct_group14_92();

int
funct_group14_91()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_92();
  return side_effect;
}

int
funct_group14_93();

[[gnu::section(".trivial_handle")]] int
funct_group14_92()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_93();
  return side_effect;
}

int
funct_group14_94();

[[gnu::section(".trivial_handle")]] int
funct_group14_93()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_94();
  return side_effect;
}

int
funct_group14_95();

[[gnu::section(".trivial_handle")]] int
funct_group14_94()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group14_95();
  return side_effect;
}

int
funct_group14_95()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group15_1();

[[gnu::section(".trivial_handle")]] int
funct_group15_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group15_1();
  return side_effect;
}

int
funct_group15_2();

int
funct_group15_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group15_2();
  return side_effect;
}

int
funct_group15_3();

[[gnu::section(".trivial_handle")]] int
funct_group15_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group15_3();
  return side_effect;
}

int
funct_group15_4();

int
funct_group15_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group15_4();
  return side_effect;
}

int
funct_group15_5();

[[gnu::section(".trivial_handle")]] int
funct_group15_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group15_5();
  return side_effect;
}

int
funct_group15_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group16_1();

[[gnu::section(".trivial_handle")]] int
funct_group16_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_1();
  return side_effect;
}

int
funct_group16_2();

int
funct_group16_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_2();
  return side_effect;
}

int
funct_group16_3();

[[gnu::section(".trivial_handle")]] int
funct_group16_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_3();
  return side_effect;
}

int
funct_group16_4();

int
funct_group16_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_4();
  return side_effect;
}

int
funct_group16_5();

[[gnu::section(".trivial_handle")]] int
funct_group16_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_5();
  return side_effect;
}

int
funct_group16_6();

int
funct_group16_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_6();
  return side_effect;
}

int
funct_group16_7();

[[gnu::section(".trivial_handle")]] int
funct_group16_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_7();
  return side_effect;
}

int
funct_group16_8();

int
funct_group16_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_8();
  return side_effect;
}

int
funct_group16_9();

[[gnu::section(".trivial_handle")]] int
funct_group16_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_9();
  return side_effect;
}

int
funct_group16_10();

int
funct_group16_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_10();
  return side_effect;
}

int
funct_group16_11();

[[gnu::section(".trivial_handle")]] int
funct_group16_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group16_11();
  return side_effect;
}

int
funct_group16_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group17_1();

[[gnu::section(".trivial_handle")]] int
funct_group17_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_1();
  return side_effect;
}

int
funct_group17_2();

int
funct_group17_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_2();
  return side_effect;
}

int
funct_group17_3();

[[gnu::section(".trivial_handle")]] int
funct_group17_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_3();
  return side_effect;
}

int
funct_group17_4();

int
funct_group17_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_4();
  return side_effect;
}

int
funct_group17_5();

[[gnu::section(".trivial_handle")]] int
funct_group17_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_5();
  return side_effect;
}

int
funct_group17_6();

int
funct_group17_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_6();
  return side_effect;
}

int
funct_group17_7();

[[gnu::section(".trivial_handle")]] int
funct_group17_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_7();
  return side_effect;
}

int
funct_group17_8();

int
funct_group17_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_8();
  return side_effect;
}

int
funct_group17_9();

[[gnu::section(".trivial_handle")]] int
funct_group17_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_9();
  return side_effect;
}

int
funct_group17_10();

int
funct_group17_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_10();
  return side_effect;
}

int
funct_group17_11();

[[gnu::section(".trivial_handle")]] int
funct_group17_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_11();
  return side_effect;
}

int
funct_group17_12();

int
funct_group17_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_12();
  return side_effect;
}

int
funct_group17_13();

[[gnu::section(".trivial_handle")]] int
funct_group17_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_13();
  return side_effect;
}

int
funct_group17_14();

int
funct_group17_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_14();
  return side_effect;
}

int
funct_group17_15();

[[gnu::section(".trivial_handle")]] int
funct_group17_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_15();
  return side_effect;
}

int
funct_group17_16();

int
funct_group17_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_16();
  return side_effect;
}

int
funct_group17_17();

[[gnu::section(".trivial_handle")]] int
funct_group17_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_17();
  return side_effect;
}

int
funct_group17_18();

int
funct_group17_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_18();
  return side_effect;
}

int
funct_group17_19();

[[gnu::section(".trivial_handle")]] int
funct_group17_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_19();
  return side_effect;
}

int
funct_group17_20();

int
funct_group17_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_20();
  return side_effect;
}

int
funct_group17_21();

[[gnu::section(".trivial_handle")]] int
funct_group17_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_21();
  return side_effect;
}

int
funct_group17_22();

int
funct_group17_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_22();
  return side_effect;
}

int
funct_group17_23();

[[gnu::section(".trivial_handle")]] int
funct_group17_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group17_23();
  return side_effect;
}

int
funct_group17_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group18_1();

[[gnu::section(".trivial_handle")]] int
funct_group18_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_1();
  return side_effect;
}

int
funct_group18_2();

int
funct_group18_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_2();
  return side_effect;
}

int
funct_group18_3();

[[gnu::section(".trivial_handle")]] int
funct_group18_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_3();
  return side_effect;
}

int
funct_group18_4();

int
funct_group18_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_4();
  return side_effect;
}

int
funct_group18_5();

[[gnu::section(".trivial_handle")]] int
funct_group18_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_5();
  return side_effect;
}

int
funct_group18_6();

int
funct_group18_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_6();
  return side_effect;
}

int
funct_group18_7();

[[gnu::section(".trivial_handle")]] int
funct_group18_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_7();
  return side_effect;
}

int
funct_group18_8();

int
funct_group18_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_8();
  return side_effect;
}

int
funct_group18_9();

[[gnu::section(".trivial_handle")]] int
funct_group18_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_9();
  return side_effect;
}

int
funct_group18_10();

int
funct_group18_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_10();
  return side_effect;
}

int
funct_group18_11();

[[gnu::section(".trivial_handle")]] int
funct_group18_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_11();
  return side_effect;
}

int
funct_group18_12();

int
funct_group18_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_12();
  return side_effect;
}

int
funct_group18_13();

[[gnu::section(".trivial_handle")]] int
funct_group18_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_13();
  return side_effect;
}

int
funct_group18_14();

int
funct_group18_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_14();
  return side_effect;
}

int
funct_group18_15();

[[gnu::section(".trivial_handle")]] int
funct_group18_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_15();
  return side_effect;
}

int
funct_group18_16();

int
funct_group18_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_16();
  return side_effect;
}

int
funct_group18_17();

[[gnu::section(".trivial_handle")]] int
funct_group18_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_17();
  return side_effect;
}

int
funct_group18_18();

int
funct_group18_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_18();
  return side_effect;
}

int
funct_group18_19();

[[gnu::section(".trivial_handle")]] int
funct_group18_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_19();
  return side_effect;
}

int
funct_group18_20();

int
funct_group18_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_20();
  return side_effect;
}

int
funct_group18_21();

[[gnu::section(".trivial_handle")]] int
funct_group18_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_21();
  return side_effect;
}

int
funct_group18_22();

int
funct_group18_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_22();
  return side_effect;
}

int
funct_group18_23();

[[gnu::section(".trivial_handle")]] int
funct_group18_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_23();
  return side_effect;
}

int
funct_group18_24();

int
funct_group18_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_24();
  return side_effect;
}

int
funct_group18_25();

[[gnu::section(".trivial_handle")]] int
funct_group18_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_25();
  return side_effect;
}

int
funct_group18_26();

int
funct_group18_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_26();
  return side_effect;
}

int
funct_group18_27();

[[gnu::section(".trivial_handle")]] int
funct_group18_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_27();
  return side_effect;
}

int
funct_group18_28();

int
funct_group18_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_28();
  return side_effect;
}

int
funct_group18_29();

[[gnu::section(".trivial_handle")]] int
funct_group18_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_29();
  return side_effect;
}

int
funct_group18_30();

int
funct_group18_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_30();
  return side_effect;
}

int
funct_group18_31();

[[gnu::section(".trivial_handle")]] int
funct_group18_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_31();
  return side_effect;
}

int
funct_group18_32();

int
funct_group18_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_32();
  return side_effect;
}

int
funct_group18_33();

[[gnu::section(".trivial_handle")]] int
funct_group18_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_33();
  return side_effect;
}

int
funct_group18_34();

int
funct_group18_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_34();
  return side_effect;
}

int
funct_group18_35();

[[gnu::section(".trivial_handle")]] int
funct_group18_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_35();
  return side_effect;
}

int
funct_group18_36();

int
funct_group18_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_36();
  return side_effect;
}

int
funct_group18_37();

[[gnu::section(".trivial_handle")]] int
funct_group18_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_37();
  return side_effect;
}

int
funct_group18_38();

int
funct_group18_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_38();
  return side_effect;
}

int
funct_group18_39();

[[gnu::section(".trivial_handle")]] int
funct_group18_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_39();
  return side_effect;
}

int
funct_group18_40();

int
funct_group18_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_40();
  return side_effect;
}

int
funct_group18_41();

[[gnu::section(".trivial_handle")]] int
funct_group18_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_41();
  return side_effect;
}

int
funct_group18_42();

int
funct_group18_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_42();
  return side_effect;
}

int
funct_group18_43();

[[gnu::section(".trivial_handle")]] int
funct_group18_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_43();
  return side_effect;
}

int
funct_group18_44();

int
funct_group18_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_44();
  return side_effect;
}

int
funct_group18_45();

[[gnu::section(".trivial_handle")]] int
funct_group18_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_45();
  return side_effect;
}

int
funct_group18_46();

int
funct_group18_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_46();
  return side_effect;
}

int
funct_group18_47();

[[gnu::section(".trivial_handle")]] int
funct_group18_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group18_47();
  return side_effect;
}

int
funct_group18_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group19_1();

[[gnu::section(".trivial_handle")]] int
funct_group19_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_1();
  return side_effect;
}

int
funct_group19_2();

int
funct_group19_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_2();
  return side_effect;
}

int
funct_group19_3();

[[gnu::section(".trivial_handle")]] int
funct_group19_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_3();
  return side_effect;
}

int
funct_group19_4();

int
funct_group19_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_4();
  return side_effect;
}

int
funct_group19_5();

[[gnu::section(".trivial_handle")]] int
funct_group19_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_5();
  return side_effect;
}

int
funct_group19_6();

int
funct_group19_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_6();
  return side_effect;
}

int
funct_group19_7();

[[gnu::section(".trivial_handle")]] int
funct_group19_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_7();
  return side_effect;
}

int
funct_group19_8();

int
funct_group19_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_8();
  return side_effect;
}

int
funct_group19_9();

[[gnu::section(".trivial_handle")]] int
funct_group19_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_9();
  return side_effect;
}

int
funct_group19_10();

int
funct_group19_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_10();
  return side_effect;
}

int
funct_group19_11();

[[gnu::section(".trivial_handle")]] int
funct_group19_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_11();
  return side_effect;
}

int
funct_group19_12();

int
funct_group19_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_12();
  return side_effect;
}

int
funct_group19_13();

[[gnu::section(".trivial_handle")]] int
funct_group19_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_13();
  return side_effect;
}

int
funct_group19_14();

int
funct_group19_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_14();
  return side_effect;
}

int
funct_group19_15();

[[gnu::section(".trivial_handle")]] int
funct_group19_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_15();
  return side_effect;
}

int
funct_group19_16();

int
funct_group19_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_16();
  return side_effect;
}

int
funct_group19_17();

[[gnu::section(".trivial_handle")]] int
funct_group19_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_17();
  return side_effect;
}

int
funct_group19_18();

int
funct_group19_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_18();
  return side_effect;
}

int
funct_group19_19();

[[gnu::section(".trivial_handle")]] int
funct_group19_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_19();
  return side_effect;
}

int
funct_group19_20();

int
funct_group19_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_20();
  return side_effect;
}

int
funct_group19_21();

[[gnu::section(".trivial_handle")]] int
funct_group19_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_21();
  return side_effect;
}

int
funct_group19_22();

int
funct_group19_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_22();
  return side_effect;
}

int
funct_group19_23();

[[gnu::section(".trivial_handle")]] int
funct_group19_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_23();
  return side_effect;
}

int
funct_group19_24();

int
funct_group19_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_24();
  return side_effect;
}

int
funct_group19_25();

[[gnu::section(".trivial_handle")]] int
funct_group19_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_25();
  return side_effect;
}

int
funct_group19_26();

int
funct_group19_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_26();
  return side_effect;
}

int
funct_group19_27();

[[gnu::section(".trivial_handle")]] int
funct_group19_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_27();
  return side_effect;
}

int
funct_group19_28();

int
funct_group19_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_28();
  return side_effect;
}

int
funct_group19_29();

[[gnu::section(".trivial_handle")]] int
funct_group19_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_29();
  return side_effect;
}

int
funct_group19_30();

int
funct_group19_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_30();
  return side_effect;
}

int
funct_group19_31();

[[gnu::section(".trivial_handle")]] int
funct_group19_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_31();
  return side_effect;
}

int
funct_group19_32();

int
funct_group19_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_32();
  return side_effect;
}

int
funct_group19_33();

[[gnu::section(".trivial_handle")]] int
funct_group19_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_33();
  return side_effect;
}

int
funct_group19_34();

int
funct_group19_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_34();
  return side_effect;
}

int
funct_group19_35();

[[gnu::section(".trivial_handle")]] int
funct_group19_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_35();
  return side_effect;
}

int
funct_group19_36();

int
funct_group19_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_36();
  return side_effect;
}

int
funct_group19_37();

[[gnu::section(".trivial_handle")]] int
funct_group19_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_37();
  return side_effect;
}

int
funct_group19_38();

int
funct_group19_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_38();
  return side_effect;
}

int
funct_group19_39();

[[gnu::section(".trivial_handle")]] int
funct_group19_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_39();
  return side_effect;
}

int
funct_group19_40();

int
funct_group19_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_40();
  return side_effect;
}

int
funct_group19_41();

[[gnu::section(".trivial_handle")]] int
funct_group19_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_41();
  return side_effect;
}

int
funct_group19_42();

int
funct_group19_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_42();
  return side_effect;
}

int
funct_group19_43();

[[gnu::section(".trivial_handle")]] int
funct_group19_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_43();
  return side_effect;
}

int
funct_group19_44();

int
funct_group19_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_44();
  return side_effect;
}

int
funct_group19_45();

[[gnu::section(".trivial_handle")]] int
funct_group19_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_45();
  return side_effect;
}

int
funct_group19_46();

int
funct_group19_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_46();
  return side_effect;
}

int
funct_group19_47();

[[gnu::section(".trivial_handle")]] int
funct_group19_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_47();
  return side_effect;
}

int
funct_group19_48();

int
funct_group19_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_48();
  return side_effect;
}

int
funct_group19_49();

[[gnu::section(".trivial_handle")]] int
funct_group19_48()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_49();
  return side_effect;
}

int
funct_group19_50();

int
funct_group19_49()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_50();
  return side_effect;
}

int
funct_group19_51();

[[gnu::section(".trivial_handle")]] int
funct_group19_50()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_51();
  return side_effect;
}

int
funct_group19_52();

int
funct_group19_51()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_52();
  return side_effect;
}

int
funct_group19_53();

[[gnu::section(".trivial_handle")]] int
funct_group19_52()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_53();
  return side_effect;
}

int
funct_group19_54();

int
funct_group19_53()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_54();
  return side_effect;
}

int
funct_group19_55();

[[gnu::section(".trivial_handle")]] int
funct_group19_54()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_55();
  return side_effect;
}

int
funct_group19_56();

int
funct_group19_55()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_56();
  return side_effect;
}

int
funct_group19_57();

[[gnu::section(".trivial_handle")]] int
funct_group19_56()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_57();
  return side_effect;
}

int
funct_group19_58();

int
funct_group19_57()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_58();
  return side_effect;
}

int
funct_group19_59();

[[gnu::section(".trivial_handle")]] int
funct_group19_58()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_59();
  return side_effect;
}

int
funct_group19_60();

int
funct_group19_59()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_60();
  return side_effect;
}

int
funct_group19_61();

[[gnu::section(".trivial_handle")]] int
funct_group19_60()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_61();
  return side_effect;
}

int
funct_group19_62();

int
funct_group19_61()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_62();
  return side_effect;
}

int
funct_group19_63();

[[gnu::section(".trivial_handle")]] int
funct_group19_62()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_63();
  return side_effect;
}

int
funct_group19_64();

int
funct_group19_63()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_64();
  return side_effect;
}

int
funct_group19_65();

[[gnu::section(".trivial_handle")]] int
funct_group19_64()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_65();
  return side_effect;
}

int
funct_group19_66();

int
funct_group19_65()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_66();
  return side_effect;
}

int
funct_group19_67();

[[gnu::section(".trivial_handle")]] int
funct_group19_66()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_67();
  return side_effect;
}

int
funct_group19_68();

int
funct_group19_67()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_68();
  return side_effect;
}

int
funct_group19_69();

[[gnu::section(".trivial_handle")]] int
funct_group19_68()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_69();
  return side_effect;
}

int
funct_group19_70();

int
funct_group19_69()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_70();
  return side_effect;
}

int
funct_group19_71();

[[gnu::section(".trivial_handle")]] int
funct_group19_70()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_71();
  return side_effect;
}

int
funct_group19_72();

int
funct_group19_71()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_72();
  return side_effect;
}

int
funct_group19_73();

[[gnu::section(".trivial_handle")]] int
funct_group19_72()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_73();
  return side_effect;
}

int
funct_group19_74();

int
funct_group19_73()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_74();
  return side_effect;
}

int
funct_group19_75();

[[gnu::section(".trivial_handle")]] int
funct_group19_74()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_75();
  return side_effect;
}

int
funct_group19_76();

int
funct_group19_75()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_76();
  return side_effect;
}

int
funct_group19_77();

[[gnu::section(".trivial_handle")]] int
funct_group19_76()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_77();
  return side_effect;
}

int
funct_group19_78();

int
funct_group19_77()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_78();
  return side_effect;
}

int
funct_group19_79();

[[gnu::section(".trivial_handle")]] int
funct_group19_78()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_79();
  return side_effect;
}

int
funct_group19_80();

int
funct_group19_79()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_80();
  return side_effect;
}

int
funct_group19_81();

[[gnu::section(".trivial_handle")]] int
funct_group19_80()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_81();
  return side_effect;
}

int
funct_group19_82();

int
funct_group19_81()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_82();
  return side_effect;
}

int
funct_group19_83();

[[gnu::section(".trivial_handle")]] int
funct_group19_82()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_83();
  return side_effect;
}

int
funct_group19_84();

int
funct_group19_83()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_84();
  return side_effect;
}

int
funct_group19_85();

[[gnu::section(".trivial_handle")]] int
funct_group19_84()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_85();
  return side_effect;
}

int
funct_group19_86();

int
funct_group19_85()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_86();
  return side_effect;
}

int
funct_group19_87();

[[gnu::section(".trivial_handle")]] int
funct_group19_86()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_87();
  return side_effect;
}

int
funct_group19_88();

int
funct_group19_87()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_88();
  return side_effect;
}

int
funct_group19_89();

[[gnu::section(".trivial_handle")]] int
funct_group19_88()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_89();
  return side_effect;
}

int
funct_group19_90();

int
funct_group19_89()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_90();
  return side_effect;
}

int
funct_group19_91();

[[gnu::section(".trivial_handle")]] int
funct_group19_90()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_91();
  return side_effect;
}

int
funct_group19_92();

int
funct_group19_91()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_92();
  return side_effect;
}

int
funct_group19_93();

[[gnu::section(".trivial_handle")]] int
funct_group19_92()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_93();
  return side_effect;
}

int
funct_group19_94();

int
funct_group19_93()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_94();
  return side_effect;
}

int
funct_group19_95();

[[gnu::section(".trivial_handle")]] int
funct_group19_94()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group19_95();
  return side_effect;
}

int
funct_group19_95()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group20_1();

int
funct_group20_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group20_1();
  return side_effect;
}

int
funct_group20_2();

int
funct_group20_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group20_2();
  return side_effect;
}

int
funct_group20_3();

int
funct_group20_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group20_3();
  return side_effect;
}

int
funct_group20_4();

int
funct_group20_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group20_4();
  return side_effect;
}

int
funct_group20_5();

int
funct_group20_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group20_5();
  return side_effect;
}

int
funct_group20_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group21_1();

int
funct_group21_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_1();
  return side_effect;
}

int
funct_group21_2();

int
funct_group21_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_2();
  return side_effect;
}

int
funct_group21_3();

int
funct_group21_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_3();
  return side_effect;
}

int
funct_group21_4();

int
funct_group21_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_4();
  return side_effect;
}

int
funct_group21_5();

int
funct_group21_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_5();
  return side_effect;
}

int
funct_group21_6();

int
funct_group21_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_6();
  return side_effect;
}

int
funct_group21_7();

int
funct_group21_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_7();
  return side_effect;
}

int
funct_group21_8();

int
funct_group21_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_8();
  return side_effect;
}

int
funct_group21_9();

int
funct_group21_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_9();
  return side_effect;
}

int
funct_group21_10();

int
funct_group21_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_10();
  return side_effect;
}

int
funct_group21_11();

int
funct_group21_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group21_11();
  return side_effect;
}

int
funct_group21_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group22_1();

int
funct_group22_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_1();
  return side_effect;
}

int
funct_group22_2();

int
funct_group22_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_2();
  return side_effect;
}

int
funct_group22_3();

int
funct_group22_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_3();
  return side_effect;
}

int
funct_group22_4();

int
funct_group22_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_4();
  return side_effect;
}

int
funct_group22_5();

int
funct_group22_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_5();
  return side_effect;
}

int
funct_group22_6();

int
funct_group22_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_6();
  return side_effect;
}

int
funct_group22_7();

int
funct_group22_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_7();
  return side_effect;
}

int
funct_group22_8();

int
funct_group22_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_8();
  return side_effect;
}

int
funct_group22_9();

int
funct_group22_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_9();
  return side_effect;
}

int
funct_group22_10();

int
funct_group22_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_10();
  return side_effect;
}

int
funct_group22_11();

int
funct_group22_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_11();
  return side_effect;
}

int
funct_group22_12();

int
funct_group22_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_12();
  return side_effect;
}

int
funct_group22_13();

int
funct_group22_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_13();
  return side_effect;
}

int
funct_group22_14();

int
funct_group22_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_14();
  return side_effect;
}

int
funct_group22_15();

int
funct_group22_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_15();
  return side_effect;
}

int
funct_group22_16();

int
funct_group22_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_16();
  return side_effect;
}

int
funct_group22_17();

int
funct_group22_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_17();
  return side_effect;
}

int
funct_group22_18();

int
funct_group22_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_18();
  return side_effect;
}

int
funct_group22_19();

int
funct_group22_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_19();
  return side_effect;
}

int
funct_group22_20();

int
funct_group22_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_20();
  return side_effect;
}

int
funct_group22_21();

int
funct_group22_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_21();
  return side_effect;
}

int
funct_group22_22();

int
funct_group22_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_22();
  return side_effect;
}

int
funct_group22_23();

int
funct_group22_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group22_23();
  return side_effect;
}

int
funct_group22_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group23_1();

int
funct_group23_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_1();
  return side_effect;
}

int
funct_group23_2();

int
funct_group23_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_2();
  return side_effect;
}

int
funct_group23_3();

int
funct_group23_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_3();
  return side_effect;
}

int
funct_group23_4();

int
funct_group23_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_4();
  return side_effect;
}

int
funct_group23_5();

int
funct_group23_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_5();
  return side_effect;
}

int
funct_group23_6();

int
funct_group23_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_6();
  return side_effect;
}

int
funct_group23_7();

int
funct_group23_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_7();
  return side_effect;
}

int
funct_group23_8();

int
funct_group23_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_8();
  return side_effect;
}

int
funct_group23_9();

int
funct_group23_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_9();
  return side_effect;
}

int
funct_group23_10();

int
funct_group23_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_10();
  return side_effect;
}

int
funct_group23_11();

int
funct_group23_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_11();
  return side_effect;
}

int
funct_group23_12();

int
funct_group23_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_12();
  return side_effect;
}

int
funct_group23_13();

int
funct_group23_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_13();
  return side_effect;
}

int
funct_group23_14();

int
funct_group23_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_14();
  return side_effect;
}

int
funct_group23_15();

int
funct_group23_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_15();
  return side_effect;
}

int
funct_group23_16();

int
funct_group23_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_16();
  return side_effect;
}

int
funct_group23_17();

int
funct_group23_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_17();
  return side_effect;
}

int
funct_group23_18();

int
funct_group23_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_18();
  return side_effect;
}

int
funct_group23_19();

int
funct_group23_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_19();
  return side_effect;
}

int
funct_group23_20();

int
funct_group23_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_20();
  return side_effect;
}

int
funct_group23_21();

int
funct_group23_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_21();
  return side_effect;
}

int
funct_group23_22();

int
funct_group23_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_22();
  return side_effect;
}

int
funct_group23_23();

int
funct_group23_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_23();
  return side_effect;
}

int
funct_group23_24();

int
funct_group23_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_24();
  return side_effect;
}

int
funct_group23_25();

int
funct_group23_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_25();
  return side_effect;
}

int
funct_group23_26();

int
funct_group23_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_26();
  return side_effect;
}

int
funct_group23_27();

int
funct_group23_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_27();
  return side_effect;
}

int
funct_group23_28();

int
funct_group23_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_28();
  return side_effect;
}

int
funct_group23_29();

int
funct_group23_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_29();
  return side_effect;
}

int
funct_group23_30();

int
funct_group23_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_30();
  return side_effect;
}

int
funct_group23_31();

int
funct_group23_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_31();
  return side_effect;
}

int
funct_group23_32();

int
funct_group23_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_32();
  return side_effect;
}

int
funct_group23_33();

int
funct_group23_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_33();
  return side_effect;
}

int
funct_group23_34();

int
funct_group23_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_34();
  return side_effect;
}

int
funct_group23_35();

int
funct_group23_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_35();
  return side_effect;
}

int
funct_group23_36();

int
funct_group23_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_36();
  return side_effect;
}

int
funct_group23_37();

int
funct_group23_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_37();
  return side_effect;
}

int
funct_group23_38();

int
funct_group23_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_38();
  return side_effect;
}

int
funct_group23_39();

int
funct_group23_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_39();
  return side_effect;
}

int
funct_group23_40();

int
funct_group23_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_40();
  return side_effect;
}

int
funct_group23_41();

int
funct_group23_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_41();
  return side_effect;
}

int
funct_group23_42();

int
funct_group23_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_42();
  return side_effect;
}

int
funct_group23_43();

int
funct_group23_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_43();
  return side_effect;
}

int
funct_group23_44();

int
funct_group23_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_44();
  return side_effect;
}

int
funct_group23_45();

int
funct_group23_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_45();
  return side_effect;
}

int
funct_group23_46();

int
funct_group23_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_46();
  return side_effect;
}

int
funct_group23_47();

int
funct_group23_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group23_47();
  return side_effect;
}

int
funct_group23_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}

int
funct_group24_1();

int
funct_group24_0()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_1();
  return side_effect;
}

int
funct_group24_2();

int
funct_group24_1()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_2();
  return side_effect;
}

int
funct_group24_3();

int
funct_group24_2()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_3();
  return side_effect;
}

int
funct_group24_4();

int
funct_group24_3()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_4();
  return side_effect;
}

int
funct_group24_5();

int
funct_group24_4()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_5();
  return side_effect;
}

int
funct_group24_6();

int
funct_group24_5()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_6();
  return side_effect;
}

int
funct_group24_7();

int
funct_group24_6()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_7();
  return side_effect;
}

int
funct_group24_8();

int
funct_group24_7()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_8();
  return side_effect;
}

int
funct_group24_9();

int
funct_group24_8()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_9();
  return side_effect;
}

int
funct_group24_10();

int
funct_group24_9()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_10();
  return side_effect;
}

int
funct_group24_11();

int
funct_group24_10()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_11();
  return side_effect;
}

int
funct_group24_12();

int
funct_group24_11()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_12();
  return side_effect;
}

int
funct_group24_13();

int
funct_group24_12()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_13();
  return side_effect;
}

int
funct_group24_14();

int
funct_group24_13()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_14();
  return side_effect;
}

int
funct_group24_15();

int
funct_group24_14()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_15();
  return side_effect;
}

int
funct_group24_16();

int
funct_group24_15()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_16();
  return side_effect;
}

int
funct_group24_17();

int
funct_group24_16()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_17();
  return side_effect;
}

int
funct_group24_18();

int
funct_group24_17()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_18();
  return side_effect;
}

int
funct_group24_19();

int
funct_group24_18()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_19();
  return side_effect;
}

int
funct_group24_20();

int
funct_group24_19()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_20();
  return side_effect;
}

int
funct_group24_21();

int
funct_group24_20()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_21();
  return side_effect;
}

int
funct_group24_22();

int
funct_group24_21()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_22();
  return side_effect;
}

int
funct_group24_23();

int
funct_group24_22()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_23();
  return side_effect;
}

int
funct_group24_24();

int
funct_group24_23()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_24();
  return side_effect;
}

int
funct_group24_25();

int
funct_group24_24()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_25();
  return side_effect;
}

int
funct_group24_26();

int
funct_group24_25()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_26();
  return side_effect;
}

int
funct_group24_27();

int
funct_group24_26()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_27();
  return side_effect;
}

int
funct_group24_28();

int
funct_group24_27()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_28();
  return side_effect;
}

int
funct_group24_29();

int
funct_group24_28()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_29();
  return side_effect;
}

int
funct_group24_30();

int
funct_group24_29()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_30();
  return side_effect;
}

int
funct_group24_31();

int
funct_group24_30()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_31();
  return side_effect;
}

int
funct_group24_32();

int
funct_group24_31()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_32();
  return side_effect;
}

int
funct_group24_33();

int
funct_group24_32()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_33();
  return side_effect;
}

int
funct_group24_34();

int
funct_group24_33()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_34();
  return side_effect;
}

int
funct_group24_35();

int
funct_group24_34()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_35();
  return side_effect;
}

int
funct_group24_36();

int
funct_group24_35()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_36();
  return side_effect;
}

int
funct_group24_37();

int
funct_group24_36()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_37();
  return side_effect;
}

int
funct_group24_38();

int
funct_group24_37()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_38();
  return side_effect;
}

int
funct_group24_39();

int
funct_group24_38()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_39();
  return side_effect;
}

int
funct_group24_40();

int
funct_group24_39()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_40();
  return side_effect;
}

int
funct_group24_41();

int
funct_group24_40()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_41();
  return side_effect;
}

int
funct_group24_42();

int
funct_group24_41()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_42();
  return side_effect;
}

int
funct_group24_43();

int
funct_group24_42()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_43();
  return side_effect;
}

int
funct_group24_44();

int
funct_group24_43()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_44();
  return side_effect;
}

int
funct_group24_45();

int
funct_group24_44()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_45();
  return side_effect;
}

int
funct_group24_46();

int
funct_group24_45()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_46();
  return side_effect;
}

int
funct_group24_47();

int
funct_group24_46()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_47();
  return side_effect;
}

int
funct_group24_48();

int
funct_group24_47()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_48();
  return side_effect;
}

int
funct_group24_49();

int
funct_group24_48()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_49();
  return side_effect;
}

int
funct_group24_50();

int
funct_group24_49()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_50();
  return side_effect;
}

int
funct_group24_51();

int
funct_group24_50()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_51();
  return side_effect;
}

int
funct_group24_52();

int
funct_group24_51()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_52();
  return side_effect;
}

int
funct_group24_53();

int
funct_group24_52()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_53();
  return side_effect;
}

int
funct_group24_54();

int
funct_group24_53()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_54();
  return side_effect;
}

int
funct_group24_55();

int
funct_group24_54()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_55();
  return side_effect;
}

int
funct_group24_56();

int
funct_group24_55()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_56();
  return side_effect;
}

int
funct_group24_57();

int
funct_group24_56()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_57();
  return side_effect;
}

int
funct_group24_58();

int
funct_group24_57()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_58();
  return side_effect;
}

int
funct_group24_59();

int
funct_group24_58()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_59();
  return side_effect;
}

int
funct_group24_60();

int
funct_group24_59()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_60();
  return side_effect;
}

int
funct_group24_61();

int
funct_group24_60()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_61();
  return side_effect;
}

int
funct_group24_62();

int
funct_group24_61()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_62();
  return side_effect;
}

int
funct_group24_63();

int
funct_group24_62()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_63();
  return side_effect;
}

int
funct_group24_64();

int
funct_group24_63()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_64();
  return side_effect;
}

int
funct_group24_65();

int
funct_group24_64()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_65();
  return side_effect;
}

int
funct_group24_66();

int
funct_group24_65()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_66();
  return side_effect;
}

int
funct_group24_67();

int
funct_group24_66()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_67();
  return side_effect;
}

int
funct_group24_68();

int
funct_group24_67()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_68();
  return side_effect;
}

int
funct_group24_69();

int
funct_group24_68()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_69();
  return side_effect;
}

int
funct_group24_70();

int
funct_group24_69()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_70();
  return side_effect;
}

int
funct_group24_71();

int
funct_group24_70()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_71();
  return side_effect;
}

int
funct_group24_72();

int
funct_group24_71()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_72();
  return side_effect;
}

int
funct_group24_73();

int
funct_group24_72()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_73();
  return side_effect;
}

int
funct_group24_74();

int
funct_group24_73()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_74();
  return side_effect;
}

int
funct_group24_75();

int
funct_group24_74()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_75();
  return side_effect;
}

int
funct_group24_76();

int
funct_group24_75()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_76();
  return side_effect;
}

int
funct_group24_77();

int
funct_group24_76()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_77();
  return side_effect;
}

int
funct_group24_78();

int
funct_group24_77()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_78();
  return side_effect;
}

int
funct_group24_79();

int
funct_group24_78()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_79();
  return side_effect;
}

int
funct_group24_80();

int
funct_group24_79()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_80();
  return side_effect;
}

int
funct_group24_81();

int
funct_group24_80()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_81();
  return side_effect;
}

int
funct_group24_82();

int
funct_group24_81()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_82();
  return side_effect;
}

int
funct_group24_83();

int
funct_group24_82()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_83();
  return side_effect;
}

int
funct_group24_84();

int
funct_group24_83()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_84();
  return side_effect;
}

int
funct_group24_85();

int
funct_group24_84()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_85();
  return side_effect;
}

int
funct_group24_86();

int
funct_group24_85()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_86();
  return side_effect;
}

int
funct_group24_87();

int
funct_group24_86()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_87();
  return side_effect;
}

int
funct_group24_88();

int
funct_group24_87()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_88();
  return side_effect;
}

int
funct_group24_89();

int
funct_group24_88()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_89();
  return side_effect;
}

int
funct_group24_90();

int
funct_group24_89()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_90();
  return side_effect;
}

int
funct_group24_91();

int
funct_group24_90()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_91();
  return side_effect;
}

int
funct_group24_92();

int
funct_group24_91()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_92();
  return side_effect;
}

int
funct_group24_93();

int
funct_group24_92()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_93();
  return side_effect;
}

int
funct_group24_94();

int
funct_group24_93()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_94();
  return side_effect;
}

int
funct_group24_95();

int
funct_group24_94()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  side_effect = side_effect + funct_group24_95();
  return side_effect;
}

int
funct_group24_95()
{
  volatile static std::uint32_t inner_side_effect = 0;
  inner_side_effect = inner_side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();

  if (side_effect > 0) {
    start_cycles = uptime();
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  return side_effect;
}
