#include "PlayScreen.hpp"

PlayScreen::PlayScreen( Game *game,
                        std::unique_ptr< Minefield > minefieldLogic,
                        std::unique_ptr< DrawingMinefield > minefieldDrawing ) :
    GameState( game ),
    mSecondsMeter( SecondsMeter() ),
    mMinefieldLogic( std::move( minefieldLogic ) ),
    mMinefieldDrawing( std::move( minefieldDrawing ) ),
    //mText( std::unordered_map< std::string, ExtendedText >() ),
    mBackToMenuButton( ButtonText( createBackToMenuFunction(),
                                   "Menu", mGame->mFont, mGame->mBaseCharacterSize ) ) {
  positionDrawables();
}

void PlayScreen::handleInput() {
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
void PlayScreen::update() {
  GameState::update();
  
  mBackToMenuButton.update();
}
void PlayScreen::draw() {
  mGame->mWindow.clear( sf::Color::Black );
  mGame->mWindow.draw( mBackToMenuButton );
  mGame->mWindow.display();
}

void PlayScreen::positionDrawables() {
  mBackToMenuButton.centerHorizontally( mGame->mVideoMode );
  mBackToMenuButton.moveY( 0.25 * mGame->mBaseCharacterSize );
}

std::function< void() > PlayScreen::createBackToMenuFunction() {
  return [ this ](){
           mGame->mSaveManager.save( *( mMinefieldLogic.get() ) );
           mGame->popState();
         };
}