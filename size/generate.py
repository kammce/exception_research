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
import random
import os
from pathlib import Path
import shutil


"""
TODO:
    1. Enable usage of rethrowing catch statements throughout function calls
"""

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


class gen_class:
    def __init__(self, id: int, has_dtor: bool = True):
        self._id = id
        self.has_dtor = has_dtor

    @property
    def id(self):
        return self._id

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

        if self.has_dtor:
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
        start = """
        int funct_group{group}_{id}()
        {{
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        """.format(id=instance, group=group_id)

        if is_terminal:
            next_function_call = """
                if (side_effect > 0)
                {
                    throw my_error_t{ .data = { 0xDE, 0xAD } };
                }
                """
        else:
            start = 'int funct_group{group}_{id}(); \n'.format(
                group=group_id, id=instance + 1) + start
            next_function_call = "funct_group{group}_{id}();".format(
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

    def result_forward_declare_start(self, group_id: int):
        return "tl::expected<int, my_error_t> funct_group{group}_0();".format(group=group_id)

    def result_call_start(self, group_id: int):
        return """
        if (auto result = funct_group{group}_0(); !result) {{
            return tl::unexpected(result.error());
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


class gen_exception_application:
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
        return_code = -1;
    }
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
        {forward_delcaration}
        int start() {{
            {body}
            return side_effect;
        }}
        """

        forwards = []
        calls = []

        for index, group in enumerate(self.groups):
            forwards.append(group.except_forward_declare_start(index))
            calls.append(group.except_call_start(index))

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

        for classes in self.classes:
            source.append(classes.generate_except())

        for index, function_group in enumerate(self.groups):
            source.append(function_group.generate_except(index))

        return "\n".join(source)


class gen_result_application:
    _EXCEPTION_START = """
    tl::expected<int, my_error_t> start();
    int main()
    {
        volatile int return_code = 0;
        auto result = start();
        if (!result) {
            return_code = result.error().data[0];
        } else {
            return_code = result.value();
        }
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
        {forward_delcaration}
        tl::expected<int, my_error_t> start() {{
            {body}
            return side_effect;
        }}
        """

        forwards = []
        calls = []

        for index, group in enumerate(self.groups):
            forwards.append(group.result_forward_declare_start(index))
            calls.append(group.result_call_start(index))

        return start_template.format(forward_delcaration="\n".join(forwards),
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
        source = [_UNIVERSAL_START, error_type, self._EXCEPTION_START]

        source.append(self.create_start())

        for classes in self.classes:
            source.append(classes.generate_result())

        for index, function_group in enumerate(self.groups):
            source.append(function_group.generate_result(index))

        return "\n".join(source)


def demo_source_generation():
    class_a = gen_class()
    class_b = gen_class()
    class_c = gen_class(False)

    usage1 = gen_class_usage(class_a, 2)
    usage2 = gen_class_usage(class_b, 1)
    usage3 = gen_class_usage(class_c, 3)

    function0 = gen_function([usage1, usage3], call_position.MIDDLE)
    function1 = gen_function([usage2, usage2, usage2], call_position.TOP)
    function2 = gen_function(
        [usage1, usage2, usage3, usage3], call_position.BOTTOM)
    function3 = gen_function(
        [usage2, usage2, usage2], call_position.BOTTOM)
    group0 = gen_function_group([function0, function1])
    group1 = gen_function_group(
        [function0, function1, function2, function3])

    return gen_exception_application(error_type_size=4,
                                     groups=[group0, group0, group1, group1],
                                     classes=[class_a, class_b, class_c]).generate_except()


def generate_random_app(rng: random.Random, error_size_upper_bounds: int = 128):
    number_of_classes = rng.randint(1, 50)
    number_of_functions = rng.randint(1, 25)
    number_of_groups = rng.randint(1, 25)
    error_type_size = rng.randint(4, error_size_upper_bounds)

    class_list = []
    class_usage_list = []
    function_list = []
    group_list = []

    for i in range(number_of_classes):
        has_dtor = rng.randint(0, 1)
        class_list.append(gen_class(id=i, has_dtor=bool(has_dtor)))

    for i in range(number_of_classes):
        usages = rng.randint(0, 5)
        class_usage_list.append(gen_class_usage(class_list[i], usages))

    for i in range(number_of_functions):
        sample_size = rng.randint(0, number_of_classes)
        # position = rng.choice(list(call_position))
        function_list.append(gen_function(usages=rng.sample(
            class_usage_list, sample_size), position=call_position.BOTTOM))

    for i in range(number_of_groups):
        group_list.append(gen_function_group(function_list))

    return (error_type_size, group_list, class_list)


def randomize_suite(rng: random.Random,
                    number_of_files: int = 20,
                    error_size_upper_bounds: int = 128):
    cmake_header = """
cmake_minimum_required(VERSION 3.20)

project(exception_v_result VERSION 0.0.1 LANGUAGES CXX)

find_package(tl-expected REQUIRED)

macro(new_exception_source name)
    add_executable(${name}.elf ${name}.cpp)
    target_compile_options(${name}.elf PRIVATE
        -g
        -Wall
        -Wextra
        -Wpedantic
        -fno-rtti
        -mthumb
        -ffunction-sections
        -fdata-sections
        -mfloat-abi=hard
        -mcpu=cortex-m4
        -fexceptions
    )
    target_include_directories(${name}.elf PUBLIC .)
    target_compile_features(${name}.elf PRIVATE cxx_std_20)
    target_link_options(${name}.elf PRIVATE
        -Wl,--wrap=__cxa_allocate_exception
        -Wl,--wrap=__cxa_free_exception
        -Wl,--wrap=__cxa_call_unexpected
        --specs=nosys.specs
        --specs=picolibc.specs
        -mfloat-abi=hard
        -mcpu=cortex-m4
        -mfpu=auto
        -fno-rtti
        -mthumb
        -ffunction-sections
        -fdata-sections
        -fexceptions
        -L${CMAKE_SOURCE_DIR}/
        -T${CMAKE_SOURCE_DIR}/linker.ld
    )
    libhal_post_build(${name}.elf)
    libhal_disassemble(${name}.elf)
endmacro()

macro(new_result_source name)
    add_executable(${name}.elf ${name}.cpp)
    target_compile_options(${name}.elf PRIVATE
        -g
        -Wall
        -Wextra
        -Wpedantic
        -fno-rtti
        -mthumb
        -ffunction-sections
        -fdata-sections
        -mfloat-abi=hard
        -mcpu=cortex-m4
        -fno-exceptions
    )
    target_include_directories(${name}.elf PUBLIC .)
    target_compile_features(${name}.elf PRIVATE cxx_std_20)
    target_link_options(${name}.elf PRIVATE
        --specs=nosys.specs
        --specs=picolibc.specs
        -mfloat-abi=hard
        -mcpu=cortex-m4
        -mfpu=auto
        -fno-rtti
        -mthumb
        -ffunction-sections
        -fdata-sections
        -fno-exceptions
        -L${CMAKE_SOURCE_DIR}/
        -T${CMAKE_SOURCE_DIR}/linker.ld
    )
    target_link_libraries(${name}.elf PRIVATE tl::expected)
    libhal_post_build(${name}.elf)
    libhal_disassemble(${name}.elf)
endmacro()
"""

    os.mkdir("test_suite/")
    os.mkdir("test_suite/third_party/")

    shutil.copy("resources/linker.ld", "test_suite/")
    shutil.copy("resources/conanfile.py", "test_suite/")
    shutil.copy("resources/baremetal.profile", "test_suite/")
    shutil.copy("resources/third_party/standard_arm.ld",
                "test_suite/third_party/")

    cmake_sources = []

    for i in range(number_of_files):
        app = generate_random_app(
            rng=rng, error_size_upper_bounds=error_size_upper_bounds)
        except_file_source = gen_exception_application(
            error_type_size=app[0],
            groups=app[1],
            classes=app[2]).generate()
        Path(f"test_suite/except_{i}.cpp").write_text(except_file_source)
        cmake_sources.append(f"new_exception_source(except_{i})")

        result_file_source = gen_result_application(*app).generate()
        Path(f"test_suite/result_{i}.cpp").write_text(result_file_source)
        cmake_sources.append(f"new_result_source(result_{i})")

    cmake_final = cmake_header + "\n".join(cmake_sources)
    Path("test_suite/CMakeLists.txt").write_text(cmake_final)


def randomize(args):
    rng = random.Random()
    rng.seed(0)
    print(f"sample_size = {args.sample_size}, bounds = {args.error_size}")
    randomize_suite(rng=rng,
                    number_of_files=args.sample_size,
                    error_size_upper_bounds=args.error_size)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()
    randomize_parser = subparsers.add_parser('randomize', help='a help')
    randomize_parser.add_argument("-d", "--depth",
                                  help="The call depth before the error is triggered.",
                                  default=10,
                                  type=int)
    randomize_parser.add_argument("-f", "--functions",
                                  help="The number of additional functions to generate and run through in the code including the depth. So with a depth of 5 and functions 10, the total functions in the code besides main is 15. If this value is less than depth then the number of functions is equal to the depth.",
                                  default=15,
                                  type=int)
    randomize_parser.add_argument("-s", "--sample_size",
                                  help="Number of files to generate",
                                  default=25,
                                  type=int)
    randomize_parser.add_argument("-e", "--error_size",
                                  help="Size, in bytes, of the error object. In randomized test suites, this will be the upper bounds.",
                                  default=128,
                                  type=int)
    randomize_parser.set_defaults(func=randomize)
    args = parser.parse_args()
    args.func(args)
