#include "Title.hpp"

Title::Title() : ExtendedText() {}
Title::Title( const sf::VideoMode &videoMode, const sf::String &string, const sf::Font &font, unsigned baseCharacterSize ) : ExtendedText( string, font, baseCharacterSize * 1.25 ) {
  centerHorizontally( videoMode );
  setPositionY( videoMode.height / 12 );
}