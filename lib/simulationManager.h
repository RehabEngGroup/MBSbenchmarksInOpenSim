// This is part of
// Multi-Body Systems Benchmark in OpenSim (MBS-BOS)
// Copyright (C) 2013, 2014 Luca Tagliapietra Michele Vivian Monica Reggiani
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

#ifndef simulationManager_h
#define simulationManager_h

#include <OpenSim/OpenSim.h>

class simulationManager{
public:
  simulationManager(SimTK::State& initialStateFaked, OpenSim::Model & model, const std::map <std::string, double> parametersMap, const std::string integratorName, const std::string outDir);
  void simulate();
  double getParameter(std::string key) const;

private:
  void setParameters();
  void initializeState();
  void saveSimulationResults(const OpenSim::Manager& manager);  

  double initialTime_;
  double finalTime_;
  double accuracy_;
  double tolerance_;
  double minStepSize_;
  double maxStepSize_;

  std::map <std::string, double> parametersMap_;
  SimTK::State& initialState_;
  OpenSim::Model osimModel_;
  std::string integratorName_;
  std::string outDir_;
};


#endif
