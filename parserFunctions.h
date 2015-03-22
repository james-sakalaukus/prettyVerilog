/*
 * parserFunctions.h
 *
 *  Created on: Mar 22, 2015
 *      Author: james
 */

#ifndef PARSERFUNCTIONS_H_
#define PARSERFUNCTIONS_H_

#include <fstream>
#include <iterator>
#include <boost/regex.hpp>
#include <sstream>
#include <fstream>
#include <vector>

#include <localSignals.h>

// forward declarations
bool parseModuleName(std::ifstream &inputFile, std::string &moduleName);
bool parseLocalSignals(std::ifstream &inputFile, std::vector<localSignals> &localSignalsVector);




#endif /* PARSERFUNCTIONS_H_ */
