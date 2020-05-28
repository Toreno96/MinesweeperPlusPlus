#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include "HelperSrc/BinaryFiles.hpp"
#include "Options.hpp"

const std::size_t maxScoresPerCategory = 3;
const std::string defaultHighScoresFilename = "highscores.dat";

class HighScores {
  public:
    // Konstruktor:
    HighScores();
    // Gettery:
    std::string getCategory( const std::size_t index ) const;
    std::string getScores( const std::size_t indexOfCategory ) const;
    bool isNewHighScore() const;
    // Dodawanie nowego wyniku:
    void addScore( const unsigned scoreInSeconds, const Options &currentOptions );
    // Obsługa plików:
    void loadFromFile( const std::string &filename = defaultHighScoresFilename );
    void saveToFile( const std::string &filename = defaultHighScoresFilename ) const;
  private:
    // Chronione metody pomocnicze:
    void addScoreToNewCategory( const unsigned scoreInSeconds, const std::string &currentOptions );
    void addScoreToExistingCategory( const std::size_t categoryIndex, const unsigned scoreInSeconds );
    void deleteLastCharacter( std::string &string ) const;
    std::string convertCellsShapeToString( const Options &options ) const;
    std::string convertCountsToString( const Options &options ) const;
    std::string convertOptionsToString( const Options &options ) const;
    std::string convertScoresToString( const std::size_t indexOfCategory ) const;
    void readCategoriesFromFile( std::ifstream &file );
    void readSingleCategoryScoresFromFile( std::ifstream &file );
    void writeCategoriesToFile( std::ofstream &file ) const;
    void writeSingleCategoryScoresToFile( std::ofstream &file ) const;
    // Składowe:
    std::vector< std::string > mCategories;
    std::vector< std::vector< unsigned > > mScores;
    bool mNewHighScore;
};
