#include <array>
#include <vector>
#include "Options.hpp"

class HighScores {
  public:
    // Konstruktor:
    HighScores();
    // Dodawanie nowego wyniku:
    void addScore( const unsigned scoreInSeconds, const Options &currentOptions );
  private:
    // Chronione metody pomocnicze:
    std::string convertOptionsToString( const Options &options ) const;
    // Składowe:
    std::vector< std::array< std::string, 3 > > mCategories;
    std::vector< unsigned > mScores;
    bool newHighScore;
};
