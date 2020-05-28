#include "GameOverScreen.hpp"

GameOverScreen::GameOverScreen( Game *game ) :
    GameState( game ),
    mBackToMenuButton( ButtonText( createBackToMenuFunction(),
                                   "Menu", mGame->mFont, mGame->mBaseCharacterSize ) ),
    mGameOverText( ExtendedText( "Game Over!", mGame->mFont, mGame->mBaseCharacterSize ) ) {
  positionDrawables();
}

void GameOverScreen::handleInput() {
  sf::Event event;
  bool leftMouseButtonClicked = false;
  bool rightMouseButtonClicked = false;

  while( mGame->mWindow.pollEvent( event ) ) {
    switch( event.type ) {
      case sf::Event::MouseButtonReleased: {
        switch( event.mouseButton.button ) {
          case sf::Mouse::Left:
            leftMouseButtonClicked = true;
            break;
          case sf::Mouse::Right:
            rightMouseButtonClicked = true;
            break;
          default:
          break;
        }
        break;
      }
      case sf::Event::Closed: {
        mExited = true;
        break;
      }
      default:
        break;
    }
  }

  mBackToMenuButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
}
void GameOverScreen::update() {
  if( mExited == true ) {
    mGame->exit();
  }
  else {
    mBackToMenuButton.update();
  }
}
void GameOverScreen::draw() {
  mGame->mWindow.draw( mBackToMenuButton );
  mGame->mWindow.draw( mGameOverText );
}

void GameOverScreen::positionDrawables() {
  mBackToMenuButton.centerHorizontally( mGame->mVideoMode );
  mBackToMenuButton.moveY( 0.05 * mGame->mBaseCharacterSize );
  mGameOverText.centerHorizontally( mGame->mVideoMode );
  mGameOverText.centerVertically( mGame->mVideoMode );
}

std::function< void() > GameOverScreen::createBackToMenuFunction() {
  return [ this ](){
           mGame->popState();
         };
}
