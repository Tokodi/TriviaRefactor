#include "game.h"

#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <string>
#include <exception>

using std::array;
using std::cout;
using std::list;
using std::size_t;
using std::string;
using std::out_of_range;

class TestGame : public Game {
public:
    [[nodiscard]] const list<string>& getPopQuestions() const {
        return popQuestions;
    }

    [[nodiscard]] const list<string>& getRockQuestions() const {
        return rockQuestions;
    }

    [[nodiscard]] const list<string>& getScienceQuestions() const {
        return scienceQuestions;
    }

    [[nodiscard]] const list<string>& getSportQuestions() const {
        return sportsQuestions;
    }

    [[nodiscard]] const array<int, 6>& getPlaces() const { // NOLINT
        return places;
    }

    [[nodiscard]] const array<int, 6>& getPurses() const { // NOLINT
        return purses;
    }

    [[nodiscard]] const array<bool, 6>& getPenaltyBoxes() const { // NOLINT
        return inPenaltyBox;
    }

    [[nodiscard]]unsigned int getCurrentPlayerId() const {
        return currentPlayer;
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
    EXPECT_FALSE(_testGame.isPlayable());
    EXPECT_EQ(0, _testGame.howManyPlayers());
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLIT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); //NOLINT

    EXPECT_EQ(6, _testGame.getPlaces().size()); // NOLINT
    EXPECT_EQ(6, _testGame.getPurses().size()); // NOLINT
    EXPECT_EQ(6, _testGame.getPenaltyBoxes().size()); // NOLINT

    for (size_t i = 0; i < 6; ++i) { // NOLINT
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }
}

TEST_F(GameTestFixture, TestPlayerAdditionOne) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_EQ(1, _testGame.howManyPlayers());
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());


    EXPECT_EQ(0, _testGame.getPlaces().at(0));
    EXPECT_EQ(0, _testGame.getPurses().at(0));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(0));

    for (size_t i = 1; i < 6; ++i) { //NOLINT
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }
}

TEST_F(GameTestFixture, TestPlayerAdditionTooMany) {
    for (size_t i = 0; i < 6; ++i) { // NOLINT
        EXPECT_TRUE(_testGame.add("TestElek" + std::to_string(i)));
    }

    EXPECT_EQ(6, _testGame.howManyPlayers()); //NOLINT

    EXPECT_THROW(_testGame.add("TestCrashElek"), out_of_range);
}

TEST_F(GameTestFixture, TestRollNoPlayers) {
    EXPECT_THROW(_testGame.roll(0), out_of_range);
}

TEST_F(GameTestFixture, TestRollOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_EQ(1, _testGame.howManyPlayers());
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    _testGame.roll(5); // NOLINT

    EXPECT_EQ(1, _testGame.howManyPlayers());
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());
    EXPECT_EQ(5, _testGame.getPlaces().at(_testGame.getCurrentPlayerId())); //NOLINT
    EXPECT_EQ(0, _testGame.getPurses().at(_testGame.getCurrentPlayerId()));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestRollPopOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(0);

    EXPECT_EQ(49, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestRollRockOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(3); // NOLINT

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(49, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestRollScienceOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(1);

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(49, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestRollSportOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(2); // NOLINT

    EXPECT_EQ(50, _testGame.getPopQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getRockQuestions().size()); // NOLINT
    EXPECT_EQ(50, _testGame.getScienceQuestions().size()); // NOLINT
    EXPECT_EQ(49, _testGame.getSportQuestions().size()); // NOLINT
}

TEST_F(GameTestFixture, TestWrongAnswereNoPlayer) {
    EXPECT_THROW(_testGame.wrongAnswer(), out_of_range);
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());
    EXPECT_EQ(0, _testGame.getPurses().at(_testGame.getCurrentPlayerId()));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestWrongAnswereOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    unsigned int _testEleksId = _testGame.getCurrentPlayerId();

    EXPECT_TRUE(_testGame.wrongAnswer()); // NOTE: Next player is also TestElek
    EXPECT_EQ(_testEleksId, _testGame.getCurrentPlayerId());
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestWrongAnswereMorePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_TRUE(_testGame.add("TestElek1"));
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    unsigned int _testEleksId = _testGame.getCurrentPlayerId();

    EXPECT_TRUE(_testGame.wrongAnswer());
    EXPECT_EQ(_testEleksId + 1, _testGame.getCurrentPlayerId());
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestRightAnswereNoPlayer) {
    EXPECT_THROW(_testGame.wrongAnswer(), out_of_range);
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());
    EXPECT_EQ(0, _testGame.getPurses().at(_testGame.getCurrentPlayerId()));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestRightAnswereOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    unsigned int _testEleksId = _testGame.getCurrentPlayerId();

    EXPECT_TRUE(_testGame.wasCorrectlyAnswered()); // NOTE: Next player is also TestElek
    EXPECT_EQ(_testEleksId, _testGame.getCurrentPlayerId());
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testEleksId));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestRightAnswereMorePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_TRUE(_testGame.add("TestElek1"));
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    unsigned int _testEleksId = _testGame.getCurrentPlayerId();

    EXPECT_TRUE(_testGame.wasCorrectlyAnswered());
    EXPECT_EQ(_testEleksId + 1, _testGame.getCurrentPlayerId());
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testEleksId));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestRightAnswereAfterWrongRollingOddMorePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_TRUE(_testGame.add("TestElek1"));
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    unsigned int _testEleksId = _testGame.getCurrentPlayerId();

    EXPECT_TRUE(_testGame.wrongAnswer());

    _testGame.roll(5); // NOLINT

    EXPECT_EQ(_testEleksId + 1, _testGame.getCurrentPlayerId());
    EXPECT_EQ(5, _testGame.getPlaces().at(_testGame.getCurrentPlayerId())); // NOLINT
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }

    EXPECT_TRUE(_testGame.wasCorrectlyAnswered());

    EXPECT_EQ(_testEleksId, _testGame.getCurrentPlayerId());
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }
}

TEST_F(GameTestFixture, TestRightAnswereAfterWrongRollingEvenMorePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_TRUE(_testGame.add("TestElek1"));
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    unsigned int _testEleksId = _testGame.getCurrentPlayerId();

    EXPECT_TRUE(_testGame.wrongAnswer());

    _testGame.roll(4); // NOLINT

    EXPECT_EQ(_testEleksId + 1, _testGame.getCurrentPlayerId());
    EXPECT_EQ(4, _testGame.getPlaces().at(_testGame.getCurrentPlayerId())); // NOLINT
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }

    EXPECT_TRUE(_testGame.wasCorrectlyAnswered());

    EXPECT_EQ(_testEleksId, _testGame.getCurrentPlayerId());
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) { // NOLINT
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }
}
