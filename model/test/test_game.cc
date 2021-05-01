#include <gtest/gtest.h>

#include <exception>
#include <iostream>

#include "game.h"

using std::runtime_error;
using std::cout;
using std::size_t;

using Trivia::Model::Game;

class GameTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        cout.rdbuf(nullptr); // Suppress cout while unit testing
    }

    void TearDown() override {
    }

protected:
    Game _testGame{};
};

TEST_F(GameTestFixture, TestGameInitialization) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    EXPECT_THROW(_testGame.getCurrentPlayer(), runtime_error); // NOLINT
#pragma GCC diagnostic pop
    EXPECT_EQ(0, _testGame.getNumberOfPlayers());
    EXPECT_EQ(0, _testGame.getDiceValue());
    EXPECT_FALSE(_testGame.isOver());
}

TEST_F(GameTestFixture, TestPlayerAdditionOne) {
    _testGame.addPlayer("TestElek");

    EXPECT_EQ("TestElek", _testGame.getCurrentPlayer().getName());
    EXPECT_EQ(1, _testGame.getNumberOfPlayers());
    EXPECT_EQ(0, _testGame.getDiceValue());
    EXPECT_FALSE(_testGame.isOver());
}

TEST_F(GameTestFixture, TestPlayerAdditionMore) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");
    _testGame.addPlayer("TestElek3");

    EXPECT_EQ("TestElek3", _testGame.getCurrentPlayer().getName());
    EXPECT_EQ(3, _testGame.getNumberOfPlayers()); // NOLINT
    EXPECT_EQ(0, _testGame.getDiceValue());
    EXPECT_FALSE(_testGame.isOver());
}

TEST_F(GameTestFixture, TestPlayerAdditionTooMany) {
    for (size_t i = 0; i < 6; ++i) { // NOLINT
        _testGame.addPlayer("TestElek" + std::to_string(i));
    }

    EXPECT_EQ(6, _testGame.getNumberOfPlayers()); // NOLINT
    EXPECT_THROW(_testGame.addPlayer("TestCrashElek"), runtime_error);
}

TEST_F(GameTestFixture, TestStepNotEnoughPlayers) {
    EXPECT_THROW(_testGame.step(), runtime_error);
    _testGame.addPlayer("TestElek");
    EXPECT_THROW(_testGame.step(), runtime_error);
}

TEST_F(GameTestFixture, TestStepNextPlayerSelected) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");

    EXPECT_EQ("TestElek2", _testGame.getCurrentPlayer().getName());
    _testGame.step();
    EXPECT_EQ("TestElek", _testGame.getCurrentPlayer().getName());
}

TEST_F(GameTestFixture, TestStepFirstPlayerSelectedAfterLast) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");

    _testGame.step();
    _testGame.step();
    _testGame.step();

    EXPECT_EQ("TestElek", _testGame.getCurrentPlayer().getName());
}

TEST_F(GameTestFixture, TestStepDiceValueChanges) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");

    EXPECT_EQ(0, _testGame.getDiceValue());
    _testGame.step();
    EXPECT_EQ(6, _testGame.getDiceValue());
}

TEST_F(GameTestFixture, TestCorrectAnswerNotEnoughPlayers) {
    EXPECT_THROW(_testGame.correctAnswer(), runtime_error);
    _testGame.addPlayer("TestElek");
    EXPECT_THROW(_testGame.correctAnswer(), runtime_error);
}

TEST_F(GameTestFixture, TestCorrectAnswerPlayerNotInPenalty) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");

    _testGame.step();

    EXPECT_FALSE(_testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(_testGame.isOver());
    EXPECT_EQ(0, _testGame.getCurrentPlayer().getNumberOfCoins());

    _testGame.correctAnswer();

    EXPECT_FALSE(_testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(_testGame.isOver());
    EXPECT_EQ(1, _testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST_F(GameTestFixture, TestCorrectAnswerPlayerInPenalty) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");

    _testGame.step();
    _testGame.wrongAnswer();
    _testGame.step();
    _testGame.step(); // Dice value is 4 so we don't get out of penalty
    EXPECT_EQ(4, _testGame.getDiceValue()); // NOLINT

    EXPECT_TRUE(_testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(_testGame.isOver());
    EXPECT_EQ(0, _testGame.getCurrentPlayer().getNumberOfCoins());

    _testGame.correctAnswer();

    EXPECT_TRUE(_testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(_testGame.isOver());
    EXPECT_EQ(0, _testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST_F(GameTestFixture, TestCorrectAnswerPlayerWins) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");

    EXPECT_FALSE(_testGame.isOver());

    for (size_t i = 0; i < 11; ++i) { // NOLINT
        _testGame.step();
        _testGame.correctAnswer();
    }

    EXPECT_TRUE(_testGame.isOver());
    EXPECT_EQ(6, _testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST_F(GameTestFixture, TestWrongAnswerNotEnoughPlayers) {
    EXPECT_THROW(_testGame.wrongAnswer(), runtime_error);
    _testGame.addPlayer("TestElek");
    EXPECT_THROW(_testGame.wrongAnswer(), runtime_error);
}

TEST_F(GameTestFixture, TestWrongAnswere) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek2");
    _testGame.step();
    _testGame.wrongAnswer();

    EXPECT_TRUE(_testGame.getCurrentPlayer().isInPenalty());
}

// TODO: Not playable after game over
