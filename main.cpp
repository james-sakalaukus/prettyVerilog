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


int main(int argc, char* argv[]) {

  ifstream inputFile;
  ofstream outputFile;

  if(argc <= 1) {
    inputFile.open("testFile.v");
  } else {
    inputFile.open(argv[1]);
  }

  if(!inputFile.is_open()) {
    cout << "Did not open the input file" << endl;
    return 0;
  }

  string outputFileName;
  if(argc <= 2) {
    outputFile.open("testFilePretty.v", ofstream::out);
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

  cout << "Calling: parseLocalSignals()" << endl;
  vector<localSignals> localSignalsVector;
  parseLocalSignals(inputFile, localSignalsVector);
  cout << "Returned from parseLocalSignals()" << endl;


  /* Parse functions:
   * 	The parse functions take in the input file stream and parse out some particular
   * 	type of Verilog construct.  Each parser should walk through the entire file and
   * 	return a vector of objects for printing later.
   */
  // parse all local signals/registers

  // parse all static assignments

  // parse all parameters

  // parse all module instantiations

  // parse always blocks with comments around each


  // print module declaration and input/outputs
  outputFile << "module " << moduleName << " (" << endl;
  // print wires
  //std::vector<localSignals>::iterator itlast = localSignalsVector.back();
  for (std::vector<localSignals>::iterator it = localSignalsVector.begin() ; it != localSignalsVector.end(); ++it) {

    if(it->getType() == "input") {
      if(!it->isIsVectorType()) {
        if(*it == localSignalsVector.back()) {
          outputFile << "  " << it->getType() << " " << it->getName() << endl;
        } else {
          outputFile << "  " << it->getType() << " " << it->getName() << "," << endl;
        }
      }
    }
  }

  // print all local signals/registers
  outputFile << ")" << endl << endl;
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

  // print all static assignments

  // print all parameters

  // print all module instantiations

  // print always blocks with comments around each


  outputFile << endl << "endmodule " << endl;

  outputFile.close();
  inputFile.close();
  return 0;
}





