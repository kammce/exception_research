
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <span>
#include <string_view>

volatile std::int32_t side_effect;

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
}
int
start();
int
main()
{
  volatile int return_code = 0;
  try {
    return_code = start();
  } catch (const my_error_t& p_error) {
    return_code = p_error.data[0];
  } catch (...) {
    return_code - 1;
  }
  return return_code;
}

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
int
funct_group25_0();
int
start()
{
  funct_group0_0();
  funct_group1_0();
  funct_group2_0();
  funct_group3_0();
  funct_group4_0();
  funct_group5_0();
  funct_group6_0();
  funct_group7_0();
  funct_group8_0();
  funct_group9_0();
  funct_group10_0();
  funct_group11_0();
  funct_group12_0();
  funct_group13_0();
  funct_group14_0();
  funct_group15_0();
  funct_group16_0();
  funct_group17_0();
  funct_group18_0();
  funct_group19_0();
  funct_group20_0();
  funct_group21_0();
  funct_group22_0();
  funct_group23_0();
  funct_group24_0();
  funct_group25_0();
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

class class_2
{
public:
  class_2(std::int32_t p_channel)
    : m_channel(p_channel)
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

  class_2(class_2&) = delete;
  class_2& operator=(class_2&) = delete;
  class_2(class_2&&) noexcept = default;
  class_2& operator=(class_2&&) noexcept = default;
  ~class_2() { side_effect = side_effect & ~(1 << m_channel); }

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

class class_3
{
public:
  class_3(std::int32_t p_channel)
    : m_channel(p_channel)
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

  class_3(class_3&) = delete;
  class_3& operator=(class_3&) = delete;
  class_3(class_3&&) noexcept = default;
  class_3& operator=(class_3&&) noexcept = default;
  ~class_3() { side_effect = side_effect & ~(1 << m_channel); }

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

class class_4
{
public:
  class_4(std::int32_t p_channel)
    : m_channel(p_channel)
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

  class_4(class_4&) = delete;
  class_4& operator=(class_4&) = delete;
  class_4(class_4&&) noexcept = default;
  class_4& operator=(class_4&&) noexcept = default;
  ~class_4() { side_effect = side_effect & ~(1 << m_channel); }

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

class class_5
{
public:
  class_5(std::int32_t p_channel)
    : m_channel(p_channel)
  {
    if (m_channel >= 1'000'000'000) {
      throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
    }
    side_effect = side_effect + 1;
  }

  class_5(class_5&) = delete;
  class_5& operator=(class_5&) = delete;
  class_5(class_5&&) noexcept = default;
  class_5& operator=(class_5&&) noexcept = default;
  ~class_5() { side_effect = side_effect & ~(1 << m_channel); }

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

int
funct_group0_0()
{
  side_effect = side_effect + 1;
  funct_group0_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group0_2();

int
funct_group0_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group0_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group0_3();

int
funct_group0_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group0_3();
  return side_effect;
}

int
funct_group0_4();

int
funct_group0_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group0_4();
  return side_effect;
}

int
funct_group0_5();

int
funct_group0_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group0_5();
  return side_effect;
}

int
funct_group0_6();

int
funct_group0_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group0_7();

int
funct_group0_6()
{
  side_effect = side_effect + 1;
  funct_group0_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group0_8();

int
funct_group0_7()
{
  side_effect = side_effect + 1;
  funct_group0_8();
  return side_effect;
}

int
funct_group0_9();

int
funct_group0_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group0_9();
  return side_effect;
}

int
funct_group0_10();

int
funct_group0_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group0_10();
  return side_effect;
}

int
funct_group0_11();

int
funct_group0_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group0_12();

int
funct_group0_11()
{
  side_effect = side_effect + 1;
  funct_group0_12();
  return side_effect;
}

int
funct_group0_13();

int
funct_group0_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group0_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group0_14();

int
funct_group0_13()
{
  side_effect = side_effect + 1;
  funct_group0_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group0_15();

int
funct_group0_14()
{
  side_effect = side_effect + 1;
  funct_group0_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group0_16();

int
funct_group0_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group0_16();
  return side_effect;
}

int
funct_group0_17();

int
funct_group0_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group0_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group0_18();

int
funct_group0_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group0_18();
  return side_effect;
}

int
funct_group0_19();

int
funct_group0_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group0_19();
  return side_effect;
}

int
funct_group0_20();

int
funct_group0_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group0_21();

int
funct_group0_20()
{
  side_effect = side_effect + 1;
  funct_group0_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group0_22();

int
funct_group0_21()
{
  side_effect = side_effect + 1;
  funct_group0_22();
  return side_effect;
}

int
funct_group0_23();

int
funct_group0_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group0_23();
  return side_effect;
}

int
funct_group0_24();

int
funct_group0_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group0_24();
  return side_effect;
}

int
funct_group0_25();

int
funct_group0_24()
{
  side_effect = side_effect + 1;
  funct_group0_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group0_26();

int
funct_group0_25()
{
  side_effect = side_effect + 1;
  funct_group0_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group0_27();

int
funct_group0_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group0_28();

int
funct_group0_27()
{
  side_effect = side_effect + 1;
  funct_group0_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group0_29();

int
funct_group0_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group0_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group0_30();

int
funct_group0_29()
{
  side_effect = side_effect + 1;
  funct_group0_30();
  return side_effect;
}

int
funct_group0_31();

int
funct_group0_30()
{
  side_effect = side_effect + 1;
  funct_group0_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group0_32();

int
funct_group0_31()
{
  side_effect = side_effect + 1;
  funct_group0_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group0_33();

int
funct_group0_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group0_34();

int
funct_group0_33()
{
  side_effect = side_effect + 1;
  funct_group0_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group0_35();

int
funct_group0_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group0_36();

int
funct_group0_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group0_37();

int
funct_group0_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group0_37();
  return side_effect;
}

int
funct_group0_38();

int
funct_group0_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group0_38();
  return side_effect;
}

int
funct_group0_39();

int
funct_group0_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group0_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group0_40();

int
funct_group0_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group0_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group0_41();

int
funct_group0_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group0_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group0_42();

int
funct_group0_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group0_42();
  return side_effect;
}

int
funct_group0_43();

int
funct_group0_42()
{
  side_effect = side_effect + 1;
  funct_group0_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group0_44();

int
funct_group0_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group0_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group0_45();

int
funct_group0_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group0_46();

int
funct_group0_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group0_46();
  return side_effect;
}

int
funct_group0_47();

int
funct_group0_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group0_47();
  return side_effect;
}

int
funct_group0_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group1_1();

int
funct_group1_0()
{
  side_effect = side_effect + 1;
  funct_group1_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group1_2();

int
funct_group1_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group1_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group1_3();

int
funct_group1_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group1_3();
  return side_effect;
}

int
funct_group1_4();

int
funct_group1_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group1_4();
  return side_effect;
}

int
funct_group1_5();

int
funct_group1_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group1_5();
  return side_effect;
}

int
funct_group1_6();

int
funct_group1_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group1_7();

int
funct_group1_6()
{
  side_effect = side_effect + 1;
  funct_group1_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group1_8();

int
funct_group1_7()
{
  side_effect = side_effect + 1;
  funct_group1_8();
  return side_effect;
}

int
funct_group1_9();

int
funct_group1_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group1_9();
  return side_effect;
}

int
funct_group1_10();

int
funct_group1_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group1_10();
  return side_effect;
}

int
funct_group1_11();

int
funct_group1_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group1_12();

int
funct_group1_11()
{
  side_effect = side_effect + 1;
  funct_group1_12();
  return side_effect;
}

int
funct_group1_13();

int
funct_group1_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group1_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group1_14();

int
funct_group1_13()
{
  side_effect = side_effect + 1;
  funct_group1_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group1_15();

int
funct_group1_14()
{
  side_effect = side_effect + 1;
  funct_group1_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group1_16();

int
funct_group1_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group1_16();
  return side_effect;
}

int
funct_group1_17();

int
funct_group1_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group1_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group1_18();

int
funct_group1_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group1_18();
  return side_effect;
}

int
funct_group1_19();

int
funct_group1_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group1_19();
  return side_effect;
}

int
funct_group1_20();

int
funct_group1_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group1_21();

int
funct_group1_20()
{
  side_effect = side_effect + 1;
  funct_group1_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group1_22();

int
funct_group1_21()
{
  side_effect = side_effect + 1;
  funct_group1_22();
  return side_effect;
}

int
funct_group1_23();

int
funct_group1_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group1_23();
  return side_effect;
}

int
funct_group1_24();

int
funct_group1_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group1_24();
  return side_effect;
}

int
funct_group1_25();

int
funct_group1_24()
{
  side_effect = side_effect + 1;
  funct_group1_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group1_26();

int
funct_group1_25()
{
  side_effect = side_effect + 1;
  funct_group1_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group1_27();

int
funct_group1_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group1_28();

int
funct_group1_27()
{
  side_effect = side_effect + 1;
  funct_group1_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group1_29();

int
funct_group1_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group1_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group1_30();

int
funct_group1_29()
{
  side_effect = side_effect + 1;
  funct_group1_30();
  return side_effect;
}

int
funct_group1_31();

int
funct_group1_30()
{
  side_effect = side_effect + 1;
  funct_group1_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group1_32();

int
funct_group1_31()
{
  side_effect = side_effect + 1;
  funct_group1_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group1_33();

int
funct_group1_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group1_34();

int
funct_group1_33()
{
  side_effect = side_effect + 1;
  funct_group1_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group1_35();

int
funct_group1_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group1_36();

int
funct_group1_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group1_37();

int
funct_group1_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group1_37();
  return side_effect;
}

int
funct_group1_38();

int
funct_group1_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group1_38();
  return side_effect;
}

int
funct_group1_39();

int
funct_group1_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group1_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group1_40();

int
funct_group1_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group1_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group1_41();

int
funct_group1_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group1_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group1_42();

int
funct_group1_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group1_42();
  return side_effect;
}

int
funct_group1_43();

int
funct_group1_42()
{
  side_effect = side_effect + 1;
  funct_group1_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group1_44();

int
funct_group1_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group1_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group1_45();

int
funct_group1_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group1_46();

int
funct_group1_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group1_46();
  return side_effect;
}

int
funct_group1_47();

int
funct_group1_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group1_47();
  return side_effect;
}

int
funct_group1_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group2_1();

int
funct_group2_0()
{
  side_effect = side_effect + 1;
  funct_group2_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group2_2();

int
funct_group2_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group2_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group2_3();

int
funct_group2_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group2_3();
  return side_effect;
}

int
funct_group2_4();

int
funct_group2_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group2_4();
  return side_effect;
}

int
funct_group2_5();

int
funct_group2_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group2_5();
  return side_effect;
}

int
funct_group2_6();

int
funct_group2_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group2_7();

int
funct_group2_6()
{
  side_effect = side_effect + 1;
  funct_group2_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group2_8();

int
funct_group2_7()
{
  side_effect = side_effect + 1;
  funct_group2_8();
  return side_effect;
}

int
funct_group2_9();

int
funct_group2_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group2_9();
  return side_effect;
}

int
funct_group2_10();

int
funct_group2_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group2_10();
  return side_effect;
}

int
funct_group2_11();

int
funct_group2_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group2_12();

int
funct_group2_11()
{
  side_effect = side_effect + 1;
  funct_group2_12();
  return side_effect;
}

int
funct_group2_13();

int
funct_group2_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group2_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group2_14();

int
funct_group2_13()
{
  side_effect = side_effect + 1;
  funct_group2_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group2_15();

int
funct_group2_14()
{
  side_effect = side_effect + 1;
  funct_group2_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group2_16();

int
funct_group2_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group2_16();
  return side_effect;
}

int
funct_group2_17();

int
funct_group2_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group2_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group2_18();

int
funct_group2_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group2_18();
  return side_effect;
}

int
funct_group2_19();

int
funct_group2_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group2_19();
  return side_effect;
}

int
funct_group2_20();

int
funct_group2_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group2_21();

int
funct_group2_20()
{
  side_effect = side_effect + 1;
  funct_group2_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group2_22();

int
funct_group2_21()
{
  side_effect = side_effect + 1;
  funct_group2_22();
  return side_effect;
}

int
funct_group2_23();

int
funct_group2_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group2_23();
  return side_effect;
}

int
funct_group2_24();

int
funct_group2_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group2_24();
  return side_effect;
}

int
funct_group2_25();

