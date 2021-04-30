#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <queue>
#include <string>

#include "game.h"
#include "player.h"

using std::array;
using std::cout;
using std::out_of_range;
using std::queue;
using std::runtime_error;
using std::size_t;
using std::string;
using std::vector;

class TestGame : public Trivia::Model::Game {
public:
    [[nodiscard]] const vector<Trivia::Model::Player>& getPlayers() const {
        return _players;
    }

    [[nodiscard]] const queue<string>& getPopQuestions() const {
        return popQuestions;
    }

    [[nodiscard]] const queue<string>& getRockQuestions() const {
        return rockQuestions;
    }

    [[nodiscard]] const queue<string>& getScienceQuestions() const {
        return scienceQuestions;
    }

    [[nodiscard]] const queue<string>& getSportQuestions() const {
        return sportsQuestions;
    }

    [[nodiscard]]vector<Trivia::Model::Player>::iterator getCurrentPlayerIt() const {
        return _currentPlayer;
    }
};

class GameTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        cout.rdbuf(nullptr); // Suppress cout while unit testing
    }

    void TearDown() override {
    }

protected:
    TestGame _testGame{};
};

TEST_F(GameTestFixture, TestGameInitialization) {
    EXPECT_EQ(0, _testGame.getNumberOfPlayers());
    EXPECT_EQ(_testGame.getPlayers().end(), _testGame.getCurrentPlayerIt());

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLIT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); //NOLINT

    for (size_t i = 0; i < 6; ++i) { // NOLINT
        EXPECT_THROW(_testGame.getPlayers().at(i), out_of_range);
    }
}

TEST_F(GameTestFixture, TestPlayerAdditionOne) {
    _testGame.addPlayer("TestElek");
    EXPECT_EQ(1, _testGame.getNumberOfPlayers());
    EXPECT_EQ(std::prev(_testGame.getPlayers().end()), _testGame.getCurrentPlayerIt());

    EXPECT_EQ(0, _testGame.getPlayers().at(0).getPosition());
    EXPECT_EQ(0, _testGame.getPlayers().at(0).getNumberOfCoins());
    EXPECT_FALSE(_testGame.getPlayers().at(0).isInPenalty());

    for (size_t i = 1; i < 6; ++i) { //NOLINT
        EXPECT_THROW(_testGame.getPlayers().at(i), out_of_range);
    }
}

TEST_F(GameTestFixture, TestPlayerAdditionTooMany) {
    for (size_t i = 0; i < 6; ++i) { // NOLINT
        _testGame.addPlayer("TestElek" + std::to_string(i));
    }

    EXPECT_EQ(6, _testGame.getNumberOfPlayers()); //NOLINT

    EXPECT_THROW(_testGame.addPlayer("TestCrashElek"), runtime_error);
}

TEST_F(GameTestFixture, TestRollNoPlayers) {
    EXPECT_THROW(_testGame.step(0), runtime_error);
}

TEST_F(GameTestFixture, TestRollOnePlayer) {
    _testGame.addPlayer("TestElek");
    EXPECT_EQ(1, _testGame.getNumberOfPlayers());
    EXPECT_EQ(std::prev(_testGame.getPlayers().end()), _testGame.getCurrentPlayerIt());

    _testGame.step(5); // NOLINT

    EXPECT_EQ(1, _testGame.getNumberOfPlayers());
    EXPECT_EQ(_testGame.getPlayers().begin(), _testGame.getCurrentPlayerIt());
    EXPECT_EQ(5, _testGame.getCurrentPlayerIt()->getPosition()); //NOLINT
    EXPECT_EQ(0, _testGame.getCurrentPlayerIt()->getNumberOfCoins());
    EXPECT_FALSE(_testGame.getCurrentPlayerIt()->isInPenalty());
}

TEST_F(GameTestFixture, TestRollPopOnePlayer) {
    _testGame.addPlayer("TestElek");

    _testGame.step(0);

    EXPECT_EQ(49, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestRollRockOnePlayer) {
    _testGame.addPlayer("TestElek");

    _testGame.step(3); // NOLINT

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(49, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestRollScienceOnePlayer) {
    _testGame.addPlayer("TestElek");

    _testGame.step(1);

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(49, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestRollSportOnePlayer) {
    _testGame.addPlayer("TestElek");

    _testGame.step(2); // NOLINT

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(49, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestWrongAnswereNoPlayer) {
    EXPECT_THROW(_testGame.wrongAnswer(), runtime_error);
    EXPECT_EQ(_testGame.getPlayers().end(), _testGame.getCurrentPlayerIt());
}

TEST_F(GameTestFixture, TestWrongAnswereOnePlayer) {
    _testGame.addPlayer("TestElek");
    EXPECT_EQ(std::prev(_testGame.getPlayers().end()), _testGame.getCurrentPlayerIt());

    _testGame.wrongAnswer();
    EXPECT_TRUE(_testGame.getCurrentPlayerIt()->isInPenalty());
}

TEST_F(GameTestFixture, TestRightAnswereNoPlayer) {
    EXPECT_THROW(_testGame.wrongAnswer(), runtime_error);
    EXPECT_EQ(_testGame.getPlayers().end(), _testGame.getCurrentPlayerIt());
}

TEST_F(GameTestFixture, TestRightAnswereOnePlayer) {
    _testGame.addPlayer("TestElek");
    EXPECT_EQ(std::prev(_testGame.getPlayers().end()), _testGame.getCurrentPlayerIt());

    _testGame.correctAnswer();
    EXPECT_FALSE(_testGame.getCurrentPlayerIt()->isInPenalty());
}

TEST_F(GameTestFixture, TestRightAnswereAfterWrongRollingOddMorePlayer) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek1");
    EXPECT_EQ(std::prev(_testGame.getPlayers().end()), _testGame.getCurrentPlayerIt());

    auto _testEleksIt = _testGame.getCurrentPlayerIt();

    _testGame.wrongAnswer();
    _testGame.step(5); // NOLINT

    EXPECT_EQ(5, _testGame.getCurrentPlayerIt()->getPosition()); // NOLINT
    EXPECT_TRUE(_testEleksIt->isInPenalty());

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_THROW(_testGame.getPlayers().at(i), out_of_range);
    }

    _testGame.correctAnswer();

    EXPECT_TRUE(_testEleksIt->isInPenalty());

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_THROW(_testGame.getPlayers().at(i), out_of_range);
    }
}

TEST_F(GameTestFixture, TestRightAnswereAfterWrongRollingEvenMorePlayer) {
    _testGame.addPlayer("TestElek");
    _testGame.addPlayer("TestElek1");
    EXPECT_EQ(std::prev(_testGame.getPlayers().end()), _testGame.getCurrentPlayerIt());

    auto _testEleksIt = _testGame.getCurrentPlayerIt();

    _testGame.wrongAnswer();

    _testGame.step(4); // NOLINT

    EXPECT_EQ(4, _testGame.getCurrentPlayerIt()->getPosition()); // NOLINT
    EXPECT_TRUE(_testEleksIt->isInPenalty());

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_THROW(_testGame.getPlayers().at(i), out_of_range);
    }

    _testGame.correctAnswer();
    EXPECT_TRUE(_testEleksIt->isInPenalty());

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_THROW(_testGame.getPlayers().at(i), out_of_range);
    }
}
