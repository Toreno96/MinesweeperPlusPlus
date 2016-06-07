#include "SaveManager.hpp"
// Konstruktor:
SaveManager::SaveManager() : mCells(), mActualSaveDataPresent( false ) {}
// Gettery:
bool SaveManager::isActualSaveDataPresent() {
  return mActualSaveDataPresent;
}
// Settery:
void SaveManager::setActualSaveDataPresent( const bool boolean ) {
  mActualSaveDataPresent = boolean;
}
// Wczytywanie stanu gry:
void SaveManager::loadFromFile( const std::string &filename ) {
  std::ifstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    readFundamentalDataFromBinaryFile( file );
    readCellsFromBinaryFile( file );
    mActualSaveDataPresent = true;
  }
}
MinefieldData SaveManager::load() {
  return mCells;
}
// Zapisywanie stanu gry:
void SaveManager::saveToFile( const std::string &filename ) const {
  if( mActualSaveDataPresent ) {
    std::ofstream file( filename, std::ios::binary );
    if( file.is_open() ) {
      writeFundamentalDataToBinaryFile( file );
      writeCellsDataToBinaryFile( file );
    }
  }
}
void SaveManager::save( const Minefield &minefield ) {
  mCells = minefield;
  mActualSaveDataPresent = true;
}
// Pomocnicze metody chronione:
// Zapisywanie danych do pliku binarnego:
void SaveManager::writeFundamentalDataToBinaryFile( std::ofstream &file ) const {
  const std::size_t fundamentalDataSet[] = { mCells.getRowsCount(),
                                             mCells.getColumnsCount(),
                                             mCells.getMinesCount(),
                                             mCells.getUncoveredCellsCount(),
                                             mCells.getUsedFlagsCount() };
  for( auto fundamentalData : fundamentalDataSet )
    BinaryFiles::write( file, fundamentalData );
  BinaryFiles::write( file, mCells.getElapsedSeconds() );
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
                    usedFlagsCount = BinaryFiles::read< std::size_t >( file );
  const unsigned elapsedSeconds = BinaryFiles::read< unsigned >( file );
  const bool mined = BinaryFiles::read< bool >( file );              
  mCells = MinefieldData( rowsCount, columnsCount, minesCount, uncoveredCellsCount, usedFlagsCount, elapsedSeconds, mined );
}
Cell SaveManager::readSingleCellFromBinaryFile( std::ifstream &file ) {
  int value = BinaryFiles::read< int >( file );
  CellState state = BinaryFiles::read< CellState >( file );
  return Cell( value, state );
}
void SaveManager::readCellsFromBinaryFile( std::ifstream &file ) {
  for( std::size_t row = 0; row < mCells.getRowsCount(); ++row )
    for( std::size_t column = 0; column < mCells.getColumnsCount(); ++column ) {
      Cell readedCell = readSingleCellFromBinaryFile( file );
      mCells.setCell( row, column, readedCell );
    }
}