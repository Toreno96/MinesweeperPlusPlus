#include "PreviousChoiceButton.hpp"

PreviousChoiceButton::PreviousChoiceButton() :
    PreviousChoiceButton( sf::Font() ) {}
PreviousChoiceButton::PreviousChoiceButton( const sf::Font &font, unsigned characterSize ) :
    ButtonText( "<", font, characterSize ) {}
PreviousChoiceButton::PreviousChoiceButton( std::function< void() > buttonFunction,
                                            const sf::Font &font, unsigned characterSize ) :
    PreviousChoiceButton( buttonFunction,
                          GameConstants::defaultColor, GameConstants::blue,
                          font, characterSize ) {}
PreviousChoiceButton::PreviousChoiceButton( std::function< void() > buttonFunction,
                                            const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                                            const sf::Font &font, unsigned characterSize ) :
    ButtonText( buttonFunction,
                defaultColor, mouseoverColor,
                "<", font, characterSize ) {}