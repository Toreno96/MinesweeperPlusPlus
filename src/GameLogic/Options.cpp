#include "options.hpp"

Options::Options() : Options( CellsShape::classic, Difficulty::easy, 9, 9, 10 ) {}
Options::Options( const CellsShape cellsShape, const Difficulty Difficulty, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : mCellsShape( cellsShape ), mDifficulty( Difficulty ), mRowsCount( rowsCount ), mColumnsCount( columnsCount ), mMinesCount( minesCount ), mMaxMinesCount( calculateMaxMinesCount() ) {}
// Gettery:
CellsShape Options::getCellsShape() const {
  return mCellsShape;
}
Difficulty Options::getDifficulty() const {
  return mDifficulty;
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
std::size_t Options::getMaxMinesCount() const {
  return mMaxMinesCount;
}
// Settery:
void Options::setCellsShape( const CellsShape &cellsShape ) {
  mCellsShape = cellsShape;
}
void Options::setDifficulty( const Difficulty &difficulty ) {
  mDifficulty = difficulty;
  switch( mDifficulty ) {
    case Difficulty::easy:
      modifyDimensions( GameConstants::minRowsCount,
                        GameConstants::minColumnsCount,
                        GameConstants::minMinesCount );
      break;
    case Difficulty::normal:
      modifyDimensions( 16, 16, 40 );
      break;
    case Difficulty::hard:
      modifyDimensions( 16, 30, 99 );
      break;
    case Difficulty::custom:
      break;
  }
}
void Options::setRowsCount( const std::size_t rowsCount ) {
  if( mDifficulty == Difficulty::custom
      && rowsCount >= GameConstants::minRowsCount
      && rowsCount <= GameConstants::maxRowsCount ) {
    mRowsCount = rowsCount;
    updateMaxMinesCount();
    correctMinesCountIfNecessary();
  }
}
void Options::setColumnsCount( const std::size_t columnsCount ) {
  if( mDifficulty == Difficulty::custom
      && columnsCount >= GameConstants::minColumnsCount
      && columnsCount <= GameConstants::maxColumnsCount ) {
    mColumnsCount = columnsCount;
    updateMaxMinesCount();
    correctMinesCountIfNecessary();
  }
}
void Options::setMinesCount( const std::size_t minesCount ) {
  if( mDifficulty == Difficulty::custom
      && minesCount >= GameConstants::minMinesCount
      && minesCount <= mMaxMinesCount ) {
    mMinesCount = minesCount;
  }
}
// Obsługa plików:
void Options::loadFromFile( const std::string filename ) {
  std::ifstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    mCellsShape = BinaryFiles::read< CellsShape >( file );
    mDifficulty = BinaryFiles::read< Difficulty >( file );
    mRowsCount = BinaryFiles::read< std::size_t >( file );
    mColumnsCount = BinaryFiles::read< std::size_t >( file );
    mMinesCount = BinaryFiles::read< std::size_t >( file );
  }
} 
void Options::saveToFile( const std::string filename ) const {
  std::ofstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    BinaryFiles::write( file, mCellsShape );
    BinaryFiles::write( file, mDifficulty );
    BinaryFiles::write( file, mRowsCount );
    BinaryFiles::write( file, mColumnsCount );
    BinaryFiles::write( file, mMinesCount );
  }
}  
// Generowanie MinefieldData, do wygodnego użycia w odpowiednim
// konstruktorze klasy Minefield:
MinefieldData Options::generateMinefieldData() const {
  return MinefieldData( mRowsCount, mColumnsCount, mMinesCount );
}
// Metody pomocnicze:
std::size_t Options::calculateMaxMinesCount() {
  return mRowsCount * mColumnsCount / 2;
}
void Options::updateMaxMinesCount() {
  mMaxMinesCount = calculateMaxMinesCount();
}
void Options::correctMinesCountIfNecessary() {
  if( mMinesCount > mMaxMinesCount )
    mMinesCount = mMaxMinesCount;
}
void Options::modifyDimensions( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) {
  mRowsCount = rowsCount;
  mColumnsCount = columnsCount;
  mMinesCount = minesCount;
}