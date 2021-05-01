#include "dice.h"

#include <gtest/gtest.h>

using Trivia::Model::Dice;

TEST(DiceTest, testDiceReturnsAllFixValuesWithFixSeed) {
    Dice testDice{1};

    EXPECT_EQ(3, testDice.roll());
    EXPECT_EQ(6, testDice.roll());
    EXPECT_EQ(5, testDice.roll());
    EXPECT_EQ(6, testDice.roll());
    EXPECT_EQ(1, testDice.roll());
    EXPECT_EQ(1, testDice.roll());
    EXPECT_EQ(2, testDice.roll());
    EXPECT_EQ(6, testDice.roll());
    EXPECT_EQ(1, testDice.roll());
    EXPECT_EQ(2, testDice.roll());
    EXPECT_EQ(1, testDice.roll());
    EXPECT_EQ(3, testDice.roll());
    EXPECT_EQ(2, testDice.roll());
    EXPECT_EQ(3, testDice.roll());
    EXPECT_EQ(3, testDice.roll());
    EXPECT_EQ(5, testDice.roll());
    EXPECT_EQ(3, testDice.roll());
    EXPECT_EQ(6, testDice.roll());
    EXPECT_EQ(4, testDice.roll());
}
