#pragma once

#include "MinefieldNonclassic.hpp"

// Pole minowe, używane w trybie Tri, tj. z komórkami
// w kształcie trójkątów.
class MinefieldTri : public MinefieldNonclassic {
  public:
    MinefieldTri( const MinefieldData &cells );
    MinefieldTri( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
  protected:
    // Pomocnicze metody chronione:
    tColumnsBoundsSet findAdjacentCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const override;
};