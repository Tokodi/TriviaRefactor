#pragma once

#include <chrono>
#include <cstdint>
#include <random>

namespace Trivia::Model {

// NOTE: Dice roll has a discrete uniform distribution
class Dice {
public:
    Dice();
    explicit Dice(std::uint32_t seed);

    void roll();

    [[nodiscard]] std::uint32_t getValue() const;

private:
    static constexpr std::uint32_t MIN_VALUE = 1;
    static constexpr std::uint32_t MAX_VALUE = 6;

private:
    std::uint32_t _currentValue{0};

    std::mt19937 _generator;
    std::uniform_int_distribution<std::uint32_t> _distribution{MIN_VALUE, MAX_VALUE};
};

}  // namespace Trivia::Model
