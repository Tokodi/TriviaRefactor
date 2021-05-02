#include <gtest/gtest.h>

#include "dice.h"

using Trivia::Model::Dice;

TEST(DiceTest, testDiceInitialization) {
    Dice testDiceRandomSeed;
    Dice testDiceFixSeed{1};

    EXPECT_EQ(0, testDiceRandomSeed.getValue());
    EXPECT_EQ(0, testDiceFixSeed.getValue());
}

TEST(DiceTest, testDiceReturnsAllFixValuesWithFixSeed) {
    Dice testDice{1};

    testDice.roll();
    EXPECT_EQ(3, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(6, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(5, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(6, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(1, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(1, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(2, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(6, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(1, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(2, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(1, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(3, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(2, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(3, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(3, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(5, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(3, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(6, testDice.getValue());
    testDice.roll();
    EXPECT_EQ(4, testDice.getValue());
}
