#pragma once

#include <map>
#include "GameState.hpp"
#include "Graphics/ButtonText.hpp"
#include "Graphics/Title.hpp"

class MenuScreen : public GameState {
  public:
    MenuScreen( Game *game );

    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    void positionButtons() override;
    
    // Składowe:
    bool mExited;
    Title mTitle;
    ButtonText mNewGameButton;
    ButtonText mContinueButton;
    ButtonText mOptionsButton;
    ButtonText mHighScoresButton;
    ButtonText mExitButton;
};