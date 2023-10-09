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

import argparse
from typing import List
from enum import Enum


_UNIVERSAL_START = """
    #include <array>
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <exception>
    #include <span>
    #include <string_view>

    volatile std::int32_t side_effect;
    """


class exception_class:
    def __init__(self, id: int, has_dtor: bool = True):
        self.has_dtor = has_dtor
        self._id = id

    @property
    def id(self):
        return self._id

    def generate(self):
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

        if self.has_dtor:
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


class exception_class_usage:
    def __init__(self, p_class: exception_class, p_trigger_count: int):
        self.m_class = p_class
        self.m_trigger_count = p_trigger_count

    def generate(self, p_instance: int):
        return 'class_{id} instance_{instance}(side_effect);\n'.format(
            id=self.m_class.id,
            instance=p_instance) + \
            'instance_{instance}.trigger();\n'.format(instance=p_instance) \
            * self.m_trigger_count


class call_position(Enum):
    TOP = 1
    MIDDLE = 2
    BOTTOM = 3


class exception_function:
    def __init__(self,
                 usages: List[exception_class_usage],
                 position: call_position):
        self.usages = usages
        self.position = position

    def generate(self, instance: int, group_id: int, is_terminal: bool = False):
        start = """
        int funct_{group}_{id}()
        {{
            side_effect = side_effect + 1;
        """.format(id=instance, group=group_id)

        if is_terminal:
            next_function_call = """
                if (side_effect > 0)
                {
                    throw my_error_t{ .data = { 0xDE, 0xAD } };
                }
                """
        else:
            start = 'int funct_{group}_{id}(); \n'.format(
                group=group_id, id=instance + 1) + start
            next_function_call = "funct_{group}_{id}();".format(
                group=group_id, id=instance + 1)

        if self.position == call_position.TOP:
            start = start + next_function_call

        body = []
        for index, usages in enumerate(self.usages):
            if (self.position == call_position.MIDDLE and
                    index == round(len(self.usages) / 2)):
                body.append(next_function_call)
            body.append(usages.generate(index))

        footer = """
        return side_effect;
        }
        """

        if self.position == call_position.BOTTOM:
            footer = next_function_call + footer

        return start + "\n".join(body) + footer


class exception_function_group:
    def __init__(self,
                 functions: List[exception_function]):
        self.functions = functions

    def forward_declare_start(self, group_id: int):
        return "int funct_{group}_0();".format(group=group_id)

    def call_start(self, group_id: int):
        return "funct_{group}_0();".format(group=group_id)

    def generate(self, group_id: int):
        list = []
        for index, funct in enumerate(self.functions):
            list.append(funct.generate(index, group_id,
                        index == len(self.functions) - 1))
        return '\n'.join(list)


class exception_application:
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
    }
    int start();
    int main()
    {
    volatile int return_code = 0;
    try {
        return_code = start();
    } catch (const my_error_t& p_error) {
        return_code = p_error.data[0];
    } catch (...) {
        return_code -1;
    }
    return return_code;
    }
    """

    def __init__(self,
                 error_type_size: int,
                 groups: List[exception_function_group],
                 exception_classes: List[exception_class]):
        self.error_type_size = error_type_size
        self.groups = groups
        self.exception_classes = exception_classes

    def create_start(self):
        start_template = """
        {forward_delcaration}
        int start() {{
            {body}
        }}
        """

        forwards = []
        calls = []

        for index, group in enumerate(self.groups):
            forwards.append(group.forward_declare_start(index))
            calls.append(group.call_start(index))

        return start_template.format(forward_delcaration="\n".join(forwards),
                                     body="\n".join(calls))

    def generate(self):
        global _UNIVERSAL_START
        error_type = """
        struct my_error_t
        {{
            std::array<std::uint8_t, {size}> data;
        }};
        """.format(size=self.error_type_size)
        source = [_UNIVERSAL_START, error_type, self._EXCEPTION_START]

        source.append(self.create_start())

        for classes in self.exception_classes:
            source.append(classes.generate())

        for index, function_group in enumerate(self.groups):
            source.append(function_group.generate(index))

        return "\n".join(source)


def exception_source():
    class_a = exception_class(0)
    class_b = exception_class(1)
    class_c = exception_class(2, False)

    usage1 = exception_class_usage(class_a, 2)
    usage2 = exception_class_usage(class_b, 1)
    usage3 = exception_class_usage(class_c, 3)

    function0 = exception_function([usage1, usage3], call_position.MIDDLE)
    function1 = exception_function([usage2, usage2, usage2], call_position.TOP)
    function2 = exception_function(
        [usage1, usage2, usage3, usage3], call_position.BOTTOM)
    function3 = exception_function(
        [usage2, usage2, usage2], call_position.BOTTOM)
    group0 = exception_function_group([function0, function1])
    group1 = exception_function_group(
        [function0, function1, function2, function3])

    return exception_application(error_type_size=4,
                                 groups=[group0, group0, group1, group1],
                                 exception_classes=[class_a, class_b, class_c]).generate()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()
    generate_parser = subparsers.add_parser('generate', help='a help')
    generate_parser.add_argument("-d", "--depth",
                                 help="The call depth before the error is triggered.",
                                 default=10,
                                 type=int)
    generate_parser.add_argument("-f", "--functions",
                                 help="The number of additional functions to generate and run through in the code including the depth. So with a depth of 5 and functions 10, the total functions in the code besides main is 15. If this value is less than depth then the number of functions is equal to the depth.",
                                 default=15,
                                 type=int)
    generate_parser.add_argument("-r", "--randomize",
                                 help="Max depth of functions",
                                 default=False,
                                 type=bool)
    args = parser.parse_args()
    print(exception_source())
