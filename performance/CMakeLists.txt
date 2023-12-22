
cmake_minimum_required(VERSION 3.20)

project(exception_v_result LANGUAGES CXX)

find_package(tl-expected REQUIRED)
find_package(prebuilt-picolibc REQUIRED)

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
    -fexceptions
  )
  target_include_directories(${name}.elf PUBLIC .)
  target_compile_features(${name}.elf PRIVATE cxx_std_20)
  target_link_options(${name}.elf PRIVATE
    -Wl,--wrap=__cxa_allocate_exception
    -Wl,--wrap=__cxa_free_exception
    -Wl,--wrap=__cxa_call_unexpected
    -Wl,--wrap=search_EIT_table
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
  target_link_libraries(${name}.elf PRIVATE picolibc)
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
    -fno-exceptions
  )
  target_include_directories(${name}.elf PUBLIC .)
  target_compile_features(${name}.elf PRIVATE cxx_std_20)
  target_link_options(${name}.elf PRIVATE
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

new_exception_source(except)
new_exception_source(except_experimental)
new_exception_source(except_experimental2)
# new_result_source(result)
