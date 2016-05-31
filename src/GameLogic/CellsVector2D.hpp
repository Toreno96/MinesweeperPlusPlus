#pragma once

#include <vector>
#include "Cell.hpp"

class CellsVector2D {
  public:
    // Konstruktory:
    CellsVector2D();
    CellsVector2D( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount, std::size_t uncoveredCellsCount = 0, std::size_t usedFlags = 0, bool mined = false );
    // Gettery:
    std::size_t getRowsCount() const;
    std::size_t getColumnsCount() const;
    std::size_t getMinesCount() const;
    std::size_t getUncoveredCellsCount() const;
    std::size_t getUsedFlags() const;
    Cell &getCell( const std::size_t row, const std::size_t column );
    const Cell &getCell( const std::size_t row, const std::size_t column ) const;
    bool isMined() const;
  protected:
    // Składowe:
    std::size_t mRowsCount, mColumnsCount, mMinesCount, mUncoveredCellsCount, mUsedFlags;
    std::vector< std::vector< Cell > > mCells;
    bool mMined;
};