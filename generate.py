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
    def __init__(self, id: int, has_dtor: bool):
        self.id = id
        self.has_dtor = has_dtor

    @property
    def id(self):
        return self.id

    def generate(self):
        start = "class class_{id} {{ public:".format(id=self.id)
        ctor = """
        class_{id}(std::int32_t p_channel)
            : m_channel(p_channel)
        {{
            if (m_channel >= 1'000'000'000) {{
                throw my_error_t{{ .data = {{ 0x55, 0xAA, 0x33, 0x44 }} }};
            }}
            side_effect = side_effect + 1;
        }}
        """.format(id=self.id)

        copy_and_move_ctors = """
        class_{id}(class_{id}&) = delete;
        class_{id}& operator=(class_{id}&) = delete;
        class_{id}(class_{id}&&) noexcept = default;
        class_{id}& operator=(class_{id}&&) noexcept = default;
        """.format(id=self.id)

        if self.has_dtor:
            dtor = """~class_{id}()
            {{
                side_effect = side_effect & ~(1 << m_channel);
            }}
            """.format(id=self.id)
        else:
            dtor = "~class_{id}() = default;"

        class_function = """
        void class_function()
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
        };
        """.format(id=self.id)

        return start + ctor + copy_and_move_ctors + dtor + class_function + \
            footer


class exception_class_usage:
    def __init__(self, p_class: exception_class, p_trigger_count: int):
        self.m_class = p_class
        self.m_trigger_count = p_trigger_count

    def generate(self, p_instance: int):
        return 'class_{id} instance_{index}(side_effect);\n' + \
            'instance_{index}.trigger();\n'.format(id=p_instance) \
            * self._m_trigger_count


class call_position(Enum):
    TOP = 1
    MIDDLE = 2
    END = 3


class exception_function:
    def __init__(self,
                 id: int,
                 group: int,
                 exception_class_usage: List[exception_class_usage],
                 position: call_position):
        self.id = id
        self.group = group
        self.exception_class_usage = exception_class_usage
        self.position = position

    @property
    def id(self):
        return self.id

    def generate(self, is_terminal: bool):
        if is_terminal:
            next_function_call = ""
        else:
            next_function_call = "funct_{group}_{id}()\n".format(
                group=self.group, id=self.id + 1)

        start = """
        int funct_{group}_{id}()
        {{
            side_effect = side_effect + 1;
        """.format(id=self.id, group=self.group)

        if self.position == call_position.TOP:
            start = start + next_function_call

        body = []
        for index, usages in enumerate(self.exception_class_usage):
            if index == round(len(self.exception_class_usage)):
                body.append(next_function_call)
            body.append(usages.generate(index))

        footer = """
        return side_effect;
        }}
        """

        if self.position == call_position.TOP:
            footer = next_function_call + footer

        return start + "\n".join(body) + footer


class exception_application:
    _EXCEPTION_START = """
    [[noreturn]] void terminate() noexcept
    {
    while (true) {
        continue;
    }
    }

    namespace __cxxabiv1 {
    std::terminate_handler __terminate_handler = terminate;
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
    struct _reent* _impure_ptr = nullptr;
    int getpid()
    {
        return 1;
    }

    std::array<std::uint8_t, 1024> storage;
    std::span<std::uint8_t> storage_left(storage);
    void* __wrap___cxa_allocate_exception(unsigned int p_size)
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
    void __wrap___cxa_free_exception(void*)
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
                 filename: str,
                 error_type_size: int,
                 exception_function: List[exception_function],
                 exception_classes: List[exception_class]):
        self.filename = filename
        self.error_type_size = error_type_size
        self.exception_function = exception_function
        self.exception_classes = exception_classes

    @property
    def filename(self):
        return self.filename

    def generate(self):
        global _UNIVERSAL_START
        error_type = """
        struct my_error_t
        {
        std::array<std::uint8_t, {size}> data;
        }
        """.format(size=self.error_type_size)
        source = [_UNIVERSAL_START, error_type, self._EXCEPTION_START]

        for classes in self.exception_classes:
            source.append(classes.generate())

        for index, function in enumerate(self.exception_function):
            source.append(function.generate(
                index == len(self.exception_function) - 1))

        return "\n".join(source)


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

    class_a = exception_class(0, False)
    class_b = exception_class(1, False)
    class_c = exception_class(2, False)

    usage1 = exception_class_usage(class_a, 2)
    usage2 = exception_class_usage(class_b, 1)
    usage3 = exception_class_usage(class_c, 3)

    function0 = exception_function(0, 0, [usage1, usage3], call_position.MIDDLE)
    function1 = exception_function(
        1, 0, [usage2, usage2, usage2], call_position.TOP)

    app0 = exception_application(filename="test.cpp",
                                 error_type_size=4,
                                 exception_function=[function0, function1],
                                 exception_classes=[class_a, class_b, class_c])

    app0.generate()
