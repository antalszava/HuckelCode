#include "TestOpenBabelUtils.h"


void TestOpenBabelUtils::buildUp(std::string filename)
{
    objectToBeTested = new OpenBabelUtils(filename);

    //Open PDB mock input file that is going to be used for the test
    std::ofstream tempOutFile(filename);
    tempOutFile.close();
}

void TestOpenBabelUtils::tearDown(std::string fileName)
{
    //Delete previously created file
    remove(fileName.c_str());
    objectToBeTested->closeInputFile();
    objectToBeTested->closeOutputFile();
    delete objectToBeTested;
}

bool TestOpenBabelUtils::obtainInputFileFormatSuccessFileName()
{
    //Getting first part of InputFileName, cutting ".<format>"
    std::string unformattedFileName1 =
                    objectToBeTested->getInputFileName().substr(0, objectToBeTested->getInputFileName().length()-
                    objectToBeTested->getInputFileName().find_last_of("."));

    //Getting first part of PdbFileName, cutting ".pdb"
    std::string unformattedFileName2 =
                    objectToBeTested->getPdbFileName().substr(0, objectToBeTested->getPdbFileName().length()-
                    objectToBeTested->getPdbFileName().find_last_of("."));

    return  unformattedFileName1==unformattedFileName2;
}

bool TestOpenBabelUtils::obtainInputFileFormatSuccessFormat()
{
    return  objectToBeTested->getPdbFileName().substr(objectToBeTested->getPdbFileName().find_last_of("."),4)==".pdb";
}

bool TestOpenBabelUtils::openBabelConversionSuccessInputClosed()
{
    return !objectToBeTested->getIsInputOpen();
}

bool TestOpenBabelUtils::openBabelConversionSuccessOutputClosed()
{
    return !objectToBeTested->getIsOutputOpen();
}

int TestOpenBabelUtils::initInPutFileSuccessFileOpen(std::string filename)
{
    objectToBeTested->initInputFile(filename);
    return objectToBeTested->getIsInputOpen();
}

int TestOpenBabelUtils::initOutPutFileSuccessFileOpen(std::string filename)
{
    objectToBeTested->initOutPutFile(filename);
    return objectToBeTested->getIsOutputOpen();
}