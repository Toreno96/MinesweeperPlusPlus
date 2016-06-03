#include "HighScores.hpp"

// Konstruktor:
HighScores::HighScores() : mCategories( std::vector< std::string >() ), mScores( std::vector< std::vector< unsigned > >() ), mNewHighScore( false ) {}
// Gettery:
std::string HighScores::getCategory( const std::size_t index ) const {
  return mCategories[ index ];
}
std::string HighScores::getScores( const std::size_t indexOfCategory ) const {
  return convertScoresToString( indexOfCategory );
}
bool HighScores::isNewHighScore() const {
  return mNewHighScore;
}
// Dodawanie nowego wyniku:
void HighScores::addScore( const unsigned scoreInSeconds, const Options &currentOptions ) {
  std::string currentOptionsAsString = convertOptionsToString( currentOptions );
  std::size_t existingCategoryIndex;
  bool indexFound = false;
  for( std::size_t categoriesIndex = 0, categoriesSize = mCategories.size();
       categoriesIndex < categoriesSize; ++categoriesIndex )
    if( mCategories[ categoriesIndex ] == currentOptionsAsString ) {
      existingCategoryIndex = categoriesIndex;
      indexFound = true;
    }
  if( indexFound ) {
    addScoreToExistingCategory( existingCategoryIndex, scoreInSeconds );
  }
  else {
    addScoreToNewCategory( scoreInSeconds, currentOptionsAsString );
  }
}
// Obsługa plików:
void HighScores::loadFromFile( const std::string &filename ) {
  std::ifstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    readCategoriesFromFile( file );
    readSingleCategoryScoresFromFile( file );
  }
}
void HighScores::saveToFile( const std::string &filename ) const {
  std::ofstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    writeCategoriesToFile( file );
    writeSingleCategoryScoresToFile( file );
  }
}
// Chronione metody pomocnicze:
void HighScores::addScoreToNewCategory( const unsigned scoreInSeconds, const std::string &currentOptionsAsString ) {
  mCategories.push_back( currentOptionsAsString );
  std::vector< unsigned > currentCategoryScores;
  currentCategoryScores.push_back( scoreInSeconds );
  mScores.push_back( currentCategoryScores );
  mNewHighScore = true;
}
void HighScores::addScoreToExistingCategory( const std::size_t categoryIndex, const unsigned scoreInSeconds ) {
  auto &currentCategoryScores = mScores[ categoryIndex ];
  if( std::none_of( currentCategoryScores.begin(), currentCategoryScores.end(),
                    [ scoreInSeconds ]( const unsigned score ){
                      return scoreInSeconds == score;
                    } ) ) {
    currentCategoryScores.push_back( scoreInSeconds );
    std::sort( currentCategoryScores.begin(), currentCategoryScores.end() );
    if( currentCategoryScores.size() > maxScoresPerCategory )
      currentCategoryScores.resize( maxScoresPerCategory );
    mNewHighScore = true;
  }
  else
    mNewHighScore = false;
}
void HighScores::deleteLastCharacter( std::string &string ) const {
  string.erase( std::next( string.rbegin() ).base() );
}
std::string HighScores::convertCellsShapeToString( const Options &options ) const {
  switch( options.getCellsShape() ) {
    case CellsShape::classic:
      return "Classic";
    case CellsShape::tri:
      return "Tri";
    case CellsShape::hex:
      return "Hex";
  }
}
std::string HighScores::convertCountsToString( const Options &options ) const {
  return std::to_string( options.getRowsCount() )    + 'x'  +
         std::to_string( options.getColumnsCount() ) + ", " +
         std::to_string( options.getMinesCount() )   + " mines";
}
std::string HighScores::convertOptionsToString( const Options &options ) const {
  return convertCellsShapeToString( options ) + '\n' +
         convertCountsToString( options );
}
std::string HighScores::convertScoresToString( const std::size_t indexOfCategory ) const {
  std::string scoresAsString;
  for( auto score : mScores[ indexOfCategory ] )
    scoresAsString += std::to_string( score ) + '\n';
  deleteLastCharacter( scoresAsString );
  return scoresAsString;
}
void HighScores::readCategoriesFromFile( std::ifstream &file ) {
  auto categoriesCount = BinaryFiles::read< std::size_t >( file );
  mCategories = std::vector< std::string >( categoriesCount );
  for( auto &category : mCategories )
    category = BinaryFiles::read< std::string >( file );
}
void HighScores::readSingleCategoryScoresFromFile( std::ifstream &file ) {
  mScores = std::vector< std::vector< unsigned > >( mCategories.size() );
  for( auto &singleCategoryScores : mScores ) {
    auto currentSingleCategoryScoresCount = BinaryFiles::read< std::size_t >( file );
    singleCategoryScores = std::vector< unsigned >( currentSingleCategoryScoresCount );
    for( auto &score : singleCategoryScores )
      score = BinaryFiles::read< unsigned >( file );
  }
}
void HighScores::writeCategoriesToFile( std::ofstream &file ) const {
  BinaryFiles::write( file, mCategories.size() );
  for( auto &category : mCategories )
    BinaryFiles::write( file, category );
}
void HighScores::writeSingleCategoryScoresToFile( std::ofstream &file ) const {
  for( auto &singleCategoryScores : mScores ) {
    BinaryFiles::write( file, singleCategoryScores.size() );
    for( auto score : singleCategoryScores )
      BinaryFiles::write( file, score );
  }
}