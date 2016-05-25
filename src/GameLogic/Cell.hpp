#pragma once

enum class CellState { covered, uncovered, flagged };

class Cell {
  public:
    // Konstruktor:
    Cell();
    Cell( int value, CellState state );
    // Gettery:
    int getValue() const;
    CellState getState() const;
    // Settery:
    void setValue( int value );
    void setState( CellState state );
    // Inne:
    void incrementValue();
  private:
    // Wartość wskazująca na to, ile min sąsiaduje z daną komórką, albo że
    // mina się w niej znajduje. W związku z tym, ta składowa powinna przyjąć
    // wartość od 0 do x, gdzie x to mina.
    // Dla trybów hex, classic oraz tri, x jest równe kolejno 7, 9, 13. 
    int mValue;
    CellState mState;
};