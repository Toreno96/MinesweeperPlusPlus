#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameLogic/Minefield.hpp"
#include "HelperSrc/GameConstants.hpp"
#include "Game.hpp"

class DrawingMinefield {
  public:
    DrawingMinefield( std::size_t rows, std::size_t columns );
    virtual ~DrawingMinefield();
    
    std::size_t getMouseContainingRow() const;
    std::size_t getMouseContainingColumn() const;
    
    bool contain( const sf::Vector2i &mousePosition );
    void update( Game *game, Minefield *minefield );
    void draw( sf::RenderWindow &window ) const;
  protected:
    void updateDrawableCell( Game *game,
                             Minefield *minefield,
                             const Cell &cell, sf::Shape &correspondingDrawableCell );
    virtual void updateDrawableCellTexture( Game *game,
                                            const int cellValue,
                                            sf::Shape &drawableCell ) = 0;
    virtual void fillDrawableCells( Game *game ) = 0;
    // Składowe:
    std::size_t mRows, mColumns,
                mMouseContainingRow, mMouseContainingColumn;
    std::vector< std::vector< std::unique_ptr< sf::Shape > > > mDrawableCells;
};