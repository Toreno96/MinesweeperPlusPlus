#pragma once

#include <string>
#include "CellsVector2D.hpp"
#include "HelperFunctions/BinaryFiles.hpp"

const std::string defaultOptionsFilename = "options.dat";

enum class GameMode { classic, automatic };
enum class CellsShape { classic, tri, hex };
enum class BoardDifficulty { easy, normal, hard, custom };

class Options {
  public:
    Options();
    // Gettery:
    GameMode getGameMode() const;
    CellsShape getCellsShape() const;
    BoardDifficulty getBoardDifficulty() const;
    std::size_t getRowsCount() const;
    std::size_t getColumnsCount() const;
    std::size_t getMinesCount() const;
    // Settery:
    void setGameMode( const GameMode gameMode );
    void setCellsShape( const CellsShape cellsShape );
    void setBoardDifficulty( const BoardDifficulty boardDifficulty );
    void setRowsCount( const std::size_t rowsCount );
    void setColumnsCount( const std::size_t columnsCount );
    void setMinesCount( const std::size_t minesCount );
    // Obsługa plików:
    void loadFromFile( const std::string filename = defaultOptionsFilename ); 
    void saveToFile( const std::string filename = defaultOptionsFilename ) const;  
    // Generowanie CellsVector2D, do wygodnego użycia w odpowiednim
    // konstruktorze klasy Minefield:
    CellsVector2D generateCellsVector2D() const;
  protected:
    Options( const GameMode gameMode, const CellsShape cellsShape, const BoardDifficulty boardDifficulty, const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
    // Metody pomocnicze:
    void modifyDimensions( const std::size_t rowsCount, const std::size_t columnsCount, const std::size_t minesCount );
    // Składowe:
    GameMode mGameMode;
    CellsShape mCellsShape;
    BoardDifficulty mBoardDifficulty;
    std::size_t mRowsCount, mColumnsCount, mMinesCount;
};