#include "text_view.h"

#include <iostream>

using std::cout;
using std::endl;

namespace Trivia::View {

TextView::TextView(const Model::Game& gameModel) : _gameModel(gameModel) {
}

void TextView::newPlayerAdded() const {
    cout << _gameModel.getCurrentPlayer().getName() << " was added" << endl;
    cout << "They are player number " << _gameModel.getNumberOfPlayers() << endl;
}

void TextView::gameStepped() const {
    cout << _gameModel.getCurrentPlayer().getName() << " is the current player" << endl;
    cout << "They have rolled a " << _gameModel.getDice().getValue() << endl;

    if (_gameModel.getCurrentPlayer().isInPenalty()) {
        cout << _gameModel.getCurrentPlayer().getName() << " is not getting out of the penalty box" << endl;
        return;
    } else {
        if (_gameModel.isCurrentPlayerJustLeftPenalty()) {
            cout << _gameModel.getCurrentPlayer().getName() << " is getting out of the penalty box" << endl;
        }
    }

    cout << _gameModel.getCurrentPlayer().getName() << "'s new location is "
         << _gameModel.getCurrentPlayer().getPosition() << endl;

    cout << "The category is " << _gameModel.getCurrentQuestion().first << endl;
    cout << _gameModel.getCurrentQuestion().second << endl;
}

void TextView::correctAnswer() const {
    if (_gameModel.getCurrentPlayer().isInPenalty())
        return;

    cout << "Answer was correct!!!!" << endl;
    cout << _gameModel.getCurrentPlayer().getName() << " now has " << _gameModel.getCurrentPlayer().getNumberOfCoins()
         << " Gold Coins." << endl;
}

void TextView::wrongAnswer() const {
    cout << "Question was incorrectly answered" << endl;
    cout << _gameModel.getCurrentPlayer().getName() << " was sent to the penalty box" << endl;
}

}  // namespace Trivia::View
