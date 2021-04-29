#pragma once

#include <array>
#include <list>
#include <vector>

#include "player.h"

namespace Trivia::Model {

class Game {
public:
    Game();

    bool   isPlayable();
    void   addPlayer(std::string playerName);

    std::size_t getNumberOfPlayers();
    void        roll(std::uint32_t roll);

    bool wasCorrectlyAnswered();
    bool wrongAnswer();

protected:
    static constexpr std::size_t NUMBER_OF_QUESTIONS_PER_SUBJECT = 50;
    static constexpr std::size_t NUMBER_OF_MAX_PLAYERS = 6;
    static constexpr std::size_t NUMBER_OF_COINS_TO_WIN = 6;

protected:
    std::string createRockQuestion(std::size_t index);
    void   askQuestion();
    std::string currentCategory();

    bool didPlayerWin();

protected:
    std::vector<Player> _players{};
    std::vector<Player>::iterator _currentPlayer{_players.end()};

    std::list<std::string> popQuestions{};
    std::list<std::string> scienceQuestions{};
    std::list<std::string> sportsQuestions{};
    std::list<std::string> rockQuestions{};

    bool         isGettingOutOfPenaltyBox{false};
};

} // namespace Trivia::Model
