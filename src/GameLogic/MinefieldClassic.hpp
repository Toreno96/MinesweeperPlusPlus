#pragma once

#include "Minefield.hpp"

// Pole minowe, używane w trybie Classic, tj. z komórkami
// w kształcie kwadratów.
class MinefieldClassic : public Minefield {
  public:
    // Konstruktor:
    MinefieldClassic( const CellsVector2D &cells );
    MinefieldClassic( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
  protected:
    // Pomocnicze metody chronione:
    void modifySurroundingCells( tMemberFunction pModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) override;
};