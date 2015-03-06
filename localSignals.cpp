/*
 * localSignals.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: james
 */

#include "localSignals.h"
#include <string>

localSignals::localSignals() : name("unnamedVariable"), type("wire"), vectorSize("0"), vectorInitial(0) {
}

localSignals::localSignals(std::string n, std::string t, std::string vs, int vi) : name(n), type(t), vectorSize(vs), vectorInitial(vi) {
}

localSignals::~localSignals() {
}

bool localSignals::print(std::fstream &out){
  if(vectorSize == "0") {
    out << "  " << type << " " << name << ";\n";
  } else {
    out << "  " << type << " [" << vectorSize << ":" << vectorInitial << "] " << name << ";\n";
  }
  return true;
}


bool localSignals::setType(std::string ls){
  type = ls;
  return true;
}
bool localSignals::setVectorSize(std::string ls){
  vectorSize = ls;
  return true;
}
bool localSignals::setVectorInitial(int li){
  vectorInitial = li;
  return true;
}

std::string localSignals::getType(void){
  return type;
}
std::string localSignals::getVectorSize(void){
  return vectorSize;
}
int localSignals::getVectorInitial(void){
  return vectorInitial;
}
