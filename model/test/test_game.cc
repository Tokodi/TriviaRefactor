#include <gtest/gtest.h>

#include <cstddef>
#include <exception>

#include "game.h"

using std::runtime_error;
using std::size_t;

using Trivia::Model::Game;

TEST(GameTestFixture, TestGameInitialization) {
    Game testGame{};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    EXPECT_THROW(testGame.getCurrentPlayer(), runtime_error);  // NOLINT
#pragma GCC diagnostic pop
    EXPECT_EQ(0, testGame.getDice().getValue());
    EXPECT_EQ(0, testGame.getNumberOfPlayers());
    EXPECT_EQ("", testGame.getCurrentQuestion().first);
    EXPECT_EQ("", testGame.getCurrentQuestion().second);
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());
    EXPECT_FALSE(testGame.isOver());
}

TEST(GameTestFixture, TestPlayerAdditionOne) {
    Game testGame{};

    testGame.addPlayer("TestElek");

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_EQ(0, testGame.getDice().getValue());
    EXPECT_EQ(1, testGame.getNumberOfPlayers());
    EXPECT_EQ("", testGame.getCurrentQuestion().first);
    EXPECT_EQ("", testGame.getCurrentQuestion().second);
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());
    EXPECT_FALSE(testGame.isOver());
}

TEST(GameTestFixture, TestPlayerAdditionMore) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");
    testGame.addPlayer("TestElek3");

    EXPECT_EQ("TestElek3", testGame.getCurrentPlayer().getName());
    EXPECT_EQ(0, testGame.getDice().getValue());
    EXPECT_EQ(3, testGame.getNumberOfPlayers());  // NOLINT
    EXPECT_EQ("", testGame.getCurrentQuestion().first);
    EXPECT_EQ("", testGame.getCurrentQuestion().second);
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());
    EXPECT_FALSE(testGame.isOver());
}

TEST(GameTestFixture, TestPlayerAdditionTooMany) {
    Game testGame{};

    for (size_t i = 0; i < 6; ++i) {  // NOLINT
        testGame.addPlayer("TestElek" + std::to_string(i));
    }

    EXPECT_EQ(6, testGame.getNumberOfPlayers());  // NOLINT
    EXPECT_THROW(testGame.addPlayer("TestCrashElek"), runtime_error);
}

TEST(GameTestFixture, TestStepNotEnoughPlayers) {
    Game testGame{};

    EXPECT_THROW(testGame.step(), runtime_error);
    testGame.addPlayer("TestElek");
    EXPECT_THROW(testGame.step(), runtime_error);
}

TEST(GameTestFixture, TestStepNextPlayerSelected) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    EXPECT_EQ("TestElek2", testGame.getCurrentPlayer().getName());
    testGame.step();
    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
}

TEST(GameTestFixture, TestStepFirstPlayerSelectedAfterLast) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    testGame.step();
    testGame.step();
    testGame.step();

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
}

TEST(GameTestFixture, TestStepDiceValueChanges) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    EXPECT_EQ(0, testGame.getDice().getValue());
    testGame.step();
    EXPECT_EQ(6, testGame.getDice().getValue());
}

// TODO: Test step player leaves penalty
// TODO: Test step player stays in penalty
// TODO: Test step currentQuestion set properly

TEST(GameTestFixture, TestCorrectAnswerNotEnoughPlayers) {
    Game testGame{};

    EXPECT_THROW(testGame.correctAnswer(), runtime_error);
    testGame.addPlayer("TestElek");
    EXPECT_THROW(testGame.correctAnswer(), runtime_error);
}

TEST(GameTestFixture, TestCorrectAnswerPlayerNotInPenalty) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    testGame.step();

    EXPECT_FALSE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isOver());
    EXPECT_EQ(0, testGame.getCurrentPlayer().getNumberOfCoins());

    testGame.correctAnswer();

    EXPECT_FALSE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isOver());
    EXPECT_EQ(1, testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST(GameTestFixture, TestCorrectAnswerPlayerInPenalty) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    testGame.step();
    testGame.wrongAnswer();
    testGame.step();
    testGame.step();                              // Dice value is 4 so we don't get out of penalty
    EXPECT_EQ(4, testGame.getDice().getValue());  // NOLINT

    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isOver());
    EXPECT_EQ(0, testGame.getCurrentPlayer().getNumberOfCoins());

    testGame.correctAnswer();

    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isOver());
    EXPECT_EQ(0, testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST(GameTestFixture, TestCorrectAnswerPlayerWins) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    EXPECT_FALSE(testGame.isOver());

    for (size_t i = 0; i < 11; ++i) {  // NOLINT
        testGame.step();
        testGame.correctAnswer();
    }

    EXPECT_TRUE(testGame.isOver());
    EXPECT_EQ(6, testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST(GameTestFixture, TestWrongAnswerNotEnoughPlayers) {
    Game testGame{};

    EXPECT_THROW(testGame.wrongAnswer(), runtime_error);
    testGame.addPlayer("TestElek");
    EXPECT_THROW(testGame.wrongAnswer(), runtime_error);
}

TEST(GameTestFixture, TestWrongAnswere) {
    Game testGame{};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");
    testGame.step();
    testGame.wrongAnswer();

    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
}

// TODO: Not playable after game over
