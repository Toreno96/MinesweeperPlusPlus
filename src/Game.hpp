#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <SFML/Graphics.hpp>
#include "GameLogic/HighScores.hpp"
#include "GameLogic/Options.hpp"
#include "GameLogic/SaveManager.hpp"
#include "HelperSrc/GameConstants.hpp"

class GameState;

class Game {
  public:
    // Konstruktor:
    Game();
    // Destruktor:
    ~Game();
    // Usunięte metody domyślne:
    Game( const Game &other ) = delete;
    Game &operator=( Game other ) = delete;
    // Obsługa stosu stanów:
    void pushState( std::unique_ptr< GameState > state );
    void popState();
    void changeState( std::unique_ptr< GameState > state );
    GameState *topState() const;
    // Uruchomienie i zakończenie gry:
    void run();
    void exit();
    // Składowe publiczne:
    boost::random::mt19937 mRandomGenerator;
    HighScores mHighScores;
    Options mOptions;
    SaveManager mSaveManager;
    sf::Font mFont;
    sf::VideoMode mVideoMode;
    sf::RenderWindow mWindow;
    std::unordered_map< unsigned, sf::Texture > mClassicAndHexTextures;
    std::unordered_map< unsigned, sf::Texture > mTriTextures;
    std::unordered_map< unsigned, sf::Texture > mReversedTriTextures;
    unsigned mBaseCharacterSize;
    float mBaseDistanceBetweenTextGraphics;
  protected:
    // Pomocnicze metody chronione:
    boost::random::mt19937 createTrueRandomSeededGenerator();
    void loadTexturesFromFile( const std::string &filepath,
                               std::unordered_map< unsigned, sf::Texture > &texturesContainer,
                               const unsigned texturesCount );
    void loadAllTexturesFromFiles();
    void loadDataFromFiles();
    void createWindow( sf::RenderWindow &window );
    // Składowe chronione:
    std::stack< std::unique_ptr< GameState > > mStates;
};