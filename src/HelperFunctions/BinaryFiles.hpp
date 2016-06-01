#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace BinaryFiles {
  
template< typename T >
void write( std::ofstream &openedFile, T data ) {
  openedFile.write( reinterpret_cast< char * >( &data ), sizeof( data ) );
}
void write( std::ofstream &openedFile, const std::string &data );

template< typename FundamentalType >
FundamentalType read( std::ifstream &openedFile ) {
  FundamentalType target;
  openedFile.read( reinterpret_cast< char * >( &target ), sizeof( target ) );
  return target;
}
template<>
std::string read< std::string >( std::ifstream &openedFile );

} // namespace BinaryFiles