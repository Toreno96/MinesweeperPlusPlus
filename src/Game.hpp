#pragma once

#include <memory>
#include <stack>
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
    HighScores mHighScores;
    Options mOptions;
    SaveManager mSaveManager;
    sf::Font mFont;
    sf::VideoMode mVideoMode;
    sf::RenderWindow mWindow;
    unsigned mBaseCharacterSize;
    float mBaseDistanceBetweenTextGraphics;
  protected:
    // Pomocnicze metody chronione:
    void loadDataFromFiles();
    void calculateNumericalData();
    void createWindow( sf::RenderWindow &window );
    // Składowe chronione:
    std::stack< std::unique_ptr< GameState > > mStates;
};