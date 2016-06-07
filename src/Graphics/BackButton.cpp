#include "BackButton.hpp"

BackButton::BackButton( Game* game,
                        const sf::Font &font, unsigned characterSize ) :
    BackButton( game,
                GameConstants::defaultColor, GameConstants::blue,
                font, characterSize ) {}
BackButton::BackButton( Game* game,
                        const sf::Color &defaultColor, const sf::Color &mouseoverColor,
                        const sf::Font &font, unsigned characterSize ) :
    ButtonText( [ game ](){ game->popState(); },
                defaultColor, mouseoverColor,
                "Back", font, characterSize ) {
  positionThisButton( game );              
}

void BackButton::positionThisButton( Game* game ) {
  auto characterSize = this->getCharacterSize();
  this->setPosition( 0.5 * characterSize, game->mVideoMode.height - 1.5 * characterSize );
}