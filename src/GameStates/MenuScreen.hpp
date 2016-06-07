#pragma once

#include <map>
#include "GameState.hpp"
#include "OptionsScreen.hpp"
#include "PlayScreen.hpp"
#include "GameLogic/MinefieldClassic.hpp"
#include "GameLogic/MinefieldHex.hpp"
#include "GameLogic/MinefieldTri.hpp"
#include "Graphics/ButtonText.hpp"
#include "Graphics/DrawingMinefieldClassic.hpp"
#include "Graphics/Title.hpp"

class MenuScreen : public GameState {
  public:
    MenuScreen( Game *game );

    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    void positionDrawables() override;
    
    void fillMainButtons();
    
    std::function< void() > createNewGameFunction();
    std::function< void() > createContinueFunction();
    std::function< void() > createOptionsFunction();
    
    // Składowe:
    Title mTitle;
    ButtonText mExitButton;
    std::unordered_map< std::string, ButtonText > mMainButtons;
};