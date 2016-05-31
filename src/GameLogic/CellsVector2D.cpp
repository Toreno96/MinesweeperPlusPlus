#include "CellsVector2D.hpp"

// Konstruktory:
CellsVector2D::CellsVector2D() : CellsVector2D( 0, 0, 0 ) {}
CellsVector2D::CellsVector2D( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount, std::size_t uncoveredCellsCount, std::size_t usedFlags, bool mined ) : mRowsCount( rowsCount ), mColumnsCount( columnsCount ), mMinesCount( minesCount ), mUncoveredCellsCount( uncoveredCellsCount ), mUsedFlags( usedFlags ), mCells( std::vector< std::vector< Cell > >( rowsCount ) ), mMined( mined ) {
  for( auto &row : mCells )
    row = std::vector< Cell >( columnsCount );
}
// Gettery:
std::size_t CellsVector2D::getRowsCount() const {
  return mRowsCount;
}
std::size_t CellsVector2D::getColumnsCount() const {
  return mColumnsCount;
}
std::size_t CellsVector2D::getMinesCount() const {
  return mMinesCount;
}
std::size_t CellsVector2D::getUncoveredCellsCount() const {
  return mUncoveredCellsCount;
}
std::size_t CellsVector2D::getUsedFlags() const {
  return mUsedFlags;
}
Cell &CellsVector2D::getCell( const std::size_t row, const std::size_t column ) {
  return mCells[ row ][ column ];
}
const Cell &CellsVector2D::getCell( const std::size_t row, const std::size_t column ) const {
  return mCells[ row ][ column ];
}
bool CellsVector2D::isMined() const {
  return mMined;
}