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

  if( mMinefieldDrawing->containMouse() ) {
    std::size_t row = mMinefieldDrawing->getMouseContainingRow();
    std::size_t column = mMinefieldDrawing->getMouseContainingColumn();
    if( leftMouseButtonClicked ) {
      if( !( mMinefieldLogic->isMined() ) )
        mMinefieldLogic->mine( mGame->mRandomGenerator, row, column );
      mMinefieldLogic->uncover( row, column );
    }
    else if( rightMouseButtonClicked )
      switch( mMinefieldLogic->getCell( row, column ).getState() ) {
        case CellState::covered:
          mMinefieldLogic->flag( row, column );
          break;
        case CellState::flagged:
          mMinefieldLogic->unflag( row, column );
          break;
        default:
          break;
      }
  }
  else
    mBackToMenuButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
}
void PlayScreen::update() {
  if( gameLost() ) {
    mGame->mSaveManager.setActualSaveDataPresent( false );
    mGame->exit(); // mGame->changeState( /* GameOverScreen */ );
  }
  else if( gameWon() ) {
    mGame->mSaveManager.setActualSaveDataPresent( false );
    mGame->popState(); // mGame->changeState( /* GameWonScreen */ );
  }
  else if( mExited == true ) {
    mGame->mSaveManager.save( *( mMinefieldLogic.get() ) );
    mGame->exit();
  }
  else {
    mMinefieldDrawing->update( mMinefieldLogic.get() );
    mBackToMenuButton.update();
  }
}
void PlayScreen::draw() {
  mMinefieldDrawing->draw( mGame->mWindow );
  mGame->mWindow.draw( mBackToMenuButton );
}

void PlayScreen::positionDrawables() {
  mBackToMenuButton.centerHorizontally( mGame->mVideoMode );
  mBackToMenuButton.moveY( 0.05 * mGame->mBaseCharacterSize );
}

std::function< void() > PlayScreen::createBackToMenuFunction() {
  return [ this ](){
           mGame->mSaveManager.save( *( mMinefieldLogic.get() ) );
           mGame->popState();
         };
}

bool PlayScreen::gameWon() {
  if( mMinefieldLogic->getUncoveredCellsCount() ==
      mMinefieldLogic->getRowsCount() *
      mMinefieldLogic->getColumnsCount() -
      mMinefieldLogic->getMinesCount() )
    return true;
  else
    return false;
}
bool PlayScreen::gameLost() {
  return mMinefieldLogic->isDetonated();
}
