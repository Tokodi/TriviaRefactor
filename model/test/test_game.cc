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
    const list<string>& getPopQuestions() const {
        return popQuestions;
    }

    const list<string>& getRockQuestions() const {
        return rockQuestions;
    }

    const list<string>& getScienceQuestions() const {
        return scienceQuestions;
    }

    const list<string>& getSportQuestions() const {
        return sportsQuestions;
    }

    const array<int, 6>& getPlaces() const {
        return places;
    }

    const array<int, 6>& getPurses() const {
        return purses;
    }

    const array<bool, 6>& getPenaltyBoxes() const {
        return inPenaltyBox;
    }

    unsigned int getCurrentPlayerId() const {
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

    EXPECT_EQ(50, _testGame.getPopQuestions().size());
    EXPECT_EQ(50, _testGame.getRockQuestions().size());
    EXPECT_EQ(50, _testGame.getScienceQuestions().size());
    EXPECT_EQ(50, _testGame.getSportQuestions().size());

    EXPECT_EQ(6, _testGame.getPlaces().size());
    EXPECT_EQ(6, _testGame.getPurses().size());
    EXPECT_EQ(6, _testGame.getPenaltyBoxes().size());

    for (size_t i = 0; i < 6; ++i) {
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

    for (size_t i = 1; i < 6; ++i) {
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }
}

TEST_F(GameTestFixture, TestPlayerAdditionTooMany) {
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_TRUE(_testGame.add("TestElek" + i));
    }

    EXPECT_EQ(6, _testGame.howManyPlayers());

    EXPECT_THROW(_testGame.add("TestCrashElek"), out_of_range);
}

TEST_F(GameTestFixture, TestRollNoPlayers) {
    EXPECT_THROW(_testGame.roll(0), out_of_range);
}

TEST_F(GameTestFixture, TestRollOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));
    EXPECT_EQ(1, _testGame.howManyPlayers());
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());

    _testGame.roll(5);

    EXPECT_EQ(1, _testGame.howManyPlayers());
    EXPECT_EQ(0, _testGame.getCurrentPlayerId());
    EXPECT_EQ(5, _testGame.getPlaces().at(_testGame.getCurrentPlayerId()));
    EXPECT_EQ(0, _testGame.getPurses().at(_testGame.getCurrentPlayerId()));
    EXPECT_FALSE(_testGame.getPenaltyBoxes().at(_testGame.getCurrentPlayerId()));
}

TEST_F(GameTestFixture, TestRollPopOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(0);

    EXPECT_EQ(49, _testGame.getPopQuestions().size());
    EXPECT_EQ(50, _testGame.getRockQuestions().size());
    EXPECT_EQ(50, _testGame.getScienceQuestions().size());
    EXPECT_EQ(50, _testGame.getSportQuestions().size());
}

TEST_F(GameTestFixture, TestRollRockOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(3);

    EXPECT_EQ(50, _testGame.getPopQuestions().size());
    EXPECT_EQ(49, _testGame.getRockQuestions().size());
    EXPECT_EQ(50, _testGame.getScienceQuestions().size());
    EXPECT_EQ(50, _testGame.getSportQuestions().size());
}

TEST_F(GameTestFixture, TestRollScienceOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(1);

    EXPECT_EQ(50, _testGame.getPopQuestions().size());
    EXPECT_EQ(50, _testGame.getRockQuestions().size());
    EXPECT_EQ(49, _testGame.getScienceQuestions().size());
    EXPECT_EQ(50, _testGame.getSportQuestions().size());
}

TEST_F(GameTestFixture, TestRollSportOnePlayer) {
    EXPECT_TRUE(_testGame.add("TestElek"));

    _testGame.roll(2);

    EXPECT_EQ(50, _testGame.getPopQuestions().size());
    EXPECT_EQ(50, _testGame.getRockQuestions().size());
    EXPECT_EQ(50, _testGame.getScienceQuestions().size());
    EXPECT_EQ(49, _testGame.getSportQuestions().size());
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

    _testGame.roll(5);

    EXPECT_EQ(_testEleksId + 1, _testGame.getCurrentPlayerId());
    EXPECT_EQ(5, _testGame.getPlaces().at(_testGame.getCurrentPlayerId()));
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) {
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }

    EXPECT_TRUE(_testGame.wasCorrectlyAnswered());

    EXPECT_EQ(_testEleksId, _testGame.getCurrentPlayerId());
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) {
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

    _testGame.roll(4);

    EXPECT_EQ(_testEleksId + 1, _testGame.getCurrentPlayerId());
    EXPECT_EQ(4, _testGame.getPlaces().at(_testGame.getCurrentPlayerId()));
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) {
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }

    EXPECT_TRUE(_testGame.wasCorrectlyAnswered());

    EXPECT_EQ(_testEleksId, _testGame.getCurrentPlayerId());
    EXPECT_TRUE(_testGame.getPenaltyBoxes().at(_testEleksId));

    for (size_t i = 2; i < 6; ++i) {
        EXPECT_EQ(0, _testGame.getPlaces().at(i));
        EXPECT_EQ(0, _testGame.getPurses().at(i));
        EXPECT_FALSE(_testGame.getPenaltyBoxes().at(i));
    }
}
