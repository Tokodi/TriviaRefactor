#pragma once

#include <cstdint>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "board.h"
#include "dice.h"
#include "player.h"

namespace Trivia::Model {

class Game {
public:
    Game();
    explicit Game(std::uint32_t diceSeed);

    void addPlayer(std::string playerName);
    void step();

    void correctAnswer();
    void wrongAnswer();

    [[nodiscard]] const Player&                              getCurrentPlayer() const;
    [[nodiscard]] const Dice&                                getDice() const;
    [[nodiscard]] std::size_t                                getNumberOfPlayers() const;
    [[nodiscard]] const std::pair<std::string, std::string>& getCurrentQuestion() const;

    [[nodiscard]] bool isCurrentPlayerJustLeftPenalty() const;
    [[nodiscard]] bool isOver() const;

private:
    static constexpr std::size_t NUMBER_OF_QUESTIONS_PER_SUBJECT = 50;
    static constexpr std::size_t NUMBER_OF_MIN_PLAYERS           = 2;
    static constexpr std::size_t NUMBER_OF_MAX_PLAYERS           = 6;
    static constexpr std::size_t NUMBER_OF_COINS_TO_WIN          = 6;

private:
    void initializeDecks();
    void setCurrentQuestion();

    [[nodiscard]] bool isPlayable() const;

private:
    Dice  _dice;
    Board _board{};

    std::vector<Player>           _players{};
    std::vector<Player>::iterator _currentPlayer{_players.end()};

    bool _isGameOver{false};
    bool _isCurrentPlayerJustLeftPenalty{false};

    std::queue<std::string> _popQuestions{};
    std::queue<std::string> _scienceQuestions{};
    std::queue<std::string> _sportsQuestions{};
    std::queue<std::string> _rockQuestions{};

    std::pair<std::string, std::string> _currentQuestion{};
};

}  // namespace Trivia::Model
