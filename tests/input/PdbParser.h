#ifndef INPUT_PDB_PDB_PARSER_H
#define INPUT_PDB_PDB_PARSER_H

#include <iostream>
#include <ESBTL/default.h>
#include <ESBTL/atom_classifier.h>
#include <ESBTL/weighted_atom_iterator.h>
#include "ErrorHandler.h"

class PdbParser {
public:
    PdbParser(std::string fileName, std::string moleculeName) :
            sel(), systems(), builder(systems,sel.max_nb_systems()), inputFileName(fileName), lineNumber(0), moleculeName(moleculeName)
    {
        auto const pos = inputFileName.find_last_of('.');
        outputFileName = inputFileName.substr(0,pos);
        outputFileName.append(".yah");
    }

    const std::string &getOutputFileName() const { return outputFileName; }

    ~PdbParser() {}

    //Reading PDB file
    bool readPdb();

    //Convert PDB file to .yah file
    bool convert();

private:
    struct CustomMandatoryFields;
    typedef ESBTL::Generic_classifier<ESBTL::Radius_of_atom<double,ESBTL::Default_system::Atom> >           T_Atom_classifier;
    typedef ESBTL::Accept_none_occupancy_policy<ESBTL::PDB::Line_format<CustomMandatoryFields> > Accept_none_occupancy_policy;

    //Members used for file manipulation and providing information for the output file
    int lineNumber;
    std::string inputFileName;
    std::string moleculeName;
    std::string outputFileName;

    //Output file containing the .yah file format
    std::ofstream outputFile;

    ESBTL::PDB_line_selector sel;
    std::vector<ESBTL::Default_system> systems;
    ESBTL::All_atom_system_builder<ESBTL::Default_system> builder;

    T_Atom_classifier atom_classifier;

    template<ESBTL::Reading_mode mode,class mandatoryFields, class Line_selector,class Builder,class Occupancy_handler>
    bool readPdb(const std::string& filename,Line_selector& sel,Builder& builder,const Occupancy_handler& occupancy,char altloc=' ');

    template<class mandatoryFields, class Line_selector,class Builder,class Occupancy_handler>
    bool readPdb(const std::string& filename,Line_selector& sel,Builder& builder,const Occupancy_handler& occupancy,char altloc=' ');

    //In this struct you can specify what attributes your PDB has
    struct CustomMandatoryFields
    {
        static const bool record_name=true;
        static const bool atom_serial_number=true;
        static const bool atom_name=true;
        static const bool alternate_location=false;
        static const bool residue_name=false;
        static const bool chain_identifier=false;
        static const bool residue_sequence_number=false;
        static const bool insertion_code=false;
        static const bool x=true;
        static const bool y=true;
        static const bool z=true;
        static const bool occupancy=false;
        static const bool temperature_factor=true;
        static const bool element=false;
        static const bool charge_str=false;
        static const bool model_number=true;
    };
};



#endif //INPUT_PDB_PDB_PARSER_H
