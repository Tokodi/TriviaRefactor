#pragma once

#include <array>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Game {
public:
    Game();

    bool   isPlayable();
    bool   add(string playerName);

    std::size_t howManyPlayers();
    void        roll(int roll);

    bool wasCorrectlyAnswered();
    bool wrongAnswer();

protected:
    static constexpr std::size_t NUMBER_OF_QUESTIONS_PER_SUBJECT = 50;
    static constexpr std::size_t NUMBER_OF_MAX_PLAYERS = 6;
    static constexpr std::size_t NUMBER_OF_COINS_TO_WIN = 6;

protected:
    string createRockQuestion(std::size_t index);
    void   askQuestion();
    string currentCategory();

    bool didPlayerWin();

protected:
    vector<string> players{};

    std::array<int, NUMBER_OF_MAX_PLAYERS> places{};
    std::array<int, NUMBER_OF_MAX_PLAYERS> purses{};
    std::array<bool, NUMBER_OF_MAX_PLAYERS> inPenaltyBox{};

    list<string> popQuestions{};
    list<string> scienceQuestions{};
    list<string> sportsQuestions{};
    list<string> rockQuestions{};

    unsigned int currentPlayer{0};
    bool         isGettingOutOfPenaltyBox{false};
};