int
funct_group2_24()
{
  side_effect = side_effect + 1;
  funct_group2_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group2_26();

int
funct_group2_25()
{
  side_effect = side_effect + 1;
  funct_group2_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group2_27();

int
funct_group2_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group2_28();

int
funct_group2_27()
{
  side_effect = side_effect + 1;
  funct_group2_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group2_29();

int
funct_group2_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group2_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group2_30();

int
funct_group2_29()
{
  side_effect = side_effect + 1;
  funct_group2_30();
  return side_effect;
}

int
funct_group2_31();

int
funct_group2_30()
{
  side_effect = side_effect + 1;
  funct_group2_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group2_32();

int
funct_group2_31()
{
  side_effect = side_effect + 1;
  funct_group2_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group2_33();

int
funct_group2_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group2_34();

int
funct_group2_33()
{
  side_effect = side_effect + 1;
  funct_group2_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group2_35();

int
funct_group2_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group2_36();

int
funct_group2_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group2_37();

int
funct_group2_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group2_37();
  return side_effect;
}

int
funct_group2_38();

int
funct_group2_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group2_38();
  return side_effect;
}

int
funct_group2_39();

int
funct_group2_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group2_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group2_40();

int
funct_group2_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group2_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group2_41();

int
funct_group2_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group2_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group2_42();

int
funct_group2_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group2_42();
  return side_effect;
}

int
funct_group2_43();

int
funct_group2_42()
{
  side_effect = side_effect + 1;
  funct_group2_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group2_44();

int
funct_group2_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group2_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group2_45();

int
funct_group2_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group2_46();

int
funct_group2_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group2_46();
  return side_effect;
}

int
funct_group2_47();

int
funct_group2_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group2_47();
  return side_effect;
}

int
funct_group2_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group3_1();

int
funct_group3_0()
{
  side_effect = side_effect + 1;
  funct_group3_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group3_2();

int
funct_group3_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group3_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group3_3();

int
funct_group3_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group3_3();
  return side_effect;
}

int
funct_group3_4();

int
funct_group3_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group3_4();
  return side_effect;
}

int
funct_group3_5();

int
funct_group3_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group3_5();
  return side_effect;
}

int
funct_group3_6();

int
funct_group3_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group3_7();

int
funct_group3_6()
{
  side_effect = side_effect + 1;
  funct_group3_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group3_8();

int
funct_group3_7()
{
  side_effect = side_effect + 1;
  funct_group3_8();
  return side_effect;
}

int
funct_group3_9();

int
funct_group3_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group3_9();
  return side_effect;
}

int
funct_group3_10();

int
funct_group3_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group3_10();
  return side_effect;
}

int
funct_group3_11();

int
funct_group3_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group3_12();

int
funct_group3_11()
{
  side_effect = side_effect + 1;
  funct_group3_12();
  return side_effect;
}

int
funct_group3_13();

int
funct_group3_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group3_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group3_14();

int
funct_group3_13()
{
  side_effect = side_effect + 1;
  funct_group3_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group3_15();

int
funct_group3_14()
{
  side_effect = side_effect + 1;
  funct_group3_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group3_16();

int
funct_group3_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group3_16();
  return side_effect;
}

int
funct_group3_17();

int
funct_group3_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group3_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group3_18();

int
funct_group3_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group3_18();
  return side_effect;
}

int
funct_group3_19();

int
funct_group3_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group3_19();
  return side_effect;
}

int
funct_group3_20();

int
funct_group3_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group3_21();

int
funct_group3_20()
{
  side_effect = side_effect + 1;
  funct_group3_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group3_22();

int
funct_group3_21()
{
  side_effect = side_effect + 1;
  funct_group3_22();
  return side_effect;
}

int
funct_group3_23();

int
funct_group3_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group3_23();
  return side_effect;
}

int
funct_group3_24();

int
funct_group3_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group3_24();
  return side_effect;
}

int
funct_group3_25();

int
funct_group3_24()
{
  side_effect = side_effect + 1;
  funct_group3_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group3_26();

int
funct_group3_25()
{
  side_effect = side_effect + 1;
  funct_group3_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group3_27();

int
funct_group3_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group3_28();

int
funct_group3_27()
{
  side_effect = side_effect + 1;
  funct_group3_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group3_29();

int
funct_group3_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group3_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group3_30();

int
funct_group3_29()
{
  side_effect = side_effect + 1;
  funct_group3_30();
  return side_effect;
}

int
funct_group3_31();

int
funct_group3_30()
{
  side_effect = side_effect + 1;
  funct_group3_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group3_32();

int
funct_group3_31()
{
  side_effect = side_effect + 1;
  funct_group3_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group3_33();

int
funct_group3_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group3_34();

int
funct_group3_33()
{
  side_effect = side_effect + 1;
  funct_group3_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group3_35();

int
funct_group3_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group3_36();

int
funct_group3_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group3_37();

int
funct_group3_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group3_37();
  return side_effect;
}

int
funct_group3_38();

int
funct_group3_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group3_38();
  return side_effect;
}

int
funct_group3_39();

int
funct_group3_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group3_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group3_40();

int
funct_group3_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group3_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group3_41();

int
funct_group3_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group3_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group3_42();

int
funct_group3_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group3_42();
  return side_effect;
}

int
funct_group3_43();

int
funct_group3_42()
{
  side_effect = side_effect + 1;
  funct_group3_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group3_44();

int
funct_group3_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group3_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group3_45();

int
funct_group3_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group3_46();

int
funct_group3_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group3_46();
  return side_effect;
}

int
funct_group3_47();

int
funct_group3_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group3_47();
  return side_effect;
}

int
funct_group3_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group4_1();

int
funct_group4_0()
{
  side_effect = side_effect + 1;
  funct_group4_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group4_2();

int
funct_group4_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group4_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group4_3();

int
funct_group4_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group4_3();
  return side_effect;
}

int
funct_group4_4();

int
funct_group4_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group4_4();
  return side_effect;
}

int
funct_group4_5();

int
funct_group4_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group4_5();
  return side_effect;
}

int
funct_group4_6();

int
funct_group4_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group4_7();

int
funct_group4_6()
{
  side_effect = side_effect + 1;
  funct_group4_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group4_8();

int
funct_group4_7()
{
  side_effect = side_effect + 1;
  funct_group4_8();
  return side_effect;
}

int
funct_group4_9();

int
funct_group4_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group4_9();
  return side_effect;
}

int
funct_group4_10();

int
funct_group4_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group4_10();
  return side_effect;
}

int
funct_group4_11();

int
funct_group4_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group4_12();

int
funct_group4_11()
{
  side_effect = side_effect + 1;
  funct_group4_12();
  return side_effect;
}

int
funct_group4_13();

int
funct_group4_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group4_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group4_14();

int
funct_group4_13()
{
  side_effect = side_effect + 1;
  funct_group4_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group4_15();

int
funct_group4_14()
{
  side_effect = side_effect + 1;
  funct_group4_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group4_16();

int
funct_group4_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group4_16();
  return side_effect;
}

int
funct_group4_17();

int
funct_group4_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group4_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group4_18();

int
funct_group4_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group4_18();
  return side_effect;
}

int
funct_group4_19();

int
funct_group4_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group4_19();
  return side_effect;
}

int
funct_group4_20();

int
funct_group4_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group4_21();

int
funct_group4_20()
{
  side_effect = side_effect + 1;
  funct_group4_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group4_22();

int
funct_group4_21()
{
  side_effect = side_effect + 1;
  funct_group4_22();
  return side_effect;
}

int
funct_group4_23();

int
funct_group4_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group4_23();
  return side_effect;
}

int
funct_group4_24();

int
funct_group4_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group4_24();
  return side_effect;
}

int
funct_group4_25();

int
funct_group4_24()
{
  side_effect = side_effect + 1;
  funct_group4_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group4_26();

int
funct_group4_25()
{
  side_effect = side_effect + 1;
  funct_group4_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group4_27();

int
funct_group4_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group4_28();

int
funct_group4_27()
{
  side_effect = side_effect + 1;
  funct_group4_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group4_29();

int
funct_group4_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group4_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group4_30();

int
funct_group4_29()
{
  side_effect = side_effect + 1;
  funct_group4_30();
  return side_effect;
}

int
funct_group4_31();

int
funct_group4_30()
{
  side_effect = side_effect + 1;
  funct_group4_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group4_32();

int
funct_group4_31()
{
  side_effect = side_effect + 1;
  funct_group4_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group4_33();

int
funct_group4_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group4_34();

int
funct_group4_33()
{
  side_effect = side_effect + 1;
  funct_group4_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group4_35();

int
funct_group4_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group4_36();

int
funct_group4_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group4_37();

int
funct_group4_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group4_37();
  return side_effect;
}

int
funct_group4_38();

int
funct_group4_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group4_38();
  return side_effect;
}

int
funct_group4_39();

int
funct_group4_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group4_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group4_40();

int
funct_group4_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group4_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group4_41();

int
funct_group4_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group4_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group4_42();

int
funct_group4_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group4_42();
  return side_effect;
}

int
funct_group4_43();

int
funct_group4_42()
{
  side_effect = side_effect + 1;
  funct_group4_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group4_44();

int
funct_group4_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group4_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group4_45();

int
funct_group4_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group4_46();

int
funct_group4_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group4_46();
  return side_effect;
}

int
funct_group4_47();

int
funct_group4_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group4_47();
  return side_effect;
}

int
funct_group4_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group5_1();

int
funct_group5_0()
{
  side_effect = side_effect + 1;
  funct_group5_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group5_2();

int
funct_group5_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group5_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group5_3();

int
funct_group5_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group5_3();
  return side_effect;
}

int
funct_group5_4();

int
funct_group5_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group5_4();
  return side_effect;
}

int
funct_group5_5();

int
funct_group5_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group5_5();
  return side_effect;
}

int
funct_group5_6();

int
funct_group5_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group5_7();

int
funct_group5_6()
{
  side_effect = side_effect + 1;
  funct_group5_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group5_8();

int
funct_group5_7()
{
  side_effect = side_effect + 1;
  funct_group5_8();
  return side_effect;
}

int
funct_group5_9();

int
funct_group5_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group5_9();
  return side_effect;
}

int
funct_group5_10();

int
funct_group5_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group5_10();
  return side_effect;
}

int
funct_group5_11();

int
funct_group5_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group5_12();

int
funct_group5_11()
{
  side_effect = side_effect + 1;
  funct_group5_12();
  return side_effect;
}

int
funct_group5_13();

int
funct_group5_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group5_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group5_14();

int
funct_group5_13()
{
  side_effect = side_effect + 1;
  funct_group5_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group5_15();

int
funct_group5_14()
{
  side_effect = side_effect + 1;
  funct_group5_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group5_16();

int
funct_group5_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group5_16();
  return side_effect;
}

int
funct_group5_17();

int
funct_group5_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group5_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group5_18();

int
funct_group5_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group5_18();
  return side_effect;
}

int
funct_group5_19();

int
funct_group5_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group5_19();
  return side_effect;
}

int
funct_group5_20();

int
funct_group5_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group5_21();

int
funct_group5_20()
{
  side_effect = side_effect + 1;
  funct_group5_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group5_22();

int
funct_group5_21()
{
  side_effect = side_effect + 1;
  funct_group5_22();
  return side_effect;
}

int
funct_group5_23();

int
funct_group5_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group5_23();
  return side_effect;
}

int
funct_group5_24();

int
funct_group5_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group5_24();
  return side_effect;
}

int
funct_group5_25();

int
funct_group5_24()
{
  side_effect = side_effect + 1;
  funct_group5_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group5_26();

int
funct_group5_25()
{
  side_effect = side_effect + 1;
  funct_group5_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group5_27();

int
funct_group5_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group5_28();

int
funct_group5_27()
{
  side_effect = side_effect + 1;
  funct_group5_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group5_29();

int
funct_group5_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group5_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group5_30();

int
funct_group5_29()
{
  side_effect = side_effect + 1;
  funct_group5_30();
  return side_effect;
}

int
funct_group5_31();

int
funct_group5_30()
{
  side_effect = side_effect + 1;
  funct_group5_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group5_32();

int
funct_group5_31()
{
  side_effect = side_effect + 1;
  funct_group5_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group5_33();

int
funct_group5_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group5_34();

int
funct_group5_33()
{
  side_effect = side_effect + 1;
  funct_group5_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group5_35();

int
funct_group5_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group5_36();

int
funct_group5_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group5_37();

int
funct_group5_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group5_37();
  return side_effect;
}

int
funct_group5_38();

int
funct_group5_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group5_38();
  return side_effect;
}

int
funct_group5_39();

int
funct_group5_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group5_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group5_40();

int
funct_group5_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group5_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group5_41();

int
funct_group5_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group5_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group5_42();

int
funct_group5_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group5_42();
  return side_effect;
}

int
funct_group5_43();

int
funct_group5_42()
{
  side_effect = side_effect + 1;
  funct_group5_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group5_44();

int
funct_group5_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group5_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group5_45();

int
funct_group5_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group5_46();

int
funct_group5_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group5_46();
  return side_effect;
}

int
funct_group5_47();

int
funct_group5_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group5_47();
  return side_effect;
}

int
funct_group5_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group6_1();

int
funct_group6_0()
{
  side_effect = side_effect + 1;
  funct_group6_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group6_2();

int
funct_group6_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group6_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group6_3();

int
funct_group6_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group6_3();
  return side_effect;
}

int
funct_group6_4();

int
funct_group6_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group6_4();
  return side_effect;
}

int
funct_group6_5();

int
funct_group6_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group6_5();
  return side_effect;
}

int
funct_group6_6();

int
funct_group6_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group6_7();

int
funct_group6_6()
{
  side_effect = side_effect + 1;
  funct_group6_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group6_8();

int
funct_group6_7()
{
  side_effect = side_effect + 1;
  funct_group6_8();
  return side_effect;
}

int
funct_group6_9();

int
funct_group6_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group6_9();
  return side_effect;
}

