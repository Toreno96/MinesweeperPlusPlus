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
    template< class ObjectWithPositionAndBounds >
    void positionLeft( const ObjectWithPositionAndBounds &relativeObject, const float distanceBetween ) {
      setPositionX( relativeObject.getPosition().x - getLocalBounds().width - distanceBetween );
    }
    template< class ObjectWithPositionAndBounds >
    void positionRight( const ObjectWithPositionAndBounds &relativeObject, const float distanceBetween ) {
      setPositionX( relativeObject.getPosition().x + relativeObject.getLocalBounds().width + distanceBetween );
    }
    template< class ObjectWithBounds >
    void alignHorizontallyRelativeTo( const ObjectWithBounds &relativeObject ) {
      setPositionX( relativeObject.getPosition().x );
    }
    template< class ObjectWithBounds >
    void alignVerticallyRelativeTo( const ObjectWithBounds &relativeObject ) {
      setPositionY( relativeObject.getPosition().y );
    }
};