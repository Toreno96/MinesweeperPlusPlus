#include <iostream>
#include <boost/random/random_device.hpp>
#include "Game Logic/MinefieldTri.hpp"
#include "Game Logic/SaveManager.hpp"

void print_minefield( MinefieldTri &minefield ) {
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
  SaveManager saveManager;
  saveManager.loadFromFile();
  if( saveManager.isSaveDataLoadedFromFile() ) {
    MinefieldTri minefield( saveManager.load() );
    std::cout << minefield.isMined() << ' ' << minefield.getUsedFlags() << "\n\n";
    print_minefield( minefield );
    std::cout << '\n';
    
    /*
    unsigned counter = 0;
    while( counter++ < 3 ) {
      std::size_t row, column;
      std::cin >> row >> column;
      std::cout << '\n';
      minefield.uncover( row, column );
      print_minefield( minefield );
    }
    while( counter++ < 5 ) {
      std::size_t row, column;
      std::cin >> row >> column;
      std::cout << '\n';
      minefield.flag( row, column );
      print_minefield( minefield );
    }
    std::cout << "\n\n" << minefield.isDetonated();
    */
    
    for( std::size_t row = 0; row < minefield.getRowsCount(); ++row )
      for( std::size_t column = 0; column < minefield.getColumnsCount(); ++column )
        minefield.uncover( row, column );
    print_minefield( minefield );
    
    saveManager.save( minefield );
    saveManager.saveToFile();
  }
  else {
    boost::random::random_device random_device;
    boost::random::mt19937 generator( random_device() );
    
    std::size_t rowsCount, columnsCount, minesCount;
    std::cout << "Enter rowsCount, columnsCount and minesCount:\n";
    std::cin >> rowsCount >> columnsCount >> minesCount;
    
    MinefieldTri minefield( rowsCount, columnsCount, minesCount );
    
    /*
    for( std::size_t row = 0; row < rowsCount; ++row )
      for( std::size_t column = 0; column < columnsCount; ++column )
        minefield.getCell( row, column ).setState( CellState::uncovered );
    */
    minefield.mine( generator, 4, 0 );
    print_minefield( minefield );
    std::cout << '\n';
    
    /*
    unsigned counter = 0;
    while( counter++ < 3 ) {
      std::size_t row, column;
      std::cin >> row >> column;
      std::cout << '\n';
      minefield.uncover( row, column );
      print_minefield( minefield );
    }
    while( counter++ < 5 ) {
      std::size_t row, column;
      std::cin >> row >> column;
      std::cout << '\n';
      minefield.flag( row, column );
      print_minefield( minefield );
    }
    std::cout << "\n\n" << minefield.isDetonated();
    */
    
    for( std::size_t row = 0; row < minefield.getRowsCount(); ++row )
      for( std::size_t column = 0; column < minefield.getColumnsCount(); ++column )
        minefield.uncover( row, column );
    print_minefield( minefield );
    
    saveManager.save( minefield );
    saveManager.saveToFile();
    
  }
  
  return 0;
}