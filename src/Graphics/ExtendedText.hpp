#pragma once

#include <SFML/Graphics.hpp>

// Klasa rozszerzająca sf::Text o dodatkową funkcjonalność.
class ExtendedText : public sf::Text {
  public:
    ExtendedText();
    ExtendedText( const sf::String &string, const sf::Font &font, unsigned characterSize = 30 );

    void setPositionX( const float x );
    void setPositionY( const float y );
    void moveX( const float x );
    void moveY( const float y );
    void centerHorizontally( const sf::VideoMode &videoMode );
    void centerVertically( const sf::VideoMode &videoMode );
    template< class ObjectWithPositionAndBounds >
    void positionBelow( const ObjectWithPositionAndBounds &relativeObject, const float distanceBetween ) {
      setPositionY( relativeObject.getPosition().y + relativeObject.getLocalBounds().height + distanceBetween );
    }
    template< class ObjectWithBounds >
    void alignHorizontallyRelativeTo( const ObjectWithBounds &relativeObject, const sf::VideoMode &videoMode ) {
      setPositionX( ( videoMode.width / 2 - relativeObject.getLocalBounds().width / 2 ) );
    }
    template< class ObjectWithBounds >
    void alignVerticallyRelativeTo( const ObjectWithBounds &relativeObject, const sf::VideoMode &videoMode ) {
      setPositionY( ( videoMode.height / 2 - relativeObject.getLocalBounds().height / 2 ) );
    }
};