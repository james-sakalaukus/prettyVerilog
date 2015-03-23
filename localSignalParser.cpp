/*
 * localSignalParser.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: james
 */

#include <parserFunctions.h>

bool parseLocalSignals(std::ifstream &inputFile, std::vector<localSignals> &localSignalsVector) {


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

  //  match the signal type - required
  regExpression << "(output|input|wire|reg|parameter)" << whiteSpace;

  // match if it was an "output reg" declaration
  regExpression << "(reg|wire)?" << whiteSpace;

  // match if vector, can be zero match
  regExpression << "(\\[" << whiteSpace << "([\\w-]*)" << whiteSpace << ":";
  regExpression << whiteSpace << "([\\w-]*)" << whiteSpace << "\\])?";

  // Match the signal name
  regExpression << whiteSpace << "(\\w*)" << whiteSpace;

  // Match Inline initialization/assignment or end of signal declaration
  regExpression << "(=|;|,)";

  // Match if assignment value
  // TODO: remove the whitespaces/tabs from the assignment value
  regExpression << "([\\[\\]\\s\\w:']*)?" << whiteSpace;

  // remove the semicolon after the assignment
  regExpression << "(;)?" << whiteSpace;

  // Match if comment at end of line
  regExpression << "(\\/\\/[\\w\\s]*)?";

  regExpression << "(.*)$";



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
  std::string line;

  // for making objects yo
  localSignals *ls;

  // walk through each line of the file
  // TODO: what if there is a newline before a semicolon?

  while(!inputFile.eof()) {
    std::getline(inputFile, line);

    // iterators for file line passed to boost regex
    std::string::const_iterator start, end;
    start = line.begin();
    end = line.end();

    // stop parsing before the next module (usually a testbench)
    // TODO: what if this is not a testbench?
    if(line.find("endmodule") != std::string::npos) {
      return true;
    }

    if(regex_search(start, end, matches, re, flags)) {

      // if we get here, then we have a successful match
      ls = new localSignals();

      logFile << "Matched string: " << matches[0] << std::endl;

      logFile << "\tI/O/reg/wire type: \"" << matches[1] << " " << matches[2] << "\"" << std::endl;

      if(matches[2] == "reg") {
        ls->setIsRegisteredOutput(true);
        ls->setType(std::string(matches[1]+" "+matches[2]));

        // remove the word 'wire' after 'output'
      } else if(matches[2] == "wire") {
        ls->setIsRegisteredOutput(false);
        ls->setType(matches[1]);
      } else {
        ls->setIsRegisteredOutput(false);
        ls->setType(matches[1]);
      }

      if(matches[3].matched) {
        logFile << "\tVector type, " << " MSB: " << matches[4] << " LSB: " << matches[5] << std::endl;
        ls->setIsVectorType(true);
        ls->setVectorMsb(matches[4]);
        ls->setVectorLsb(matches[5]);

      } else {
        logFile << "\tNot a vector type" << std::endl;
        ls->setIsVectorType(false);
      }

      logFile << "\tsignal name: " << matches[6] << std::endl;
      ls->setName(matches[6]);

      if(matches[7] == ";" || matches[7] == ",") {
        logFile << "\tNo inline assignment" << std::endl;
      } else {
        logFile << "\tassignment value: " << matches[8] << std::endl;
        ls->setIsInlineAssignment(true);
        ls->setSignalAssignment(matches[8]);
      }

      if(matches[9].matched) {
        logFile << "\tComment is: " << matches[10] << std::endl;
        ls->setComment(matches[10]);
      } else {
        logFile << "\tNo inline comment" << std::endl;
      }
      logFile << std::endl;

      localSignalsVector.push_back(*ls);
    }
  }
  return true;
}


