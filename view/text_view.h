#pragma once

#include "game.h"
#include "view_if.h"

namespace Trivia::View {

class TextView final : public IView {
public:
    explicit TextView(const Model::Game& gameModel);

    void newPlayerAdded() const override;
    void gameStepped() const override;
    void wrongAnswer() const override;
    void correctAnswer() const override;

private:
    const Model::Game& _gameModel;
};

}  // namespace Trivia::View
