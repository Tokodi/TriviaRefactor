#include "board.h"

using std::uint32_t;
using std::array;

namespace Trivia::Model {

Field Board::getField(uint32_t position) const {
    return _board.at(position);
}

const array<Field, Board::SIZE> Board::_board = { Field::POP, Field::SCIENCE, Field::SPORTS, Field::ROCK,
                                                  Field::POP, Field::SCIENCE, Field::SPORTS, Field::ROCK,
                                                  Field::POP, Field::SCIENCE, Field::SPORTS, Field::ROCK };

}  // namespace Trivia::Model
