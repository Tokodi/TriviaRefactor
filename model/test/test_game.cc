#include <gtest/gtest.h>

#include <cstddef>
#include <exception>

#include "game.h"

using std::runtime_error;
using std::size_t;

using Trivia::Model::Game;

TEST(GameTest, TestGameInitialization) {
    Game testGame{4};

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

TEST(GameTest, TestPlayerAdditionOne) {
    Game testGame{4};

    testGame.addPlayer("TestElek");

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_EQ(0, testGame.getDice().getValue());
    EXPECT_EQ(1, testGame.getNumberOfPlayers());
    EXPECT_EQ("", testGame.getCurrentQuestion().first);
    EXPECT_EQ("", testGame.getCurrentQuestion().second);
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());
    EXPECT_FALSE(testGame.isOver());
}

TEST(GameTest, TestPlayerAdditionMore) {
    Game testGame{4};

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

TEST(GameTest, TestPlayerAdditionTooMany) {
    Game testGame{4};

    for (size_t i = 0; i < 6; ++i) {  // NOLINT
        testGame.addPlayer("TestElek" + std::to_string(i));
    }

    EXPECT_EQ(6, testGame.getNumberOfPlayers());  // NOLINT
    EXPECT_THROW(testGame.addPlayer("TestCrashElek"), runtime_error);
}

TEST(GameTest, TestStepNotEnoughPlayers) {
    Game testGame{4};

    EXPECT_THROW(testGame.step(), runtime_error);
    testGame.addPlayer("TestElek");
    EXPECT_THROW(testGame.step(), runtime_error);
}

TEST(GameTest, TestStepNextPlayerSelected) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    EXPECT_EQ("TestElek2", testGame.getCurrentPlayer().getName());
    testGame.step();
    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
}

TEST(GameTest, TestStepFirstPlayerSelectedAfterLast) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    testGame.step();
    testGame.step();
    testGame.step();

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
}

TEST(GameTest, TestStepDiceValueChanges) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    EXPECT_EQ(0, testGame.getDice().getValue());
    testGame.step();
    EXPECT_EQ(6, testGame.getDice().getValue()); // NOLINT
}

TEST(GameTest, TestStepPlayerPositionChanges) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_EQ(0, testGame.getCurrentPlayer().getPosition());

    testGame.addPlayer("TestElek2");
    testGame.step();

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_EQ(6, testGame.getCurrentPlayer().getPosition());
}

TEST(GameTest, TestStepPlayerStaysInPenalty) {
    Game testGame{4};

    testGame.addPlayer("TestElek");

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_FALSE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());

    testGame.addPlayer("TestElek2");
    testGame.step();
    testGame.wrongAnswer();

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());

    testGame.step();
    testGame.step();

    EXPECT_EQ("TestElek", testGame.getCurrentPlayer().getName());
    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isCurrentPlayerJustLeftPenalty());
}

TEST(GameTest, TestStepCurrentQuestionIsSetProperly) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    EXPECT_EQ("", testGame.getCurrentQuestion().first);
    EXPECT_EQ("", testGame.getCurrentQuestion().second);

    testGame.step();

    EXPECT_EQ("Sports", testGame.getCurrentQuestion().first);
    EXPECT_EQ("Sports Question 0", testGame.getCurrentQuestion().second);
}

TEST(GameTest, TestCorrectAnswerNotEnoughPlayers) {
    Game testGame{4};

    EXPECT_THROW(testGame.correctAnswer(), runtime_error);
    testGame.addPlayer("TestElek");
    EXPECT_THROW(testGame.correctAnswer(), runtime_error);
}

TEST(GameTest, TestCorrectAnswerPlayerNotInPenalty) {
    Game testGame{4};

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

TEST(GameTest, TestCorrectAnswerPlayerInPenalty) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");

    testGame.step();
    testGame.wrongAnswer();
    testGame.step();
    testGame.step();
    EXPECT_EQ(4, testGame.getDice().getValue());  // NOLINT

    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isOver());
    EXPECT_EQ(0, testGame.getCurrentPlayer().getNumberOfCoins());

    testGame.correctAnswer();

    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
    EXPECT_FALSE(testGame.isOver());
    EXPECT_EQ(0, testGame.getCurrentPlayer().getNumberOfCoins());
}

TEST(GameTest, TestCorrectAnswerPlayerWins) {
    Game testGame{4};

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

TEST(GameTest, TestWrongAnswerNotEnoughPlayers) {
    Game testGame{4};

    EXPECT_THROW(testGame.wrongAnswer(), runtime_error);
    testGame.addPlayer("TestElek");
    EXPECT_THROW(testGame.wrongAnswer(), runtime_error);
}

TEST(GameTest, TestWrongAnswere) {
    Game testGame{4};

    testGame.addPlayer("TestElek");
    testGame.addPlayer("TestElek2");
    testGame.step();
    testGame.wrongAnswer();

    EXPECT_TRUE(testGame.getCurrentPlayer().isInPenalty());
}
