#pragma once

#include <string>

#include "game.h"
#include "text_view.h"

namespace Trivia::Controller {

class Controller {
public:
    Controller() = default;

    void addPlayer(std::string name);
    void startGame();

private:
    Model::Game _game{};
    View::TextView _view{_game};
};

}  // namespace Trivia::Controller
