/*
 * parserFunctions.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: james
 */

#include <parserFunctions.h>

bool parseModuleName(std::ifstream &inputFile, std::string &moduleName){

  std::ofstream logFile("parseLocalSignalLog.txt");

  // match structure from boost library
  boost::match_results<std::string::const_iterator> matches;
  boost::match_flag_type flags = boost::match_default;

  // used to build up the regular expression
  std::stringstream regExpression;

  // whitespaces are everywhere!!
  std::string whiteSpace = "\\s*";

  /* Example crappy code:
   *  output reg      e_rd_stb=rd_1_every_3_sr[2]&&(rx_opcode==OP_READ)&&OUT_TICK; // comment
   */

  regExpression << "^" << whiteSpace;

   //  match the module type - required
  regExpression << "(module)" << whiteSpace;

  // Match the module name
  regExpression << whiteSpace << "(\\w*)" << whiteSpace;

  // Match the trailing open paren
  regExpression << "(\\()" << whiteSpace;

  regExpression << "(.*)$";

  // make the boost regular expression
  boost::regex re(regExpression.str());
  std::string line;

  while(!inputFile.eof()) {
    std::getline(inputFile, line);

    // iterators for file line passed to boost regex
    std::string::const_iterator start, end;
    start = line.begin();
    end = line.end();

    if(regex_search(start, end, matches, re, flags)) {
      moduleName = matches[2];
      return true;
    }
  }
  return false;
}


