#include "MinefieldTri.hpp"

// Konstruktor:
MinefieldTri::MinefieldTri( const CellsVector2D &cells ) : MinefieldNonclassic( 13, cells ) {}
MinefieldTri::MinefieldTri( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : MinefieldTri( CellsVector2D( rowsCount, columnsCount, minesCount ) ) {}
// Pomocnicze metody chronione:
MinefieldTri::tColumnsBoundsSet MinefieldTri::findSurroundingCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const {
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