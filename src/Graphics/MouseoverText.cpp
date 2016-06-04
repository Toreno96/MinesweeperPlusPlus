#include "MouseoverText.hpp"

MouseoverText::MouseoverText() : ExtendedText(), mContainMouseCursor( false ) {}
MouseoverText::MouseoverText( const sf::String &string, const sf::Font &font, unsigned characterSize) : ExtendedText( string, font, characterSize ), mContainMouseCursor( false ) {}
void MouseoverText::handleInput( const sf::RenderWindow &window ) {
  auto currentMousePosition = sf::Mouse::getPosition( window );
  if( this->getGlobalBounds().contains( currentMousePosition.x, currentMousePosition.y ) )
    mContainMouseCursor = true;
  else
    mContainMouseCursor = false;
}
void MouseoverText::update() {
  if( mContainMouseCursor )
    this->setColor( GameConstants::blue );
  else
    this->setColor( GameConstants::defaultColor );
}