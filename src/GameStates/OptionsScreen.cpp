#include "OptionsScreen.hpp"

OptionsScreen::OptionsScreen( Game *game ) :
    GameState( game ),
    mTitle( game->mVideoMode, "Options", game->mFont, game->mBaseCharacterSize ),
    mBackButton( game,
                 game->mFont, game->mBaseCharacterSize ),
    mOptionsNames( std::unordered_map< std::string, ExtendedText >() ),
    mCurrentlyChosenOptions( std::unordered_map< std::string, ExtendedText >() ),
    mPreviousOptionButtons( std::unordered_map< std::string, PreviousChoiceButton >() ),
    mNextOptionButtons( std::unordered_map< std::string, NextChoiceButton >() ) {
  fillOptionsNames();
  fillCurrentlyChosenOptions();
  fillPreviousOptionButtons();
  fillNextOptionButtons();
  positionDrawables();
}

void OptionsScreen::handleInput() {
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

  for( auto &previousOptionButton : mPreviousOptionButtons )
    previousOptionButton.second.handleInput( mGame->mWindow, leftMouseButtonClicked );
  for( auto &nextOptionButton : mNextOptionButtons )
    nextOptionButton.second.handleInput( mGame->mWindow, leftMouseButtonClicked );
  mBackButton.handleInput( mGame->mWindow, leftMouseButtonClicked );
}
void OptionsScreen::update() {
  GameState::update();

  for( auto &previousOptionButton : mPreviousOptionButtons )
    previousOptionButton.second.update();
  for( auto &nextOptionButton : mNextOptionButtons )
    nextOptionButton.second.update();
  updateCurrentlyChosenOptions();
  mBackButton.update();
}
void OptionsScreen::draw() {
  mGame->mWindow.clear( sf::Color::Black );
  mGame->mWindow.draw( mTitle );
  mGame->mWindow.draw( mBackButton );
  for( auto &optionName : mOptionsNames )
    mGame->mWindow.draw( optionName.second );
  for( auto &currentlyChosenOption : mCurrentlyChosenOptions )
    mGame->mWindow.draw( currentlyChosenOption.second );
  for( auto &previousOptionButton : mPreviousOptionButtons )
    mGame->mWindow.draw( previousOptionButton.second );
  for( auto &nextOptionButton : mNextOptionButtons )
    mGame->mWindow.draw( nextOptionButton.second );
  mGame->mWindow.display();
}

void OptionsScreen::positionDrawables() {
  mOptionsNames[ "Cells Shape" ].centerHorizontally( mGame->mVideoMode );
  mOptionsNames[ "Cells Shape" ].moveX( -( mOptionsNames[ "Cells Shape" ].getLocalBounds().width / 2 ) );
  mOptionsNames[ "Cells Shape" ].positionBelow( mTitle, 2 * mGame->mBaseDistanceBetweenTextGraphics );
  mPreviousOptionButtons[ "Cells Shape" ].alignVerticallyRelativeTo( mOptionsNames[ "Cells Shape" ] );
  mPreviousOptionButtons[ "Cells Shape" ].positionRight( mOptionsNames[ "Cells Shape" ],
                                                        2 * mGame->mBaseDistanceBetweenTextGraphics );
  positionCurrentlyChosenOption( "Cells Shape" );
  positionNextOptionButton( "Cells Shape" );
  positionOptionBelowTheOther( "Difficulty", "Cells Shape" );
  positionOptionBelowTheOther( "Rows", "Difficulty" );
  positionOptionBelowTheOther( "Columns", "Rows" );
  positionOptionBelowTheOther( "Mines", "Columns" );
}

