#include "board.h"

namespace Trivia::Model {

Field Board::getField(std::uint32_t position) const {
    return _board.at(position);
}

const std::array<Field, Board::SIZE> Board::_board = { Field::POP, Field::SCIENCE, Field::SPORTS, Field::ROCK,
                                                             Field::POP, Field::SCIENCE, Field::SPORTS, Field::ROCK,
                                                             Field::POP, Field::SCIENCE, Field::SPORTS, Field::ROCK };

}  // namespace Trivia::Model