int
funct_group6_10();

int
funct_group6_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group6_10();
  return side_effect;
}

int
funct_group6_11();

int
funct_group6_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group6_12();

int
funct_group6_11()
{
  side_effect = side_effect + 1;
  funct_group6_12();
  return side_effect;
}

int
funct_group6_13();

int
funct_group6_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group6_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group6_14();

int
funct_group6_13()
{
  side_effect = side_effect + 1;
  funct_group6_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group6_15();

int
funct_group6_14()
{
  side_effect = side_effect + 1;
  funct_group6_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group6_16();

int
funct_group6_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group6_16();
  return side_effect;
}

int
funct_group6_17();

int
funct_group6_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group6_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group6_18();

int
funct_group6_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group6_18();
  return side_effect;
}

int
funct_group6_19();

int
funct_group6_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group6_19();
  return side_effect;
}

int
funct_group6_20();

int
funct_group6_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group6_21();

int
funct_group6_20()
{
  side_effect = side_effect + 1;
  funct_group6_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group6_22();

int
funct_group6_21()
{
  side_effect = side_effect + 1;
  funct_group6_22();
  return side_effect;
}

int
funct_group6_23();

int
funct_group6_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group6_23();
  return side_effect;
}

int
funct_group6_24();

int
funct_group6_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group6_24();
  return side_effect;
}

int
funct_group6_25();

int
funct_group6_24()
{
  side_effect = side_effect + 1;
  funct_group6_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group6_26();

int
funct_group6_25()
{
  side_effect = side_effect + 1;
  funct_group6_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group6_27();

int
funct_group6_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group6_28();

int
funct_group6_27()
{
  side_effect = side_effect + 1;
  funct_group6_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group6_29();

int
funct_group6_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group6_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group6_30();

int
funct_group6_29()
{
  side_effect = side_effect + 1;
  funct_group6_30();
  return side_effect;
}

int
funct_group6_31();

int
funct_group6_30()
{
  side_effect = side_effect + 1;
  funct_group6_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group6_32();

int
funct_group6_31()
{
  side_effect = side_effect + 1;
  funct_group6_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group6_33();

int
funct_group6_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group6_34();

int
funct_group6_33()
{
  side_effect = side_effect + 1;
  funct_group6_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group6_35();

int
funct_group6_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group6_36();

int
funct_group6_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group6_37();

int
funct_group6_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group6_37();
  return side_effect;
}

int
funct_group6_38();

int
funct_group6_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group6_38();
  return side_effect;
}

int
funct_group6_39();

int
funct_group6_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group6_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group6_40();

int
funct_group6_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group6_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group6_41();

int
funct_group6_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group6_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group6_42();

int
funct_group6_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group6_42();
  return side_effect;
}

int
funct_group6_43();

int
funct_group6_42()
{
  side_effect = side_effect + 1;
  funct_group6_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group6_44();

int
funct_group6_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group6_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group6_45();

int
funct_group6_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group6_46();

int
funct_group6_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group6_46();
  return side_effect;
}

int
funct_group6_47();

int
funct_group6_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group6_47();
  return side_effect;
}

int
funct_group6_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group7_1();

int
funct_group7_0()
{
  side_effect = side_effect + 1;
  funct_group7_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group7_2();

int
funct_group7_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group7_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group7_3();

int
funct_group7_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group7_3();
  return side_effect;
}

int
funct_group7_4();

int
funct_group7_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group7_4();
  return side_effect;
}

int
funct_group7_5();

int
funct_group7_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group7_5();
  return side_effect;
}

int
funct_group7_6();

int
funct_group7_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group7_7();

int
funct_group7_6()
{
  side_effect = side_effect + 1;
  funct_group7_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group7_8();

int
funct_group7_7()
{
  side_effect = side_effect + 1;
  funct_group7_8();
  return side_effect;
}

int
funct_group7_9();

int
funct_group7_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group7_9();
  return side_effect;
}

int
funct_group7_10();

int
funct_group7_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group7_10();
  return side_effect;
}

int
funct_group7_11();

int
funct_group7_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group7_12();

int
funct_group7_11()
{
  side_effect = side_effect + 1;
  funct_group7_12();
  return side_effect;
}

int
funct_group7_13();

int
funct_group7_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group7_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group7_14();

int
funct_group7_13()
{
  side_effect = side_effect + 1;
  funct_group7_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group7_15();

int
funct_group7_14()
{
  side_effect = side_effect + 1;
  funct_group7_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group7_16();

int
funct_group7_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group7_16();
  return side_effect;
}

int
funct_group7_17();

int
funct_group7_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group7_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group7_18();

int
funct_group7_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group7_18();
  return side_effect;
}

int
funct_group7_19();

int
funct_group7_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group7_19();
  return side_effect;
}

int
funct_group7_20();

int
funct_group7_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group7_21();

int
funct_group7_20()
{
  side_effect = side_effect + 1;
  funct_group7_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group7_22();

int
funct_group7_21()
{
  side_effect = side_effect + 1;
  funct_group7_22();
  return side_effect;
}

int
funct_group7_23();

int
funct_group7_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group7_23();
  return side_effect;
}

int
funct_group7_24();

int
funct_group7_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group7_24();
  return side_effect;
}

int
funct_group7_25();

int
funct_group7_24()
{
  side_effect = side_effect + 1;
  funct_group7_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group7_26();

int
funct_group7_25()
{
  side_effect = side_effect + 1;
  funct_group7_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group7_27();

int
funct_group7_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group7_28();

int
funct_group7_27()
{
  side_effect = side_effect + 1;
  funct_group7_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group7_29();

int
funct_group7_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group7_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group7_30();

int
funct_group7_29()
{
  side_effect = side_effect + 1;
  funct_group7_30();
  return side_effect;
}

int
funct_group7_31();

int
funct_group7_30()
{
  side_effect = side_effect + 1;
  funct_group7_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group7_32();

int
funct_group7_31()
{
  side_effect = side_effect + 1;
  funct_group7_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group7_33();

int
funct_group7_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group7_34();

int
funct_group7_33()
{
  side_effect = side_effect + 1;
  funct_group7_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group7_35();

int
funct_group7_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group7_36();

int
funct_group7_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group7_37();

int
funct_group7_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group7_37();
  return side_effect;
}

int
funct_group7_38();

int
funct_group7_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group7_38();
  return side_effect;
}

int
funct_group7_39();

int
funct_group7_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group7_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group7_40();

int
funct_group7_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group7_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group7_41();

int
funct_group7_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group7_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group7_42();

int
funct_group7_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group7_42();
  return side_effect;
}

int
funct_group7_43();

int
funct_group7_42()
{
  side_effect = side_effect + 1;
  funct_group7_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group7_44();

int
funct_group7_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group7_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group7_45();

int
funct_group7_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group7_46();

int
funct_group7_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group7_46();
  return side_effect;
}

int
funct_group7_47();

int
funct_group7_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group7_47();
  return side_effect;
}

int
funct_group7_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group8_1();

int
funct_group8_0()
{
  side_effect = side_effect + 1;
  funct_group8_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group8_2();

int
funct_group8_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group8_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group8_3();

int
funct_group8_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group8_3();
  return side_effect;
}

int
funct_group8_4();

int
funct_group8_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group8_4();
  return side_effect;
}

int
funct_group8_5();

int
funct_group8_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group8_5();
  return side_effect;
}

int
funct_group8_6();

int
funct_group8_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group8_7();

int
funct_group8_6()
{
  side_effect = side_effect + 1;
  funct_group8_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group8_8();

int
funct_group8_7()
{
  side_effect = side_effect + 1;
  funct_group8_8();
  return side_effect;
}

int
funct_group8_9();

int
funct_group8_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group8_9();
  return side_effect;
}

int
funct_group8_10();

int
funct_group8_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group8_10();
  return side_effect;
}

int
funct_group8_11();

int
funct_group8_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group8_12();

int
funct_group8_11()
{
  side_effect = side_effect + 1;
  funct_group8_12();
  return side_effect;
}

int
funct_group8_13();

int
funct_group8_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group8_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group8_14();

int
funct_group8_13()
{
  side_effect = side_effect + 1;
  funct_group8_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group8_15();

int
funct_group8_14()
{
  side_effect = side_effect + 1;
  funct_group8_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group8_16();

int
funct_group8_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group8_16();
  return side_effect;
}

int
funct_group8_17();

int
funct_group8_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group8_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group8_18();

int
funct_group8_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group8_18();
  return side_effect;
}

int
funct_group8_19();

int
funct_group8_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group8_19();
  return side_effect;
}

int
funct_group8_20();

int
funct_group8_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group8_21();

int
funct_group8_20()
{
  side_effect = side_effect + 1;
  funct_group8_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group8_22();

int
funct_group8_21()
{
  side_effect = side_effect + 1;
  funct_group8_22();
  return side_effect;
}

int
funct_group8_23();

int
funct_group8_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group8_23();
  return side_effect;
}

int
funct_group8_24();

int
funct_group8_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group8_24();
  return side_effect;
}

int
funct_group8_25();

int
funct_group8_24()
{
  side_effect = side_effect + 1;
  funct_group8_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group8_26();

int
funct_group8_25()
{
  side_effect = side_effect + 1;
  funct_group8_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group8_27();

int
funct_group8_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group8_28();

int
funct_group8_27()
{
  side_effect = side_effect + 1;
  funct_group8_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group8_29();

int
funct_group8_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group8_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group8_30();

int
funct_group8_29()
{
  side_effect = side_effect + 1;
  funct_group8_30();
  return side_effect;
}

int
funct_group8_31();

int
funct_group8_30()
{
  side_effect = side_effect + 1;
  funct_group8_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group8_32();

int
funct_group8_31()
{
  side_effect = side_effect + 1;
  funct_group8_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group8_33();

int
funct_group8_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group8_34();

int
funct_group8_33()
{
  side_effect = side_effect + 1;
  funct_group8_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group8_35();

int
funct_group8_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group8_36();

int
funct_group8_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group8_37();

int
funct_group8_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group8_37();
  return side_effect;
}

int
funct_group8_38();

int
funct_group8_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group8_38();
  return side_effect;
}

int
funct_group8_39();

int
funct_group8_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group8_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group8_40();

int
funct_group8_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group8_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group8_41();

int
funct_group8_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group8_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group8_42();

int
funct_group8_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group8_42();
  return side_effect;
}

int
funct_group8_43();

int
funct_group8_42()
{
  side_effect = side_effect + 1;
  funct_group8_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group8_44();

int
funct_group8_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group8_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group8_45();

int
funct_group8_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group8_46();

int
funct_group8_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group8_46();
  return side_effect;
}

int
funct_group8_47();

int
funct_group8_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group8_47();
  return side_effect;
}

int
funct_group8_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group9_1();

int
funct_group9_0()
{
  side_effect = side_effect + 1;
  funct_group9_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group9_2();

int
funct_group9_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group9_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group9_3();

int
funct_group9_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group9_3();
  return side_effect;
}

int
funct_group9_4();

int
funct_group9_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group9_4();
  return side_effect;
}

int
funct_group9_5();

int
funct_group9_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group9_5();
  return side_effect;
}

int
funct_group9_6();

int
funct_group9_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group9_7();

int
funct_group9_6()
{
  side_effect = side_effect + 1;
  funct_group9_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group9_8();

int
funct_group9_7()
{
  side_effect = side_effect + 1;
  funct_group9_8();
  return side_effect;
}

int
funct_group9_9();

int
funct_group9_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group9_9();
  return side_effect;
}

int
funct_group9_10();

int
funct_group9_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group9_10();
  return side_effect;
}

int
funct_group9_11();

int
funct_group9_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group9_12();

int
funct_group9_11()
{
  side_effect = side_effect + 1;
  funct_group9_12();
  return side_effect;
}

int
funct_group9_13();

int
funct_group9_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group9_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group9_14();

int
funct_group9_13()
{
  side_effect = side_effect + 1;
  funct_group9_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group9_15();

int
funct_group9_14()
{
  side_effect = side_effect + 1;
  funct_group9_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group9_16();

int
funct_group9_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group9_16();
  return side_effect;
}

int
funct_group9_17();

int
funct_group9_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group9_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group9_18();

int
funct_group9_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group9_18();
  return side_effect;
}

int
funct_group9_19();

int
funct_group9_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group9_19();
  return side_effect;
}

int
funct_group9_20();

int
funct_group9_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group9_21();

int
funct_group9_20()
{
  side_effect = side_effect + 1;
  funct_group9_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group9_22();

int
funct_group9_21()
{
  side_effect = side_effect + 1;
  funct_group9_22();
  return side_effect;
}

int
funct_group9_23();

int
funct_group9_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group9_23();
  return side_effect;
}

int
funct_group9_24();

int
funct_group9_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group9_24();
  return side_effect;
}

int
funct_group9_25();

