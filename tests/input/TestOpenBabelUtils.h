#ifndef INPUT_PDB_TESTOPENBABELUTILS_H
#define INPUT_PDB_TESTOPENBABELUTILS_H

#include "OpenBabelUtils.h"

class TestOpenBabelUtils
{
private:
    OpenBabelUtils* objectToBeTested;
public:

    void buildUp(std::string filename);
    void tearDown(std::string fileName);

    //Redefining private member's functions due to inaccessibility
    void obtainInputFileFormat()  { objectToBeTested->obtainInputFileFormat(); }
    void openBabelConversion()  { objectToBeTested->OpenBabelConversion(); }
    int convert() { return objectToBeTested->convert(); }

    //Redefining I/O functions for accessibility and testing purposes
    int initInPutFileSuccessFileOpen(std::string filename);
    int initOutPutFileSuccessFileOpen(std::string filename);

    //Testing OpenBabelUtils obtainInputFileFormat function
    bool obtainInputFileFormatSuccessFileName();
    bool obtainInputFileFormatSuccessFormat();

    //Testing OpenBabelUtils openBabelConversion function (most of it consists of OpenBabel API calls)
    bool openBabelConversionSuccessInputClosed();
    bool openBabelConversionSuccessOutputClosed();
};


#endif //INPUT_PDB_TESTOPENBABELUTILS_H
