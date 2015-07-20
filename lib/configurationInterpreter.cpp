// This is part of
// Multi-Body Systems Benchmark in OpenSim (MBS-BOS)
// Copyright (C) 2013-2015 Luca Tagliapietra, Michele Vivian, Elena Ceseracciu, and Monica Reggiani
//
// MBS-BOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MBS-BOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MBS-BOS.  If not, see <http://www.gnu.org/licenses/>.
//
// The authors may be contacted via:
// email: tagliapietra@gest.unipd.it

#include <fstream>
#include <map>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>

#include "configurationInterpreter.h"

namespace patch{
  double to_double(const std::string numString){
    double val = 0;
    std::stringstream stm(numString);
    stm >> val;
    return val;
  }
}

//***************************************************
//    Public Constructors
//***************************************************

configurationInterpreter::configurationInterpreter(const char* filename, const char fieldSeparator){
  using namespace std;
  fstream file(filename, ios::in);
  if (file){
    string line;
    while (getline(file, line)){
      size_t sep = line.find_first_of(fieldSeparator);
      if (sep != string::npos){
        string key   = trim(line.substr(0, sep));
        string value = trim(line.substr(sep + 1));
        if (!key.empty() && !value.empty())
          configItems_[key] = patch::to_double(value);
        else
          throw runtime_error("Error within configuration file.");
      }
      else
        throw runtime_error("Error within configuration file.");
    }
  }
  else
    throw runtime_error("Cannot open config file.");
}



//***************************************************
//    Public Accessor Functions
//***************************************************

void configurationInterpreter::getMap(std::map<std::string, double> & newMap){
  newMap = configItems_;
}


double configurationInterpreter::getValue(const std::string& key) const {
  std::map<std::string, double>::const_iterator it = configItems_.find(key);
  if (it != configItems_.end())
    return it->second;
  else
    throw std::runtime_error("Cannot find config item.");
}


//***************************************************
//    Private Functions
//***************************************************

std::string configurationInterpreter::trim(std::string str) {
  size_t pos = str.find_first_not_of(" \t\n");
  if (pos != std::string::npos)
    str.erase(0, pos);
  pos = str.find_last_not_of(" \t\n");
  if (pos != std::string::npos)
    str.erase(pos + 1);
  return str;
}
