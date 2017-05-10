#include <cmath>
#include <omp.h>
#include "MarketMatrixWriter.h"

void MatrixMarketWriter::writeToFileBinary(std::string outputString)
{
    write(outputFile, outputString.c_str(),outputString.size());
}

void MatrixMarketWriter::writeToFileBinary(double number)
{
    write(outputFile, (const char *) &number, sizeof(double));
}

void MatrixMarketWriter::writeToFileBinary(long number)
{
    write(outputFile, (const char *) &number, sizeof(long));
}

//Writing the matrix to file in binary mode
bool MatrixMarketWriter::createBinaryFile()
{
    //Open file using UNIX system call for binary formatted writing
    outputFile = open(outputFileName.c_str(), O_RDWR | O_TRUNC | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);

    //If we managed to open the file, write the necessary data
    if (outputFile != -1)
    {
        //Writing the first line of the file containing the type of matrix
        writeToFileBinary("%%MatrixMarket");
        writeFormat();
        writeSparsity();
        writeField();
        writeSymmetry();
        writeToFileBinary("\n");

        //COMMENTS COME HERE

        //Writing the dimensions and the number of nonzero elements
        writeSparseDetails();

        //Writing the coordinates of the matrix
        writeCoordinates();
    }
    else
    {
        return EXIT_FAILURE;
    }
    close(outputFile);
    return EXIT_SUCCESS;
}

bool MatrixMarketWriter::createDumpFile()
{
    //Open file using UNIX system call for binary formatted writing
    outputFile = open(outputFileName.c_str(), O_RDWR | O_TRUNC | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);

    //If we managed to open the file, write the necessary data
    if (outputFile != -1)
    {
        dumpCoordinates();
    }
    else
    {
        return EXIT_FAILURE;
    }
    close(outputFile);
    return EXIT_SUCCESS;
}

bool MatrixMarketWriter::writeFormat()
{
    switch(formatType) {
        case FormatType::matrix:
            writeToFileBinary(" matrix");
            break;
    }
}

bool MatrixMarketWriter::writeSparsity()
{
    switch(sparsityType) {
        case SparsityType::sparse:
            writeToFileBinary(" coordinate");
            break;
        case SparsityType::dense:
            writeToFileBinary(" array");
            break;
    }
}

bool MatrixMarketWriter::writeField()
{
    switch(fieldType) {
        case FieldType::real:
            writeToFileBinary(" real");
            break;
        case FieldType::complex:
            writeToFileBinary(" complex");
            break;
        case FieldType::integer:
            writeToFileBinary(" integer");
            break;
        case FieldType::pattern:
            writeToFileBinary(" pattern");
            break;
    }
}

bool MatrixMarketWriter::writeSymmetry()
{
    switch(symmetryType) {
        case SymmetryType::general:
            writeToFileBinary(" general");
            break;
        case SymmetryType::hermitian:
            writeToFileBinary(" hermitian");
            break;
        case SymmetryType::symmetric:
            writeToFileBinary(" symmetric");
            break;
        case SymmetryType::skewsymmetric:
            writeToFileBinary(" skew-symmetric");
            break;
    }
}

bool MatrixMarketWriter::writeSparseDetails()
{
    long numberOfNonZero = 0;
    #pragma omp parallel for shared(numberOfNonZero)
    for (long i = 0; i < rowNumber; i++) {
        long itab = i * columnNumber;
        for (long j = 0; j < columnNumber; j++){
            if (fabs(matrix[itab + j]) > cutoff)
            {
                #pragma omp atomic
                ++numberOfNonZero;
            }
        }
    }
    writeToFileBinary(rowNumber);
    writeToFileBinary(" ");
    writeToFileBinary(columnNumber);
    writeToFileBinary(" ");
    writeToFileBinary(numberOfNonZero);
    writeToFileBinary("\n");
}

bool MatrixMarketWriter::writeCoordinates()
{
    // writeToFileBinary the nonzero elements
    for (long i = 0; i < rowNumber; i++) {
        long itab = i * columnNumber;
        for (long j = 0; j < columnNumber; j++){
            if (fabs(matrix[itab + j]) > cutoff)
            {
                writeToFileBinary(i);
                writeToFileBinary(" ");
                writeToFileBinary(j);
                writeToFileBinary(" ");
                writeToFileBinary(matrix[itab + j]);
                writeToFileBinary("\n");
            }
        }
    }
}

bool MatrixMarketWriter::dumpCoordinates()
{
    // writeToFileBinary the nonzero elements
    for (long i = 0; i < rowNumber; i++) {
        long itab = i * columnNumber;
        for (long j = 0; j < columnNumber; j++){
            if (fabs(matrix[itab + j]) > cutoff)
            {
                writeToFileBinary(i);
                writeToFileBinary(j);
                writeToFileBinary(matrix[itab + j]);
            }
        }
    }
}