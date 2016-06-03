#pragma once

#include "Game.hpp"

class GameState {
  public:
    // Konstruktor:
    GameState( Game *game );
    // Destruktor:
    virtual ~GameState();
    // Metody podstawowe:
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
  protected:
    // Składowe:
    Game *mGame;
};