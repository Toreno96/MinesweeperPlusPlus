#include "MenuScreen.hpp"

MenuScreen::MenuScreen( Game *game ) :
    GameState( game ),
    mTitle( game->mVideoMode, GameConstants::title, game->mFont, game->mBaseCharacterSize ),
    mNewGameButton( [](){}, "New Game", game->mFont, game->mBaseCharacterSize ),
    mContinueButton( [](){}, "Continue", game->mFont, game->mBaseCharacterSize ),
    mOptionsButton( [ game ](){
                      game->pushState( std::make_unique< OptionsScreen >( game ) );
                    }, "Options", game->mFont, game->mBaseCharacterSize ),
    mHighScoresButton( [](){}, "High Scores", game->mFont, game->mBaseCharacterSize ),
    mExitButton( [ game ](){ game->exit(); },
                 "Exit", game->mFont, game->mBaseCharacterSize ) {
  positionDrawables();
}

void MenuScreen::handleInput() {
  sf::Event event;
  bool leftMouseButtonClicked = false;
  
  while( mGame->mWindow.pollEvent( event ) ) {
    switch( event.type ) {
      case sf::Event::MouseButtonReleased: {
        if( event.mouseButton.button == sf::Mouse::Left )
          leftMouseButtonClicked = true;
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
  
  mNewGameButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
  mContinueButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
  mOptionsButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
  mHighScoresButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
  mExitButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
}
void MenuScreen::update() {
  GameState::update();
  
  if( mGame->mSaveManager.isActualSaveDataPresent() )
    mContinueButton.activate();
  else
    mContinueButton.deactivate();
  
  mNewGameButton.update();
  mContinueButton.update();
  mOptionsButton.update();
  mHighScoresButton.update();
  mExitButton.update();
}
void MenuScreen::draw() {
  mGame->mWindow.clear( sf::Color::Black );
  mGame->mWindow.draw( mTitle );
  mGame->mWindow.draw( mNewGameButton );
  mGame->mWindow.draw( mContinueButton );
  mGame->mWindow.draw( mOptionsButton );
  mGame->mWindow.draw( mHighScoresButton );
  mGame->mWindow.draw( mExitButton );
  mGame->mWindow.display();
}

void MenuScreen::positionDrawables() {
  mNewGameButton.centerHorizontally( mGame->mVideoMode );
  mNewGameButton.positionBelow( mTitle, 2 * mGame->mBaseDistanceBetweenTextGraphics );
  
  mContinueButton.alignHorizontallyRelativeTo( mNewGameButton );
  mContinueButton.positionBelow( mNewGameButton, mGame->mBaseDistanceBetweenTextGraphics );
  
  mOptionsButton.alignHorizontallyRelativeTo( mNewGameButton );
  mOptionsButton.positionBelow( mContinueButton, mGame->mBaseDistanceBetweenTextGraphics );
  
  mHighScoresButton.alignHorizontallyRelativeTo( mNewGameButton );
  mHighScoresButton.positionBelow( mOptionsButton, mGame->mBaseDistanceBetweenTextGraphics );
  
  mExitButton.alignHorizontallyRelativeTo( mNewGameButton );
  mExitButton.positionBelow( mHighScoresButton, mGame->mBaseDistanceBetweenTextGraphics );
}