#include "GameStates/MenuScreen.hpp"

// Konstruktor:
Game::Game() : mHighScores( HighScores() ), mOptions( Options() ), mSaveManager( SaveManager() ), mStates( std::stack< std::unique_ptr< GameState > >() ), mVideoMode( sf::VideoMode( 800, 600 ) ) {
  pushState( std::make_unique< MenuScreen >( this ) );
  mHighScores.loadFromFile();
  mOptions.loadFromFile();
  mSaveManager.loadFromFile();
}
// Destruktor:
Game::~Game() {}
// Obsługa stosu stanów:
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
GameState *Game::topState() const {
  if( mStates.empty() )
    return nullptr;
  else
    return mStates.top().get();
}
// Uruchomienie i zakończenie gry:
void Game::run() {
  createWindow( mWindow );
  while( mWindow.isOpen() ) {
    GameState *pTopState = topState();
    if( pTopState == nullptr )
      mWindow.close();
    pTopState->handleInput();
    pTopState->update();
    mWindow.clear( sf::Color::Black );
    pTopState->draw();
    mWindow.display();
  }
}
void Game::exit() {
  mWindow.close();
}
// Pomocnicze metody chronione:
void Game::createWindow( sf::RenderWindow &window ) {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  window.create( mVideoMode, GameConstants::title, sf::Style::Titlebar | sf::Style::Close, settings );
  window.setFramerateLimit( 60 );
}