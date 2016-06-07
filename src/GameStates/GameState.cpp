#include "GameState.hpp"

GameState::GameState( Game *game ) :
    mGame( game ), mExited( false ) {}
GameState::~GameState() {}

void GameState::update() {
  if( mExited )
    mGame->exit();
}