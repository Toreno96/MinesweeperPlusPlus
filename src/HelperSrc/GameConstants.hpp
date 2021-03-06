#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace GameConstants {
  
  const std::string title = "Minesweeper++";
  const std::string fontName = "arial.ttf";
  
  // Colors RGB codes from http://www.rapidtables.com/web/color/RGB_Color.htm
  const sf::Color defaultColor = sf::Color(255, 255, 255);
  const sf::Color deactivatedButton = sf::Color	( 192, 192, 192 ); // Silver
  const sf::Color blue = sf::Color( 30, 144, 255 ); // Dodger Blue
  const sf::Color lightBlue = sf::Color( 175, 238, 238 ); // Pale Turquoise
  const sf::Color red = sf::Color( 235, 0, 0 ); // Custom Red
  
  const std::size_t minRowsCount = 9;
  const std::size_t minColumnsCount = 9;
  const std::size_t minMinesCount = 10;
  const std::size_t maxRowsCount = 22;
  const std::size_t maxColumnsCount = 33;
  
} // namespace GameConstants
