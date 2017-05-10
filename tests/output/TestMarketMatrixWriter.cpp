#include "TestMarketMatrixWriter.h"


void TestMarketMatrixWriter::buildUp(std::string fileName)
{
    testOutputFileName = fileName;
    testMatrix = {1.1,0,0,0,0,2.2,3.3,0,0,0,0,0,4.4,0,0,5.21,0,0,0,0,0,0,0};
    objectToBeTested = new MatrixMarketWriter(fileName,&testMatrix[0],testMatrix.size());
}

void TestMarketMatrixWriter::buildUp(std::string fileName, double cutoff)
{
    testMatrix = {1.1,0,0,0,0,2.2,3.3,0,0,0,0,0,4.4,0,0,5.21,0,0,0,0,0,0,0};
    objectToBeTested = new MatrixMarketWriter(fileName,cutoff,&testMatrix[0],testMatrix.size());
}

bool TestMarketMatrixWriter::writeSuccessFileNotempty()
{
    fileChecker.open(testOutputFileName);
    return fileChecker.peek() != std::ifstream::traits_type::eof();
}

void TestMarketMatrixWriter::tearDown(std::string fileName)
{
    fileChecker.close();
    remove(fileName.c_str());
    delete objectToBeTested;
}