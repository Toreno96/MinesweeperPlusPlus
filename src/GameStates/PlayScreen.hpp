#pragma once

#include "GameState.hpp"
#include "GameLogic/Minefield.hpp"
#include "GameLogic/SecondsMeter.hpp"
#include "Graphics/ButtonText.hpp"
#include "Graphics/DrawingMinefield.hpp"

class PlayScreen : public GameState {
  public:
    PlayScreen( Game *game,
                std::unique_ptr< Minefield > minefieldLogic,
                std::unique_ptr< DrawingMinefield > minefieldDrawing );

    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    void positionDrawables() override;
    
    std::function< void() > createBackToMenuFunction();
    
    bool gameWon();
    bool gameLost();
    
    // Składowe:
    SecondsMeter mSecondsMeter;
    std::unique_ptr< Minefield > mMinefieldLogic;
    std::unique_ptr< DrawingMinefield > mMinefieldDrawing;
    //std::unordered_map< std::string, ExtendedText > mText;
    ButtonText mBackToMenuButton;
};