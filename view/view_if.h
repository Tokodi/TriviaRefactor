#pragma once

namespace Trivia::View {

class IView {
public:
    virtual ~IView() = default;

    virtual void newPlayerAdded() const = 0;
    virtual void gameStepped() const = 0;
    virtual void wrongAnswer() const = 0;
    virtual void correctAnswer() const = 0;
};

}  // namespace Trivia::View
