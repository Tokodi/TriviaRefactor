#include "game.h"

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <sstream>

using namespace std;
using std::size_t;

Game::Game() {
    for (size_t i = 0; i < NUMBER_OF_QUESTIONS_PER_SUBJECT; ++i) {
        ostringstream oss(ostringstream::out);
        oss << "Pop Question " << i;

        popQuestions.emplace_back(oss.str());

        char str[255]; // NOLINT
        sprintf(str, "Science Question %zu", i);
        scienceQuestions.emplace_back(str);

        char str1[255]; // NOLINT
        sprintf(str1, "Sports Question %zu", i);
        sportsQuestions.emplace_back(str1);

        rockQuestions.emplace_back(createRockQuestion(i));
    }
}

string Game::createRockQuestion(size_t index) {
    char indexStr[127]; // NOLINT
    sprintf(indexStr, "Rock Question %zu", index);
    return indexStr;
}

bool Game::isPlayable() {
    return (howManyPlayers() >= 2);
}

bool Game::add(string playerName) {
    players.emplace_back(playerName);
    places.at(howManyPlayers()-1)       = 0;
    purses.at(howManyPlayers()-1)       = 0;
    inPenaltyBox.at(howManyPlayers()-1) = false;

    cout << playerName << " was added" << endl;
    cout << "They are player number " << players.size() << endl;
    return true;
}

size_t Game::howManyPlayers() {
    return players.size();
}

void Game::roll(int roll) {
    cout << players.at(currentPlayer) << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if (inPenaltyBox.at(currentPlayer)) {
        if (roll % 2 != 0) {
            isGettingOutOfPenaltyBox = true;

            cout << players.at(currentPlayer) << " is getting out of the penalty box" << endl;
            places.at(currentPlayer) = places.at(currentPlayer) + roll;
            if (places.at(currentPlayer) > 11) // NOLINT
                places.at(currentPlayer) = places.at(currentPlayer) - 12; // NOLINT

            cout << players.at(currentPlayer) << "'s new location is " << places.at(currentPlayer) << endl;
            cout << "The category is " << currentCategory() << endl;
            askQuestion();
        } else {
            cout << players.at(currentPlayer) << " is not getting out of the penalty box" << endl;
            isGettingOutOfPenaltyBox = false;
        }

    } else {
        places.at(currentPlayer) = places.at(currentPlayer) + roll;
        if (places.at(currentPlayer) > 11) // NOLINT
            places.at(currentPlayer) = places.at(currentPlayer) - 12; // NOLINT

        cout << players.at(currentPlayer) << "'s new location is " << places.at(currentPlayer) << endl;
        cout << "The category is " << currentCategory() << endl;
        askQuestion();
    }
}

void Game::askQuestion() {
    if (currentCategory() == "Pop") {
        cout << popQuestions.front() << endl;
        popQuestions.pop_front();
    }
    if (currentCategory() == "Science") {
        cout << scienceQuestions.front() << endl;
        scienceQuestions.pop_front();
    }
    if (currentCategory() == "Sports") {
        cout << sportsQuestions.front() << endl;
        sportsQuestions.pop_front();
    }
    if (currentCategory() == "Rock") {
        cout << rockQuestions.front() << endl;
        rockQuestions.pop_front();
    }
}

string Game::currentCategory() {
    if (places[currentPlayer] == 0) // NOLINT
        return "Pop";
    if (places[currentPlayer] == 4) // NOLINT
        return "Pop";
    if (places[currentPlayer] == 8) // NOLINT
        return "Pop";
    if (places[currentPlayer] == 1) // NOLINT
        return "Science";
    if (places[currentPlayer] == 5) // NOLINT
        return "Science";
    if (places[currentPlayer] == 9) // NOLINT
        return "Science";
    if (places[currentPlayer] == 2) // NOLINT
        return "Sports";
    if (places[currentPlayer] == 6) // NOLINT
        return "Sports";
    if (places[currentPlayer] == 10) // NOLINT
        return "Sports";
    return "Rock";
}

bool Game::wasCorrectlyAnswered() {
    if (inPenaltyBox.at(currentPlayer)) {
        if (isGettingOutOfPenaltyBox) {
            cout << "Answer was correct!!!!" << endl;
            purses.at(currentPlayer)++;
            cout << players.at(currentPlayer) << " now has " << purses.at(currentPlayer) << " Gold Coins." << endl;

            bool winner = didPlayerWin();
            currentPlayer++;
            if (currentPlayer == players.size())
                currentPlayer = 0;

            return winner;
        } else {
            currentPlayer++;
            if (currentPlayer == players.size())
                currentPlayer = 0;
            return true;
        }

    } else {
        cout << "Answer was corrent!!!!" << endl;
        purses.at(currentPlayer)++;
        cout << players.at(currentPlayer) << " now has " << purses.at(currentPlayer) << " Gold Coins." << endl;

        bool winner = didPlayerWin();
        currentPlayer++;
        if (currentPlayer == players.size())
            currentPlayer = 0;

        return winner;
    }
}

bool Game::wrongAnswer() {
    cout << "Question was incorrectly answered" << endl;
    cout << players.at(currentPlayer) + " was sent to the penalty box" << endl;
    inPenaltyBox.at(currentPlayer) = true;

    currentPlayer++;
    if (currentPlayer == players.size())
        currentPlayer = 0;
    return true;
}

bool Game::didPlayerWin() {
    return !(purses[currentPlayer] == NUMBER_OF_COINS_TO_WIN);
}
