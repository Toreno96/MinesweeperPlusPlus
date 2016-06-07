#pragma once

#include <string>
#include "MinefieldData.hpp"
#include "HelperSrc/BinaryFiles.hpp"
#include "HelperSrc/GameConstants.hpp"

const std::string defaultOptionsFilename = "options.dat";

enum class CellsShape { classic, tri, hex };
enum class Difficulty { easy, normal, hard, custom };

class Options {
  public:
    Options();
    // Gettery:
    CellsShape getCellsShape() const;
    Difficulty getDifficulty() const;
    std::size_t getRowsCount() const;
    std::size_t getColumnsCount() const;
    std::size_t getMinesCount() const;
    std::size_t getMaxMinesCount() const;
    // Settery:
    void setCellsShape( const CellsShape &cellsShape );
    void setDifficulty( const Difficulty &difficulty );
    void setRowsCount( const std::size_t rowsCount );
    void setColumnsCount( const std::size_t columnsCount );
    void setMinesCount( const std::size_t minesCount );
    // Obsługa plików:
    void loadFromFile( const std::string filename = defaultOptionsFilename ); 
    void saveToFile( const std::string filename = defaultOptionsFilename ) const;  
    // Generowanie MinefieldData, do wygodnego użycia w odpowiednim
    // konstruktorze klasy Minefield:
    MinefieldData generateMinefieldData() const;
  protected:
    Options( const CellsShape cellsShape, const Difficulty Difficulty, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
    // Metody pomocnicze:
    std::size_t calculateMaxMinesCount();
    void updateMaxMinesCount();
    void correctMinesCountIfNeeded();
    void modifyDimensions( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
    // Składowe:
    CellsShape mCellsShape;
    Difficulty mDifficulty;
    std::size_t mRowsCount, mColumnsCount, mMinesCount, mMaxMinesCount;
};