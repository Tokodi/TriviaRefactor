#include "game.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::move;
using std::next;
using std::ostringstream;
using std::prev;
using std::runtime_error;
using std::size_t;
using std::string;
using std::to_string;
using std::uint32_t;

namespace Trivia::Model {

Game::Game() {
    initializeDecks();
}

void Game::addPlayer(string name) {
    if (NUMBER_OF_MAX_PLAYERS == getNumberOfPlayers()) {
        throw runtime_error("Maximum player number reached");
    }

    _players.emplace_back(move(name));
    _currentPlayer = prev(_players.end());

    cout << _players.back().getName() << " was added" << endl;
    cout << "They are player number " << getNumberOfPlayers() << endl;
}

void Game::step() {
    if (!isPlayable())
        throw runtime_error("Not enough players");

    if (next(_currentPlayer) == _players.end()) {
        _currentPlayer = _players.begin();
    } else {
        ++_currentPlayer;
    }

    cout << _currentPlayer->getName() << " is the current player" << endl;

    _diceValue = _dice.roll();
    cout << "They have rolled a " << _diceValue << endl;

    if (_currentPlayer->isInPenalty()) {
        if (_diceValue % 2 == 0) {
            cout << _currentPlayer->getName() << " is not getting out of the penalty box" << endl;
            return;
        } else {
            _currentPlayer->leavePenalty();
            cout << _currentPlayer->getName() << " is getting out of the penalty box" << endl;
        }
    }
    _currentPlayer->step(_diceValue);

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

    if (NUMBER_OF_COINS_TO_WIN == _currentPlayer->getNumberOfCoins()) {
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


const Player& Game::getCurrentPlayer() const {
    if (_currentPlayer == _players.end())
        throw runtime_error("Not enough players");

    return *_currentPlayer;
}

size_t Game::getNumberOfPlayers() const {
    return _players.size();
}

uint32_t Game::getDiceValue() const {
    return _diceValue;
}

bool Game::isOver() const {
    return _isGameOver;
}

void Game::initializeDecks() {
    for (size_t i = 0; i < NUMBER_OF_QUESTIONS_PER_SUBJECT; i++) {
        _popQuestions.emplace("Pop Question " + to_string(i));
        _scienceQuestions.emplace("Science Question " + to_string(i));
        _sportsQuestions.emplace("Sports Question " + to_string(i));
        _rockQuestions.emplace("Rock Question " + to_string(i));
    }
}

bool Game::isPlayable() const {
    return (getNumberOfPlayers() >= NUMBER_OF_MIN_PLAYERS && !isOver());
}

void Game::askQuestion() {
    switch (_board.getField(_currentPlayer->getPosition())) {
        case Field::POP:
            cout << "The category is Pop" << endl;
            cout << _popQuestions.front() << endl;
            _popQuestions.pop();
            break;
        case Field::SCIENCE:
            cout << "The category is Science" << endl;
            cout << _scienceQuestions.front() << endl;
            _scienceQuestions.pop();
            break;
        case Field::SPORTS:
            cout << "The category is Sports" << endl;
            cout << _sportsQuestions.front() << endl;
            _sportsQuestions.pop();
            break;
        case Field::ROCK:
            cout << "The category is Rock" << endl;
            cout << _rockQuestions.front() << endl;
            _rockQuestions.pop();
            break;
    }
}

} //  namespace Trivia::Model
