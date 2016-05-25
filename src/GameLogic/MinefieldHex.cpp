#include "MinefieldHex.hpp"

// Konstruktor:
MinefieldHex::MinefieldHex( const CellsVector2D &cells ) : MinefieldNonclassic( 7, cells ) {}
MinefieldHex::MinefieldHex( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : MinefieldHex( CellsVector2D( rowsCount, columnsCount, minesCount ) ) {}
// Pomocnicze metody chronione:
MinefieldHex::tColumnsBoundsSet MinefieldHex::findSurroundingCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const { // TO-DO
  std::size_t minColumnTop, maxColumnTop,
              minColumnMiddle = findLowerCoordinate( centerColumn, 0, 2 ),
              maxColumnMiddle = findGreaterCoordinate( centerColumn, mRowsCount - 1, 2 ),
              minColumnBottom, maxColumnBottom;
  if( centerRow % 2 == centerColumn % 2 ) {
    minColumnTop = findLowerCoordinate( centerColumn );
    maxColumnTop = findGreaterCoordinate( centerColumn, mRowsCount - 1 );
    minColumnBottom = minColumnMiddle;
    maxColumnBottom = maxColumnMiddle;
  }
  else {
    minColumnTop = minColumnMiddle;
    maxColumnTop = maxColumnMiddle;
    minColumnBottom = findLowerCoordinate( centerColumn );
    maxColumnBottom = findGreaterCoordinate( centerColumn, mRowsCount - 1 );
  }
  return { { { { minColumnTop, maxColumnTop } },
             { { minColumnMiddle, maxColumnMiddle } },
             { { minColumnBottom, maxColumnBottom } } } };
}