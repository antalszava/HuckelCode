#include "TestSettingsParser.h"

void TestSettingsParser::buildUp(std::string fileName)
{
    objectToBeTested = new SettingsParser(fileName, testProps);
    std::ofstream tempOutFile(fileName);

    tempOutFile << "something1=true " << std::endl;
    tempOutFile << "something2=true " << std::endl;
    tempOutFile << "something3=false " << std::endl;
    tempOutFile << "something4=true " << std::endl;
    tempOutFile << "something5=false " << std::endl;

    tempOutFile.close();
}

bool TestSettingsParser::readSettingsSuccessPropsNotEmpty()
{
    return !objectToBeTested->getIsPropsEmpty();
}

bool TestSettingsParser::writeSettingsSuccessFileNotempty()
{
    fileChecker.open(objectToBeTested->getConfigFileName());
    return fileChecker.peek() != std::ifstream::traits_type::eof();
}

void TestSettingsParser::tearDown(std::string fileName1,std::string fileName2)
{
    remove(fileName1.c_str());
    remove(fileName2.c_str());
    delete objectToBeTested;
}

