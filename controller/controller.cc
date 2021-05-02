#include "controller.h"

#include <exception>
#include <functional>
#include <iostream>

using std::bind;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;

namespace Trivia::Controller {

void Controller::addPlayer(string name) {
    _game.addPlayer(name);
    _view.newPlayerAdded();
}

void Controller::startGame() {
    while (!_game.isOver()) {
        _game.step();
        _view.gameStepped();

        if (isCorrectAnswer()) {
            _game.correctAnswer();
            _view.correctAnswer();
        } else {
            _game.wrongAnswer();
            _view.wrongAnswer();
        }
    }
}

bool Controller::isCorrectAnswer() {
    return _distribution(_generator);
}

}  // namespace Trivia::Controller
