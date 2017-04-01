#include <iostream>
#include "Title.hpp"
#include "ButtonText.hpp"

int main() {
sf::VideoMode videoMode( 800, 600 );
  unsigned characterSize = videoMode.width / 15;
  sf::Font font;
  if( !font.loadFromFile( GameConstants::fontName ) )
    return 0;
  
  float baseDistanceBetweenTextGraphics = videoMode.height / 24;
  
  sf::RenderWindow window( videoMode, "Centered Text" );
  
  Title titleGraphic( videoMode, GameConstants::title, font, characterSize );
  
  ButtonText newGameGraphic( "New Game", font, characterSize );
  newGameGraphic.centerHorizontally( videoMode );
  newGameGraphic.positionBelow( titleGraphic, baseDistanceBetweenTextGraphics * 2 );
  
  ButtonText continueGraphic( "Continue", font, characterSize );
  continueGraphic.alignHorizontallyRelativeTo( newGameGraphic, videoMode );
  continueGraphic.positionBelow( newGameGraphic, baseDistanceBetweenTextGraphics );
  
  ButtonText optionsGraphic( "Options", font, characterSize );
  optionsGraphic.alignHorizontallyRelativeTo( newGameGraphic, videoMode );
  optionsGraphic.positionBelow( continueGraphic, baseDistanceBetweenTextGraphics );
  
  ButtonText highScoresGraphic( "High Scores", font, characterSize );
  highScoresGraphic.alignHorizontallyRelativeTo( newGameGraphic, videoMode );
  highScoresGraphic.positionBelow( optionsGraphic, baseDistanceBetweenTextGraphics );
  
  ButtonText exitGraphic( [ &window ](){ window.close(); }, "Exit", font, characterSize );
  exitGraphic.alignHorizontallyRelativeTo( newGameGraphic, videoMode );
  exitGraphic.positionBelow( highScoresGraphic, baseDistanceBetweenTextGraphics );
  
  
  while( window.isOpen() ) {
    sf::Event event;
    bool leftMouseButtonClicked = false;
    
    while( window.pollEvent( event ) ) {
      switch( event.type ) {
        case sf::Event::MouseButtonReleased: {
          if( event.mouseButton.button == sf::Mouse::Left )
            leftMouseButtonClicked = true;
          break;
        }
        case sf::Event::Closed: {
          window.close();
          break;
        }
        default:
          break;
      }
    }
    
    newGameGraphic.handleInput( window, leftMouseButtonClicked );
    continueGraphic.handleInput( window, leftMouseButtonClicked );
    optionsGraphic.handleInput( window, leftMouseButtonClicked );
    highScoresGraphic.handleInput( window, leftMouseButtonClicked );
    exitGraphic.handleInput( window, leftMouseButtonClicked );
    
    newGameGraphic.update();
    continueGraphic.update();
    optionsGraphic.update();
    highScoresGraphic.update();
    exitGraphic.update();
    
    window.clear( sf::Color::Black );
    window.draw( titleGraphic );
    window.draw( newGameGraphic );
    window.draw( continueGraphic );
    window.draw( optionsGraphic );
    window.draw( highScoresGraphic );
    window.draw( exitGraphic );
    window.display();
  }
}