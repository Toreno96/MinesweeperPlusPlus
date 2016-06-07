#pragma once

#include "ButtonText.hpp"

class NextChoiceButton : public ButtonText {
  public:
    NextChoiceButton();
    NextChoiceButton( std::function< void() > buttonFunction,
                      const sf::Font &font, unsigned characterSize = 30 );
    NextChoiceButton( std::function< void() > buttonFunction,
                      const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                      const sf::Font &font, unsigned characterSize = 30 );
};