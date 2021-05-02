#pragma once

#include <array>
#include <cstdint>

namespace Trivia::Model {

enum class Field { POP, ROCK, SCIENCE, SPORTS };

class Board {
public:
    [[nodiscard]] Field getField(std::uint32_t position) const;

public:
    static constexpr std::uint32_t SIZE = 12;

private:
    static const std::array<Field, SIZE> _board;
};

}  // namespace Trivia::Model
