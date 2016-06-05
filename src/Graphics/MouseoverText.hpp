#pragma once

#include "ExtendedText.hpp"
#include "HelperSrc/GameConstants.hpp"

class MouseoverText : public ExtendedText {
  public:
    MouseoverText();
    MouseoverText( const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );
    MouseoverText( const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                   const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );
    
    void handleInput( const sf::RenderWindow &window );
    virtual void update();
    
    void setDefaultColor( const sf::Color &newDefaultColor );
    void setMouseoverColor( const sf::Color &newMouseoverColor );
  protected:
    // Składowe:
    sf::Color mDefaultColor;
    sf::Color mMouseoverColor;
    bool mContainMouseCursor;
};