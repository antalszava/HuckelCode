#include "ErrorHandler.h"
#include <iostream>

//
// Created by toncsi on 2017.05.01..
//
void ErrorHandler::invalidNumberOfArguments()
{
    std::cerr << "Please provide two filenames: one for your molecule file and one for your configuration file."  << std::endl;
}

void ErrorHandler::notAvailableFormats(const char * inputFormat, const char * outputFormat)
{
    std::cerr << "Formats not currently available in OpenBabel: " << inputFormat << " or " << outputFormat << std::endl;
}

void ErrorHandler::inputFileNotOpen()
{
    std::cerr << "Cannot open input file, please check if it exists in the current folder." << std::endl;
}

void ErrorHandler::inputFileNotOpen(std::string fileName)
{
    std::cerr << "Cannot open input file(" <<  fileName << "), please check if it exists in the current folder." << std::endl;
}

void ErrorHandler::outputFileNotOpen()
{
    std::cerr << "Cannot open output file, please check if you have rights to write the file." << std::endl;
}