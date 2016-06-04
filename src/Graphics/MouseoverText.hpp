#pragma once

#include <functional>
#include "ExtendedText.hpp"
#include "HelperSrc/GameConstants.hpp"

class MouseoverText : public ExtendedText {
  public:
    MouseoverText();
    MouseoverText( const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );
    virtual void handleInput( const sf::RenderWindow &window );
    virtual void update();
  private:
    bool mContainMouseCursor;
};