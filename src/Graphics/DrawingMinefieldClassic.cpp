#include "DrawingMinefieldClassic.hpp"

DrawingMinefieldClassic::DrawingMinefieldClassic( Game *game, const std::size_t rows, const std::size_t columns ) :
    DrawingMinefield( rows, columns ) {
  fillDrawableCells( game );
}
void DrawingMinefieldClassic::updateDrawableCellTexture( Game *game,
                                                         const int cellValue,
                                                         sf::Shape &correspondingDrawableCell ) {
  correspondingDrawableCell.setTexture( &( game->mClassicAndHexTextures[ cellValue ] ) );
}
void DrawingMinefieldClassic::fillDrawableCells( Game *game ) {
  const float squareSide = 20.f;
  for( size_t row = 0; row < mRows; ++row )
    for( size_t column = 0; column < mColumns; ++column ) {
      sf::RectangleShape square( sf::Vector2f( squareSide, squareSide ) );
      float squarePositionX = column * squareSide;
      float squarePositionY = row * squareSide + 3 * game->mBaseCharacterSize;
      square.setPosition( squarePositionX, squarePositionY );
      mDrawableCells[ row ].push_back( std::make_unique< sf::RectangleShape >( square ) );
    }
}