int
funct_group9_24()
{
  side_effect = side_effect + 1;
  funct_group9_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group9_26();

int
funct_group9_25()
{
  side_effect = side_effect + 1;
  funct_group9_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group9_27();

int
funct_group9_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group9_28();

int
funct_group9_27()
{
  side_effect = side_effect + 1;
  funct_group9_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group9_29();

int
funct_group9_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group9_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group9_30();

int
funct_group9_29()
{
  side_effect = side_effect + 1;
  funct_group9_30();
  return side_effect;
}

int
funct_group9_31();

int
funct_group9_30()
{
  side_effect = side_effect + 1;
  funct_group9_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group9_32();

int
funct_group9_31()
{
  side_effect = side_effect + 1;
  funct_group9_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group9_33();

int
funct_group9_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group9_34();

int
funct_group9_33()
{
  side_effect = side_effect + 1;
  funct_group9_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group9_35();

int
funct_group9_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group9_36();

int
funct_group9_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group9_37();

int
funct_group9_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group9_37();
  return side_effect;
}

int
funct_group9_38();

int
funct_group9_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group9_38();
  return side_effect;
}

int
funct_group9_39();

int
funct_group9_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group9_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group9_40();

int
funct_group9_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group9_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group9_41();

int
funct_group9_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group9_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group9_42();

int
funct_group9_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group9_42();
  return side_effect;
}

int
funct_group9_43();

int
funct_group9_42()
{
  side_effect = side_effect + 1;
  funct_group9_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group9_44();

int
funct_group9_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group9_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group9_45();

int
funct_group9_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group9_46();

int
funct_group9_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group9_46();
  return side_effect;
}

int
funct_group9_47();

int
funct_group9_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group9_47();
  return side_effect;
}

int
funct_group9_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group10_1();

int
funct_group10_0()
{
  side_effect = side_effect + 1;
  funct_group10_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group10_2();

int
funct_group10_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group10_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group10_3();

int
funct_group10_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group10_3();
  return side_effect;
}

int
funct_group10_4();

int
funct_group10_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group10_4();
  return side_effect;
}

int
funct_group10_5();

int
funct_group10_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group10_5();
  return side_effect;
}

int
funct_group10_6();

int
funct_group10_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group10_7();

int
funct_group10_6()
{
  side_effect = side_effect + 1;
  funct_group10_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group10_8();

int
funct_group10_7()
{
  side_effect = side_effect + 1;
  funct_group10_8();
  return side_effect;
}

int
funct_group10_9();

int
funct_group10_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group10_9();
  return side_effect;
}

int
funct_group10_10();

int
funct_group10_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group10_10();
  return side_effect;
}

int
funct_group10_11();

int
funct_group10_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group10_12();

int
funct_group10_11()
{
  side_effect = side_effect + 1;
  funct_group10_12();
  return side_effect;
}

int
funct_group10_13();

int
funct_group10_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group10_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group10_14();

int
funct_group10_13()
{
  side_effect = side_effect + 1;
  funct_group10_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group10_15();

int
funct_group10_14()
{
  side_effect = side_effect + 1;
  funct_group10_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group10_16();

int
funct_group10_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group10_16();
  return side_effect;
}

int
funct_group10_17();

int
funct_group10_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group10_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group10_18();

int
funct_group10_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group10_18();
  return side_effect;
}

int
funct_group10_19();

int
funct_group10_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group10_19();
  return side_effect;
}

int
funct_group10_20();

int
funct_group10_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group10_21();

int
funct_group10_20()
{
  side_effect = side_effect + 1;
  funct_group10_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group10_22();

int
funct_group10_21()
{
  side_effect = side_effect + 1;
  funct_group10_22();
  return side_effect;
}

int
funct_group10_23();

int
funct_group10_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group10_23();
  return side_effect;
}

int
funct_group10_24();

int
funct_group10_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group10_24();
  return side_effect;
}

int
funct_group10_25();

int
funct_group10_24()
{
  side_effect = side_effect + 1;
  funct_group10_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group10_26();

int
funct_group10_25()
{
  side_effect = side_effect + 1;
  funct_group10_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group10_27();

int
funct_group10_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group10_28();

int
funct_group10_27()
{
  side_effect = side_effect + 1;
  funct_group10_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group10_29();

int
funct_group10_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group10_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group10_30();

int
funct_group10_29()
{
  side_effect = side_effect + 1;
  funct_group10_30();
  return side_effect;
}

int
funct_group10_31();

int
funct_group10_30()
{
  side_effect = side_effect + 1;
  funct_group10_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group10_32();

int
funct_group10_31()
{
  side_effect = side_effect + 1;
  funct_group10_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group10_33();

int
funct_group10_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group10_34();

int
funct_group10_33()
{
  side_effect = side_effect + 1;
  funct_group10_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group10_35();

int
funct_group10_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group10_36();

int
funct_group10_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group10_37();

int
funct_group10_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group10_37();
  return side_effect;
}

int
funct_group10_38();

int
funct_group10_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group10_38();
  return side_effect;
}

int
funct_group10_39();

int
funct_group10_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group10_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group10_40();

int
funct_group10_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group10_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group10_41();

int
funct_group10_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group10_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group10_42();

int
funct_group10_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group10_42();
  return side_effect;
}

int
funct_group10_43();

int
funct_group10_42()
{
  side_effect = side_effect + 1;
  funct_group10_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group10_44();

int
funct_group10_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group10_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group10_45();

int
funct_group10_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group10_46();

int
funct_group10_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group10_46();
  return side_effect;
}

int
funct_group10_47();

int
funct_group10_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group10_47();
  return side_effect;
}

int
funct_group10_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group11_1();

int
funct_group11_0()
{
  side_effect = side_effect + 1;
  funct_group11_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group11_2();

int
funct_group11_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group11_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group11_3();

int
funct_group11_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group11_3();
  return side_effect;
}

int
funct_group11_4();

int
funct_group11_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group11_4();
  return side_effect;
}

int
funct_group11_5();

int
funct_group11_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group11_5();
  return side_effect;
}

int
funct_group11_6();

int
funct_group11_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group11_7();

int
funct_group11_6()
{
  side_effect = side_effect + 1;
  funct_group11_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group11_8();

int
funct_group11_7()
{
  side_effect = side_effect + 1;
  funct_group11_8();
  return side_effect;
}

int
funct_group11_9();

int
funct_group11_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group11_9();
  return side_effect;
}

int
funct_group11_10();

int
funct_group11_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group11_10();
  return side_effect;
}

int
funct_group11_11();

int
funct_group11_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group11_12();

int
funct_group11_11()
{
  side_effect = side_effect + 1;
  funct_group11_12();
  return side_effect;
}

int
funct_group11_13();

int
funct_group11_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group11_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group11_14();

int
funct_group11_13()
{
  side_effect = side_effect + 1;
  funct_group11_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group11_15();

int
funct_group11_14()
{
  side_effect = side_effect + 1;
  funct_group11_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group11_16();

int
funct_group11_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group11_16();
  return side_effect;
}

int
funct_group11_17();

int
funct_group11_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group11_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group11_18();

int
funct_group11_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group11_18();
  return side_effect;
}

int
funct_group11_19();

int
funct_group11_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group11_19();
  return side_effect;
}

int
funct_group11_20();

int
funct_group11_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group11_21();

int
funct_group11_20()
{
  side_effect = side_effect + 1;
  funct_group11_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group11_22();

int
funct_group11_21()
{
  side_effect = side_effect + 1;
  funct_group11_22();
  return side_effect;
}

int
funct_group11_23();

int
funct_group11_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group11_23();
  return side_effect;
}

int
funct_group11_24();

int
funct_group11_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group11_24();
  return side_effect;
}

int
funct_group11_25();

int
funct_group11_24()
{
  side_effect = side_effect + 1;
  funct_group11_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group11_26();

int
funct_group11_25()
{
  side_effect = side_effect + 1;
  funct_group11_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group11_27();

int
funct_group11_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group11_28();

int
funct_group11_27()
{
  side_effect = side_effect + 1;
  funct_group11_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group11_29();

int
funct_group11_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group11_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group11_30();

int
funct_group11_29()
{
  side_effect = side_effect + 1;
  funct_group11_30();
  return side_effect;
}

int
funct_group11_31();

int
funct_group11_30()
{
  side_effect = side_effect + 1;
  funct_group11_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group11_32();

int
funct_group11_31()
{
  side_effect = side_effect + 1;
  funct_group11_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group11_33();

int
funct_group11_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group11_34();

int
funct_group11_33()
{
  side_effect = side_effect + 1;
  funct_group11_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group11_35();

int
funct_group11_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group11_36();

int
funct_group11_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group11_37();

int
funct_group11_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group11_37();
  return side_effect;
}

int
funct_group11_38();

int
funct_group11_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group11_38();
  return side_effect;
}

int
funct_group11_39();

int
funct_group11_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group11_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group11_40();

int
funct_group11_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group11_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group11_41();

int
funct_group11_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group11_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group11_42();

int
funct_group11_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group11_42();
  return side_effect;
}

int
funct_group11_43();

int
funct_group11_42()
{
  side_effect = side_effect + 1;
  funct_group11_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group11_44();

int
funct_group11_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group11_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group11_45();

int
funct_group11_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group11_46();

int
funct_group11_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group11_46();
  return side_effect;
}

int
funct_group11_47();

int
funct_group11_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group11_47();
  return side_effect;
}

int
funct_group11_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group12_1();

int
funct_group12_0()
{
  side_effect = side_effect + 1;
  funct_group12_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group12_2();

int
funct_group12_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group12_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group12_3();

int
funct_group12_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group12_3();
  return side_effect;
}

int
funct_group12_4();

int
funct_group12_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group12_4();
  return side_effect;
}

int
funct_group12_5();

int
funct_group12_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group12_5();
  return side_effect;
}

int
funct_group12_6();

int
funct_group12_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group12_7();

int
funct_group12_6()
{
  side_effect = side_effect + 1;
  funct_group12_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group12_8();

int
funct_group12_7()
{
  side_effect = side_effect + 1;
  funct_group12_8();
  return side_effect;
}

int
funct_group12_9();

int
funct_group12_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group12_9();
  return side_effect;
}

int
funct_group12_10();

int
funct_group12_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group12_10();
  return side_effect;
}

int
funct_group12_11();

int
funct_group12_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group12_12();

int
funct_group12_11()
{
  side_effect = side_effect + 1;
  funct_group12_12();
  return side_effect;
}

int
funct_group12_13();

int
funct_group12_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group12_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group12_14();

int
funct_group12_13()
{
  side_effect = side_effect + 1;
  funct_group12_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group12_15();

int
funct_group12_14()
{
  side_effect = side_effect + 1;
  funct_group12_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group12_16();

int
funct_group12_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group12_16();
  return side_effect;
}

int
funct_group12_17();

int
funct_group12_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group12_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group12_18();

int
funct_group12_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group12_18();
  return side_effect;
}

int
funct_group12_19();

int
funct_group12_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group12_19();
  return side_effect;
}

int
funct_group12_20();

int
funct_group12_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group12_21();

int
funct_group12_20()
{
  side_effect = side_effect + 1;
  funct_group12_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group12_22();

int
funct_group12_21()
{
  side_effect = side_effect + 1;
  funct_group12_22();
  return side_effect;
}

int
funct_group12_23();

int
funct_group12_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group12_23();
  return side_effect;
}

int
funct_group12_24();

int
funct_group12_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group12_24();
  return side_effect;
}

int
funct_group12_25();

int
funct_group12_24()
{
  side_effect = side_effect + 1;
  funct_group12_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group12_26();

int
funct_group12_25()
{
  side_effect = side_effect + 1;
  funct_group12_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group12_27();

int
funct_group12_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group12_28();

int
funct_group12_27()
{
  side_effect = side_effect + 1;
  funct_group12_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group12_29();

int
funct_group12_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group12_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group12_30();

int
funct_group12_29()
{
  side_effect = side_effect + 1;
  funct_group12_30();
  return side_effect;
}

int
funct_group12_31();

int
funct_group12_30()
{
  side_effect = side_effect + 1;
  funct_group12_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group12_32();

int
funct_group12_31()
{
  side_effect = side_effect + 1;
  funct_group12_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group12_33();

int
funct_group12_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group12_34();

int
funct_group12_33()
{
  side_effect = side_effect + 1;
  funct_group12_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group12_35();

int
funct_group12_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group12_36();

int
funct_group12_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group12_37();

int
funct_group12_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group12_37();
  return side_effect;
}

int
funct_group12_38();

int
funct_group12_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group12_38();
  return side_effect;
}

int
funct_group12_39();

int
funct_group12_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group12_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group12_40();

int
funct_group12_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group12_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group12_41();

int
funct_group12_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group12_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group12_42();

int
funct_group12_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group12_42();
  return side_effect;
}

int
funct_group12_43();

int
funct_group12_42()
{
  side_effect = side_effect + 1;
  funct_group12_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group12_44();

int
funct_group12_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group12_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group12_45();

int
funct_group12_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group12_46();

int
funct_group12_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group12_46();
  return side_effect;
}

int
funct_group12_47();

int
funct_group12_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group12_47();
  return side_effect;
}

int
funct_group12_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group13_1();

int
funct_group13_0()
{
  side_effect = side_effect + 1;
  funct_group13_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group13_2();

int
funct_group13_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group13_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group13_3();

int
funct_group13_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group13_3();
  return side_effect;
}

int
funct_group13_4();

int
funct_group13_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group13_4();
  return side_effect;
}

int
funct_group13_5();

int
funct_group13_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group13_5();
  return side_effect;
}

