/*
 * localSignals.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: james
 */

//#include "localSignals.h"
#include <localSignals.h>
#include <parserFunctions.h>

#include <string>

localSignals::localSignals() {
}

localSignals::~localSignals() {

}

const std::string& localSignals::getComment() const {
  return comment;
}

void localSignals::setComment(const std::string& comment) {
  this->comment = comment;
}

bool localSignals::isIsVectorType() const {
  return isVectorType;
}

void localSignals::setIsVectorType(bool isVectorType) {
  this->isVectorType = isVectorType;
}

const std::string& localSignals::getName() const {
  return name;
}

void localSignals::setName(const std::string& name) {
  this->name = name;
}

bool localSignals::isIsInlineAssignment() const {
  return isInlineAssignment;
}

void localSignals::setIsInlineAssignment(bool isInlineAssignment){
  this->isInlineAssignment = isInlineAssignment;
}

const std::string& localSignals::getSignalAssignment() const {
  return signalAssignment;
}

void localSignals::setSignalAssignment(const std::string& signalAssignment) {
  this->signalAssignment = signalAssignment;
}

const std::string& localSignals::getType() const {
  return type;
}

void localSignals::setType(const std::string& type) {
  this->type = type;
}

const std::string& localSignals::getVectorLsb() const {
  return vectorLsb;
}

void localSignals::setVectorLsb(const std::string& vectorLsb) {
  this->vectorLsb = vectorLsb;
}

const std::string& localSignals::getVectorMsb() const {
  return vectorMsb;
}

void localSignals::setVectorMsb(const std::string& vectorMsb) {
  this->vectorMsb = vectorMsb;
}

