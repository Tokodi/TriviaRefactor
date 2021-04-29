#include "player.h"

using std::move;
using std::ostream;
using std::string;
using std::uint32_t;

namespace Trivia::Model {

Player::Player(string name)
    : _name(move(name))
    , _numberOfCoins(0)
    , _isInPenalty(false)
    , _position(0) {
}

void Player::addCoin() {
    ++_numberOfCoins;
}

void Player::toPenalty() {
    _isInPenalty = true;
}

void Player::leavePenalty() {
    _isInPenalty = false;
}

void Player::step(uint32_t steps) {
    // TODO: Magic number 12 should be the boards length
    _position = (_position + steps) % 12; //NOLINT
}

const string& Player::getName() const {
    return _name;
}

uint32_t Player::getNumberOfCoins() const {
    return _numberOfCoins;
}

bool Player::isInPenalty() const {
    return _isInPenalty;
}

uint32_t Player::getPosition() const {
    return _position;
}

ostream& operator<<(ostream& os, const Player& player) {
    os << player._name;
    return os;
}

}  // namespace Trivia::Model
