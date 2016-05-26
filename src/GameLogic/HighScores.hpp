#include <array>
#include <string>
#include <vector>
#include "Options.hpp"

const std::size_t maxScoresPerCategory = 3;

class HighScores {
  public:
    // Konstruktor:
    HighScores();
    // Dodawanie nowego wyniku:
    void addScore( const unsigned scoreInSeconds, const Options &currentOptions );
    // Gettery:
    std::string getCategory( const std::size_t index ) const;
    std::string getScores( const std::size_t indexOfCategory ) const;
    bool isNewHighScore() const;
  private:
    // Chronione metody pomocnicze:
    void deleteLastCharacter( std::string &string ) const;
    std::string convertOptionsToString( const Options &options ) const;
    std::string convertScoresToString( const std::size_t indexOfCategory ) const;
    // Składowe:
    std::vector< std::string > mCategories;
    std::vector< std::array< unsigned, maxScoresPerCategory > > mScores;
    bool mNewHighScore;
};