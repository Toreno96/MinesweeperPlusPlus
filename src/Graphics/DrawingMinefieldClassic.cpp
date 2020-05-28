#include "DrawingMinefieldClassic.hpp"

DrawingMinefieldClassic::DrawingMinefieldClassic( Game *game, const std::size_t rows, const std::size_t columns ) :
    DrawingMinefield( game, rows, columns ) {
  fillDrawableCells();
}
void DrawingMinefieldClassic::updateDrawableCellTexture( const int cellValue,
                                                         sf::Shape &correspondingDrawableCell ) {
  correspondingDrawableCell.setTexture( &( mGame->mClassicAndHexTextures[ cellValue ] ) );
}
void DrawingMinefieldClassic::fillDrawableCells() {
  const float squareSide = 20.f;
  for( size_t row = 0; row < mRows; ++row )
    for( size_t column = 0; column < mColumns; ++column ) {
      sf::RectangleShape square( sf::Vector2f( squareSide, squareSide ) );
      float squarePositionX = 1.15 * column * squareSide + squareSide;
      float squarePositionY = 1.15 * row * squareSide + 1.5 * mGame->mBaseCharacterSize;
      square.setPosition( squarePositionX, squarePositionY );
      mDrawableCells[ row ].push_back( std::make_unique< sf::RectangleShape >( square ) );
    }
}
