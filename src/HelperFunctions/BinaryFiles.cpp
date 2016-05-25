#include "BinaryFiles.hpp"

namespace BinaryFiles {

void write( std::ofstream &openedFile, std::string &data ) {
  std::size_t dataSize = data.size();
  write( openedFile, dataSize );
  openedFile.write( data.c_str(), dataSize );
}

std::string read( std::ifstream &openedFile ) {
  auto dataSize = read< std::size_t >( openedFile );
  auto buffer = std::make_unique< char[] >( dataSize );
  openedFile.read( buffer.get(), dataSize );
  std::string data = buffer.get();
  return data;
}

} // namespace BinaryFiles