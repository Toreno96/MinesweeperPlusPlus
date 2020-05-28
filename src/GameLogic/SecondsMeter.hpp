#pragma once

#include <SFML/System.hpp>

class SecondsMeter {
  private:
    sf::Clock m_clock;
  public:
    SecondsMeter();
    unsigned getElapsedSeconds();
};
