#pragma once

#include "MinefieldNonclassic.hpp"

// Pole minowe, używane w trybie Hex, tj. z komórkami
// w kształcie sześciokątów.
class MinefieldHex : public MinefieldNonclassic {
  public:
    MinefieldHex( const CellsVector2D &cells );
    MinefieldHex( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
  protected:
    // Pomocnicze metody chronione:
    tColumnsBoundsSet findSurroundingCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const override;
};