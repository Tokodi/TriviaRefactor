#pragma once

#include <queue>
#include <string>
#include <vector>

#include "board.h"
#include "player.h"

namespace Trivia::Model {

class Game {
public:
    Game();

    void addPlayer(std::string playerName);
    void step(std::uint32_t dicedValue);

    void correctAnswer();
    void wrongAnswer();

    [[nodiscard]] std::size_t getNumberOfPlayers() const;
    [[nodiscard]] bool isOver() const;

private:
    void initializeDecks();

    [[nodiscard]] bool isPlayable() const;

private:
    static constexpr std::size_t NUMBER_OF_QUESTIONS_PER_SUBJECT = 50;
    static constexpr std::size_t NUMBER_OF_MAX_PLAYERS = 6;
    static constexpr std::size_t NUMBER_OF_COINS_TO_WIN = 6;

private:
    bool _isGameOver{false};

protected:
    void   askQuestion();

protected:
    Board _board{};
    std::vector<Player> _players{};
    std::vector<Player>::iterator _currentPlayer{_players.end()};

    std::queue<std::string> _popQuestions{};
    std::queue<std::string> _scienceQuestions{};
    std::queue<std::string> _sportsQuestions{};
    std::queue<std::string> _rockQuestions{};
};

} // namespace Trivia::Model
