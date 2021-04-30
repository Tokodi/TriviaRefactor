#include <cstdlib>

#include "game.h"

int main() {
    srand(1);
    Trivia::Model::Game game;

    game.addPlayer("Chet");
    game.addPlayer("Pat");
    game.addPlayer("Sue");

    do {
        game.step(rand() % 5 + 1); // NOLINT
        if (rand() % 9 == 7) { // NOLINT
            game.wrongAnswer();
        } else {
            game.correctAnswer();
        }
    } while (!game.isOver());
}
