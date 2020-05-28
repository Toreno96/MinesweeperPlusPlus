#pragma once

#include "DrawingMinefield.hpp"

class DrawingMinefieldClassic : public DrawingMinefield {
  public:
    DrawingMinefieldClassic( Game *game, const std::size_t rows, const std::size_t columns );
  protected:
    void updateDrawableCellTexture( const int cellValue,
                                    sf::Shape &correspondingDrawableCell ) override;
    void fillDrawableCells() override;
};
