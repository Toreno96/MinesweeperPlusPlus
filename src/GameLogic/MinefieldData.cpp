#include "MinefieldData.hpp"

// Konstruktory:
MinefieldData::MinefieldData() : MinefieldData( 0, 0, 0 ) {}
MinefieldData::MinefieldData( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount, std::size_t uncoveredCellsCount, std::size_t usedFlagsCount, unsigned elapsedSeconds, bool mined ) : mRowsCount( rowsCount ), mColumnsCount( columnsCount ), mMinesCount( minesCount ), mUncoveredCellsCount( uncoveredCellsCount ), mUsedFlagsCount( usedFlagsCount ), mElapsedSeconds( elapsedSeconds ), mCells( std::vector< std::vector< Cell > >( rowsCount ) ), mMined( mined ) {
  for( auto &row : mCells )
    row = std::vector< Cell >( columnsCount );
}
// Gettery:
std::size_t MinefieldData::getRowsCount() const {
  return mRowsCount;
}
std::size_t MinefieldData::getColumnsCount() const {
  return mColumnsCount;
}
std::size_t MinefieldData::getMinesCount() const {
  return mMinesCount;
}
std::size_t MinefieldData::getUncoveredCellsCount() const {
  return mUncoveredCellsCount;
}
std::size_t MinefieldData::getUsedFlagsCount() const {
  return mUsedFlagsCount;
}
unsigned MinefieldData::getElapsedSeconds() const {
  return mElapsedSeconds;
}
Cell MinefieldData::getCell( const std::size_t row, const std::size_t column ) const {
  return mCells[ row ][ column ];
}
bool MinefieldData::isMined() const {
  return mMined;
}
// Settery:
void MinefieldData::setElapsedSeconds( unsigned elapsedSeconds ) {
  mElapsedSeconds = elapsedSeconds;
}
void MinefieldData::setCell( const std::size_t row, const std::size_t column, const Cell &cell ) {
  mCells[ row ][ column ] = cell;
}