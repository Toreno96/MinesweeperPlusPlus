#pragma once

#include "ButtonText.hpp"
#include "Game.hpp"

class BackButton : public ButtonText {
  public:
    BackButton( Game* game,
                const sf::Font &font, unsigned characterSize = 30 );
    BackButton( Game* game,
                const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                const sf::Font &font, unsigned characterSize = 30 );
  private:
    void positionThisButton( Game* game );
};