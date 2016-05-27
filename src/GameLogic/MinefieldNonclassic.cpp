#include "MinefieldNonclassic.hpp"

// Konstruktory:
MinefieldNonclassic::MinefieldNonclassic( const int mineValue, const CellsVector2D &cells ) : Minefield( mineValue, cells ) {}
MinefieldNonclassic::MinefieldNonclassic( const int mineValue, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount ) : MinefieldNonclassic( mineValue, CellsVector2D( rowsCount, columnsCount, minesCount ) ) {}
// Pomocnicze metody chronione:
MinefieldNonclassic::tCoordinateBounds MinefieldNonclassic::findEnclosingCellsRowsBounds( const std::size_t centerRow ) const {
  std::size_t minRow = findLowerCoordinate( centerRow ),
              maxRow = findGreaterCoordinate( centerRow, mRowsCount - 1 );
  return { { minRow, maxRow } };
}
void MinefieldNonclassic::modifyRow( tMemberFunction pModifyingMemberFunction, const std::size_t row, const std::size_t minColumn, const std::size_t maxColumn ) {
  for( std::size_t column = minColumn; column <= maxColumn; ++column )
    ( this->*pModifyingMemberFunction )( row, column );
}
void MinefieldNonclassic::doToEnclosingCells( tMemberFunction pModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) {
  auto rowsBounds = findEnclosingCellsRowsBounds( centerRow );
  auto columnsBoundsSet = findEnclosingCellsColumnsBounds( centerRow, centerColumn );
  const std::size_t indexOfMinCoordinate = 0,
                    indexOfMaxCoordinate = 1;
  
  // Modyfikacja górnego rzędu sąsiadujących komórek:
  if( rowsBounds[ indexOfMinCoordinate ] < centerRow )
    modifyRow( pModifyingMemberFunction, rowsBounds[ indexOfMinCoordinate ],
               columnsBoundsSet[ 0 ][ indexOfMinCoordinate ],
               columnsBoundsSet[ 0 ][ indexOfMaxCoordinate ] );
  // Modyfikacja środkowego rzędu sąsiadujących komórek:
  modifyRow( pModifyingMemberFunction, centerRow,
              columnsBoundsSet[ 1 ][ indexOfMinCoordinate ],
              columnsBoundsSet[ 1 ][ indexOfMaxCoordinate ] );
  // Modyfikacja dolnego rzędu sąsiadujących komórek:
  if( rowsBounds[ indexOfMaxCoordinate ] > centerRow )
    modifyRow( pModifyingMemberFunction, rowsBounds[ indexOfMaxCoordinate ],
               columnsBoundsSet[ 2 ][ indexOfMinCoordinate ],
               columnsBoundsSet[ 2 ][ indexOfMaxCoordinate ] );
    
}