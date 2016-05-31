#include "SaveManager.hpp"
// Konstruktor:
SaveManager::SaveManager() : mCells(), mSaveDataLoadedFromFile( false ) {}
// Gettery:
bool SaveManager::isSaveDataLoadedFromFile() {
  return mSaveDataLoadedFromFile;
}
// Wczytywanie stanu gry:
void SaveManager::loadFromFile( const std::string &filename ) {
  std::ifstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    readFundamentalDataFromBinaryFile( file );
    readCellsFromBinaryFile( file );
    mSaveDataLoadedFromFile = true;
  }
}
CellsVector2D SaveManager::load() {
  return mCells;
}
// Zapisywanie stanu gry:
void SaveManager::saveToFile( const std::string &filename ) const {
  std::ofstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    writeFundamentalDataToBinaryFile( file );
    writeCellsDataToBinaryFile( file );
  }
}
void SaveManager::save( const Minefield &minefield ) {
  mCells = minefield;
}
// Pomocnicze metody chronione:
// Zapisywanie danych do pliku binarnego:
void SaveManager::writeFundamentalDataToBinaryFile( std::ofstream &file ) const {
  const std::size_t fundamentalDataSet[] = { mCells.getRowsCount(),
                                             mCells.getColumnsCount(),
                                             mCells.getMinesCount(),
                                             mCells.getUncoveredCellsCount(),
                                             mCells.getUsedFlags() };
  for( auto fundamentalData : fundamentalDataSet )
    BinaryFiles::write( file, fundamentalData );
  BinaryFiles::write( file, mCells.isMined() );
}
void SaveManager::writeSingleCellDataToBinaryFile( std::ofstream &file, const Cell &cell ) const {
  const int value = cell.getValue();
  const CellState state = cell.getState();
  BinaryFiles::write( file, value );
  BinaryFiles::write( file, state );
}
void SaveManager::writeCellsDataToBinaryFile( std::ofstream &file ) const {
  for( std::size_t row = 0; row < mCells.getRowsCount(); ++row )
    for( std::size_t column = 0; column < mCells.getColumnsCount(); ++column ) {
      writeSingleCellDataToBinaryFile( file, mCells.getCell( row, column ) );
    }
}
// Wczytywanie danych z pliku binarnego:
void SaveManager::readFundamentalDataFromBinaryFile( std::ifstream &file ) {
  const std::size_t rowsCount = BinaryFiles::read< std::size_t >( file ),
                    columnsCount = BinaryFiles::read< std::size_t >( file ),
                    minesCount = BinaryFiles::read< std::size_t >( file ),
                    uncoveredCellsCount = BinaryFiles::read< std::size_t >( file ),
                    usedFlags = BinaryFiles::read< std::size_t >( file );
  const bool mined = BinaryFiles::read< bool >( file );              
  mCells = CellsVector2D( rowsCount, columnsCount, minesCount, uncoveredCellsCount, usedFlags, mined );
}
Cell SaveManager::readSingleCellFromBinaryFile( std::ifstream &file ) {
  int value = BinaryFiles::read< int >( file );
  CellState state = BinaryFiles::read< CellState >( file );
  return Cell( value, state );
}
void SaveManager::readCellsFromBinaryFile( std::ifstream &file ) {
  for( std::size_t row = 0; row < mCells.getRowsCount(); ++row )
    for( std::size_t column = 0; column < mCells.getColumnsCount(); ++column ) {
      Cell &cell = mCells.getCell( row, column );
      cell = readSingleCellFromBinaryFile( file );
    }
}