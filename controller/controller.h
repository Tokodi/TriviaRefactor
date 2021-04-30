#pragma once

#include <string>

#include "game.h"

namespace Trivia::Controller {

class Controller {
public:
    Controller() = default;

    void addPlayer(std::string name);
    void startGame();

private:
    Model::Game _game{};
};

}  // namespace Trivia::Controller
