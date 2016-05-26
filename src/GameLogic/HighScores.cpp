#include "HighScores.hpp"

// Konstruktor:
HighScores::HighScores() : mCategories( std::vector< std::string >() ), mScores( std::vector< std::array< unsigned, maxScoresPerCategory > >() ), mNewHighScore( false ) {}
// Dodawanie nowego wyniku:
void HighScores::addScore( const unsigned scoreInSeconds, const Options &currentOptions ) {}
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
// Chronione metody pomocnicze:
void HighScores::deleteLastCharacter( std::string &string ) const {
  string.erase( std::next( string.rbegin() ).base() );
}
std::string HighScores::convertOptionsToString( const Options &options ) const {}
std::string HighScores::convertScoresToString( const std::size_t indexOfCategory ) const {
  std::string scoresAsString;
  for( auto score : mScores[ indexOfCategory ] )
    scoresAsString = std::to_string( score ) + '\n';
  deleteLastCharacter( scoresAsString );
  return scoresAsString;
}