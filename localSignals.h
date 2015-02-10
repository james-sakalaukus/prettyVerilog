/*
 * localSignals.h
 *
 *  Created on: Feb 9, 2015
 *      Author: james
 */

#ifndef LOCALSIGNALS_H_
#define LOCALSIGNALS_H_

#include <fstream>
#include <string>

class localSignals {

  private:
    std::string name;
    std::string type;
    std::string vectorSize;
    int vectorInitial;

  public:
    localSignals();
    virtual ~localSignals();
    bool print(std::fstream &);
    bool setType(std::string);
    bool setVectorSize(std::string);
    bool setVectorInitial(int);
    std::string getType(void);
    std::string getVectorSize(void);
    int getVectorInitial(void);
};

#endif /* LOCALSIGNALS_H_ */
