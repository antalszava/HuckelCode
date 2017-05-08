//
// Created by toncsi on 2017.05.01..
//

#ifndef INPUT_PDB_ERRORHANDLER_H
#define INPUT_PDB_ERRORHANDLER_H

#include <iostream>

namespace ErrorHandler {
    //Handling error of unknown filename
    extern int checkNumberOfArguments(int numberOfArguments);

    //Handling error of unknown formats given for OpenBabel
    extern void notAvailableFormats(const char * inputFormat, const char * outputFormat);

    //Informing user about inability to open input file
    extern void inputFileNotOpen();

    extern void inputFileNotOpen(std::string fileName);

    //Informing user about inability to open output file
    extern void outputFileNotOpen();
};


#endif //INPUT_PDB_ERRORHANDLER_H
