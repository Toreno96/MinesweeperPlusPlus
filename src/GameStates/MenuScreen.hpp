#pragma once

#include "GameState.hpp"

class MenuScreen : public GameState {
  public:
    // Konsruktor:
    MenuScreen( Game *game );
    // Metody podstawowe:
    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    // Składowe:
    bool isExited;
};