void OptionsScreen::fillOptionsNames() {
  mOptionsNames[ "Cells Shape" ] = ExtendedText( "Cells Shape", mGame->mFont, mGame->mBaseCharacterSize );
  mOptionsNames[ "Difficulty" ] = ExtendedText( "Difficulty", mGame->mFont, mGame->mBaseCharacterSize );
  mOptionsNames[ "Rows" ] = ExtendedText( "Rows", mGame->mFont, mGame->mBaseCharacterSize );
  mOptionsNames[ "Columns" ] = ExtendedText( "Columns", mGame->mFont, mGame->mBaseCharacterSize );
  mOptionsNames[ "Mines" ] = ExtendedText( "Mines", mGame->mFont, mGame->mBaseCharacterSize );
}
void OptionsScreen::fillCurrentlyChosenOptions() {
  mCurrentlyChosenOptions[ "Cells Shape" ] = mCurrentlyChosenOptions[ "Difficulty" ]
                                           = mCurrentlyChosenOptions[ "Rows" ]
                                           = mCurrentlyChosenOptions[ "Columns" ]
                                           = mCurrentlyChosenOptions[ "Mines" ]
                                           = ExtendedText( "", mGame->mFont, mGame->mBaseCharacterSize );
}
void OptionsScreen::fillPreviousOptionButtons() {
  mPreviousOptionButtons[ "Cells Shape" ] = PreviousChoiceButton( createPreviousCellsShapeFunction(),
                                                          mGame->mFont, mGame->mBaseCharacterSize );
  mPreviousOptionButtons[ "Difficulty" ] = PreviousChoiceButton( createPreviousDifficultyFunction(),
                                                         mGame->mFont, mGame->mBaseCharacterSize );
  mPreviousOptionButtons[ "Rows" ] = PreviousChoiceButton( createDecrementRowsFunction(),
                                                   mGame->mFont, mGame->mBaseCharacterSize );
  mPreviousOptionButtons[ "Columns" ] = PreviousChoiceButton( createDecrementColumnsFunction(),
                                                      mGame->mFont, mGame->mBaseCharacterSize );
  mPreviousOptionButtons[ "Mines" ] = PreviousChoiceButton( createDecrementMinesFunction(),
                                                    mGame->mFont, mGame->mBaseCharacterSize );
}
void OptionsScreen::fillNextOptionButtons() {
  mNextOptionButtons[ "Cells Shape" ] = NextChoiceButton( createNextCellsShapeFunction(),
                                                          mGame->mFont, mGame->mBaseCharacterSize );
  mNextOptionButtons[ "Difficulty" ] = NextChoiceButton( createNextDifficultyFunction(),
                                                         mGame->mFont, mGame->mBaseCharacterSize );
  mNextOptionButtons[ "Rows" ] = NextChoiceButton( createIncrementRowsFunction(),
                                                   mGame->mFont, mGame->mBaseCharacterSize );
  mNextOptionButtons[ "Columns" ] = NextChoiceButton( createIncrementColumnsFunction(),
                                                      mGame->mFont, mGame->mBaseCharacterSize );
  mNextOptionButtons[ "Mines" ] = NextChoiceButton( createIncrementMinesFunction(),
                                                    mGame->mFont, mGame->mBaseCharacterSize );
}

std::function< void() > OptionsScreen::createPreviousCellsShapeFunction() {
  return [ this ](){
           switch( mGame->mOptions.getCellsShape() ) {
             case CellsShape::tri:
               mGame->mOptions.setCellsShape( CellsShape::hex );
               break;
             case CellsShape::hex:
               mGame->mOptions.setCellsShape( CellsShape::classic );
               break;
             default:
               break;
           }
         };
}
std::function< void() > OptionsScreen::createPreviousDifficultyFunction() {
  return [ this ](){
           switch( mGame->mOptions.getDifficulty() ) {
             case Difficulty::custom:
               mGame->mOptions.setDifficulty( Difficulty::hard );
               break;
             case Difficulty::hard:
               mGame->mOptions.setDifficulty( Difficulty::normal );
               break;
             case Difficulty::normal:
               mGame->mOptions.setDifficulty( Difficulty::easy );
               break;
             default:
               break;
           }
         };
}
std::function< void() > OptionsScreen::createNextCellsShapeFunction() {
  return [ this ](){
           switch( mGame->mOptions.getCellsShape() ) {
             case CellsShape::classic:
               mGame->mOptions.setCellsShape( CellsShape::hex );
               break;
             case CellsShape::hex:
               mGame->mOptions.setCellsShape( CellsShape::tri );
               break;
             default:
               break;
           }
         };
}
std::function< void() > OptionsScreen::createNextDifficultyFunction() {
  return [ this ](){
           switch( mGame->mOptions.getDifficulty() ) {
             case Difficulty::easy:
               mGame->mOptions.setDifficulty( Difficulty::normal );
               break;
             case Difficulty::normal:
               mGame->mOptions.setDifficulty( Difficulty::hard );
               break;
             case Difficulty::hard:
               mGame->mOptions.setDifficulty( Difficulty::custom );
               break;
             default:
               break;
           }
         };
}
std::function< void() > OptionsScreen::createDecrementRowsFunction() {
  return [ this ](){
           auto rowsCount = mGame->mOptions.getRowsCount();
           mGame->mOptions.setRowsCount( rowsCount - 1 ); 
         };
}
std::function< void() > OptionsScreen::createDecrementColumnsFunction() {
  return [ this ](){
           auto columnsCount = mGame->mOptions.getColumnsCount();
           mGame->mOptions.setColumnsCount( columnsCount - 1 ); 
         };
}
std::function< void() > OptionsScreen::createDecrementMinesFunction() {
  return [ this ](){
           auto minesCount = mGame->mOptions.getMinesCount();
           mGame->mOptions.setMinesCount( minesCount - 1 ); 
         };
}
std::function< void() > OptionsScreen::createIncrementRowsFunction() {
  return [ this ](){
           auto rowsCount = mGame->mOptions.getRowsCount();
           mGame->mOptions.setRowsCount( rowsCount + 1 ); 
         };
}
std::function< void() > OptionsScreen::createIncrementColumnsFunction() {
  return [ this ](){
           auto columnsCount = mGame->mOptions.getColumnsCount();
           mGame->mOptions.setColumnsCount( columnsCount + 1 ); 
         };
}
std::function< void() > OptionsScreen::createIncrementMinesFunction() {
  return [ this ](){
           auto minesCount = mGame->mOptions.getMinesCount();
           if( minesCount > GameConstants::minMinesCount )
             mGame->mOptions.setMinesCount( minesCount + 1 ); 
         };
}

