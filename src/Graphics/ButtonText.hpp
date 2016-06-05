#pragma once

#include <functional>
#include "MouseoverText.hpp"

class ButtonText : public MouseoverText {
  public:
    ButtonText();
    ButtonText( const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );
    ButtonText( std::function< void() > buttonFunction,
                const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );
    ButtonText( std::function< void() > buttonFunction,
                const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );
    
    virtual void handleInput( const sf::RenderWindow &window, const bool leftMouseButtonWasReleased );
    virtual void update() override;
    
    void setButtonFunction( std::function< void() > newButtonFunction );
  protected:
    // Składowe:
    std::function< void() > mButtonFunction;
    bool mLeftClicked;
};