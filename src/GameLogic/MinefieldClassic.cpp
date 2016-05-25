#include "MinefieldClassic.hpp"

// Konstruktor:
MinefieldClassic::MinefieldClassic( const CellsVector2D &cells ) : Minefield( 9, cells ) {}
MinefieldClassic::MinefieldClassic( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : MinefieldClassic( CellsVector2D( rowsCount, columnsCount, minesCount ) ) {}
// Pomocnicze metody chronione:
void MinefieldClassic::modifySurroundingCells( tMemberFunction pModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) {      
  std::size_t maxRow = findGreaterCoordinate( centerRow, mRowsCount - 1 ),
              maxColumn = findGreaterCoordinate( centerColumn, mColumnsCount - 1 ),
              row = findLowerCoordinate( centerRow );
  while( row <= maxRow ) {
    std::size_t column = findLowerCoordinate( centerColumn );
    while( column <= maxColumn ) {
      // if( ( row == centerRow ) && ( column == centerColumn ) ) continue;
      ( this->*pModifyingMemberFunction )( row, column );
      ++column;
    }
    ++row;
  }
}