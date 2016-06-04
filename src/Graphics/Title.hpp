#pragma once

#include "ExtendedText.hpp"

// Klasa, która domyślnie przyjmuje:
// - odpowiednio powiększoną względem pozostałego tekstu czcionkę,
// - horyzontalne wycentrowanie,
// - odpowiednią pozycję wertykalną.
class Title : public ExtendedText {
  public:
    Title();
    // baseCharacterSize, jest to bazowy rozmiar czcionki dla większości
    // pozostałego tekstu w grze. Na jego podstawie klasa Title dobierze
    // dla siebie rozmiar odpowiednio większy.
    Title( const sf::VideoMode &videoMode, const sf::String &string, const sf::Font &font, unsigned baseCharacterSize = 30 );
};