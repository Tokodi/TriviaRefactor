#include <stdlib.h>

#include "game.h"

static bool notAWinner;

int main() {
    srand(1);
    Game aGame;

    aGame.add("Chet");
    aGame.add("Pat");
    aGame.add("Sue");

    do {
        aGame.roll(rand() % 5 + 1);

        if (rand() % 9 == 7) {
            notAWinner = aGame.wrongAnswer();
        } else {
            notAWinner = aGame.wasCorrectlyAnswered();
        }
    } while (notAWinner);
}