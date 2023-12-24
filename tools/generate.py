#!/usr/bin/python
#
# Copyright 2023 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from typing import List
from enum import Enum
from pathlib import Path


_UNIVERSAL_START = """
    #include <array>
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <exception>
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
    """


class gen_class:
    def __init__(self, id: int, nontrivial_dtor: bool = True):
        self._id = id
        self.nontrivial_dtor = nontrivial_dtor

    @property
    def id(self):
        return self._id

    @property
    def is_nontrivial(self):
        return self.nontrivial_dtor

    def generate_except(self):
        start = "class class_{id} {{ public:".format(id=self._id)
        ctor = """
        class_{id}(std::int32_t p_channel)
            : m_channel(p_channel)
        {{
            if (m_channel >= 1'000'000'000) {{
                throw my_error_t{{ .data = {{ 0x55, 0xAA, 0x33, 0x44 }} }};
            }}
            side_effect = side_effect + 1;
        }}
        """.format(id=self._id)

        copy_and_move_ctors = """
        class_{id}(class_{id}&) = delete;
        class_{id}& operator=(class_{id}&) = delete;
        class_{id}(class_{id}&&) noexcept = default;
        class_{id}& operator=(class_{id}&&) noexcept = default;
        """.format(id=self._id)

        if self.nontrivial_dtor:
            dtor = """~class_{id}()
            {{
                side_effect = side_effect & ~(1 << m_channel);
            }}
            """.format(id=self._id)
        else:
            dtor = "~class_{id}() = default;".format(id=self._id)

        class_function = """
        void trigger()
        {
            if (m_channel >= 1'000'000'000) {
                throw my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } };
            }
            side_effect = side_effect + 1;
        }
        """

        footer = """
        private:
            std::int32_t m_channel = 0;
        }};
        """.format(id=self._id)

        return start + ctor + copy_and_move_ctors + dtor + class_function + \
            footer

    def generate_result(self):
        start = "class class_{id} {{ public:".format(id=self._id)
        factory = """
        static tl::expected<class_{id}, my_error_t> make(std::int32_t p_channel)
        {{
            if (p_channel >= 1'000'000'000) {{
                return tl::unexpected(
                    my_error_t{{ .data = {{ 0x55, 0xAA, 0x33, 0x44 }} }}
                );
            }}
            side_effect = side_effect + 1;
            return class_{id}(p_channel);
        }}
        """.format(id=self._id)

        copy_and_move_ctors = """
        class_{id}(class_{id}&) = delete;
        class_{id}& operator=(class_{id}&) = delete;
        class_{id}(class_{id}&&) noexcept = default;
        class_{id}& operator=(class_{id}&&) noexcept = default;
        """.format(id=self._id)

        if self.nontrivial_dtor:
            dtor = """~class_{id}()
            {{
                side_effect = side_effect & ~(1 << m_channel);
            }}
            """.format(id=self._id)
        else:
            dtor = "~class_{id}() = default;".format(id=self._id)

        class_function = """
        tl::expected<void, my_error_t> trigger()
        {
            if (m_channel >= 1'000'000'000) {
                return tl::unexpected(
                    my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } }
                );
            }
            side_effect = side_effect + 1;

            return {};
        }
        """

        ctor = """
        private:
        class_{id}(std::int32_t p_channel)
            : m_channel(p_channel)
        {{
        }}
        """.format(id=self._id)

        footer = """
            std::int32_t m_channel = 0;
        }};
        """.format(id=self._id)

        return start + factory + copy_and_move_ctors + dtor + class_function + \
            ctor + footer


class gen_class_usage:
    def __init__(self, p_class: gen_class, p_trigger_count: int):
        self.m_class = p_class
        self.m_trigger_count = p_trigger_count

    @property
    def is_nontrivial(self):
        return self.m_class.is_nontrivial

    def generate_except(self, p_instance: int):
        return 'class_{id} instance_{instance}(side_effect);\n'.format(
            id=self.m_class.id,
            instance=p_instance) + \
            'instance_{instance}.trigger();\n'.format(instance=p_instance) \
            * self.m_trigger_count

    def generate_result(self, p_instance: int):
        create = """
        auto instance_{instance} = class_{id}::make(side_effect);
        if (!instance_{instance}) {{
            return tl::unexpected(instance_{instance}.error());
        }}
        """.format(
            id=self.m_class.id,
            instance=p_instance)

        # NOTE: I scoped this so I wouldn't have to come up with random variable
        # names for each result object
        call = """{{
        auto scoped_result = instance_{instance}.value().trigger();
        if (!scoped_result) {{
            return tl::unexpected(scoped_result.error());
        }}
        }}""".format(instance=p_instance) * self.m_trigger_count

        return create + call


