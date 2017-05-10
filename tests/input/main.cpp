#include "OpenBabelUtils.h"
#include "SettingsParser.h"
#include "PdbParser.h"

#include "TestOpenBabelUtils.h"
#include "TestPdbParser.h"
#include "TestSettingsParser.h"

int main(int argc, char** argv)
{
    //Values needed for testing
    std::string sampleOtherFormatterFileName = "some.sdf";
    std::string samplePDBFileName = "some.pdb";

    //Testing OpenBabelUtils class
    TestOpenBabelUtils testObabelOject;
    testObabelOject.buildUp(sampleOtherFormatterFileName);

    //Checking if the init input and init output functions open the files
    assert(testObabelOject.initInPutFileSuccessFileOpen(sampleOtherFormatterFileName));
    assert(testObabelOject.initOutPutFileSuccessFileOpen(sampleOtherFormatterFileName));

    //Checking if the file format is well acquired
    testObabelOject.obtainInputFileFormat();
    assert(testObabelOject.obtainInputFileFormatSuccessFileName());
    assert(testObabelOject.obtainInputFileFormatSuccessFormat());

    //Checking if files are closed after OpenBabel conversion
    testObabelOject.openBabelConversion();
    assert(testObabelOject.openBabelConversionSuccessInputClosed());
    assert(testObabelOject.openBabelConversionSuccessOutputClosed());

    //Checking if convert function uses the previously unit tested functions well
    assert(testObabelOject.convert()==0);

    testObabelOject.tearDown(sampleOtherFormatterFileName);

    //Checking if it is already PDB
    testObabelOject.buildUp(samplePDBFileName);
    assert(testObabelOject.convert()==0);
    testObabelOject.tearDown(samplePDBFileName);

    //Testing PdbParser class
    TestPdbParser testPdbParserObject;
    testPdbParserObject.buildUp(samplePDBFileName,"somemolecule");

    //After parsing the PDB file, checking if the .yah file was created
    testPdbParserObject.convert();
    assert(testPdbParserObject.readSuccessFileExists());
    assert(testPdbParserObject.readSuccessFileNotempty());
    testPdbParserObject.tearDown(samplePDBFileName);

    //Testing the SettingsParser class
    std::string sampleConfigFileName = "someconfig.txt";
    std::string sampleOutputFileName = "someoutputfile.yah";

    std::map<std::string, std::string> testProps;
    TestSettingsParser testSettingsParserObject(testProps);
    testSettingsParserObject.buildUp(sampleConfigFileName);

    //Testing if properties were parsed from configuration file
    testSettingsParserObject.readSettings();
    assert(testSettingsParserObject.readSettingsSuccessPropsNotEmpty());

    //Testing if file was created in the process of appending
    testSettingsParserObject.writeSettings(sampleOutputFileName);
    assert(testSettingsParserObject.writeSettingsSuccessFileNotempty());
    testSettingsParserObject.tearDown(sampleConfigFileName,sampleOutputFileName);

    return EXIT_SUCCESS;
}