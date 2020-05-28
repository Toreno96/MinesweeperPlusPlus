#include "SecondsMeter.hpp"

SecondsMeter::SecondsMeter() : m_clock( sf::Clock() ) {}
unsigned SecondsMeter::getElapsedSeconds() {
  return static_cast< unsigned >( m_clock.getElapsedTime().asSeconds() );
}
