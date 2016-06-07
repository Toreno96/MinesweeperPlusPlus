#include "DrawingMinefield.hpp"

DrawingMinefield::DrawingMinefield( std::size_t rows, std::size_t columns ) :
    mRows( rows ), mColumns( columns ),
    mClickedRow( std::size_t() ), mClickedColumn( std::size_t() ),
    mDrawableCells( std::vector< std::vector< std::unique_ptr< sf::Shape > > >( rows ) ) {}
DrawingMinefield::~DrawingMinefield() {}

std::size_t DrawingMinefield::getClickedRow() const {
  return mClickedRow;
}
std::size_t DrawingMinefield::getClickedColumn() const {
  return mClickedColumn;
}

bool DrawingMinefield::isClicked( const sf::Vector2i &mousePosition ) {
  for( std::size_t row = 0; row < mRows; ++row )
    for( std::size_t column = 0; column < mColumns; ++column ) {
      auto &currentCell = mDrawableCells[ row ][ column ];
      if( currentCell->getGlobalBounds().contains( mousePosition.x,
                                                  mousePosition.y ) ) {
        mClickedRow = row;
        mClickedColumn = column;
        return true;
      }
    }
  return false;
}
void DrawingMinefield::update( Game *game, Minefield *minefield ) {
  for( std::size_t row = 0; row < mRows; ++row )
    for( std::size_t column = 0; column < mColumns; ++column ) {
      const Cell currentCell = minefield->getCell( row, column );
      sf::Shape &currentDrawableCell = *( mDrawableCells[ row ][ column ].get() ); 
      updateDrawableCell( game, minefield, currentCell, currentDrawableCell );
      }
}
void DrawingMinefield::draw( sf::RenderWindow &window ) const {
  for( const auto &row : mDrawableCells )
    for( const auto &uniquePtrToCell : row )
      window.draw( *( uniquePtrToCell.get() ) );
}

void DrawingMinefield::updateDrawableCell( Game *game,
                                           Minefield *minefield,
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
        updateDrawableCellTexture( game, cellValue, correspondingDrawableCell );
      }
      break;
    }
  }
}