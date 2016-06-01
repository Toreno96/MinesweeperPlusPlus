#include "BinaryFiles.hpp"

namespace BinaryFiles {

void write( std::ofstream &openedFile, const std::string &data ) {
  std::size_t dataSize = data.size();
  write( openedFile, dataSize );
  openedFile.write( data.c_str(), dataSize );
}

template<>
std::string read< std::string >( std::ifstream &openedFile ) {
  auto dataSize = read< std::size_t >( openedFile );
  std::vector< char > buffer( dataSize );
  openedFile.read( buffer.data(), dataSize );
  std::string data( buffer.data(), dataSize );
  return data;
}

} // namespace BinaryFiles