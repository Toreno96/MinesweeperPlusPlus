#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace BinaryFiles {
  
template< typename T >
void write( std::ofstream &openedFile, T data ) {
  openedFile.write( reinterpret_cast< char * >( &data ), sizeof( data ) );
}
void write( std::ofstream &openedFile, std::string &data );

template< typename FundamentalType >
FundamentalType read( std::ifstream &openedFile ) {
  FundamentalType target;
  openedFile.read( reinterpret_cast< char * >( &target ), sizeof( target ) );
  return target;
}
std::string read( std::ifstream &openedFile );

} // namespace BinaryFiles