int
funct_group13_6();

int
funct_group13_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group13_7();

int
funct_group13_6()
{
  side_effect = side_effect + 1;
  funct_group13_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group13_8();

int
funct_group13_7()
{
  side_effect = side_effect + 1;
  funct_group13_8();
  return side_effect;
}

int
funct_group13_9();

int
funct_group13_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group13_9();
  return side_effect;
}

int
funct_group13_10();

int
funct_group13_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group13_10();
  return side_effect;
}

int
funct_group13_11();

int
funct_group13_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group13_12();

int
funct_group13_11()
{
  side_effect = side_effect + 1;
  funct_group13_12();
  return side_effect;
}

int
funct_group13_13();

int
funct_group13_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group13_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group13_14();

int
funct_group13_13()
{
  side_effect = side_effect + 1;
  funct_group13_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group13_15();

int
funct_group13_14()
{
  side_effect = side_effect + 1;
  funct_group13_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group13_16();

int
funct_group13_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group13_16();
  return side_effect;
}

int
funct_group13_17();

int
funct_group13_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group13_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group13_18();

int
funct_group13_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group13_18();
  return side_effect;
}

int
funct_group13_19();

int
funct_group13_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group13_19();
  return side_effect;
}

int
funct_group13_20();

int
funct_group13_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group13_21();

int
funct_group13_20()
{
  side_effect = side_effect + 1;
  funct_group13_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group13_22();

int
funct_group13_21()
{
  side_effect = side_effect + 1;
  funct_group13_22();
  return side_effect;
}

int
funct_group13_23();

int
funct_group13_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group13_23();
  return side_effect;
}

int
funct_group13_24();

int
funct_group13_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group13_24();
  return side_effect;
}

int
funct_group13_25();

int
funct_group13_24()
{
  side_effect = side_effect + 1;
  funct_group13_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group13_26();

int
funct_group13_25()
{
  side_effect = side_effect + 1;
  funct_group13_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group13_27();

int
funct_group13_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group13_28();

int
funct_group13_27()
{
  side_effect = side_effect + 1;
  funct_group13_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group13_29();

int
funct_group13_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group13_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group13_30();

int
funct_group13_29()
{
  side_effect = side_effect + 1;
  funct_group13_30();
  return side_effect;
}

int
funct_group13_31();

int
funct_group13_30()
{
  side_effect = side_effect + 1;
  funct_group13_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group13_32();

int
funct_group13_31()
{
  side_effect = side_effect + 1;
  funct_group13_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group13_33();

int
funct_group13_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group13_34();

int
funct_group13_33()
{
  side_effect = side_effect + 1;
  funct_group13_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group13_35();

int
funct_group13_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group13_36();

int
funct_group13_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group13_37();

int
funct_group13_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group13_37();
  return side_effect;
}

int
funct_group13_38();

int
funct_group13_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group13_38();
  return side_effect;
}

int
funct_group13_39();

int
funct_group13_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group13_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group13_40();

int
funct_group13_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group13_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group13_41();

int
funct_group13_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group13_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group13_42();

int
funct_group13_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group13_42();
  return side_effect;
}

int
funct_group13_43();

int
funct_group13_42()
{
  side_effect = side_effect + 1;
  funct_group13_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group13_44();

int
funct_group13_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group13_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group13_45();

int
funct_group13_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group13_46();

int
funct_group13_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group13_46();
  return side_effect;
}

int
funct_group13_47();

int
funct_group13_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group13_47();
  return side_effect;
}

int
funct_group13_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group14_1();

int
funct_group14_0()
{
  side_effect = side_effect + 1;
  funct_group14_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group14_2();

int
funct_group14_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group14_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group14_3();

int
funct_group14_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group14_3();
  return side_effect;
}

int
funct_group14_4();

int
funct_group14_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group14_4();
  return side_effect;
}

int
funct_group14_5();

int
funct_group14_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group14_5();
  return side_effect;
}

int
funct_group14_6();

int
funct_group14_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group14_7();

int
funct_group14_6()
{
  side_effect = side_effect + 1;
  funct_group14_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group14_8();

int
funct_group14_7()
{
  side_effect = side_effect + 1;
  funct_group14_8();
  return side_effect;
}

int
funct_group14_9();

int
funct_group14_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group14_9();
  return side_effect;
}

int
funct_group14_10();

int
funct_group14_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group14_10();
  return side_effect;
}

int
funct_group14_11();

int
funct_group14_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group14_12();

int
funct_group14_11()
{
  side_effect = side_effect + 1;
  funct_group14_12();
  return side_effect;
}

int
funct_group14_13();

int
funct_group14_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group14_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group14_14();

int
funct_group14_13()
{
  side_effect = side_effect + 1;
  funct_group14_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group14_15();

int
funct_group14_14()
{
  side_effect = side_effect + 1;
  funct_group14_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group14_16();

int
funct_group14_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group14_16();
  return side_effect;
}

int
funct_group14_17();

int
funct_group14_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group14_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group14_18();

int
funct_group14_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group14_18();
  return side_effect;
}

int
funct_group14_19();

int
funct_group14_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group14_19();
  return side_effect;
}

int
funct_group14_20();

int
funct_group14_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group14_21();

int
funct_group14_20()
{
  side_effect = side_effect + 1;
  funct_group14_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group14_22();

int
funct_group14_21()
{
  side_effect = side_effect + 1;
  funct_group14_22();
  return side_effect;
}

int
funct_group14_23();

int
funct_group14_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group14_23();
  return side_effect;
}

int
funct_group14_24();

int
funct_group14_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group14_24();
  return side_effect;
}

int
funct_group14_25();

int
funct_group14_24()
{
  side_effect = side_effect + 1;
  funct_group14_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group14_26();

int
funct_group14_25()
{
  side_effect = side_effect + 1;
  funct_group14_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group14_27();

int
funct_group14_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group14_28();

int
funct_group14_27()
{
  side_effect = side_effect + 1;
  funct_group14_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group14_29();

int
funct_group14_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group14_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group14_30();

int
funct_group14_29()
{
  side_effect = side_effect + 1;
  funct_group14_30();
  return side_effect;
}

int
funct_group14_31();

int
funct_group14_30()
{
  side_effect = side_effect + 1;
  funct_group14_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group14_32();

int
funct_group14_31()
{
  side_effect = side_effect + 1;
  funct_group14_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group14_33();

int
funct_group14_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group14_34();

int
funct_group14_33()
{
  side_effect = side_effect + 1;
  funct_group14_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group14_35();

int
funct_group14_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group14_36();

int
funct_group14_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group14_37();

int
funct_group14_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group14_37();
  return side_effect;
}

int
funct_group14_38();

int
funct_group14_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group14_38();
  return side_effect;
}

int
funct_group14_39();

int
funct_group14_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group14_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group14_40();

int
funct_group14_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group14_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group14_41();

int
funct_group14_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group14_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group14_42();

int
funct_group14_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group14_42();
  return side_effect;
}

int
funct_group14_43();

int
funct_group14_42()
{
  side_effect = side_effect + 1;
  funct_group14_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group14_44();

int
funct_group14_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group14_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group14_45();

int
funct_group14_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group14_46();

int
funct_group14_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group14_46();
  return side_effect;
}

int
funct_group14_47();

int
funct_group14_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group14_47();
  return side_effect;
}

int
funct_group14_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group15_1();

int
funct_group15_0()
{
  side_effect = side_effect + 1;
  funct_group15_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group15_2();

int
funct_group15_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group15_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group15_3();

int
funct_group15_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group15_3();
  return side_effect;
}

int
funct_group15_4();

int
funct_group15_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group15_4();
  return side_effect;
}

int
funct_group15_5();

int
funct_group15_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group15_5();
  return side_effect;
}

int
funct_group15_6();

int
funct_group15_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group15_7();

int
funct_group15_6()
{
  side_effect = side_effect + 1;
  funct_group15_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group15_8();

int
funct_group15_7()
{
  side_effect = side_effect + 1;
  funct_group15_8();
  return side_effect;
}

int
funct_group15_9();

int
funct_group15_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group15_9();
  return side_effect;
}

int
funct_group15_10();

int
funct_group15_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group15_10();
  return side_effect;
}

int
funct_group15_11();

int
funct_group15_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group15_12();

int
funct_group15_11()
{
  side_effect = side_effect + 1;
  funct_group15_12();
  return side_effect;
}

int
funct_group15_13();

int
funct_group15_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group15_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group15_14();

int
funct_group15_13()
{
  side_effect = side_effect + 1;
  funct_group15_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group15_15();

int
funct_group15_14()
{
  side_effect = side_effect + 1;
  funct_group15_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group15_16();

int
funct_group15_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group15_16();
  return side_effect;
}

int
funct_group15_17();

int
funct_group15_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group15_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group15_18();

int
funct_group15_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group15_18();
  return side_effect;
}

int
funct_group15_19();

int
funct_group15_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group15_19();
  return side_effect;
}

int
funct_group15_20();

int
funct_group15_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group15_21();

int
funct_group15_20()
{
  side_effect = side_effect + 1;
  funct_group15_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group15_22();

int
funct_group15_21()
{
  side_effect = side_effect + 1;
  funct_group15_22();
  return side_effect;
}

int
funct_group15_23();

int
funct_group15_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group15_23();
  return side_effect;
}

int
funct_group15_24();

int
funct_group15_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group15_24();
  return side_effect;
}

int
funct_group15_25();

int
funct_group15_24()
{
  side_effect = side_effect + 1;
  funct_group15_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group15_26();

int
funct_group15_25()
{
  side_effect = side_effect + 1;
  funct_group15_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group15_27();

int
funct_group15_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group15_28();

int
funct_group15_27()
{
  side_effect = side_effect + 1;
  funct_group15_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group15_29();

int
funct_group15_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group15_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group15_30();

int
funct_group15_29()
{
  side_effect = side_effect + 1;
  funct_group15_30();
  return side_effect;
}

int
funct_group15_31();

int
funct_group15_30()
{
  side_effect = side_effect + 1;
  funct_group15_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group15_32();

int
funct_group15_31()
{
  side_effect = side_effect + 1;
  funct_group15_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group15_33();

int
funct_group15_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group15_34();

int
funct_group15_33()
{
  side_effect = side_effect + 1;
  funct_group15_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group15_35();

int
funct_group15_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group15_36();

int
funct_group15_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group15_37();

int
funct_group15_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group15_37();
  return side_effect;
}

int
funct_group15_38();

int
funct_group15_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group15_38();
  return side_effect;
}

int
funct_group15_39();

int
funct_group15_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group15_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group15_40();

int
funct_group15_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group15_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group15_41();

int
funct_group15_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group15_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group15_42();

int
funct_group15_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group15_42();
  return side_effect;
}

int
funct_group15_43();

int
funct_group15_42()
{
  side_effect = side_effect + 1;
  funct_group15_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group15_44();

int
funct_group15_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group15_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group15_45();

int
funct_group15_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group15_46();

int
funct_group15_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group15_46();
  return side_effect;
}

int
funct_group15_47();

int
funct_group15_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group15_47();
  return side_effect;
}

int
funct_group15_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group16_1();

int
funct_group16_0()
{
  side_effect = side_effect + 1;
  funct_group16_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group16_2();

int
funct_group16_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group16_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group16_3();

int
funct_group16_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group16_3();
  return side_effect;
}

int
funct_group16_4();

int
funct_group16_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group16_4();
  return side_effect;
}

int
funct_group16_5();

int
funct_group16_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group16_5();
  return side_effect;
}

int
funct_group16_6();

int
funct_group16_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group16_7();

int
funct_group16_6()
{
  side_effect = side_effect + 1;
  funct_group16_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group16_8();

int
funct_group16_7()
{
  side_effect = side_effect + 1;
  funct_group16_8();
  return side_effect;
}

int
funct_group16_9();

int
funct_group16_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group16_9();
  return side_effect;
}

int
funct_group16_10();

int
funct_group16_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group16_10();
  return side_effect;
}

int
funct_group16_11();

int
funct_group16_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group16_12();

int
funct_group16_11()
{
  side_effect = side_effect + 1;
  funct_group16_12();
  return side_effect;
}

int
funct_group16_13();

int
funct_group16_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group16_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group16_14();

int
funct_group16_13()
{
  side_effect = side_effect + 1;
  funct_group16_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group16_15();

int
funct_group16_14()
{
  side_effect = side_effect + 1;
  funct_group16_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group16_16();

int
funct_group16_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group16_16();
  return side_effect;
}

int
funct_group16_17();

int
funct_group16_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group16_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group16_18();

int
funct_group16_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group16_18();
  return side_effect;
}

int
funct_group16_19();

int
funct_group16_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group16_19();
  return side_effect;
}

int
funct_group16_20();

int
funct_group16_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group16_21();

