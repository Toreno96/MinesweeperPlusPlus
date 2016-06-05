#include "ButtonText.hpp"

ButtonText::ButtonText() :
    ButtonText( sf::String(), sf::Font() ) {}
ButtonText::ButtonText( const sf::String &string, const sf::Font &font, unsigned characterSize ) :
    ButtonText( [](){},
                string, font, characterSize ) {}
ButtonText::ButtonText( std::function< void() > buttonFunction,
                        const sf::String &string, const sf::Font &font, unsigned characterSize ) :
    ButtonText( buttonFunction,
                GameConstants::defaultColor, GameConstants::blue,
                string, font, characterSize ) {}
ButtonText::ButtonText( std::function< void() > buttonFunction,
                        const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                        const sf::String &string, const sf::Font &font, unsigned characterSize ) :
    MouseoverText( defaultColor, mouseoverColor,
                   string, font, characterSize ),
    mButtonFunction( buttonFunction ),
    mLeftClicked( false ) {}

void ButtonText::handleInput( const sf::RenderWindow &window, const bool leftMouseButtonWasReleased ) {
  MouseoverText::handleInput( window );
  if( mContainMouseCursor && leftMouseButtonWasReleased )
    mLeftClicked = true;
  else
    mLeftClicked = false;
}
void ButtonText::update() {
  MouseoverText::update();
  if( mLeftClicked == true )
    mButtonFunction();
}

void ButtonText::setButtonFunction( std::function< void() > newButtonFunction ) {
  mButtonFunction = newButtonFunction;
}