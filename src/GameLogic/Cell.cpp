#include "Cell.hpp"

// Konstruktor:
Cell::Cell() : Cell( 0, CellState::covered ) {}
Cell::Cell( int value, CellState state ) : mValue( value ), mState( state ){}
// Gettery:
int Cell::getValue() const {
  return mValue;
}
CellState Cell::getState() const {
  return mState;
}
// Settery:
void Cell::setValue( int value ) {
  mValue = value;
}
void Cell::setState( CellState state ) {
  mState = state;
}
// Inne:
void Cell::incrementValue() {
  ++mValue;
}