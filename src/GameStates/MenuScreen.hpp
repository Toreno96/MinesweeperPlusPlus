#pragma once

#include <map>
#include "GameState.hpp"
#include "OptionsScreen.hpp"
#include "Graphics/ButtonText.hpp"
#include "Graphics/Title.hpp"

class MenuScreen : public GameState {
  public:
    MenuScreen( Game *game );

    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    void positionDrawables() override;
    
    // Składowe:
    Title mTitle;
    ButtonText mNewGameButton;
    ButtonText mContinueButton;
    ButtonText mOptionsButton;
    ButtonText mHighScoresButton;
    ButtonText mExitButton;
};