class call_position(Enum):
    TOP = 1
    MIDDLE = 2
    BOTTOM = 3


class gen_function:
    def __init__(self,
                 usages: List[gen_class_usage],
                 position: call_position):
        self.usages = usages
        self.position = position

    def generate_except(self,
                        instance: int,
                        group_id: int,
                        is_terminal: bool = False):
        section_marker = ""

        for usage in self.usages:
            if not usage.is_nontrivial:
                section_marker = '[[gnu::section(".trivial_handle")]]'

        start = """
        {section_marker} int funct_group{group}_{id}()
        {{
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        """.format(section_marker=section_marker, id=instance, group=group_id)

        if is_terminal:
            next_function_call = """
                if (side_effect > 0)
                {
                    start_cycles = uptime();
                    throw my_error_t{ .data = { 0xDE, 0xAD } };
                }
                """
        else:
            start = 'int funct_group{group}_{id}(); \n'.format(
                group=group_id, id=instance + 1) + start
            next_function_call = \
                "side_effect = side_effect + funct_group{group}_{id}();".format(
                    group=group_id, id=instance + 1)

        if self.position == call_position.TOP:
            start = start + next_function_call

        body = []
        for index, usages in enumerate(self.usages):
            if (self.position == call_position.MIDDLE and
                    index == round(len(self.usages) / 2)):
                body.append(next_function_call)
            body.append(usages.generate_except(index))

        footer = """
        return side_effect;
        }
        """

        if self.position == call_position.BOTTOM:
            footer = next_function_call + footer

        return start + "\n".join(body) + footer

    def generate_result(self,
                        instance: int,
                        group_id: int,
                        is_terminal: bool = False):
        start = """
        tl::expected<int, my_error_t> funct_group{group}_{id}()
        {{
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        """.format(id=instance, group=group_id)

        if is_terminal:
            next_function_call = """
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                """
        else:
            start = """
            tl::expected<int, my_error_t> funct_group{group}_{id}(); \n
            """.format(
                group=group_id, id=instance + 1) + start
            next_function_call = """
                if(auto result = funct_group{group}_{id}(); !result) {{
                    return tl::unexpected(result.error());
                }} else {{
                    side_effect = side_effect + result.value();
                }}""".format(
                group=group_id, id=instance + 1)

        if self.position == call_position.TOP:
            start = start + next_function_call

        body = []
        for index, usages in enumerate(self.usages):
            if (self.position == call_position.MIDDLE and
                    index == round(len(self.usages) / 2)):
                body.append(next_function_call)
            body.append(usages.generate_result(index))

        footer = """
        return side_effect;
        }
        """

        if self.position == call_position.BOTTOM:
            footer = next_function_call + footer

        return start + "\n".join(body) + footer


class gen_function_group:
    def __init__(self,
                 functions: List[gen_function]):
        self.functions = functions

    def except_forward_declare_start(self, group_id: int):
        return "int funct_group{group}_0();".format(group=group_id)

    def except_call_start(self, group_id: int):
        return "funct_group{group}_0();".format(group=group_id)

    def except_call_start_with_time_check(self, group_id: int):
        return """
        try {{
            start_cycles = uptime();
            funct_group{group}_0();
        }} catch ([[maybe_unused]] const my_error_t& p_error) {{
            end_cycles = uptime();
            cycle_map[{group}] = end_cycles - start_cycles;
        }}
        """.format(group=group_id)

    def except_call_function_signature(self, group_id: int):
        return "funct_group{group}_0".format(group=group_id)

    def result_forward_declare_start(self, group_id: int):
        return "tl::expected<int, my_error_t> funct_group{group}_0();".format(group=group_id)

    def result_call_start(self, group_id: int):
        return """
        if (auto result = funct_group{group}_0(); !result) {{
            return tl::unexpected(result.error());
        }}
        """.format(group=group_id)

    def result_call_start_with_time_check(self, group_id: int):
        return """
        start_cycles = uptime();
        if (auto result = funct_group{group}_0(); !result) {{
            end_cycles = uptime();
            cycle_map[{group}] = end_cycles - start_cycles;
        }}
        """.format(group=group_id)

    def generate_except(self, group_id: int):
        list = []
        for index, funct in enumerate(self.functions):
            list.append(funct.generate_except(index, group_id,
                        index == len(self.functions) - 1))
        return '\n'.join(list)

    def generate_result(self, group_id: int):
        list = []
        for index, funct in enumerate(self.functions):
            list.append(funct.generate_result(index, group_id,
                        index == len(self.functions) - 1))
        return '\n'.join(list)