int
funct_group16_20()
{
  side_effect = side_effect + 1;
  funct_group16_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group16_22();

int
funct_group16_21()
{
  side_effect = side_effect + 1;
  funct_group16_22();
  return side_effect;
}

int
funct_group16_23();

int
funct_group16_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group16_23();
  return side_effect;
}

int
funct_group16_24();

int
funct_group16_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group16_24();
  return side_effect;
}

int
funct_group16_25();

int
funct_group16_24()
{
  side_effect = side_effect + 1;
  funct_group16_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group16_26();

int
funct_group16_25()
{
  side_effect = side_effect + 1;
  funct_group16_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group16_27();

int
funct_group16_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group16_28();

int
funct_group16_27()
{
  side_effect = side_effect + 1;
  funct_group16_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group16_29();

int
funct_group16_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group16_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group16_30();

int
funct_group16_29()
{
  side_effect = side_effect + 1;
  funct_group16_30();
  return side_effect;
}

int
funct_group16_31();

int
funct_group16_30()
{
  side_effect = side_effect + 1;
  funct_group16_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group16_32();

int
funct_group16_31()
{
  side_effect = side_effect + 1;
  funct_group16_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group16_33();

int
funct_group16_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group16_34();

int
funct_group16_33()
{
  side_effect = side_effect + 1;
  funct_group16_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group16_35();

int
funct_group16_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group16_36();

int
funct_group16_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group16_37();

int
funct_group16_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group16_37();
  return side_effect;
}

int
funct_group16_38();

int
funct_group16_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group16_38();
  return side_effect;
}

int
funct_group16_39();

int
funct_group16_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group16_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group16_40();

int
funct_group16_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group16_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group16_41();

int
funct_group16_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group16_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group16_42();

int
funct_group16_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group16_42();
  return side_effect;
}

int
funct_group16_43();

int
funct_group16_42()
{
  side_effect = side_effect + 1;
  funct_group16_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group16_44();

int
funct_group16_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group16_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group16_45();

int
funct_group16_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group16_46();

int
funct_group16_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group16_46();
  return side_effect;
}

int
funct_group16_47();

int
funct_group16_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group16_47();
  return side_effect;
}

int
funct_group16_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group17_1();

int
funct_group17_0()
{
  side_effect = side_effect + 1;
  funct_group17_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group17_2();

int
funct_group17_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group17_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group17_3();

int
funct_group17_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group17_3();
  return side_effect;
}

int
funct_group17_4();

int
funct_group17_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group17_4();
  return side_effect;
}

int
funct_group17_5();

int
funct_group17_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group17_5();
  return side_effect;
}

int
funct_group17_6();

int
funct_group17_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group17_7();

int
funct_group17_6()
{
  side_effect = side_effect + 1;
  funct_group17_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group17_8();

int
funct_group17_7()
{
  side_effect = side_effect + 1;
  funct_group17_8();
  return side_effect;
}

int
funct_group17_9();

int
funct_group17_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group17_9();
  return side_effect;
}

int
funct_group17_10();

int
funct_group17_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group17_10();
  return side_effect;
}

int
funct_group17_11();

int
funct_group17_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group17_12();

int
funct_group17_11()
{
  side_effect = side_effect + 1;
  funct_group17_12();
  return side_effect;
}

int
funct_group17_13();

int
funct_group17_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group17_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group17_14();

int
funct_group17_13()
{
  side_effect = side_effect + 1;
  funct_group17_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group17_15();

int
funct_group17_14()
{
  side_effect = side_effect + 1;
  funct_group17_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group17_16();

int
funct_group17_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group17_16();
  return side_effect;
}

int
funct_group17_17();

int
funct_group17_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group17_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group17_18();

int
funct_group17_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group17_18();
  return side_effect;
}

int
funct_group17_19();

int
funct_group17_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group17_19();
  return side_effect;
}

int
funct_group17_20();

int
funct_group17_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group17_21();

int
funct_group17_20()
{
  side_effect = side_effect + 1;
  funct_group17_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group17_22();

int
funct_group17_21()
{
  side_effect = side_effect + 1;
  funct_group17_22();
  return side_effect;
}

int
funct_group17_23();

int
funct_group17_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group17_23();
  return side_effect;
}

int
funct_group17_24();

int
funct_group17_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group17_24();
  return side_effect;
}

int
funct_group17_25();

int
funct_group17_24()
{
  side_effect = side_effect + 1;
  funct_group17_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group17_26();

int
funct_group17_25()
{
  side_effect = side_effect + 1;
  funct_group17_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group17_27();

int
funct_group17_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group17_28();

int
funct_group17_27()
{
  side_effect = side_effect + 1;
  funct_group17_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group17_29();

int
funct_group17_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group17_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group17_30();

int
funct_group17_29()
{
  side_effect = side_effect + 1;
  funct_group17_30();
  return side_effect;
}

int
funct_group17_31();

int
funct_group17_30()
{
  side_effect = side_effect + 1;
  funct_group17_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group17_32();

int
funct_group17_31()
{
  side_effect = side_effect + 1;
  funct_group17_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group17_33();

int
funct_group17_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group17_34();

int
funct_group17_33()
{
  side_effect = side_effect + 1;
  funct_group17_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group17_35();

int
funct_group17_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group17_36();

int
funct_group17_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group17_37();

int
funct_group17_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group17_37();
  return side_effect;
}

int
funct_group17_38();

int
funct_group17_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group17_38();
  return side_effect;
}

int
funct_group17_39();

int
funct_group17_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group17_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group17_40();

int
funct_group17_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group17_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group17_41();

int
funct_group17_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group17_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group17_42();

int
funct_group17_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group17_42();
  return side_effect;
}

int
funct_group17_43();

int
funct_group17_42()
{
  side_effect = side_effect + 1;
  funct_group17_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group17_44();

int
funct_group17_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group17_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group17_45();

int
funct_group17_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group17_46();

int
funct_group17_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group17_46();
  return side_effect;
}

int
funct_group17_47();

int
funct_group17_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group17_47();
  return side_effect;
}

int
funct_group17_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group18_1();

int
funct_group18_0()
{
  side_effect = side_effect + 1;
  funct_group18_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group18_2();

int
funct_group18_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group18_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group18_3();

int
funct_group18_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group18_3();
  return side_effect;
}

int
funct_group18_4();

int
funct_group18_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group18_4();
  return side_effect;
}

int
funct_group18_5();

int
funct_group18_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group18_5();
  return side_effect;
}

int
funct_group18_6();

int
funct_group18_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group18_7();

int
funct_group18_6()
{
  side_effect = side_effect + 1;
  funct_group18_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group18_8();

int
funct_group18_7()
{
  side_effect = side_effect + 1;
  funct_group18_8();
  return side_effect;
}

int
funct_group18_9();

int
funct_group18_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group18_9();
  return side_effect;
}

int
funct_group18_10();

int
funct_group18_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group18_10();
  return side_effect;
}

int
funct_group18_11();

int
funct_group18_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group18_12();

int
funct_group18_11()
{
  side_effect = side_effect + 1;
  funct_group18_12();
  return side_effect;
}

int
funct_group18_13();

int
funct_group18_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group18_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group18_14();

int
funct_group18_13()
{
  side_effect = side_effect + 1;
  funct_group18_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group18_15();

int
funct_group18_14()
{
  side_effect = side_effect + 1;
  funct_group18_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group18_16();

int
funct_group18_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group18_16();
  return side_effect;
}

int
funct_group18_17();

int
funct_group18_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group18_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group18_18();

int
funct_group18_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group18_18();
  return side_effect;
}

int
funct_group18_19();

int
funct_group18_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group18_19();
  return side_effect;
}

int
funct_group18_20();

int
funct_group18_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group18_21();

int
funct_group18_20()
{
  side_effect = side_effect + 1;
  funct_group18_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group18_22();

int
funct_group18_21()
{
  side_effect = side_effect + 1;
  funct_group18_22();
  return side_effect;
}

int
funct_group18_23();

int
funct_group18_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group18_23();
  return side_effect;
}

int
funct_group18_24();

int
funct_group18_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group18_24();
  return side_effect;
}

int
funct_group18_25();

int
funct_group18_24()
{
  side_effect = side_effect + 1;
  funct_group18_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group18_26();

int
funct_group18_25()
{
  side_effect = side_effect + 1;
  funct_group18_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group18_27();

int
funct_group18_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group18_28();

int
funct_group18_27()
{
  side_effect = side_effect + 1;
  funct_group18_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group18_29();

int
funct_group18_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group18_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group18_30();

int
funct_group18_29()
{
  side_effect = side_effect + 1;
  funct_group18_30();
  return side_effect;
}

int
funct_group18_31();

int
funct_group18_30()
{
  side_effect = side_effect + 1;
  funct_group18_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group18_32();

int
funct_group18_31()
{
  side_effect = side_effect + 1;
  funct_group18_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group18_33();

int
funct_group18_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group18_34();

int
funct_group18_33()
{
  side_effect = side_effect + 1;
  funct_group18_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group18_35();

int
funct_group18_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group18_36();

int
funct_group18_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group18_37();

int
funct_group18_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group18_37();
  return side_effect;
}

int
funct_group18_38();

int
funct_group18_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group18_38();
  return side_effect;
}

int
funct_group18_39();

int
funct_group18_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group18_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group18_40();

int
funct_group18_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group18_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group18_41();

int
funct_group18_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group18_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group18_42();

int
funct_group18_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group18_42();
  return side_effect;
}

int
funct_group18_43();

int
funct_group18_42()
{
  side_effect = side_effect + 1;
  funct_group18_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group18_44();

int
funct_group18_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group18_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group18_45();

int
funct_group18_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group18_46();

int
funct_group18_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group18_46();
  return side_effect;
}

int
funct_group18_47();

int
funct_group18_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group18_47();
  return side_effect;
}

int
funct_group18_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group19_1();

int
funct_group19_0()
{
  side_effect = side_effect + 1;
  funct_group19_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group19_2();

int
funct_group19_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group19_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group19_3();

int
funct_group19_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group19_3();
  return side_effect;
}

int
funct_group19_4();

int
funct_group19_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group19_4();
  return side_effect;
}

int
funct_group19_5();

int
funct_group19_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group19_5();
  return side_effect;
}

int
funct_group19_6();

int
funct_group19_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group19_7();

int
funct_group19_6()
{
  side_effect = side_effect + 1;
  funct_group19_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group19_8();

int
funct_group19_7()
{
  side_effect = side_effect + 1;
  funct_group19_8();
  return side_effect;
}

int
funct_group19_9();

int
funct_group19_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group19_9();
  return side_effect;
}

int
funct_group19_10();

int
funct_group19_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group19_10();
  return side_effect;
}

int
funct_group19_11();

int
funct_group19_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group19_12();

int
funct_group19_11()
{
  side_effect = side_effect + 1;
  funct_group19_12();
  return side_effect;
}

int
funct_group19_13();

int
funct_group19_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group19_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group19_14();

int
funct_group19_13()
{
  side_effect = side_effect + 1;
  funct_group19_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group19_15();

int
funct_group19_14()
{
  side_effect = side_effect + 1;
  funct_group19_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group19_16();

int
funct_group19_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group19_16();
  return side_effect;
}

int
funct_group19_17();

int
funct_group19_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group19_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group19_18();

int
funct_group19_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group19_18();
  return side_effect;
}

int
funct_group19_19();

int
funct_group19_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group19_19();
  return side_effect;
}

int
funct_group19_20();

int
funct_group19_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group19_21();

int
funct_group19_20()
{
  side_effect = side_effect + 1;
  funct_group19_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group19_22();

int
funct_group19_21()
{
  side_effect = side_effect + 1;
  funct_group19_22();
  return side_effect;
}

int
funct_group19_23();

int
funct_group19_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group19_23();
  return side_effect;
}

int
funct_group19_24();

int
funct_group19_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group19_24();
  return side_effect;
}

int
funct_group19_25();

int
funct_group19_24()
{
  side_effect = side_effect + 1;
  funct_group19_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group19_26();

int
funct_group19_25()
{
  side_effect = side_effect + 1;
  funct_group19_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group19_27();

int
funct_group19_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group19_28();

int
funct_group19_27()
{
  side_effect = side_effect + 1;
  funct_group19_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group19_29();

int
funct_group19_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group19_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group19_30();

int
funct_group19_29()
{
  side_effect = side_effect + 1;
  funct_group19_30();
  return side_effect;
}

int
funct_group19_31();

int
funct_group19_30()
{
  side_effect = side_effect + 1;
  funct_group19_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group19_32();

int
funct_group19_31()
{
  side_effect = side_effect + 1;
  funct_group19_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group19_33();

int
funct_group19_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group19_34();

int
funct_group19_33()
{
  side_effect = side_effect + 1;
  funct_group19_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group19_35();

int
funct_group19_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group19_36();

int
funct_group19_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group19_37();

int
funct_group19_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group19_37();
  return side_effect;
}

int
funct_group19_38();

int
funct_group19_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group19_38();
  return side_effect;
}

int
funct_group19_39();

int
funct_group19_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group19_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group19_40();

int
funct_group19_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group19_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group19_41();

int
funct_group19_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group19_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group19_42();

int
funct_group19_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group19_42();
  return side_effect;
}

int
funct_group19_43();

int
funct_group19_42()
{
  side_effect = side_effect + 1;
  funct_group19_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group19_44();

int
funct_group19_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group19_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group19_45();

int
funct_group19_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group19_46();

int
funct_group19_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group19_46();
  return side_effect;
}

int
funct_group19_47();

int
funct_group19_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group19_47();
  return side_effect;
}

int
funct_group19_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group20_1();

int
funct_group20_0()
{
  side_effect = side_effect + 1;
  funct_group20_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group20_2();

int
funct_group20_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group20_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group20_3();

int
funct_group20_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group20_3();
  return side_effect;
}

int
funct_group20_4();

int
funct_group20_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group20_4();
  return side_effect;
}

int
funct_group20_5();

int
funct_group20_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group20_5();
  return side_effect;
}

