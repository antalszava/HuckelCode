//
// Created by toncsi on 2017.03.01..
//

#ifndef INPUT_PROPERTIES_SETTINGSPARSER_H
#define INPUT_PROPERTIES_SETTINGSPARSER_H

#include <iostream>
#include <map>
#include <fstream>
#include "ErrorHandler.h"

class SettingsParser {
    std::map<std::string, std::string>& properties;
    std::string configFileName;
    std::string inputFilename;
    std::string inputMolecule;
public:
    SettingsParser(std::string inFileName, std::string configFileName, std::map<std::string, std::string>& props) :
            inputFilename(inFileName), configFileName(configFileName), properties(props) {}
    ~SettingsParser() {}
    void read_settings();
    void write_settings(std::string outputFileName);

    const std::string &getInputMolecule() const;
    const std::string &getInputFilename() const;

};


#endif //INPUT_PROPERTIES_SETTINGSPARSER_H
