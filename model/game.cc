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
    initializeDecks();
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

void Game::step(uint32_t value) {
    if (!isPlayable())
        throw runtime_error("Not enough players");

    if (std::next(_currentPlayer) == _players.end()) {
        _currentPlayer = _players.begin();
    } else {
        ++_currentPlayer;
    }

    cout << _currentPlayer->getName() << " is the current player" << endl;
    cout << "They have rolled a " << value << endl;

    if (_currentPlayer->isInPenalty()) {
        if (value % 2 != 0) {
            _currentPlayer->leavePenalty();
            cout << _currentPlayer->getName() << " is getting out of the penalty box" << endl;
        } else {
            cout << _currentPlayer->getName() << " is not getting out of the penalty box" << endl;
            return;
        }

    }
    _currentPlayer->step(value);

    cout << _currentPlayer->getName() << "'s new location is " << _currentPlayer->getPosition() << endl;
    askQuestion();
}

void Game::correctAnswer() {
    if (!isPlayable())
        throw runtime_error("Not enough players");

    if (_currentPlayer->isInPenalty())
        return;

    cout << "Answer was correct!!!!" << endl;
    _currentPlayer->addCoin();
    cout << _currentPlayer->getName() << " now has " << _currentPlayer->getNumberOfCoins() << " Gold Coins." << endl;

    if (NUMBER_OF_COINS_TO_WIN == _currentPlayer->getNumberOfCoins()){
        _isGameOver = true;
        return;
    }
}

void Game::wrongAnswer() {
    if (!isPlayable())
        throw runtime_error("Not enough players");

    cout << "Question was incorrectly answered" << endl;
    cout << _currentPlayer->getName() << " was sent to the penalty box" << endl;
    _currentPlayer->toPenalty();
}

size_t Game::getNumberOfPlayers() const {
    return _players.size();
}

bool Game::isOver() const {
    return _isGameOver;
}

void Game::initializeDecks() {
    for (size_t i = 0; i < NUMBER_OF_QUESTIONS_PER_SUBJECT; i++) {
        popQuestions.emplace("Pop Question " + std::to_string(i));
        scienceQuestions.emplace("Science Question " + std::to_string(i));
        sportsQuestions.emplace("Sports Question " + std::to_string(i));
        rockQuestions.emplace("Rock Question " + std::to_string(i));
    }
}

bool Game::isPlayable() const {
    return (getNumberOfPlayers() >= 1); // TODO: Default was 2
}

void Game::askQuestion() {
    cout << "The category is " << currentCategory() << endl;
    if (currentCategory() == "Pop") {
        cout << popQuestions.front() << endl;
        popQuestions.pop();
    }
    if (currentCategory() == "Science") {
        cout << scienceQuestions.front() << endl;
        scienceQuestions.pop();
    }
    if (currentCategory() == "Sports") {
        cout << sportsQuestions.front() << endl;
        sportsQuestions.pop();
    }
    if (currentCategory() == "Rock") {
        cout << rockQuestions.front() << endl;
        rockQuestions.pop();
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

} //  namespace Trivia::Model