int
funct_group20_6();

int
funct_group20_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group20_7();

int
funct_group20_6()
{
  side_effect = side_effect + 1;
  funct_group20_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group20_8();

int
funct_group20_7()
{
  side_effect = side_effect + 1;
  funct_group20_8();
  return side_effect;
}

int
funct_group20_9();

int
funct_group20_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group20_9();
  return side_effect;
}

int
funct_group20_10();

int
funct_group20_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group20_10();
  return side_effect;
}

int
funct_group20_11();

int
funct_group20_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group20_12();

int
funct_group20_11()
{
  side_effect = side_effect + 1;
  funct_group20_12();
  return side_effect;
}

int
funct_group20_13();

int
funct_group20_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group20_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group20_14();

int
funct_group20_13()
{
  side_effect = side_effect + 1;
  funct_group20_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group20_15();

int
funct_group20_14()
{
  side_effect = side_effect + 1;
  funct_group20_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group20_16();

int
funct_group20_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group20_16();
  return side_effect;
}

int
funct_group20_17();

int
funct_group20_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group20_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group20_18();

int
funct_group20_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group20_18();
  return side_effect;
}

int
funct_group20_19();

int
funct_group20_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group20_19();
  return side_effect;
}

int
funct_group20_20();

int
funct_group20_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group20_21();

int
funct_group20_20()
{
  side_effect = side_effect + 1;
  funct_group20_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group20_22();

int
funct_group20_21()
{
  side_effect = side_effect + 1;
  funct_group20_22();
  return side_effect;
}

int
funct_group20_23();

int
funct_group20_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group20_23();
  return side_effect;
}

int
funct_group20_24();

int
funct_group20_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group20_24();
  return side_effect;
}

int
funct_group20_25();

int
funct_group20_24()
{
  side_effect = side_effect + 1;
  funct_group20_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group20_26();

int
funct_group20_25()
{
  side_effect = side_effect + 1;
  funct_group20_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group20_27();

int
funct_group20_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group20_28();

int
funct_group20_27()
{
  side_effect = side_effect + 1;
  funct_group20_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group20_29();

int
funct_group20_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group20_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group20_30();

int
funct_group20_29()
{
  side_effect = side_effect + 1;
  funct_group20_30();
  return side_effect;
}

int
funct_group20_31();

int
funct_group20_30()
{
  side_effect = side_effect + 1;
  funct_group20_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group20_32();

int
funct_group20_31()
{
  side_effect = side_effect + 1;
  funct_group20_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group20_33();

int
funct_group20_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group20_34();

int
funct_group20_33()
{
  side_effect = side_effect + 1;
  funct_group20_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group20_35();

int
funct_group20_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group20_36();

int
funct_group20_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group20_37();

int
funct_group20_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group20_37();
  return side_effect;
}

int
funct_group20_38();

int
funct_group20_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group20_38();
  return side_effect;
}

int
funct_group20_39();

int
funct_group20_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group20_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group20_40();

int
funct_group20_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group20_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group20_41();

int
funct_group20_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group20_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group20_42();

int
funct_group20_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group20_42();
  return side_effect;
}

int
funct_group20_43();

int
funct_group20_42()
{
  side_effect = side_effect + 1;
  funct_group20_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group20_44();

int
funct_group20_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group20_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group20_45();

int
funct_group20_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group20_46();

int
funct_group20_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group20_46();
  return side_effect;
}

int
funct_group20_47();

int
funct_group20_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group20_47();
  return side_effect;
}

int
funct_group20_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group21_1();

int
funct_group21_0()
{
  side_effect = side_effect + 1;
  funct_group21_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group21_2();

int
funct_group21_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group21_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group21_3();

int
funct_group21_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group21_3();
  return side_effect;
}

int
funct_group21_4();

int
funct_group21_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group21_4();
  return side_effect;
}

int
funct_group21_5();

int
funct_group21_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group21_5();
  return side_effect;
}

int
funct_group21_6();

int
funct_group21_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group21_7();

int
funct_group21_6()
{
  side_effect = side_effect + 1;
  funct_group21_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group21_8();

int
funct_group21_7()
{
  side_effect = side_effect + 1;
  funct_group21_8();
  return side_effect;
}

int
funct_group21_9();

int
funct_group21_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group21_9();
  return side_effect;
}

int
funct_group21_10();

int
funct_group21_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group21_10();
  return side_effect;
}

int
funct_group21_11();

int
funct_group21_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group21_12();

int
funct_group21_11()
{
  side_effect = side_effect + 1;
  funct_group21_12();
  return side_effect;
}

int
funct_group21_13();

int
funct_group21_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group21_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group21_14();

int
funct_group21_13()
{
  side_effect = side_effect + 1;
  funct_group21_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group21_15();

int
funct_group21_14()
{
  side_effect = side_effect + 1;
  funct_group21_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group21_16();

int
funct_group21_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group21_16();
  return side_effect;
}

int
funct_group21_17();

int
funct_group21_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group21_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group21_18();

int
funct_group21_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group21_18();
  return side_effect;
}

int
funct_group21_19();

int
funct_group21_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group21_19();
  return side_effect;
}

int
funct_group21_20();

int
funct_group21_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group21_21();

int
funct_group21_20()
{
  side_effect = side_effect + 1;
  funct_group21_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group21_22();

int
funct_group21_21()
{
  side_effect = side_effect + 1;
  funct_group21_22();
  return side_effect;
}

int
funct_group21_23();

int
funct_group21_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group21_23();
  return side_effect;
}

int
funct_group21_24();

int
funct_group21_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group21_24();
  return side_effect;
}

int
funct_group21_25();

int
funct_group21_24()
{
  side_effect = side_effect + 1;
  funct_group21_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group21_26();

int
funct_group21_25()
{
  side_effect = side_effect + 1;
  funct_group21_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group21_27();

int
funct_group21_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group21_28();

int
funct_group21_27()
{
  side_effect = side_effect + 1;
  funct_group21_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group21_29();

int
funct_group21_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group21_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group21_30();

int
funct_group21_29()
{
  side_effect = side_effect + 1;
  funct_group21_30();
  return side_effect;
}

int
funct_group21_31();

int
funct_group21_30()
{
  side_effect = side_effect + 1;
  funct_group21_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group21_32();

int
funct_group21_31()
{
  side_effect = side_effect + 1;
  funct_group21_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group21_33();

int
funct_group21_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group21_34();

int
funct_group21_33()
{
  side_effect = side_effect + 1;
  funct_group21_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group21_35();

int
funct_group21_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group21_36();

int
funct_group21_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group21_37();

int
funct_group21_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group21_37();
  return side_effect;
}

int
funct_group21_38();

int
funct_group21_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group21_38();
  return side_effect;
}

int
funct_group21_39();

int
funct_group21_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group21_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group21_40();

int
funct_group21_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group21_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group21_41();

int
funct_group21_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group21_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group21_42();

int
funct_group21_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group21_42();
  return side_effect;
}

int
funct_group21_43();

int
funct_group21_42()
{
  side_effect = side_effect + 1;
  funct_group21_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group21_44();

int
funct_group21_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group21_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group21_45();

int
funct_group21_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group21_46();

int
funct_group21_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group21_46();
  return side_effect;
}

int
funct_group21_47();

int
funct_group21_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group21_47();
  return side_effect;
}

int
funct_group21_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group22_1();

int
funct_group22_0()
{
  side_effect = side_effect + 1;
  funct_group22_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group22_2();

int
funct_group22_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group22_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group22_3();

int
funct_group22_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group22_3();
  return side_effect;
}

int
funct_group22_4();

int
funct_group22_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group22_4();
  return side_effect;
}

int
funct_group22_5();

int
funct_group22_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group22_5();
  return side_effect;
}

int
funct_group22_6();

int
funct_group22_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group22_7();

int
funct_group22_6()
{
  side_effect = side_effect + 1;
  funct_group22_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group22_8();

int
funct_group22_7()
{
  side_effect = side_effect + 1;
  funct_group22_8();
  return side_effect;
}

int
funct_group22_9();

int
funct_group22_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group22_9();
  return side_effect;
}

int
funct_group22_10();

int
funct_group22_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group22_10();
  return side_effect;
}

int
funct_group22_11();

int
funct_group22_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group22_12();

int
funct_group22_11()
{
  side_effect = side_effect + 1;
  funct_group22_12();
  return side_effect;
}

int
funct_group22_13();

int
funct_group22_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group22_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group22_14();

int
funct_group22_13()
{
  side_effect = side_effect + 1;
  funct_group22_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group22_15();

int
funct_group22_14()
{
  side_effect = side_effect + 1;
  funct_group22_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group22_16();

int
funct_group22_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group22_16();
  return side_effect;
}

int
funct_group22_17();

int
funct_group22_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group22_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group22_18();

int
funct_group22_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group22_18();
  return side_effect;
}

int
funct_group22_19();

int
funct_group22_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group22_19();
  return side_effect;
}

int
funct_group22_20();

int
funct_group22_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group22_21();

int
funct_group22_20()
{
  side_effect = side_effect + 1;
  funct_group22_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group22_22();

int
funct_group22_21()
{
  side_effect = side_effect + 1;
  funct_group22_22();
  return side_effect;
}

int
funct_group22_23();

int
funct_group22_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group22_23();
  return side_effect;
}

int
funct_group22_24();

int
funct_group22_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group22_24();
  return side_effect;
}

int
funct_group22_25();

int
funct_group22_24()
{
  side_effect = side_effect + 1;
  funct_group22_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group22_26();

int
funct_group22_25()
{
  side_effect = side_effect + 1;
  funct_group22_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group22_27();

int
funct_group22_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group22_28();

int
funct_group22_27()
{
  side_effect = side_effect + 1;
  funct_group22_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group22_29();

int
funct_group22_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group22_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group22_30();

int
funct_group22_29()
{
  side_effect = side_effect + 1;
  funct_group22_30();
  return side_effect;
}

int
funct_group22_31();

int
funct_group22_30()
{
  side_effect = side_effect + 1;
  funct_group22_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group22_32();

int
funct_group22_31()
{
  side_effect = side_effect + 1;
  funct_group22_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group22_33();

int
funct_group22_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group22_34();

int
funct_group22_33()
{
  side_effect = side_effect + 1;
  funct_group22_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group22_35();

int
funct_group22_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group22_36();

int
funct_group22_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group22_37();

int
funct_group22_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group22_37();
  return side_effect;
}

int
funct_group22_38();

int
funct_group22_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group22_38();
  return side_effect;
}

int
funct_group22_39();

int
funct_group22_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group22_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group22_40();

int
funct_group22_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group22_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group22_41();

int
funct_group22_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group22_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group22_42();

int
funct_group22_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group22_42();
  return side_effect;
}

int
funct_group22_43();

int
funct_group22_42()
{
  side_effect = side_effect + 1;
  funct_group22_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group22_44();

int
funct_group22_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group22_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group22_45();

int
funct_group22_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group22_46();

int
funct_group22_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group22_46();
  return side_effect;
}

int
funct_group22_47();

int
funct_group22_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group22_47();
  return side_effect;
}

int
funct_group22_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group23_1();

int
funct_group23_0()
{
  side_effect = side_effect + 1;
  funct_group23_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group23_2();

int
funct_group23_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group23_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group23_3();

int
funct_group23_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group23_3();
  return side_effect;
}

int
funct_group23_4();

int
funct_group23_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group23_4();
  return side_effect;
}

int
funct_group23_5();

int
funct_group23_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group23_5();
  return side_effect;
}

int
funct_group23_6();

int
funct_group23_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group23_7();

int
funct_group23_6()
{
  side_effect = side_effect + 1;
  funct_group23_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group23_8();

int
funct_group23_7()
{
  side_effect = side_effect + 1;
  funct_group23_8();
  return side_effect;
}

int
funct_group23_9();

int
funct_group23_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group23_9();
  return side_effect;
}

int
funct_group23_10();

int
funct_group23_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group23_10();
  return side_effect;
}

int
funct_group23_11();

int
funct_group23_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group23_12();

int
funct_group23_11()
{
  side_effect = side_effect + 1;
  funct_group23_12();
  return side_effect;
}

int
funct_group23_13();

int
funct_group23_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group23_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group23_14();

