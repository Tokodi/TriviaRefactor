#include "dice.h"

using std::chrono::system_clock;
using std::uint32_t;
using std::uint64_t;

namespace Trivia::Model {

Dice::Dice()
    : _generator(static_cast<uint64_t>(system_clock::now().time_since_epoch().count())) {
}

Dice::Dice(std::uint32_t seed)
    : _generator(seed) {
}

uint32_t Dice::roll() {
   return _distribution(_generator);
}

}  // namespace Trivia::Model
