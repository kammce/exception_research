#include <array>
#include <cstdint>

namespace estell::cxxabiv1::arm {
struct short16_table_t
{
  std::uint8_t instructions3;
  std::uint8_t instructions2;
  std::uint8_t instructions1;
  std::uint8_t personality_select;
};

struct long16_32_table_t
{
  // All other words
  std::array<std::uint8_t, 32> instructions;
  // First word
  std::uint8_t instructions2;
  std::uint8_t instructions1;
  std::uint8_t word_count;
  std::uint8_t personality_select;
};

}  // namespace estell::cxxabiv1::arm