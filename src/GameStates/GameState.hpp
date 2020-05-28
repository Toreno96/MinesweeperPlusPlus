#pragma once

#include "Game.hpp"

class GameState {
  public:
    GameState( Game *game );
    virtual ~GameState();

    virtual void handleInput() = 0;
    virtual void update();
    virtual void draw() = 0;
  protected:
    virtual void positionDrawables() = 0;
    
    // Składowe:
    Game *mGame;
    bool mExited;
};
