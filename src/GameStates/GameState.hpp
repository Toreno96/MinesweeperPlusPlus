#pragma once

#include "Game.hpp"

class GameState {
  public:
    GameState( Game *game );
    virtual ~GameState();

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
  protected:
    virtual void positionButtons() = 0;
    
    // Składowe:
    Game *mGame;
};