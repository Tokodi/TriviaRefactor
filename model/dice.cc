#include "dice.h"

using std::uint32_t;
using std::uint64_t;
using std::chrono::system_clock;

namespace Trivia::Model {

Dice::Dice() : _generator(static_cast<uint64_t>(system_clock::now().time_since_epoch().count())) {
}

Dice::Dice(std::uint32_t seed) : _generator(seed) {
}

void Dice::roll() {
    _currentValue = _distribution(_generator);
}

uint32_t Dice::getValue() const {
    return _currentValue;
}

}  // namespace Trivia::Model
