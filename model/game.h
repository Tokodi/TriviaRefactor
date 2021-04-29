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
    string createRockQuestion(int index);
    void   askQuestion();
    string currentCategory();

    bool didPlayerWin();

protected:
    vector<string> players{};

    std::array<int, 6> places{};
    std::array<int, 6> purses{};
    std::array<bool, 6> inPenaltyBox{};

    list<string> popQuestions{};
    list<string> scienceQuestions{};
    list<string> sportsQuestions{};
    list<string> rockQuestions{};

    unsigned int currentPlayer;
    bool         isGettingOutOfPenaltyBox{false};
};
