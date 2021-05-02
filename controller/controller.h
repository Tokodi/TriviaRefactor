#pragma once

#include <chrono>
#include <cstdint>
#include <random>
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
    static constexpr double PROBABILITY_OF_CORRECT_ANSWER = static_cast<double>(8) / 9;

private:
    bool isCorrectAnswer();

private:
    // NOTE: Hash test settings
    // Model::Game    _game{4};
    // std::mt19937 _generator{1};

    Model::Game    _game{};
    View::TextView _view{_game};

    std::mt19937 _generator{static_cast<std::uint64_t>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::bernoulli_distribution _distribution{PROBABILITY_OF_CORRECT_ANSWER};
};

}  // namespace Trivia::Controller
