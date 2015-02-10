/*
 * main.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: james
 */


#include <localSignals.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


// forward declarations
bool parseLocalSignals(ifstream &inputFile, vector<localSignals> &localSignalsVector);



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

  if(argc <= 2) {
    outputFile.open("../testFilePretty.v", ofstream::out);
  } else {
    outputFile.open(argv[2], ofstream::out);
  }

  if(!outputFile.is_open()) {
    cout << "Did not open the output file" << endl;
    return 0;
  }

  vector<localSignals> localSignalsVector;

  cout << "Calling: parseLocalSignals()" << endl;
  parseLocalSignals(inputFile, localSignalsVector);
  cout << "Returned from parseLocalSignals()" << endl;

  outputFile.close();
  inputFile.close();
  return 0;
}

bool parseLocalSignals(ifstream &inputFile, vector<localSignals> &localSignalsVector) {

  string lineBuffer;
  size_t startPosition;

  while(!inputFile.eof()) {
    getline(inputFile, lineBuffer);

    // find all 'wire', but ignore 'output wire' stuff
    if (lineBuffer.find("output\twire") != string::npos) {
      // ignore for now
      continue;
    } else if (lineBuffer.find("output wire") != string::npos) {
      // ignore for now
      continue;

    // check for vector brackets first
    } else if ((lineBuffer.find("wire\t[") != string::npos) ||
                  (lineBuffer.find("wire [") != string::npos)) {

      lineBuffer.find("wire\t[");
      //localSignalsVector.push_back(string())
      cout << lineBuffer << endl;

    } else if ((lineBuffer.find("wire\t") != string::npos) ||
              (lineBuffer.find("wire ") != string::npos)) {

    } else {
      //cout << "I don't know how to parse this:" << endl;
      //cout << lineBuffer << endl;
    }

  } // end while()

  return true;
}
