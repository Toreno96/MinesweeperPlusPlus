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
    MinefieldNonclassic( const int mineValue, const CellsVector2D &cells );
    MinefieldNonclassic( const int mineValue, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
    // Pomocnicze metody chronione:
    tCoordinateBounds findEnclosingCellsRowsBounds( const std::size_t centerRow ) const;
    virtual tColumnsBoundsSet findEnclosingCellsColumnsBounds( const std::size_t centerRow, const std::size_t centerColumn ) const = 0;
    void modifyRow( tMemberFunction pModifyingMemberFunction, const std::size_t row, const std::size_t minColumn, const std::size_t maxColumn );
    void doToEnclosingCells( tMemberFunction pModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) override;
};