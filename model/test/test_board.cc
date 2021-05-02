#include <gtest/gtest.h>

#include "board.h"

using std::out_of_range;

using Trivia::Model::Board;
using Trivia::Model::Field;

TEST(BoardTest, testBoardIndexLimits) {
    Board testBoard;

    EXPECT_EQ(Field::POP, testBoard.getField(0));    // NOLINT
    EXPECT_EQ(Field::ROCK, testBoard.getField(11));  // NOLINT
}

TEST(BoardTest, testBoardPositionOutOfRange) {
    Board testBoard;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    EXPECT_THROW(testBoard.getField(12), out_of_range);  // NOLINT
#pragma GCC diagnostic pop
}

TEST(BoardTest, testBoardSize) {
    EXPECT_EQ(12, Board::SIZE);
}

TEST(BoardTest, testBoardFields) {
    Board testBoard;

    EXPECT_EQ(Field::POP, testBoard.getField(0));      // NOLINT
    EXPECT_EQ(Field::SCIENCE, testBoard.getField(1));  // NOLINT
    EXPECT_EQ(Field::SPORTS, testBoard.getField(2));   // NOLINT
    EXPECT_EQ(Field::ROCK, testBoard.getField(3));     // NOLINT
    EXPECT_EQ(Field::POP, testBoard.getField(4));      // NOLINT
    EXPECT_EQ(Field::SCIENCE, testBoard.getField(5));  // NOLINT
    EXPECT_EQ(Field::SPORTS, testBoard.getField(6));   // NOLINT
    EXPECT_EQ(Field::ROCK, testBoard.getField(7));     // NOLINT
    EXPECT_EQ(Field::POP, testBoard.getField(8));      // NOLINT
    EXPECT_EQ(Field::SCIENCE, testBoard.getField(9));  // NOLINT
    EXPECT_EQ(Field::SPORTS, testBoard.getField(10));  // NOLINT
    EXPECT_EQ(Field::ROCK, testBoard.getField(11));    // NOLINT
}
