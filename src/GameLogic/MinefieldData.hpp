#pragma once

#include <vector>
#include "Cell.hpp"

class MinefieldData {
  public:
    // Konstruktory:
    MinefieldData();
    MinefieldData( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount, std::size_t uncoveredCellsCount = 0, std::size_t usedFlagsCount = 0, unsigned elapsedSeconds = 0, bool mined = false );
    // Gettery:
    std::size_t getRowsCount() const;
    std::size_t getColumnsCount() const;
    std::size_t getMinesCount() const;
    std::size_t getUncoveredCellsCount() const;
    std::size_t getUsedFlagsCount() const;
    unsigned getElapsedSeconds() const;
    Cell getCell( const std::size_t row, const std::size_t column ) const;
    bool isMined() const;
    // Settery:
    void setElapsedSeconds( unsigned elapsedSeconds );
    void setCell( const std::size_t row, const std::size_t column, const Cell &cell );
  protected:
    // Składowe:
    std::size_t mRowsCount, mColumnsCount, mMinesCount, mUncoveredCellsCount, mUsedFlagsCount;
    unsigned mElapsedSeconds;
    std::vector< std::vector< Cell > > mCells;
    bool mMined;
};
