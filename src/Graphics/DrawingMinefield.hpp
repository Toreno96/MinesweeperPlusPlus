#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameLogic/Minefield.hpp"
#include "HelperSrc/GameConstants.hpp"
#include "Game.hpp"

class DrawingMinefield {
  public:
    DrawingMinefield( Game *game, std::size_t rows, std::size_t columns );
    virtual ~DrawingMinefield();
    
    std::size_t getMouseContainingRow() const;
    std::size_t getMouseContainingColumn() const;
    
    bool containMouse();
    void update( Minefield *minefield );
    void draw( sf::RenderWindow &window ) const;
  protected:
    void updateDrawableCell( Minefield *minefield,
                             const Cell &cell, sf::Shape &correspondingDrawableCell );
    virtual void updateDrawableCellTexture( const int cellValue,
                                            sf::Shape &drawableCell ) = 0;
    virtual void fillDrawableCells() = 0;
    // Składowe:
    Game *mGame;
    std::size_t mRows, mColumns,
                mMouseContainingRow, mMouseContainingColumn;
    std::vector< std::vector< std::unique_ptr< sf::Shape > > > mDrawableCells;
};
