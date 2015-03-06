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
#include <iterator>
#include <boost/regex.hpp>
#include <sstream>

using namespace std;
using namespace boost;


// forward declarations
//bool parseLocalSignals(ifstream &inputFile, vector<localSignals> &localSignalsVector);
bool parseLocalSignals(const std::string& file, vector<localSignals> &localSignalsVector);


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
  string lineBuffer;

  while(!inputFile.eof()) {
    getline(inputFile, lineBuffer);
    parseLocalSignals(lineBuffer, localSignalsVector);
  }
  cout << "Returned from parseLocalSignals()" << endl;

  outputFile.close();
  inputFile.close();
  return 0;
}




bool parseLocalSignals(const std::string& file, vector<localSignals> &localSignalsVector) {

//  boost::regex re("(wire|reg)\s*\[\s*([\w-]*)\s*:\s*(\w*)\s*]\s*(\w*)\s*(=|;)\s*(\w*)\s*(\[|;)\s*(\w*)\s*:(\w*)\s*(\w*)\s*\]\s*;\s*//(.*)");
//  boost::regex re("(wire|reg)\\s*\\[\\s*([\\w-]*)\\s*:\\s*(\\w*)\\s*\\]\\s*(\\w*)\\s*(=|;)\\s*(\\w*)\\s*(\\[|;)\\s*(\\w*)\\s*:(\\w*)\\s*(\\w*)\\s*\\]\\s*;\\s*//(.*)");

//  boost::regex re("^\\s*(output|input)?\\s*(wire|reg)\\s*(\\[\\s*([\\w-]*)\\s*:\\s*(\\w*)\\s*\\])?\\s*(\\w*)\\s*(=|;)\\s*([\\[\\]\\s\\w:]*);\\s*(\/\/[\w\\s]*)(.*)$");

  stringstream regExpression;
  regExpression << "^\\s*"
                << "(output|input)?" << "\\s*"
                << "(wire|reg)" << "\\s*"
                << "(\\[\\s*([\\w-]*)\\s*:\\s*(\\w*)\\s*\\])?" << "\\s*"
                << "(\\w*)" << "\\s*"
                << "(=)?" << "\\s*"
                << "([^;,]*)" << "\\s*"
//                << "([\\[\\]\\s\\w:]*)" << "\\s*"
                << "(;|,)?" << "\\s*"
                << "(\\/\\/[\\w\\s]*)?" << "\\s*"
                << "(.*)$";


  boost::regex re(regExpression.str());

  std::string::const_iterator start, end;
  boost::match_results<std::string::const_iterator> what;
  boost::match_flag_type flags = boost::match_default;

  /* Example crappy code:
   *  output reg      e_rd_stb=rd_1_every_3_sr[2]&&(rx_opcode==OP_READ)&&OUT_TICK; // comment
   *
   *  (output|input)?                               May be an input/output declaration
   *  (wire|reg)                                    Match the type
   *    (\\[\\s*([\\w-]*)\\s*:\\s*(\\w*)\\s*\\])?   Match if vector, can be zero match
   *      ([\\w-\\+]*)                              MSB could be a string with addition/subtraction
   *      ([\\w-\\+]*)                              LSB could be a string with addition/subtraction
   *  (\\w*)                                        Match the signal name
   *  (=|;)                                         Possible Inline initialization/assignment
   *  ([\\[\\]\\s\\w:]*)                            Match the assignment value
   *  (\/\/[\w\\s]*)                                Match a comment
   *  (.*)                                          Anything else
  */


//
//    cmatch what;
//    if(boost::regex_search(lineBuffer.c_str(), what, re)) {
//      cout <<  lineBuffer << endl;
//    }

      start = file.begin();
      end = file.end();
      if(regex_search(start, end, what, re, flags))
      {

        cout << "Matched string: " << what[0] << endl;

        if(what[1].matched)
          cout << "\tI/O type: " << what[1] << endl;

        cout << "\treg/wire type: " << what[2] << endl;

        if(what[3].matched) {
          cout << "\tVector type, " << " MSB: " << what[4] << " LSB: " << what[5] <<endl;
        }

        cout << "\tsignal name: " << what[6] << endl;

        cout << "\tArg 7: " << what[7] << endl;

        if(what[7] == ";") {
          cout << "\tNo inline assignment" << endl;
        } else {
          cout << "\tassignment value: " << what[8] << endl;
        }

        if(what[9].matched) {
          cout << "\tComment is: " << what[9] << endl;
        }
        cout << endl;
    //    // update search position:
//        start = what[0].second;
        // update flags:
//        flags |= boost::match_prev_avail;
//        flags |= boost::match_not_bob;
      }
//  }



  return true;
}

// This was the original approach, before somebody mentioned regular expressions...
//bool parseLocalSignals(ifstream &inputFile, vector<localSignals> &localSignalsVector) {
//
//  string lineBuffer;
//
//  while(!inputFile.eof()) {
//    getline(inputFile, lineBuffer);
//
//    // find all 'wire', but ignore 'output wire' stuff
//    if (lineBuffer.find("output\twire") != string::npos) {
//      // ignore for now
//      continue;
//    } else if (lineBuffer.find("output wire") != string::npos) {
//      // ignore for now
//      continue;
//
//    // check for vector brackets first
//    } else if ((lineBuffer.find("wire\t[") != string::npos) || (lineBuffer.find("wire [") != string::npos)) {
//
//      // get the size of the vector, and the lsb number
//      size_t vectorSizeStart = lineBuffer.find("[");
//      size_t vectorSizeEnd = lineBuffer.find(":", vectorSizeStart);
//      size_t vectorInitalEnd = lineBuffer.find("]", vectorSizeEnd);
//
//      size_t nameEnd = lineBuffer.find("\t", vectorInitalEnd); // look for a tab
//      if(nameEnd == string::npos)
//        nameEnd = lineBuffer.find(" ", vectorInitalEnd); // look for a space
//
//      cout << "wire " << lineBuffer.substr(vectorSizeStart, (vectorSizeEnd-vectorSizeStart))
//           << lineBuffer.substr(vectorSizeEnd, (vectorInitalEnd-vectorSizeEnd))
//           << lineBuffer.substr(vectorInitalEnd) << endl;
//
//      // create and push the signal vector
//      // localSignalsVector.push_back(localSignals(name, "wire", lineBuffer.substr(vectorSizeStart, (vectorSizeEnd-vectorSizeStart))));
//
//
//
//    } else if ((lineBuffer.find("wire\t") != string::npos) ||
//              (lineBuffer.find("wire ") != string::npos)) {
//
//    } else {
//      //cout << "I don't know how to parse this:" << endl;
//      //cout << lineBuffer << endl;
//    }
//
//  } // end while()
//
//  return true;
//}
