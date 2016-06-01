#pragma once

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "GameLogic/HighScores.hpp"
#include "GameLogic/Options.hpp"
#include "GameLogic/SaveManager.hpp"
//#include "GameState.hpp"

class GameState;

class Game {
  public:
    Game();
    Game( const Game &other ) = delete;
    Game &operator=( Game other ) = delete;
    
    void pushState( std::unique_ptr< GameState > state );
    void popState();
    void changeState( std::unique_ptr< GameState > state );
    GameState* topState();
    
    void run();
  private:
    std::stack< std::unique_ptr< GameState > > mStates;
    sf::RenderWindow mWindow;
    HighScores mHighScores;
    Options mOptions;
    SaveManager mSaveManager;
};