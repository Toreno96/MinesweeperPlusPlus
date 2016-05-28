#pragma once

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "CellsVector2D.hpp"

class Minefield : public CellsVector2D {
  public:
    // Destruktor:
    virtual ~Minefield();
    // Gettery:
    int getMineValue() const;
    bool isDetonated() const;
    // Losowanie położenia min:
    void mine( boost::random::mt19937 &generator, const std::size_t excludedRow, const std::size_t excludedColumn );
    // Modyfikacja wybranych komórek pola minowego:
    void uncover( const std::size_t row, const std::size_t column );
    virtual void flag( const std::size_t row, const std::size_t column );
    void unflag( const std::size_t row, const std::size_t column );
  protected:
    // Chronione typedefy:
    typedef void ( Minefield:: *tCellModifyingMemberFunction )( const std::size_t row, const std::size_t column );
    // Konstruktor:
    Minefield( const int mineValue, const CellsVector2D &cells );
    // Pomocniczne metody chronione:
    std::size_t findLowerCoordinate( const std::size_t coordinate, const std::size_t theLowestPossibleCoordinate = 0, const std::size_t howMuchLower = 1 ) const;
    std::size_t findGreaterCoordinate( const std::size_t coordinate, const std::size_t theGreatestPossibleCoordinate, const std::size_t howMuchGreater = 1 ) const;
    virtual void modifyAdjacentCells( tCellModifyingMemberFunction pCellModifyingMemberFunction, const std::size_t centerRow, const std::size_t centerColumn ) = 0;
    void incrementSingleCell( const std::size_t row, const std::size_t column );
    void incrementAdjacentCells( const std::size_t centerRow, const std::size_t centerColumn );
    void uncoverAdjacentCells( const std::size_t centerRow, const std::size_t centerColumn );
    // Składowe:
    // Jeśli wartość danej komórki jest równa "wartości miny", oznacza
    // to, że ta komórka jest zaminowana. 
    // Jest to inaczej x, wspomniane w komentarzu zawartym w pliku nagłówkowym
    // "Cell.hpp".
    int mMineValue;
    bool mDetonated;
};