int
funct_group23_13()
{
  side_effect = side_effect + 1;
  funct_group23_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group23_15();

int
funct_group23_14()
{
  side_effect = side_effect + 1;
  funct_group23_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group23_16();

int
funct_group23_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group23_16();
  return side_effect;
}

int
funct_group23_17();

int
funct_group23_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group23_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group23_18();

int
funct_group23_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group23_18();
  return side_effect;
}

int
funct_group23_19();

int
funct_group23_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group23_19();
  return side_effect;
}

int
funct_group23_20();

int
funct_group23_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group23_21();

int
funct_group23_20()
{
  side_effect = side_effect + 1;
  funct_group23_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group23_22();

int
funct_group23_21()
{
  side_effect = side_effect + 1;
  funct_group23_22();
  return side_effect;
}

int
funct_group23_23();

int
funct_group23_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group23_23();
  return side_effect;
}

int
funct_group23_24();

int
funct_group23_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group23_24();
  return side_effect;
}

int
funct_group23_25();

int
funct_group23_24()
{
  side_effect = side_effect + 1;
  funct_group23_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group23_26();

int
funct_group23_25()
{
  side_effect = side_effect + 1;
  funct_group23_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group23_27();

int
funct_group23_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group23_28();

int
funct_group23_27()
{
  side_effect = side_effect + 1;
  funct_group23_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group23_29();

int
funct_group23_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group23_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group23_30();

int
funct_group23_29()
{
  side_effect = side_effect + 1;
  funct_group23_30();
  return side_effect;
}

int
funct_group23_31();

int
funct_group23_30()
{
  side_effect = side_effect + 1;
  funct_group23_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group23_32();

int
funct_group23_31()
{
  side_effect = side_effect + 1;
  funct_group23_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group23_33();

int
funct_group23_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group23_34();

int
funct_group23_33()
{
  side_effect = side_effect + 1;
  funct_group23_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group23_35();

int
funct_group23_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group23_36();

int
funct_group23_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group23_37();

int
funct_group23_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group23_37();
  return side_effect;
}

int
funct_group23_38();

int
funct_group23_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group23_38();
  return side_effect;
}

int
funct_group23_39();

int
funct_group23_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group23_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group23_40();

int
funct_group23_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group23_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group23_41();

int
funct_group23_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group23_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group23_42();

int
funct_group23_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group23_42();
  return side_effect;
}

int
funct_group23_43();

int
funct_group23_42()
{
  side_effect = side_effect + 1;
  funct_group23_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group23_44();

int
funct_group23_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group23_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group23_45();

int
funct_group23_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group23_46();

int
funct_group23_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group23_46();
  return side_effect;
}

int
funct_group23_47();

int
funct_group23_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group23_47();
  return side_effect;
}

int
funct_group23_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group24_1();

int
funct_group24_0()
{
  side_effect = side_effect + 1;
  funct_group24_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group24_2();

int
funct_group24_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group24_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group24_3();

int
funct_group24_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group24_3();
  return side_effect;
}

int
funct_group24_4();

int
funct_group24_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group24_4();
  return side_effect;
}

int
funct_group24_5();

int
funct_group24_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group24_5();
  return side_effect;
}

int
funct_group24_6();

int
funct_group24_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group24_7();

int
funct_group24_6()
{
  side_effect = side_effect + 1;
  funct_group24_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group24_8();

int
funct_group24_7()
{
  side_effect = side_effect + 1;
  funct_group24_8();
  return side_effect;
}

int
funct_group24_9();

int
funct_group24_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group24_9();
  return side_effect;
}

int
funct_group24_10();

int
funct_group24_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group24_10();
  return side_effect;
}

int
funct_group24_11();

int
funct_group24_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group24_12();

int
funct_group24_11()
{
  side_effect = side_effect + 1;
  funct_group24_12();
  return side_effect;
}

int
funct_group24_13();

int
funct_group24_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group24_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group24_14();

int
funct_group24_13()
{
  side_effect = side_effect + 1;
  funct_group24_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group24_15();

int
funct_group24_14()
{
  side_effect = side_effect + 1;
  funct_group24_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group24_16();

int
funct_group24_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group24_16();
  return side_effect;
}

int
funct_group24_17();

int
funct_group24_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group24_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group24_18();

int
funct_group24_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group24_18();
  return side_effect;
}

int
funct_group24_19();

int
funct_group24_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group24_19();
  return side_effect;
}

int
funct_group24_20();

int
funct_group24_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group24_21();

int
funct_group24_20()
{
  side_effect = side_effect + 1;
  funct_group24_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group24_22();

int
funct_group24_21()
{
  side_effect = side_effect + 1;
  funct_group24_22();
  return side_effect;
}

int
funct_group24_23();

int
funct_group24_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group24_23();
  return side_effect;
}

int
funct_group24_24();

int
funct_group24_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group24_24();
  return side_effect;
}

int
funct_group24_25();

int
funct_group24_24()
{
  side_effect = side_effect + 1;
  funct_group24_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group24_26();

int
funct_group24_25()
{
  side_effect = side_effect + 1;
  funct_group24_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group24_27();

int
funct_group24_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group24_28();

int
funct_group24_27()
{
  side_effect = side_effect + 1;
  funct_group24_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group24_29();

int
funct_group24_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group24_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group24_30();

int
funct_group24_29()
{
  side_effect = side_effect + 1;
  funct_group24_30();
  return side_effect;
}

int
funct_group24_31();

int
funct_group24_30()
{
  side_effect = side_effect + 1;
  funct_group24_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group24_32();

int
funct_group24_31()
{
  side_effect = side_effect + 1;
  funct_group24_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group24_33();

int
funct_group24_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group24_34();

int
funct_group24_33()
{
  side_effect = side_effect + 1;
  funct_group24_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group24_35();

int
funct_group24_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group24_36();

int
funct_group24_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group24_37();

int
funct_group24_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group24_37();
  return side_effect;
}

int
funct_group24_38();

int
funct_group24_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group24_38();
  return side_effect;
}

int
funct_group24_39();

int
funct_group24_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group24_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group24_40();

int
funct_group24_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group24_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group24_41();

int
funct_group24_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group24_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group24_42();

int
funct_group24_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group24_42();
  return side_effect;
}

int
funct_group24_43();

int
funct_group24_42()
{
  side_effect = side_effect + 1;
  funct_group24_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group24_44();

int
funct_group24_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group24_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group24_45();

int
funct_group24_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group24_46();

int
funct_group24_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group24_46();
  return side_effect;
}

int
funct_group24_47();

int
funct_group24_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group24_47();
  return side_effect;
}

int
funct_group24_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group25_1();

int
funct_group25_0()
{
  side_effect = side_effect + 1;
  funct_group25_1();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group25_2();

int
funct_group25_1()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group25_2();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();

  return side_effect;
}

int
funct_group25_3();

int
funct_group25_2()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group25_3();
  return side_effect;
}

int
funct_group25_4();

int
funct_group25_3()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group25_4();
  return side_effect;
}

int
funct_group25_5();

int
funct_group25_4()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group25_5();
  return side_effect;
}

int
funct_group25_6();

int
funct_group25_5()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_6();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group25_7();

int
funct_group25_6()
{
  side_effect = side_effect + 1;
  funct_group25_7();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group25_8();

int
funct_group25_7()
{
  side_effect = side_effect + 1;
  funct_group25_8();
  return side_effect;
}

int
funct_group25_9();

int
funct_group25_8()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group25_9();
  return side_effect;
}

int
funct_group25_10();

int
funct_group25_9()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  funct_group25_10();
  return side_effect;
}

int
funct_group25_11();

int
funct_group25_10()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_11();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group25_12();

int
funct_group25_11()
{
  side_effect = side_effect + 1;
  funct_group25_12();
  return side_effect;
}

int
funct_group25_13();

int
funct_group25_12()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  funct_group25_13();
  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_0 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group25_14();

int
funct_group25_13()
{
  side_effect = side_effect + 1;
  funct_group25_14();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group25_15();

int
funct_group25_14()
{
  side_effect = side_effect + 1;
  funct_group25_15();
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_5 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group25_16();

int
funct_group25_15()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_5 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  funct_group25_16();
  return side_effect;
}

int
funct_group25_17();

int
funct_group25_16()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group25_17();
  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group25_18();

int
funct_group25_17()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group25_18();
  return side_effect;
}

int
funct_group25_19();

int
funct_group25_18()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  funct_group25_19();
  return side_effect;
}

int
funct_group25_20();

int
funct_group25_19()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_20();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_4 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group25_21();

int
funct_group25_20()
{
  side_effect = side_effect + 1;
  funct_group25_21();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group25_22();

int
funct_group25_21()
{
  side_effect = side_effect + 1;
  funct_group25_22();
  return side_effect;
}

int
funct_group25_23();

int
funct_group25_22()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();
  funct_group25_23();
  return side_effect;
}

int
funct_group25_24();

int
funct_group25_23()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_1 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  funct_group25_24();
  return side_effect;
}

int
funct_group25_25();

int
funct_group25_24()
{
  side_effect = side_effect + 1;
  funct_group25_25();
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  class_1 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group25_26();

int
funct_group25_25()
{
  side_effect = side_effect + 1;
  funct_group25_26();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_4 instance_2(side_effect);
  instance_2.trigger();

  return side_effect;
}

int
funct_group25_27();

int
funct_group25_26()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_27();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}

int
funct_group25_28();

int
funct_group25_27()
{
  side_effect = side_effect + 1;
  funct_group25_28();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group25_29();

int
funct_group25_28()
{
  side_effect = side_effect + 1;
  class_3 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  funct_group25_29();
  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group25_30();

int
funct_group25_29()
{
  side_effect = side_effect + 1;
  funct_group25_30();
  return side_effect;
}

int
funct_group25_31();

int
funct_group25_30()
{
  side_effect = side_effect + 1;
  funct_group25_31();
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_0 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group25_32();

int
funct_group25_31()
{
  side_effect = side_effect + 1;
  funct_group25_32();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  return side_effect;
}

int
funct_group25_33();

int
funct_group25_32()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_33();
  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_2 instance_4(side_effect);
  instance_4.trigger();

  return side_effect;
}

int
funct_group25_34();

int
funct_group25_33()
{
  side_effect = side_effect + 1;
  funct_group25_34();
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_0 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_3 instance_5(side_effect);
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();
  instance_5.trigger();

  return side_effect;
}

int
funct_group25_35();

int
funct_group25_34()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group25_36();

int
funct_group25_35()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_36();
  class_2 instance_2(side_effect);
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  return side_effect;
}

int
funct_group25_37();

int
funct_group25_36()
{
  side_effect = side_effect + 1;
  class_2 instance_0(side_effect);
  instance_0.trigger();

  class_1 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group25_37();
  return side_effect;
}

int
funct_group25_38();

int
funct_group25_37()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  class_5 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  funct_group25_38();
  return side_effect;
}

int
funct_group25_39();

int
funct_group25_38()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  funct_group25_39();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group25_40();

int
funct_group25_39()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_2 instance_1(side_effect);
  instance_1.trigger();

  funct_group25_40();
  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_4 instance_3(side_effect);
  instance_3.trigger();

  return side_effect;
}

int
funct_group25_41();

int
funct_group25_40()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  funct_group25_41();
  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  return side_effect;
}

int
funct_group25_42();

int
funct_group25_41()
{
  side_effect = side_effect + 1;
  class_0 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  class_1 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  class_2 instance_3(side_effect);
  instance_3.trigger();

  class_3 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_4 instance_5(side_effect);
  instance_5.trigger();
  funct_group25_42();
  return side_effect;
}

int
funct_group25_43();

int
funct_group25_42()
{
  side_effect = side_effect + 1;
  funct_group25_43();
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  return side_effect;
}

int
funct_group25_44();

int
funct_group25_43()
{
  side_effect = side_effect + 1;
  class_5 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();

  class_4 instance_1(side_effect);
  instance_1.trigger();

  funct_group25_44();
  class_3 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();
  instance_2.trigger();

  return side_effect;
}

int
funct_group25_45();

int
funct_group25_44()
{
  side_effect = side_effect + 1;

  return side_effect;
}

int
funct_group25_46();

int
funct_group25_45()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_5 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();

  class_1 instance_4(side_effect);
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();
  instance_4.trigger();

  class_2 instance_5(side_effect);
  instance_5.trigger();
  funct_group25_46();
  return side_effect;
}

int
funct_group25_47();

int
funct_group25_46()
{
  side_effect = side_effect + 1;
  class_1 instance_0(side_effect);
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();
  instance_0.trigger();

  class_3 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  instance_1.trigger();
  funct_group25_47();
  return side_effect;
}

int
funct_group25_47()
{
  side_effect = side_effect + 1;
  class_4 instance_0(side_effect);
  instance_0.trigger();

  class_5 instance_1(side_effect);
  instance_1.trigger();
  instance_1.trigger();

  if (side_effect > 0) {
    throw my_error_t{ .data = { 0xDE, 0xAD } };
  }

  class_0 instance_2(side_effect);
  instance_2.trigger();
  instance_2.trigger();

  class_3 instance_3(side_effect);
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();
  instance_3.trigger();

  return side_effect;
}
