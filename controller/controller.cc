#include "controller.h"

#include <iostream>
#include <exception>

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
    srand(1); // TODO: Fixed seed while refactoring

    while (!_game.isOver()) {
        _game.step();
        _view.gameStepped();

        if (rand() % 9 == 7) { // NOLINT
            _game.wrongAnswer();
            _view.wrongAnswer();
        } else {
            _game.correctAnswer();
            _view.correctAnswer();
        }
    }
}

}  // namespace Trivia::Controller
