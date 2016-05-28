#include "Minefield.hpp"

// Konstruktor:
Minefield::Minefield( const int mineValue, const CellsVector2D &cells ) : CellsVector2D( cells ), mMineValue( mineValue ), mDetonated( false ) {}
// Destruktor:
Minefield::~Minefield() {}
// Gettery:
int Minefield::getMineValue() const {
  return mMineValue;
}
bool Minefield::isDetonated() const {
  return mDetonated;
}
// Losowanie położenia min:
void Minefield::mine( boost::random::mt19937 &generator, const std::size_t excludedRow, const std::size_t excludedColumn ) {
  boost::random::uniform_int_distribution< std::size_t > rowsDistribution( 0, mRowsCount - 1 );
  boost::random::uniform_int_distribution< std::size_t > columnsDistribution( 0, mColumnsCount - 1 );
  for( std::size_t minesToDispose = mMinesCount; minesToDispose > 0; ) {
    std::size_t randomRow = rowsDistribution( generator ),
                randomColumn = columnsDistribution( generator );
    if( ( randomRow != excludedRow ) && ( randomColumn != excludedColumn ) ) {
      Cell &randomCell = mCells[ randomRow ][ randomColumn ]; 
      if( randomCell.getValue() != mMineValue ) {
        randomCell.setValue( mMineValue );
        incrementAdjacentCells( randomRow, randomColumn );
        --minesToDispose;
      }
    }
  }
  mMined = true;
}
// Modyfikacja wybranych komórek pola minowego:
void Minefield::uncover( const std::size_t row, const std::size_t column ) {
  Cell &chosenCell = mCells[ row ][ column ]; 
  if( chosenCell.getState() == CellState::covered ) {
    chosenCell.setState( CellState::uncovered );
    if( chosenCell.getValue() == 0 )
      uncoverAdjacentCells( row, column );
    else if( chosenCell.getValue() == mMineValue )
      mDetonated = true;
  }
}
void Minefield::flag( const std::size_t row, const std::size_t column ) {
  Cell &chosenCell = mCells[ row ][ column ]; 
  if( ( mUsedFlags < mMinesCount ) && ( chosenCell.getState() == CellState::covered ) ) {
    chosenCell.setState( CellState::flagged );
    ++mUsedFlags;
  }
}
void Minefield::unflag( const std::size_t row, const std::size_t column ) {
  Cell &chosenCell = mCells[ row ][ column ]; 
  if( chosenCell.getState() == CellState::flagged ) {
    chosenCell.setState( CellState::covered );
    --mUsedFlags;
  }
}
// Pomocniczne metody chronione:
std::size_t Minefield::findLowerCoordinate( const std::size_t coordinate, const std::size_t theLowestPossibleCoordinate, const std::size_t howMuchLower ) const {
  if( coordinate >= theLowestPossibleCoordinate + howMuchLower )
    return coordinate - howMuchLower;
  else
    return theLowestPossibleCoordinate;
}
std::size_t Minefield::findGreaterCoordinate( const std::size_t coordinate, const std::size_t theGreatestPossibleCoordinate, const std::size_t howMuchGreater ) const {
  if( coordinate <= theGreatestPossibleCoordinate - howMuchGreater )
    return coordinate + howMuchGreater;
  else
    return theGreatestPossibleCoordinate;
}
void Minefield::incrementSingleCell( const std::size_t row, const std::size_t column ) {
  Cell &currentCell = mCells[ row ][ column ];
  if( currentCell.getValue() != mMineValue )
    currentCell.incrementValue();
}
void Minefield::incrementAdjacentCells( const std::size_t centerRow, const std::size_t centerColumn ) {
  modifyAdjacentCells( &Minefield::incrementSingleCell, centerRow, centerColumn );
}
void Minefield::uncoverAdjacentCells( const std::size_t centerRow, const std::size_t centerColumn ) {
  modifyAdjacentCells( &Minefield::uncover, centerRow, centerColumn );
}