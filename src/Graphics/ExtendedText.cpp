#include "ExtendedText.hpp"

ExtendedText::ExtendedText() :
    ExtendedText( sf::String(), sf::Font() ) {}
ExtendedText::ExtendedText( const sf::String &string, const sf::Font &font, unsigned characterSize ) :
    Text( string, font, characterSize ) {}

void ExtendedText::setPositionX( const float x ) {
  setPosition( x, getPosition().y );
}
void ExtendedText::setPositionY( const float y ) {
  setPosition( getPosition().x, y );
}
void ExtendedText::moveX( const float x ) {
  move( x, 0.f );
}
void ExtendedText::moveY( const float y ) {
  move( 0.f, y );
}
void ExtendedText::centerHorizontally( const sf::VideoMode &videoMode ) {
  setPositionX( ( videoMode.width / 2 - getLocalBounds().width / 2 ) );

}
void ExtendedText::centerVertically( const sf::VideoMode &videoMode ) {
  setPositionY( ( videoMode.height / 2 - getLocalBounds().height / 2 ) );
}
