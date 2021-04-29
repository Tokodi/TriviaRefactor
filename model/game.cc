#include "game.h"

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;
using std::runtime_error;
using std::size_t;
using std::string;
using std::uint32_t;

namespace Trivia::Model {

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
    return (getNumberOfPlayers() >= 1); // TODO: Default was 2
}

void Game::addPlayer(string name) {
    if (NUMBER_OF_MAX_PLAYERS == getNumberOfPlayers()) {
        throw runtime_error("Maximum player number reached");
    }
    _players.emplace_back(std::move(name));
    _currentPlayer = std::prev(_players.end());

    cout << _players.back().getName() << " was added" << endl;
    cout << "They are player number " << getNumberOfPlayers() << endl;
}

size_t Game::getNumberOfPlayers() {
    return _players.size();
}

void Game::roll(uint32_t roll) {
    if (!isPlayable())
        throw runtime_error("Not enough players");

    if (std::next(_currentPlayer) == _players.end()) {
        _currentPlayer = _players.begin();
    } else {
        ++_currentPlayer;
    }

    cout << _currentPlayer->getName() << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if (_currentPlayer->isInPenalty()) {
        if (roll % 2 != 0) {
            isGettingOutOfPenaltyBox = true;

            cout << _currentPlayer->getName() << " is getting out of the penalty box" << endl;
            _currentPlayer->step(roll);

            cout << _currentPlayer->getName() << "'s new location is " << _currentPlayer->getPosition() << endl;
            cout << "The category is " << currentCategory() << endl;
            askQuestion();
        } else {
            cout << _currentPlayer->getName() << " is not getting out of the penalty box" << endl;
            isGettingOutOfPenaltyBox = false;
        }

    } else {
        _currentPlayer->step(roll);

        cout << _currentPlayer->getName() << "'s new location is " << _currentPlayer->getPosition() << endl;
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
    if (_currentPlayer->getPosition() == 0) // NOLINT
        return "Pop";
    if (_currentPlayer->getPosition() == 4) // NOLINT
        return "Pop";
    if (_currentPlayer->getPosition() == 8) // NOLINT
        return "Pop";
    if (_currentPlayer->getPosition() == 1) // NOLINT
        return "Science";
    if (_currentPlayer->getPosition() == 5) // NOLINT
        return "Science";
    if (_currentPlayer->getPosition() == 9) // NOLINT
        return "Science";
    if (_currentPlayer->getPosition() == 2) // NOLINT
        return "Sports";
    if (_currentPlayer->getPosition() == 6) // NOLINT
        return "Sports";
    if (_currentPlayer->getPosition() == 10) // NOLINT
        return "Sports";
    return "Rock";
}

bool Game::wasCorrectlyAnswered() {
    if (_currentPlayer->isInPenalty()) {
        if (isGettingOutOfPenaltyBox) {
            cout << "Answer was correct!!!!" << endl;
            _currentPlayer->addCoin();
            cout << _currentPlayer->getName() << " now has " << _currentPlayer->getNumberOfCoins() << " Gold Coins." << endl;

            bool winner = didPlayerWin();

            return winner;
        } else {
            return true;
        }

    } else {
        cout << "Answer was corrent!!!!" << endl;
        _currentPlayer->addCoin();
        cout << _currentPlayer->getName() << " now has " << _currentPlayer->getNumberOfCoins() << " Gold Coins." << endl;

        bool winner = didPlayerWin();

        return winner;
    }
}

bool Game::wrongAnswer() {
    if (!isPlayable())
        throw runtime_error("Not enough players");

    cout << "Question was incorrectly answered" << endl;
    cout << _currentPlayer->getName() << " was sent to the penalty box" << endl;
    _currentPlayer->toPenalty();

    return true;
}

bool Game::didPlayerWin() {
    return !(_currentPlayer->getNumberOfCoins() == NUMBER_OF_COINS_TO_WIN);
}

} //  namespace Trivia::Model
