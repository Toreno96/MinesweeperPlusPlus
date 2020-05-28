#pragma once

#include "GameState.hpp"
#include "Graphics/ButtonText.hpp"
#include "Graphics/ExtendedText.hpp"

class GameOverScreen : public GameState {
  public:
    GameOverScreen( Game *game );

    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    void positionDrawables() override;
    
    std::function< void() > createBackToMenuFunction();
    
    // Składowe:
    ButtonText mBackToMenuButton;
    ExtendedText mGameOverText;
};