void OptionsScreen::positionOptionName( const std::string &keyToOption, const std::string &keyToOtherOption ) {
  mOptionsNames[ keyToOption ].alignHorizontallyRelativeTo( mOptionsNames[ keyToOtherOption ] );
  mOptionsNames[ keyToOption ].positionBelow( mOptionsNames[ keyToOtherOption ],
                                                        mGame->mBaseDistanceBetweenTextGraphics );
}
void OptionsScreen::positionPreviousOptionButton( const std::string &keyToOption, const std::string &keyToOtherOption ) {
  mPreviousOptionButtons[ keyToOption ].alignHorizontallyRelativeTo( mPreviousOptionButtons[ keyToOtherOption ] );
  mPreviousOptionButtons[ keyToOption ].setPositionY( mOptionsNames[ keyToOption ].getPosition().y );
}
void OptionsScreen::positionCurrentlyChosenOption( const std::string &keyToOption ) {
  mCurrentlyChosenOptions[ keyToOption ].alignVerticallyRelativeTo( mOptionsNames[ keyToOption ] );
  mCurrentlyChosenOptions[ keyToOption ].positionRight( mPreviousOptionButtons[ keyToOption ],
                                                        mGame->mBaseDistanceBetweenTextGraphics );
}
void OptionsScreen::positionNextOptionButton( const std::string &keyToOption ) {
  mNextOptionButtons[ keyToOption ].alignVerticallyRelativeTo( mOptionsNames[ keyToOption ] );
  mNextOptionButtons[ keyToOption ].setPositionX( mGame->mVideoMode.width
                                                  - 4 * mGame->mBaseDistanceBetweenTextGraphics );
}
void OptionsScreen::positionOptionBelowTheOther( const std::string &keyToOption, const std::string &keyToOtherOption ) {
  positionOptionName( keyToOption, keyToOtherOption );
  positionPreviousOptionButton( keyToOption, keyToOtherOption );
  positionCurrentlyChosenOption( keyToOption );
  positionNextOptionButton( keyToOption );
}

void OptionsScreen::updateCurrentlyChosenCellsShape() {
  std::string currentlyChosenCellsShapeString;
   switch( mGame->mOptions.getCellsShape() ) {
     case CellsShape::classic:
        currentlyChosenCellsShapeString = "Classic";
        break;
     case CellsShape::tri:
       currentlyChosenCellsShapeString = "Tri";
       break;
     case CellsShape::hex:
       currentlyChosenCellsShapeString = "Hex";
       break;
   }
   mCurrentlyChosenOptions[ "Cells Shape" ].setString( currentlyChosenCellsShapeString );
}
void OptionsScreen::updateCurrentlyChosenDifficulty() {
  std::string currentlyChosenDifficultyString;
   switch( mGame->mOptions.getDifficulty() ) {
     case Difficulty::easy:
        currentlyChosenDifficultyString = "Easy";
        break;
     case Difficulty::normal:
       currentlyChosenDifficultyString = "Normal";
       break;
     case Difficulty::hard:
       currentlyChosenDifficultyString = "Hard";
       break;
     case Difficulty::custom:
       currentlyChosenDifficultyString = "Custom";
       break;
   }  
   mCurrentlyChosenOptions[ "Difficulty" ].setString( currentlyChosenDifficultyString );
}
void OptionsScreen::updateCurrentlyChosenDimensions() {
  mCurrentlyChosenOptions[ "Rows" ].setString( std::to_string( mGame->mOptions.getRowsCount() ) );
  mCurrentlyChosenOptions[ "Columns" ].setString( std::to_string( mGame->mOptions.getColumnsCount() ) );
  mCurrentlyChosenOptions[ "Mines" ].setString( std::to_string( mGame->mOptions.getMinesCount() ) );
}
void OptionsScreen::updateCurrentlyChosenOptions() {
  updateCurrentlyChosenCellsShape();
  updateCurrentlyChosenDifficulty();
  updateCurrentlyChosenDimensions();
}