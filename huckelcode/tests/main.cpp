#include <unordered_map>
#include <cstdio>
#include <omp.h>

#include <iostream>
#include <assert.h>
#include "TestMarketMatrixWriter.h"

int main()
{
    std::string sampleOutputFileName = "someoutput.bin";

    //Testing MarketMatrixWriter class without using cutoff value
    TestMarketMatrixWriter testObject;
    testObject.buildUp(sampleOutputFileName);

    //Creating output binary file and checking if the file was not left empty
    testObject.createBinaryFile();
    testObject.writeSuccessFileNotempty();

    testObject.tearDown(sampleOutputFileName);

    //New test for dump function
    testObject.buildUp(sampleOutputFileName);

    //Creating dump file and checking if the file was not left empty
    testObject.createDumpFile();
    testObject.writeSuccessFileNotempty();

    testObject.tearDown(sampleOutputFileName);

    //Repeating previous tests for MarketMatrixWriter class with cutoff value

    testObject.buildUp(sampleOutputFileName,0.5);

    testObject.createBinaryFile();
    testObject.writeSuccessFileNotempty();
    testObject.tearDown(sampleOutputFileName);

    testObject.buildUp(sampleOutputFileName,0.5);

    testObject.createDumpFile();
    testObject.writeSuccessFileNotempty();

    testObject.tearDown(sampleOutputFileName);
    return 0;

}

