#include "OpenBabelUtils.h"
#include "SettingsParser.h"
#include "PdbParser.h"
#include "ErrorHandler.h"

int main(int argc, char** argv)
{
        //Check number of arguments given by the user
        if(argc < 3)
        {
            ErrorHandler::invalidNumberOfArguments();
            return EXIT_FAILURE;
        }

        //Convert file to PDB format if not given so
        OpenBabelUtils toPdbConversion(argv[1]);
        if(toPdbConversion.convert())
        {
            return EXIT_FAILURE;
        }

        //Getting information from properties file
        std::map<std::string, std::string> props;
        SettingsParser settingsParser{toPdbConversion.getPdbFileName(), argv[2], props};
        settingsParser.read_settings();

        //Parsing molecule from PDB file
        PdbParser moleculeParser(settingsParser.getInputFilename(),settingsParser.getInputMolecule());
        moleculeParser.read();

        //Creating outputfile with the parsed molecule and the given properties
        settingsParser.write_settings(moleculeParser.getOutputFileName());
        return EXIT_SUCCESS;
}