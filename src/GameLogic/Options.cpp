#include "options.hpp"

Options::Options() : Options( GameMode::classic, CellsShape::classic, BoardDifficulty::easy, 9, 9, 10 ) {}
Options::Options( const GameMode gameMode, const CellsShape cellsShape, const BoardDifficulty boardDifficulty, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : mGameMode( gameMode ), mCellsShape( cellsShape ), mBoardDifficulty( boardDifficulty ), mRowsCount( rowsCount ), mColumnsCount( columnsCount ), mMinesCount( minesCount ) {}
// Gettery:
GameMode Options::getGameMode() const {
  return mGameMode;
}
CellsShape Options::getCellsShape() const {
  return mCellsShape;
}
BoardDifficulty Options::getBoardDifficulty() const {
  return mBoardDifficulty;
}
std::size_t Options::getRowsCount() const {
  return mRowsCount;
}
std::size_t Options::getColumnsCount() const {
  return mColumnsCount;
}
std::size_t Options::getMinesCount() const {
  return mMinesCount;
}
// Settery:
void Options::setGameMode( const GameMode gameMode ) {
  mGameMode = gameMode;
}
void Options::setCellsShape( const CellsShape cellsShape ) {
  mCellsShape = cellsShape;
}
void Options::setBoardDifficulty( const BoardDifficulty boardDifficulty ) {
  mBoardDifficulty = boardDifficulty;
  switch( mBoardDifficulty ) {
    case BoardDifficulty::easy:
      modifyDimensions( 9, 9, 10 );
      break;
    case BoardDifficulty::normal:
      modifyDimensions( 16, 16, 40 );
      break;
    case BoardDifficulty::hard:
      modifyDimensions( 16, 30, 99 );
      break;
    case BoardDifficulty::custom:
      break;
  }
}
void Options::setRowsCount( const std::size_t rowsCount ) {
  if( mBoardDifficulty == BoardDifficulty::custom )
    mRowsCount = rowsCount;
}
void Options::setColumnsCount( const std::size_t columnsCount ) {
  if( mBoardDifficulty == BoardDifficulty::custom )
    mColumnsCount = columnsCount;
}
void Options::setMinesCount( const std::size_t minesCount ) {
  if( mBoardDifficulty == BoardDifficulty::custom )
    mMinesCount = minesCount;
}
// Obsługa plików:
void Options::loadFromFile( const std::string filename ) {
  std::ifstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    mGameMode = BinaryFiles::read< GameMode >( file );
    mCellsShape = BinaryFiles::read< CellsShape >( file );
    mBoardDifficulty = BinaryFiles::read< BoardDifficulty >( file );
    mRowsCount = BinaryFiles::read< std::size_t >( file );
    mColumnsCount = BinaryFiles::read< std::size_t >( file );
    mMinesCount = BinaryFiles::read< std::size_t >( file );
  }
} 
void Options::saveToFile( const std::string filename ) const {
  std::ofstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    BinaryFiles::write( file, mGameMode );
    BinaryFiles::write( file, mCellsShape );
    BinaryFiles::write( file, mBoardDifficulty );
    BinaryFiles::write( file, mRowsCount );
    BinaryFiles::write( file, mColumnsCount );
    BinaryFiles::write( file, mMinesCount );
  }
}  
// Generowanie CellsVector2D, do wygodnego użycia w odpowiednim
// konstruktorze klasy Minefield:
CellsVector2D Options::generateCellsVector2D() const {
  return CellsVector2D( mRowsCount, mColumnsCount, mMinesCount );
}
// Metody pomocnicze:
void Options::modifyDimensions( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) {
  mRowsCount = rowsCount;
  mColumnsCount = columnsCount;
  mMinesCount = minesCount;
}