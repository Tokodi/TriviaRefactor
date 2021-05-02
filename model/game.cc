#include "game.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>

using std::move;
using std::next;
using std::ostringstream;
using std::pair;
using std::prev;
using std::runtime_error;
using std::size_t;
using std::string;
using std::to_string;
using std::uint32_t;

namespace Trivia::Model {

Game::Game() : _dice{} {
    initializeDecks();
}

// NOTE: For testing purposes
Game::Game(std::uint32_t diceSeed) : _dice{diceSeed} {
    initializeDecks();
}

void Game::addPlayer(string name) {
    if (NUMBER_OF_MAX_PLAYERS == getNumberOfPlayers()) {
        throw runtime_error("Maximum player number reached");
    }

    _players.emplace_back(move(name));
    _currentPlayer = prev(_players.end());
}

void Game::step() {
    if (!isPlayable())
        throw runtime_error("Invalid operation");

    if (next(_currentPlayer) == _players.end()) {
        _currentPlayer = _players.begin();
    } else {
        ++_currentPlayer;
    }

    _dice.roll();

    _isCurrentPlayerJustLeftPenalty = false;
    if (_currentPlayer->isInPenalty()) {
        if (_dice.getValue() % 2 == 0) {
            return;
        } else {
            _currentPlayer->leavePenalty();
            _isCurrentPlayerJustLeftPenalty = true;
        }
    }
    _currentPlayer->step(_dice.getValue());

    setCurrentQuestion();
}

void Game::correctAnswer() {
    if (!isPlayable())
        throw runtime_error("Invalid operation");

    if (_currentPlayer->isInPenalty())
        return;

    _currentPlayer->addCoin();

    if (NUMBER_OF_COINS_TO_WIN == _currentPlayer->getNumberOfCoins()) {
        _isGameOver = true;
        return;
    }
}

void Game::wrongAnswer() {
    if (!isPlayable())
        throw runtime_error("Invalid operation");

    _currentPlayer->toPenalty();
}

const Dice& Game::getDice() const {
    return _dice;
}

const Player& Game::getCurrentPlayer() const {
    if (_currentPlayer == _players.end())
        throw runtime_error("Not enough players");

    return *_currentPlayer;
}

bool Game::isCurrentPlayerJustLeftPenalty() const {
    return _isCurrentPlayerJustLeftPenalty;
}

size_t Game::getNumberOfPlayers() const {
    return _players.size();
}

const pair<string, string>& Game::getCurrentQuestion() const {
    return _currentQuestion;
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

void Game::setCurrentQuestion() {
    switch (_board.getField(_currentPlayer->getPosition())) {
        case Field::POP:
            _currentQuestion = {"Pop", _popQuestions.front()};
            _popQuestions.pop();
            break;
        case Field::SCIENCE:
            _currentQuestion = {"Science", _scienceQuestions.front()};
            _scienceQuestions.pop();
            break;
        case Field::SPORTS:
            _currentQuestion = {"Sports", _sportsQuestions.front()};
            _sportsQuestions.pop();
            break;
        case Field::ROCK:
            _currentQuestion = {"Rock", _rockQuestions.front()};
            _rockQuestions.pop();
            break;
    }
}

}  //  namespace Trivia::Model
