//
// Created by toncsi on 2017.05.01..
//

#ifndef INPUT_PDB_OPENBABELUTILS_H
#define INPUT_PDB_OPENBABELUTILS_H

#include <iostream>
#include <fstream>
#include <openbabel/obconversion.h>
#include <string>
#include <locale>


class OpenBabelUtils {
private:
    std::string inputFileName;
    std::string outputFileName;

    std::string inputFileFormat;
    std::string pdbFileName;

    std::ifstream inputFile;
    std::ofstream outputFile;
public:
    OpenBabelUtils(std::string fileName) : inputFileName(fileName) {}
    int convert();
    int OpenBabelConversion();
    int initInputFile(std::string filename);
    int initOutPutFile(std::string filename);
    void obtainInputFileFormat();

    const std::string &getPdbFileName() const;

};


#endif //INPUT_PDB_OPENBABELUTILS_H
