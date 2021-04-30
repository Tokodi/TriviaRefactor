#include <exception>
#include <iostream>

#include "controller.h"

int main() {
    try {
        Trivia::Controller::Controller _gameController;

        _gameController.addPlayer("Chet");
        _gameController.addPlayer("Pat");
        _gameController.addPlayer("Sue");

        _gameController.startGame();
    } catch (std::runtime_error& ex) {
        std::cout << "Runtime error: " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception occured" << std::endl;
    }
}
