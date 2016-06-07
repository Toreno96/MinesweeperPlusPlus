#include "GameStates/MenuScreen.hpp"

// Konstruktor:
Game::Game() :
    mHighScores( HighScores() ), mOptions( Options() ), mSaveManager( SaveManager() ),
    mFont( sf::Font() ), mVideoMode( sf::VideoMode( 800, 600 ) ),
    mStates( std::stack< std::unique_ptr< GameState > >() ) {
      loadDataFromFiles();
      calculateNumericalData();
      pushState( std::make_unique< MenuScreen >( this ) );
    }
// Destruktor:
Game::~Game() {
  mOptions.saveToFile();
}
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
    if( topState() == nullptr )
      mWindow.close();
    topState()->handleInput();
    topState()->update();
    mWindow.clear( sf::Color::Black );
    topState()->draw();
    mWindow.display();
  }
}
void Game::exit() {
  mWindow.close();
}
// Pomocnicze metody chronione:
void Game::loadDataFromFiles() {
  mHighScores.loadFromFile();
  mOptions.loadFromFile();
  mSaveManager.loadFromFile();
  mFont.loadFromFile( GameConstants::fontName );
}
void Game::calculateNumericalData() {
  mBaseCharacterSize = mVideoMode.width / 15;
  mBaseDistanceBetweenTextGraphics = mVideoMode.height / 24;
}
void Game::createWindow( sf::RenderWindow &window ) {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  window.create( mVideoMode, GameConstants::title, sf::Style::Titlebar | sf::Style::Close, settings );
  window.setFramerateLimit( 60 );
}