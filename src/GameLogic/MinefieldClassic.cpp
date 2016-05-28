#include "MinefieldClassic.hpp"

// Konstruktor:
MinefieldClassic::MinefieldClassic( const CellsVector2D &cells ) : Minefield( 9, cells ) {}
MinefieldClassic::MinefieldClassic( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : MinefieldClassic( CellsVector2D( rowsCount, columnsCount, minesCount ) ) {}
// Pomocnicze metody chronione:
void MinefieldClassic::modifyAdjacentCells( tCellModifyingMemberFunction pModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) {      
  std::size_t maxRow = findGreaterCoordinate( centerRow, mRowsCount - 1 ),
              maxColumn = findGreaterCoordinate( centerColumn, mColumnsCount - 1 );
  for( std::size_t row = findLowerCoordinate( centerRow ); row <= maxRow; ++row )
    for( std::size_t column = findLowerCoordinate( centerColumn ); column <= maxColumn; ++column )
      pModifyingMemberFunction( row, column );
}