#include "MinefieldHex.hpp"

// Konstruktor:
MinefieldHex::MinefieldHex( const CellsVector2D &cells ) : MinefieldNonclassic( 7, cells ) {}
MinefieldHex::MinefieldHex( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : MinefieldHex( CellsVector2D( rowsCount, columnsCount, minesCount ) ) {}
// Pomocnicze metody chronione:
MinefieldHex::tColumnsBoundsSet MinefieldHex::findEnclosingCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const {
  std::size_t minColumnTop, maxColumnTop,
              minColumnMiddle = findLowerCoordinate( centerColumn ),
              maxColumnMiddle = findGreaterCoordinate( centerColumn, mColumnsCount - 1 ),
              &minColumnBottom = minColumnTop,
              &maxColumnBottom = maxColumnTop;
  if( centerRow % 2 == 0 ) {
    minColumnTop = findLowerCoordinate( centerColumn );
    maxColumnTop = centerColumn;
  }
  else {
    minColumnTop = centerColumn;
    maxColumnTop = findGreaterCoordinate( centerColumn, mColumnsCount - 1 );
  }
  return { { { { minColumnTop, maxColumnTop } },
             { { minColumnMiddle, maxColumnMiddle } },
             { { minColumnBottom, maxColumnBottom } } } };
}