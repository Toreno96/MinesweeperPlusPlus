#pragma once

#include <array>
#include "Minefield.hpp"

// Abstrakcyjna klasa bazowa, po której dziedziczyć będą
// pola minowe dla trybów  innych niż Classic.
class MinefieldNonclassic : public Minefield {
  protected:
    // Chronione typedefy:
    typedef std::array< std::size_t, 2 > tCoordinateBounds;
    typedef std::array< tCoordinateBounds, 3 > tColumnsBoundsSet;
    // Konstruktory:
    MinefieldNonclassic( const int mineValue, const MinefieldData &cells );
    MinefieldNonclassic( const int mineValue, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
    // Pomocnicze metody chronione:
    tCoordinateBounds findAdjacentCellsRowsBounds( const std::size_t centerRow ) const;
    virtual tColumnsBoundsSet findAdjacentCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const = 0;
    void modifyRow( tCellModifyingMemberFunction pModifyingMemberFunction, const std::size_t row, const std::size_t minColumn, const std::size_t maxColumn );
    void modifyAdjacentCells( tCellModifyingMemberFunction pModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) override;
};
