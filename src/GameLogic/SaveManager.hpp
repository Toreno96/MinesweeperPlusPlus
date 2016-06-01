#include <array>
#include <fstream>
#include <string>
#include "HelperFunctions/BinaryFiles.hpp"
#include "Minefield.hpp"

const std::string defaultSaveFilename = "save.dat";

class SaveManager {
  public:
    // Konstruktor:
    SaveManager();
    // Gettery:
    bool isSaveDataLoadedFromFile();
    // Wczytywanie stanu gry:
    void loadFromFile( const std::string &filename = defaultSaveFilename );
    MinefieldData load();
    // Zapisywanie stanu gry:
    void saveToFile( const std::string &filename = defaultSaveFilename ) const;
    void save( const Minefield &minefield );
  protected:
    // Pomocnicze metody chronione:
    // Zapisywanie danych do pliku binarnego:
    void writeFundamentalDataToBinaryFile( std::ofstream &file ) const;
    void writeSingleCellDataToBinaryFile( std::ofstream &file, const Cell &cell ) const;
    void writeCellsDataToBinaryFile( std::ofstream &file ) const;
    // Wczytywanie danych z pliku binarnego:
    void readFundamentalDataFromBinaryFile( std::ifstream &file );
    Cell readSingleCellFromBinaryFile( std::ifstream &file );
    void readCellsFromBinaryFile( std::ifstream &file );
    // Składowe:
    MinefieldData mCells;
    bool mSaveDataLoadedFromFile;
};