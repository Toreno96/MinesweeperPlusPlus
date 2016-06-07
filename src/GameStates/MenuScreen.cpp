#include "MenuScreen.hpp"

MenuScreen::MenuScreen( Game *game ) :
    GameState( game ),
    mTitle( game->mVideoMode, GameConstants::title, game->mFont, game->mBaseCharacterSize ),
    mExitButton( [ game ](){ game->exit(); },
                 "Exit", game->mFont, game->mBaseCharacterSize ),
    mMainButtons( std::unordered_map< std::string, ButtonText >() ) {
  fillMainButtons();
  positionDrawables();
  mMainButtons[ "High Scores" ].deactivate();
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
  
  for( auto &button : mMainButtons )
    button.second.handleInput( mGame->mWindow, leftMouseButtonClicked );
  mExitButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
}
void MenuScreen::update() {
  GameState::update();
  
  if( mGame->mSaveManager.isActualSaveDataPresent() )
    mMainButtons[ "Continue" ].activate();
  else
    mMainButtons[ "Continue" ].deactivate();
  
  for( auto &button : mMainButtons )
    button.second.update();
  mExitButton.update();
}
void MenuScreen::draw() {
  mGame->mWindow.clear( sf::Color::Black );
  mGame->mWindow.draw( mTitle );
  mGame->mWindow.draw( mExitButton );
  for( auto &button : mMainButtons )
    mGame->mWindow.draw( button.second );
  mGame->mWindow.display();
}

void MenuScreen::positionDrawables() {
  mMainButtons[ "New Game" ].centerHorizontally( mGame->mVideoMode );
  mMainButtons[ "New Game" ].positionBelow( mTitle, 2 * mGame->mBaseDistanceBetweenTextGraphics );
  
  mMainButtons[ "Continue" ].alignHorizontallyRelativeTo( mMainButtons[ "New Game" ] );
  mMainButtons[ "Continue" ].positionBelow( mMainButtons[ "New Game" ], mGame->mBaseDistanceBetweenTextGraphics );
  
  mMainButtons[ "Options" ].alignHorizontallyRelativeTo( mMainButtons[ "New Game" ] );
  mMainButtons[ "Options" ].positionBelow( mMainButtons[ "Continue" ], mGame->mBaseDistanceBetweenTextGraphics );
  
  mMainButtons[ "High Scores" ].alignHorizontallyRelativeTo( mMainButtons[ "New Game" ] );
  mMainButtons[ "High Scores" ].positionBelow( mMainButtons[ "Options" ], mGame->mBaseDistanceBetweenTextGraphics );
  
  mExitButton.alignHorizontallyRelativeTo( mMainButtons[ "New Game" ] );
  mExitButton.positionBelow( mMainButtons[ "High Scores" ], mGame->mBaseDistanceBetweenTextGraphics );
}

void MenuScreen::fillMainButtons() {
  mMainButtons[ "New Game" ] = ButtonText( createNewGameFunction(), "New Game", mGame->mFont, mGame->mBaseCharacterSize );
  mMainButtons[ "Continue" ] = ButtonText( createContinueFunction(), "Continue", mGame->mFont, mGame->mBaseCharacterSize );
  mMainButtons[ "Options" ] = ButtonText( createOptionsFunction(), "Options", mGame->mFont, mGame->mBaseCharacterSize );
  mMainButtons[ "High Scores" ] = ButtonText( [](){}, "High Scores", mGame->mFont, mGame->mBaseCharacterSize );
}

std::function< void() > MenuScreen::createNewGameFunction() {
  return [ this ](){
           switch( mGame->mOptions.getCellsShape() ) {
             case CellsShape::classic: {
               mGame->pushState( std::make_unique< PlayScreen >(
                   mGame,
                   std::make_unique< MinefieldClassic >( mGame->mOptions.generateMinefieldData() ),
                   std::make_unique< DrawingMinefieldClassic >(
                       mGame,
                       mGame->mOptions.getRowsCount(),
                       mGame->mOptions.getColumnsCount() ) ) );
               break;
             }
             default:
              break;
           }
         };
}
std::function< void() > MenuScreen::createContinueFunction() {
  return [ this ](){
           switch( mGame->mOptions.getCellsShape() ) {
             case CellsShape::classic: {
               mGame->pushState( std::make_unique< PlayScreen >(
                   mGame,
                   std::make_unique< MinefieldClassic >( mGame->mSaveManager.load() ),
                   std::make_unique< DrawingMinefieldClassic >(
                       mGame,
                       mGame->mOptions.getRowsCount(),
                       mGame->mOptions.getColumnsCount() ) ) );
               break;
             }
             default:
              break;
           }
         };
}
std::function< void() > MenuScreen::createOptionsFunction() {
  return [ this ](){
           mGame->pushState( std::make_unique< OptionsScreen >( mGame ) );
           mGame->mSaveManager.setActualSaveDataPresent( false );
         };
}