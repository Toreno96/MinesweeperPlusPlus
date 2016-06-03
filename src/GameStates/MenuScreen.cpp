#include "MenuScreen.hpp"

MenuScreen::MenuScreen( Game *game ) : GameState( game ), isExited( false ) {}
void MenuScreen::handleInput() {
  sf::Event event;
  while( mGame->mWindow.pollEvent( event ) ) {
    switch( event.type ) {
      case sf::Event::Closed:
        isExited = true;
        break;
      case sf::Event::MouseButtonReleased:
        if( event.mouseButton.button == sf::Mouse::Right )
          isExited = true;
        break;
      default:
        break;
    }
  }
}
void MenuScreen::update() {
  if( isExited )
    mGame->exit();
}
void MenuScreen::draw() {
  mGame->mWindow.clear( sf::Color::Blue );
}