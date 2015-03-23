/*
 * main.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: james
 */

#include <vector>
#include <iostream>


#include <localSignals.h>
#include <parserFunctions.h>

using namespace std;

bool printSignalTypes(vector<localSignals> &localSignalsVector, fstream &outputFile, string type, bool printVectorTypes);

int main(int argc, char* argv[]) {

  ifstream inputFile;
  fstream outputFile;

  if(argc <= 1) {
    inputFile.open("testFile.v", fstream::in);
  } else {
    inputFile.open(argv[1]);
  }

  if(!inputFile.is_open()) {
    cout << "Did not open the input file" << endl;
    return 0;
  }

  string outputFileName;
  if(argc <= 2) {
    outputFile.open("testFilePretty.v", fstream::out | fstream::in | fstream::trunc);
    outputFileName = "testFilePretty.v";

  } else {
    outputFile.open(argv[2], ofstream::out);
    outputFileName = argv[2];
  }

  if(!outputFile.is_open()) {
    cout << "Did not open the output file" << endl;
    return 0;
  } else {
    cout << "Opened: " << outputFileName << endl;
  }


  string moduleName;
  if(!parseModuleName(inputFile, moduleName)) {
    cerr << "Could not find Module Name in file" << endl;
    return 0;
  }




  /* Parse functions:
   * 	The parse functions take in the input file stream and parse out some particular
   * 	type of Verilog construct.  Each parser should walk through the entire file and
   * 	return a vector of objects for printing later.
   */

  // parse all local signals/registers
  vector<localSignals> localSignalsVector;
  parseLocalSignals(inputFile, localSignalsVector);

  // TODO: parse all static assignments

  // TODO: parse all parameters

  // TODO: parse all module instantiations

  // TODO: parse always blocks with comments around each


  /********************************************************
   *  print module declaration and input/outputs
   ********************************************************/
  outputFile << "module " << moduleName << " (" << endl;

  outputFile << endl << "  // input signals" << endl;
  printSignalTypes(localSignalsVector, outputFile, "input", false);

  outputFile << endl << "  // input vectors" << endl;
  printSignalTypes(localSignalsVector, outputFile, "input", true);

  outputFile << endl << "  // output signals" << endl;
  printSignalTypes(localSignalsVector, outputFile, "output", false);

  outputFile << endl << "  // output vectors" << endl;
  printSignalTypes(localSignalsVector, outputFile, "output", true);

  outputFile << endl << "  // registered output signals" << endl;
  printSignalTypes(localSignalsVector, outputFile, "output reg", false);

  outputFile << endl << "  // registered output vectors" << endl;
  printSignalTypes(localSignalsVector, outputFile, "output reg", true);

  // remove the comma from the last argument
  long pos = outputFile.tellp();
  outputFile.seekp (pos-2);
  outputFile.write ("\n",1);

  // close the module
  outputFile << ");" << endl << endl;


  /********************************************************
   *  print all local signals/registers
   ********************************************************/

  outputFile << "/*******************************************************************" << endl;
  outputFile << "*    Local Signal Declarations" << endl;
  outputFile << "*******************************************************************/" << endl;
  // print wires
  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {

    if(it->getType() == "wire") {
      if(!it->isIsVectorType()) {
        outputFile << it->getType() << " " << it->getName() << ";" << endl;
      }
    }
  }
  // print regs
  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {

    if(it->getType() == "reg") {
      outputFile << it->getType() << " " << it->getName() << ";" << endl;
    }
  }
  // print wire vectors
  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {

    if(it->getType() == "wire") {
      if(it->isIsVectorType()) {
        outputFile << it->getType() << " [" << it->getVectorMsb() << ":" << it->getVectorLsb() << "] " << it->getName() << ";" << endl;
      }
    }
  }
  // print reg vectors
  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {

    if(it->getType() == "reg") {
      if(it->isIsVectorType()) {
        outputFile << it->getType() << " [" << it->getVectorMsb() << ":" << it->getVectorLsb() << "] " << it->getName() << ";" << endl;
      }
    }
  }


  // print all reg initial values
  outputFile << "/*******************************************************************" << endl;
  outputFile << "*    Initial Values" << endl;
  outputFile << "*******************************************************************/" << endl;
  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {

    if(it->getType() == "reg") {
      if(it->isIsInlineAssignment()) {
        outputFile << it->getName() << " = " << it->getSignalAssignment() << ";" << endl;
      }
    }
  }

  // TODO: print all static assignments

  // TODO: print all parameters

  // TODO: print all module instantiations

  // TODO: print always blocks with comments around each


  outputFile << endl << "endmodule " << endl;

  outputFile.close();
  inputFile.close();
  return 0;
}


bool printSignalTypes(vector<localSignals> &localSignalsVector, fstream &outputFile, string type, bool printVectorTypes) {

  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {
    if(it->getType() == type) {

      if(!printVectorTypes && !it->isIsVectorType()) {
          outputFile << "  " << it->getType() << " " << it->getName() << "," << endl;

        } else if(printVectorTypes && it->isIsVectorType()) {
          outputFile << "  " << it->getType() << " [" << it->getVectorMsb() << ":" << it->getVectorLsb() << "] " << it->getName() << "," << endl;
      }
    } else {
      // not the signal type we want to print, do nothing
    }
  } // for()

  return true;
}


