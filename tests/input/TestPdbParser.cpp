#include "TestPdbParser.h"


void TestPdbParser::buildUp(std::string filename, std::string molecule)
{
    objectToBeTested = new PdbParser(filename, molecule);

    std::ofstream tempOutFile(filename);

    //placing sample molecule's details into a PDB file
    tempOutFile << "TITLE       " << molecule << std::endl;
    tempOutFile << "ATOM      1  CAY MET P   1      11.479 -16.234  64.191  1.00  0.00      PRO" << std::endl;
    tempOutFile << "ATOM      2  CAY MET P   1      11.479 -16.234  64.191  1.00  0.00      PRO" << std::endl;
    tempOutFile << "ATOM      3  CAY MET P   1      11.479 -16.234  64.191  1.00  0.00      PRO" << std::endl;
    tempOutFile << "ATOM      4  CAY MET P   1      11.479 -16.234  64.191  1.00  0.00      PRO" << std::endl;
    tempOutFile << "ATOM      5  CAY MET P   1      11.479 -16.234  64.191  1.00  0.00      PRO" << std::endl;
    tempOutFile << "ATOM      6  CAY MET P   1      11.479 -16.234  64.191  1.00  0.00      PRO" << std::endl;
    tempOutFile.close();
}

int TestPdbParser::readSuccessFileExists()
{
    fileChecker.open(objectToBeTested->getOutputFileName());
    return fileChecker.is_open();
}

int TestPdbParser::readSuccessFileNotempty()
{
    return fileChecker.peek() != std::ifstream::traits_type::eof();
}

void TestPdbParser::tearDown(std::string fileName)
{

    auto const pos = fileName.find_last_of('.');
    std::string tempFileName = fileName.substr(0,pos);
    tempFileName.append(".yah");

    remove(tempFileName.c_str());
    remove(fileName.c_str());
    fileChecker.close();
    delete objectToBeTested;
}
