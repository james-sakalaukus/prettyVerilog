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
//using namespace boost;


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




  cout << "Calling: parseLocalSignals()" << endl;
  vector<localSignals> localSignalsVector;
  parseLocalSignals(inputFile, localSignalsVector);
  cout << "Returned from parseLocalSignals()" << endl;

//  while(!inputFile.eof()) {
//    getline(inputFile, lineBuffer);
//    parseLocalSignals(lineBuffer, localSignalsVector);
//  }


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




  // print all local signals/registers

  // print all static assignments

  // print all parameters

  // print all module instantiations

  // print always blocks with comments around each



  outputFile.close();
  inputFile.close();
  return 0;
}




bool parseLocalSignals(ifstream &inputFile, vector<localSignals> &localSignalsVector) {



  // match structure from boost library
  boost::match_results<std::string::const_iterator> matches;
  boost::match_flag_type flags = boost::match_default;

  // used to build up the regular expression
  stringstream regExpression;

  // whitespaces are everywhere!!
  string whiteSpace = "\\s*";

  string arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;

  /* Example crappy code:
   *  output reg      e_rd_stb=rd_1_every_3_sr[2]&&(rx_opcode==OP_READ)&&OUT_TICK; // comment
   */

  regExpression << "^" << whiteSpace;

   //  arg1: match if line is an input/output declaration
  regExpression << "(output|input|wire|reg)" << whiteSpace;


  // arg2: match the signal type
//  regExpression << "(wire|reg)";

  // arg3,4,5: match if vector, can be zero match
//  arg3 = "(\\[\\s*([\\w-]*)\\s*:\\s*(\\w*)\\s*\\])?";
  regExpression << "(\\[" << whiteSpace << "([\\w-]*)" << whiteSpace << ":";
  regExpression << whiteSpace << "([\\w-]*)" << whiteSpace << "\\])?";

//  // arg6: The vector MSB could be a string with addition/subtraction and/or numbers
//  regExpression << "([\\w-]*)";
//
//  // arg7: LSB could be a string with addition/subtraction and/or numbers
//  regExpression << "([\\w-]*)";

  // arg8: Match the signal name
  regExpression << whiteSpace << "(\\w*)" << whiteSpace;

  // arg9 Match Inline initialization/assignment or end of signal declaration
  regExpression << "(=|;|,)";

  // arg8: Match if assignment value
  regExpression << "([\\[\\]\\s\\w:]*)?" << whiteSpace;

  regExpression << "(;)?" << whiteSpace;

  // arg10: Match if comment at end of line
  regExpression << "(\\/\\/[\\w\\s]*)?";

//  regExpression << "(.*)$";



  //OLD
//  regExpression << "^" << whiteSpace
//                << arg1 << whiteSpace
//                << arg2 << whiteSpace
//                << "(\\[\\s*([\\w-]*)\\s*:\\s*(\\w*)\\s*\\])?" << "\\s*"
//                << "(\\w*)" << whiteSpace
//                << "(=)?" << whiteSpace
//                << "([^;,]*)" << whiteSpace
////                << "([\\[\\]\\s\\w:]*)" << "\\s*"
//                << "(;|,)?" << whiteSpace
//                << "(\\/\\/[\\w\\s]*)?" << whiteSpace
//                << "(.*)$";

  // make the boost regular expression
  boost::regex re(regExpression.str());
  string line;

  // walk through each line of the file
  // TODO: what if there is a newline before a semicolon?  fixme
  if(!inputFile.is_open()) {
    cout << "Did not open the input file" << endl;
  }

  while(!inputFile.eof()) {
	  getline(inputFile, line);

	  // iterators for file line passed to boost regex
	  std::string::const_iterator start, end;
	  start = line.begin();
	  end = line.end();

	  if(regex_search(start, end, matches, re, flags)) {

      cout << "Matched string: " << matches[0] << endl;

      if(matches[1].matched)
        cout << "\tI/O/reg/wire type: " << matches[1] << endl;

  //		cout << "\treg/wire type: " << matches[2] << endl;

      if(matches[2].matched) {
        cout << "\tVector type, " << " MSB: " << matches[3] << " LSB: " << matches[4] <<endl;
      }

      cout << "\tsignal name: " << matches[5] << endl;

  //		cout << "\tArg 6: " << matches[6] << endl;

      if(matches[6] == ";" || ",") {
        cout << "\tNo inline assignment" << endl;
      } else {
        cout << "\tassignment value: " << matches[7] << endl;
      }

      if(matches[9].matched) {
        cout << "\tComment is: " << matches[9] << endl;
      }
      cout << endl;
	  }
  }
  return true;
}
