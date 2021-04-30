#pragma once

#include <ostream>
#include <string>

namespace Trivia::Model {

class Player {
public:
    explicit Player(std::string name);

    void addCoin();
    void toPenalty();
    void leavePenalty();
    void step(std::uint32_t steps);

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] std::uint32_t getNumberOfCoins() const;
    [[nodiscard]] bool isInPenalty() const;
    [[nodiscard]] std::uint32_t getPosition() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    std::string _name;
    std::uint32_t _numberOfCoins;
    bool _isInPenalty;
    std::uint32_t _position;
};

}  // namespace Trivia::Model