class gen_exception_performance_application:
    _EXCEPTION_START = """
    [[noreturn]] void terminate() noexcept
    {
    while (true) {
        continue;
    }
    }

    namespace __cxxabiv1 {  // NOLINT
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
    void __wrap___cxa_call_unexpected(void*) // NOLINT
    {
        std::terminate();
    }

    using _uw = std::uint32_t;

    typedef struct __EIT_entry
    {
        _uw fnoffset;
        _uw content;
    } __EIT_entry;

    static inline _uw selfrel_offset31(const _uw* p)
    {
        _uw offset;

        offset = *p;
        /* Sign extend to 32 bits.  */
        if (offset & (1 << 30))
        offset |= 1u << 31;
        else
        offset &= ~(1u << 31);

        return offset + (_uw)p;
    }

    extern std::uint32_t __trivial_handle_start;
    extern std::uint32_t __trivial_handle_end;

    // NOLINTNEXTLINE
    const void* search_EIT_table(const __EIT_entry* table,
                                int nrec, // NOLINT
                                _uw return_address)
    {
        _uw next_fn;
        _uw this_fn;
        int n, left, right;

        std::uint32_t* start = &__trivial_handle_start;
        std::uint32_t* end = &__trivial_handle_end;
        std::uint32_t* check = reinterpret_cast<std::uint32_t*>(return_address);
        bool is_trivial_function = (start <= check && check <= end);

        if (is_trivial_function) {
            return nullptr;
        }

        if (nrec == 0)
        return nullptr;

        left = 0;
        right = nrec - 1;

        while (true) {
        n = (left + right) / 2;
        this_fn = selfrel_offset31(&table[n].fnoffset);
        if (n != nrec - 1)
            next_fn = selfrel_offset31(&table[n + 1].fnoffset) - 1;
        else
            next_fn = (_uw)0 - 1;

        if (return_address < this_fn) {
            if (n == left)
            return nullptr;
            right = n - 1;
        } else if (return_address <= next_fn)
            return &table[n];
        else
            left = n + 1;
        }
    }
    }
    int start();

    int main()
    {
        dwt_counter_enable();
        volatile int return_code = 0;
        try {
            return_code = start();
        } catch (...) {
            return_code = -1;
        }
        std::terminate();
        return return_code;
    }
    """

    def __init__(self,
                 error_type_size: int,
                 groups: List[gen_function_group],
                 classes: List[gen_class]):
        self.error_type_size = error_type_size
        self.groups = groups
        self.classes = classes

    def create_start(self):
        start_template = """
        {forward_declarations}

        using signature = int(void);

        std::array<signature*, {function_count}> functions = {{
            {function_list}
        }};
        int start() {{
            cycle_map.fill(0);
            std::uint32_t index = 0;
            for (auto& funct : functions) {{
                try {{
                    start_cycles = uptime();
                    funct();
                }} catch ([[maybe_unused]] const my_error_t& p_error) {{
                    end_cycles = uptime();
                    cycle_map[index++] = end_cycles - start_cycles;
                }}
            }}
            return side_effect;
        }}
        """

        forwards = []
        calls = []

        for index, group in enumerate(self.groups):
            forwards.append(group.except_forward_declare_start(index))
            calls.append(group.except_call_function_signature(index))

        return start_template.format(forward_declarations="\n".join(forwards),
                                     body="\n".join(calls),
                                     function_count=len(calls),
                                     function_list=",".join(calls))

    def generate(self):
        global _UNIVERSAL_START
        error_type = """
        struct my_error_t
        {{
            std::array<std::uint8_t, {size}> data;
        }};
        """.format(size=self.error_type_size)
        cycle_map = """
        std::array<std::uint64_t, {groups}> cycle_map{{}};
        """.format(groups=len(self.groups))
        source = [_UNIVERSAL_START, error_type,
                  self._EXCEPTION_START, cycle_map]

        source.append(self.create_start())

        for classes in self.classes:
            source.append(classes.generate_except())

        for index, function_group in enumerate(self.groups):
            source.append(function_group.generate_except(index))

        return "\n".join(source)


