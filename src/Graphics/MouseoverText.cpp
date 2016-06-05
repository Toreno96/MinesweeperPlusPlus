#include "MouseoverText.hpp"

MouseoverText::MouseoverText() :
    MouseoverText( sf::String(), sf::Font() ) {}
MouseoverText::MouseoverText( const sf::String &string, const sf::Font &font, unsigned characterSize) :
    MouseoverText( GameConstants::defaultColor, GameConstants::blue,
                   string, font, characterSize ) {}
MouseoverText::MouseoverText( const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                              const sf::String &string, const sf::Font &font, unsigned characterSize ) :
    ExtendedText( string, font, characterSize ),
    mDefaultColor( defaultColor ), mMouseoverColor( mouseoverColor ),
    mContainMouseCursor( false ) {}

void MouseoverText::handleInput( const sf::RenderWindow &window ) {
  auto currentMousePosition = sf::Mouse::getPosition( window );
  if( this->getGlobalBounds().contains( currentMousePosition.x, currentMousePosition.y ) )
    mContainMouseCursor = true;
  else
    mContainMouseCursor = false;
}
void MouseoverText::update() {
  if( mContainMouseCursor )
    this->setColor( mMouseoverColor );
  else
    this->setColor( mDefaultColor );
}

void MouseoverText::setDefaultColor( const sf::Color &newDefaultColor ) {
  mDefaultColor = newDefaultColor;
}
void MouseoverText::setMouseoverColor( const sf::Color &newMouseoverColor ) {
  mMouseoverColor = newMouseoverColor;
}