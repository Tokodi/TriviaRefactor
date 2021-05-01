#pragma once

#include <cstdint>
#include <queue>
#include <string>
#include <vector>

#include "board.h"
#include "dice.h"
#include "player.h"

namespace Trivia::Model {

class Game {
public:
    Game();

    void addPlayer(std::string playerName);
    void step();

    void correctAnswer();
    void wrongAnswer();

    [[nodiscard]] const Player& getCurrentPlayer() const;
    [[nodiscard]] std::size_t getNumberOfPlayers() const;
    [[nodiscard]] std::uint32_t getDiceValue() const;
    [[nodiscard]] bool isOver() const;

private:
    static constexpr std::size_t NUMBER_OF_QUESTIONS_PER_SUBJECT = 50;
    static constexpr std::size_t NUMBER_OF_MIN_PLAYERS = 2;
    static constexpr std::size_t NUMBER_OF_MAX_PLAYERS = 6;
    static constexpr std::size_t NUMBER_OF_COINS_TO_WIN = 6;

private:
    void initializeDecks();
    void   askQuestion();

    [[nodiscard]] bool isPlayable() const;

private:
    // TODO: Fixed seed while developement
    Dice _dice{4}; // NOLINT
    Board _board{};
    std::vector<Player> _players{};
    std::vector<Player>::iterator _currentPlayer{_players.end()};

    bool _isGameOver{false};
    std::uint32_t _diceValue{0};

    std::queue<std::string> _popQuestions{};
    std::queue<std::string> _scienceQuestions{};
    std::queue<std::string> _sportsQuestions{};
    std::queue<std::string> _rockQuestions{};
};

} // namespace Trivia::Model
