#include <cstdlib>

#include "game.h"

static bool notAWinner;

int main() {
    srand(1);
    Trivia::Model::Game aGame;

    aGame.addPlayer("Chet");
    aGame.addPlayer("Pat");
    aGame.addPlayer("Sue");

    do {
        aGame.roll(rand() % 5 + 1); // NOLINT

        if (rand() % 9 == 7) { // NOLINT
            notAWinner = aGame.wrongAnswer();
        } else {
            notAWinner = aGame.wasCorrectlyAnswered();
        }
    } while (notAWinner);
}
