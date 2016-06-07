#pragma once

#include "ButtonText.hpp"

class PreviousChoiceButton : public ButtonText {
  public:
    PreviousChoiceButton();
    PreviousChoiceButton( std::function< void() > buttonFunction,
                          const sf::Font &font, unsigned characterSize = 30 );
    PreviousChoiceButton( std::function< void() > buttonFunction,
                          const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                          const sf::Font &font, unsigned characterSize = 30 );
};