#include "board.h"

#include <gtest/gtest.h>

using std::out_of_range;

using Trivia::Model::Board;
using Trivia::Model::Field;

TEST(BoardTest, testBoardIndexLimits) {
    Board board;

    EXPECT_EQ(Field::POP, board.getField(0)); //NOLINT
    EXPECT_EQ(Field::ROCK, board.getField(11)); //NOLINT
}

TEST(BoardTest, testBoardPositionOutOfRange) {
    Board board;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    EXPECT_THROW(board.getField(12), out_of_range); //NOLINT
#pragma GCC diagnostic pop
}

TEST(BoardTest, testBoardSize) {
    EXPECT_EQ(12, Board::SIZE);
}

TEST(BoardTest, testBoardFields) {
    Board board;

    EXPECT_EQ(Field::POP, board.getField(0)); //NOLINT
    EXPECT_EQ(Field::SCIENCE, board.getField(1)); //NOLINT
    EXPECT_EQ(Field::SPORTS, board.getField(2)); //NOLINT
    EXPECT_EQ(Field::ROCK, board.getField(3)); //NOLINT
    EXPECT_EQ(Field::POP, board.getField(4)); //NOLINT
    EXPECT_EQ(Field::SCIENCE, board.getField(5)); //NOLINT
    EXPECT_EQ(Field::SPORTS, board.getField(6)); //NOLINT
    EXPECT_EQ(Field::ROCK, board.getField(7)); //NOLINT
    EXPECT_EQ(Field::POP, board.getField(8)); //NOLINT
    EXPECT_EQ(Field::SCIENCE, board.getField(9)); //NOLINT
    EXPECT_EQ(Field::SPORTS, board.getField(10)); //NOLINT
    EXPECT_EQ(Field::ROCK, board.getField(11)); //NOLINT
}
