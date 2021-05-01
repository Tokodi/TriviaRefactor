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
}

void Controller::startGame() {
    srand(1); // TODO: Fixed seed while refactoring

    while (!_game.isOver()) {
        _game.step();
        if (rand() % 9 == 7) { // NOLINT
            _game.wrongAnswer();
        } else {
            _game.correctAnswer();
        }
    }
}

}  // namespace Trivia::Controller
