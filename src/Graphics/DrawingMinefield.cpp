#include "DrawingMinefield.hpp"

DrawingMinefield::DrawingMinefield( Game *game, std::size_t rows, std::size_t columns ) :
    mGame( game ),
    mRows( rows ), mColumns( columns ),
    mMouseContainingRow( std::size_t() ), mMouseContainingColumn( std::size_t() ),
    mDrawableCells( std::vector< std::vector< std::unique_ptr< sf::Shape > > >( rows ) ) {}
DrawingMinefield::~DrawingMinefield() {}

std::size_t DrawingMinefield::getMouseContainingRow() const {
  return mMouseContainingRow;
}
std::size_t DrawingMinefield::getMouseContainingColumn() const {
  return mMouseContainingColumn;
}

bool DrawingMinefield::containMouse() {
  const sf::Vector2i mousePosition = sf::Mouse::getPosition( mGame->mWindow );
  for( std::size_t row = 0; row < mRows; ++row )
    for( std::size_t column = 0; column < mColumns; ++column ) {
      auto &currentCell = mDrawableCells[ row ][ column ];
      if( currentCell->getGlobalBounds().contains( mousePosition.x,
                                                   mousePosition.y ) ) {
        mMouseContainingRow = row;
        mMouseContainingColumn = column;
        return true;
      }
    }
  return false;
}
void DrawingMinefield::update( Minefield *minefield ) {
  for( std::size_t row = 0; row < mRows; ++row )
    for( std::size_t column = 0; column < mColumns; ++column ) {
      const Cell currentCell = minefield->getCell( row, column );
      sf::Shape &currentDrawableCell = *( mDrawableCells[ row ][ column ].get() ); 
      updateDrawableCell( minefield, currentCell, currentDrawableCell );
      }
}
void DrawingMinefield::draw( sf::RenderWindow &window ) const {
  for( const auto &row : mDrawableCells )
    for( const auto &uniquePtrToCell : row )
      window.draw( *( uniquePtrToCell.get() ) );
}

void DrawingMinefield::updateDrawableCell( Minefield *minefield,
                                           const Cell &cell, sf::Shape &correspondingDrawableCell ) {
  switch( cell.getState() ) {
    case CellState::covered:
      correspondingDrawableCell.setFillColor( GameConstants::blue );
      break;
    case CellState::flagged:
      correspondingDrawableCell.setFillColor( GameConstants::red );
      break;
    case CellState::uncovered: {
      correspondingDrawableCell.setFillColor( GameConstants::lightBlue );
      auto cellValue = cell.getValue();
      if( ( cellValue > 0 ) &&
          ( cellValue < minefield->getMineValue() ) ) {
        updateDrawableCellTexture( cellValue, correspondingDrawableCell );
      }
      break;
    }
  }
}
