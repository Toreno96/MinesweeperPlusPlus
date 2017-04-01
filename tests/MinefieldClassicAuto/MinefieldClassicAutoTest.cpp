#include <iostream>
#include <boost/random/random_device.hpp>
#include "MinefieldClassicAuto.hpp"

void print_minefield( MinefieldClassicAuto &minefield ) {
  for( std::size_t row = 0; row < minefield.getRowsCount(); ++row ) {
    for( std::size_t column = 0; column < minefield.getColumnsCount(); ++column ) {
      std::cout << ' ';
      switch( minefield.getCell( row, column ).getState() ) {
        case CellState::covered: 
          std::cout << '?';
          break;
        case CellState::flagged:
          std::cout << 'F';
          break;
        case CellState::uncovered:
          if( minefield.getCell( row, column ).getValue() == minefield.getMineValue() )
            std::cout << 'x';
          else
            std::cout << minefield.getCell( row, column ).getValue();
          break;
      }
    }
    std::cout << '\n';
  }
}

int main() {
    boost::random::random_device random_device;
    boost::random::mt19937 generator( random_device() );
    
    std::size_t rowsCount, columnsCount, minesCount;
    std::cout << "Enter rowsCount, columnsCount and minesCount:\n";
    std::cin >> rowsCount >> columnsCount >> minesCount;
    
    MinefieldClassicAuto minefield( rowsCount, columnsCount, minesCount );
    minefield.mine( generator, 4, 0 );
    print_minefield( minefield );
    std::cout << '\n';
    
    bool play = true;
    while( play && !( minefield.isDetonated() ) ) {
      std::size_t row, column;
      char operation;
      std::cin >> row >> column >> operation;
      switch( operation ) {
        case 'u':
          minefield.uncover( row, column );
          break;
        case 'f':
          minefield.flag( row, column );
          break;
        case 'q':
          play = false;
          break;
        default:
          break;
      }
      print_minefield( minefield );
    }

    std::cout << "\n\n" << minefield.isDetonated();

    /*
    for( std::size_t row = 0; row < minefield.getRowsCount(); ++row )
      for( std::size_t column = 0; column < minefield.getColumnsCount(); ++column )
        minefield.uncover( row, column );
    print_minefield( minefield );
    */
  
  return 0;
}