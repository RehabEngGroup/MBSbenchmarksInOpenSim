// This is part of
// Multi-Body Systems Benchmark in OpenSim (MBS-BOS)
// Copyright (C) 2014 Luca Tagliapietra Michele Vivian Monica Reggiani
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

#ifndef configurationInterpreter_h
#define configurationInterpreter_h

#include <OpenSim/OpenSim.h>

class configurationInterpreter
{
  public:
    configurationInterpreter(const char* filename, const char fieldSeparator = ':');
    double getValue(const std::string& key) const;
    void getMap(std::map<std::string, double> & newMap);
  private:
    std::string trim(std::string str);
    std::map<std::string, double> configItems_;
};

#endif
