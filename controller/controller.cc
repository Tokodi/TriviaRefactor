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
    srand(1); // TODO: Fix seed while refactoring

    while (!_game.isOver()) {
        _game.step(rand() % 5 + 1); // NOLINT
        if (rand() % 9 == 7) { // NOLINT
            _game.wrongAnswer();
        } else {
            _game.correctAnswer();
        }
    }
}

}  // namespace Trivia::Controller
