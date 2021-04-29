#include "player.h"

#include <gtest/gtest.h>

#include <memory>

using std::make_unique;
using std::unique_ptr;

using Trivia::Model::Player;

class PlayerTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        _testPlayer = make_unique<Player>("TestElek");
    }

    void TearDown() override {
    }

    unique_ptr<Player> _testPlayer{};
};

TEST_F(PlayerTestFixture, testPlayerInitialization) {
    EXPECT_EQ("TestElek", _testPlayer->getName()); // NOLINT
    EXPECT_EQ(0, _testPlayer->getNumberOfCoins());
    EXPECT_FALSE(_testPlayer->isInPenalty());
    EXPECT_EQ(0, _testPlayer->getPosition());
}

TEST_F(PlayerTestFixture, testToPenalty) {
    EXPECT_FALSE(_testPlayer->isInPenalty());
    _testPlayer->toPenalty();
    EXPECT_TRUE(_testPlayer->isInPenalty());
}

TEST_F(PlayerTestFixture, testLeavePenalty) {
    EXPECT_FALSE(_testPlayer->isInPenalty());
    _testPlayer->leavePenalty();
    EXPECT_FALSE(_testPlayer->isInPenalty());
}

TEST_F(PlayerTestFixture, testCoinAddition) {
    EXPECT_EQ(0, _testPlayer->getNumberOfCoins());
    _testPlayer->addCoin();
    EXPECT_EQ(1, _testPlayer->getNumberOfCoins());
}

TEST_F(PlayerTestFixture, testSimpleStep) {
    EXPECT_EQ(0, _testPlayer->getPosition());
    _testPlayer->step(1);
    EXPECT_EQ(1, _testPlayer->getPosition());
}

TEST_F(PlayerTestFixture, testZeroStep) {
    EXPECT_EQ(0, _testPlayer->getPosition());
    _testPlayer->step(0);
    EXPECT_EQ(0, _testPlayer->getPosition());
}

TEST_F(PlayerTestFixture, testStepOwerflow) {
    EXPECT_EQ(0, _testPlayer->getPosition());
    _testPlayer->step(12); // NOLINT
    EXPECT_EQ(0, _testPlayer->getPosition());
}

TEST_F(PlayerTestFixture, testStepOwerflowWithOne) {
    EXPECT_EQ(0, _testPlayer->getPosition());
    _testPlayer->step(13); // NOLINT
    EXPECT_EQ(1, _testPlayer->getPosition());
}
