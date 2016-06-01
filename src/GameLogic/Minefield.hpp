#pragma once

#include <functional>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "MinefieldData.hpp"

class Minefield : public MinefieldData {
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
    void flag( const std::size_t row, const std::size_t column );
    void unflag( const std::size_t row, const std::size_t column );
  protected:
    // Chronione typedefy:
    typedef std::function< void( const std::size_t, const std::size_t ) > tCellModifyingMemberFunction;
    // Konstruktor:
    Minefield( const int mineValue, const MinefieldData &cells );
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