class gen_result_performance_application:
    _EXCEPTION_START = """
    [[noreturn]] void
    halt()
    {
        while (true) {
            continue;
        }
    }
    tl::expected<int, my_error_t> start();
    int main()
    {
        dwt_counter_enable();
        volatile int return_code = 0;
        auto result = start();
        if (!result) {
            return_code = result.error().data[0];
        } else {
            return_code = result.value();
        }
        halt();
        return return_code;
    }
    """

    def __init__(self,
                 error_type_size: int,
                 groups: List[gen_function_group],
                 classes: List[gen_class]):
        self.error_type_size = error_type_size
        self.groups = groups
        self.classes = classes

    def create_start(self):
        start_template = """
        {forward_declarations}
        tl::expected<int, my_error_t> start() {{
            {body}
            return side_effect;
        }}
        """

        forwards = []
        calls = []

        for index, group in enumerate(self.groups):
            forwards.append(group.result_forward_declare_start(index))
            calls.append(group.result_call_start_with_time_check(index))

        return start_template.format(forward_declarations="\n".join(forwards),
                                     body="\n".join(calls))

    def generate(self):
        global _UNIVERSAL_START
        error_type = """
        #include <tl/expected.hpp>
        struct my_error_t
        {{
            std::array<std::uint8_t, {size}> data;
        }};
        """.format(size=self.error_type_size)
        cycle_map = """
        std::array<std::uint64_t, {groups}> cycle_map{{}};
        """.format(groups=len(self.groups))
        source = [_UNIVERSAL_START, error_type,
                  self._EXCEPTION_START, cycle_map]

        source.append(self.create_start())

        for classes in self.classes:
            source.append(classes.generate_result())

        for index, function_group in enumerate(self.groups):
            source.append(function_group.generate_result(index))

        return "\n".join(source)


def generate_app():
    trivial_class = gen_class(id=0, nontrivial_dtor=False)
    nontrivial_class = gen_class(id=1, nontrivial_dtor=True)

    call_depth_list = [6, 12, 24, 48, 96]
    dtor_percentage_in_stack = [0.00, 0.10, 0.25, 0.50, 1.00]

    group_list = []
    group_index = 0

    print("group_index,depth,ratio")

    for dtor_ratio in dtor_percentage_in_stack:
        for call_depth in call_depth_list:
            function_list = []
            for function_index in range(call_depth):
                function_index = function_index + 1
                use_nontrivial_dtor = (
                    (dtor_ratio * function_index).is_integer() and
                    dtor_ratio != 0.0)

                if use_nontrivial_dtor:
                    class_usage_list = [gen_class_usage(nontrivial_class, 1)]
                else:
                    class_usage_list = [gen_class_usage(trivial_class, 1)]

                function_list.append(gen_function(
                    usages=class_usage_list, position=call_position.BOTTOM))
            print("{},{},{}".format(group_index, call_depth, dtor_ratio))
            group_list.append(gen_function_group(function_list))
            group_index = group_index + 1

    return (group_list, [trivial_class, nontrivial_class])


def generate():
    app = generate_app()
    except_source = gen_exception_performance_application(error_type_size=4,
                                                          groups=app[0],
                                                          classes=app[1]).generate()
    Path(f"except.cpp").write_text(except_source)
    result_file_source = gen_result_performance_application(error_type_size=4,
                                                            groups=app[0],
                                                            classes=app[1]).generate()
    Path(f"result.cpp").write_text(result_file_source)


if __name__ == "__main__":
    generate()
