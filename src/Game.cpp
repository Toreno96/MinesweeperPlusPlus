#include "Game.hpp"

Game::Game() {}
void Game::pushState( std::unique_ptr< GameState > state ) {
  mStates.push( std::move( state ) );
}
void Game::popState() {
  if( !( mStates.empty() ) )
    mStates.pop();
}
void Game::changeState( std::unique_ptr< GameState > state ) {
  popState();
  pushState( std::move( state ) );
}
GameState* Game::topState() {
  if( !( mStates.empty() ) )
    return mStates.top().get();
  else
    return nullptr;
}
void Game::run() {}