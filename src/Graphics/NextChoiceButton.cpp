#include "NextChoiceButton.hpp"

NextChoiceButton::NextChoiceButton() :
    NextChoiceButton( std::function< void() >(),
                      sf::Font() ) {}
NextChoiceButton::NextChoiceButton( std::function< void() > buttonFunction,
                                    const sf::Font &font, unsigned characterSize ) :
    NextChoiceButton( buttonFunction,
                      GameConstants::defaultColor, GameConstants::blue,
                      font, characterSize ) {}
NextChoiceButton::NextChoiceButton( std::function< void() > buttonFunction,
                                    const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                                    const sf::Font &font, unsigned characterSize ) :
    ButtonText( buttonFunction,
                defaultColor, mouseoverColor,
                ">", font, characterSize ) {}