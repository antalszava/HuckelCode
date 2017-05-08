//
// Created by toncsi on 2017.03.01..
//

#include <vector>
#include "SettingsParser.h"

void SettingsParser::read_settings()
{
    std::string delimiter = "=";
    std::ifstream input_file(configFileName.c_str());
    std::string line;
    if (input_file.good())
    {
        while (std::getline(input_file, line))
        {
            int pos = line.find(delimiter);
            std::string propKey = line.substr(0, pos);
            std::string propValue = line.substr(pos + 1, line.length());
            if(propKey=="molecule name")
                inputMolecule=propValue;
            properties[propKey] = propValue;
        }
        input_file.close();
    }
    else {

        std::string errmsg("File ");
        errmsg.append(configFileName);
        errmsg.append(" does not exist.\n");
        throw std::runtime_error(errmsg);
    }
}

void SettingsParser::write_settings(std::string outputFileName)
{
    std::ofstream outputFile;
    outputFile.open(outputFileName, std::fstream::app);
    outputFile << std::endl;
    outputFile << ";Printiing options" << std::endl;
    outputFile << "Print" << std::endl;
    std::vector<std::string> dumps;
    if (outputFile.is_open())
    {
        for (auto const &item : properties) {
            if (item.second == "true" && item.first.find("dump") == std::string::npos)
            {
                outputFile << item.first << std::endl;
            }
            else if(item.second == "true")
            {
                dumps.push_back(item.first);
            }
        }
    }
    outputFile << "End_Print \n" << std::endl;
    for(auto const &item : dumps)
    {
        outputFile << item << std::endl;
    }
    std::cout << "Successfully created the yah file." << std::endl;
}

const std::string &SettingsParser::getInputFilename() const {
    return inputFilename;
}

const std::string &SettingsParser::getInputMolecule() const {
    return inputMolecule;
}

