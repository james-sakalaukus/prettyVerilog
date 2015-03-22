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
    // the signal name
    std::string name;

    // the signal type - wire|reg|input|output
    std::string type;

    // if it is a vector, the MSB and LSB can be strings
    bool isVectorType;
    std::string vectorMsb;
    std::string vectorLsb;

    // the initial assignment value(if any) given to the signal
    bool isInlineAssignment;
    std::string signalAssignment;

    // the comment (if any) on the line
    std::string comment;


  public:
    localSignals();
    virtual ~localSignals();
    const std::string& getComment() const;
    void setComment(const std::string& comment);
    bool isIsVectorType() const;
    void setIsVectorType(bool isVectorType);
    const std::string& getName() const;
    void setName(const std::string& name);

    bool isIsInlineAssignment() const;
    void setIsInlineAssignment(bool isInlineAssignment);

    const std::string& getSignalAssignment() const;
    void setSignalAssignment(const std::string& signalAssignment);
    const std::string& getType() const;
    void setType(const std::string& type);
    const std::string& getVectorLsb() const;
    void setVectorLsb(const std::string& vectorLsb);
    const std::string& getVectorMsb() const;
    void setVectorMsb(const std::string& vectorMsb);
};

#endif /* LOCALSIGNALS_H_ */
