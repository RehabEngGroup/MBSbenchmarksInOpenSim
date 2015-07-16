// This is part of
// Multi-Body Systems Benchmark in OpenSim (MBS-BOS)
// Copyright (C) 2013, 2014  Luca Tagliapietra Michele Vivian Monica Reggiani
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

#include <iostream>
    using std::cout;
    using std::endl;

#include "OpenSim/OpenSim.h"
#include "OpenSim/Simulation/Model/SystemEnergyProbe.h"
#include "simulationManager.h"
#include "configurationInterpreter.h"

int main(int argc, char **argv) {
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " Multi-Body System Benchmark in OpenSim" << endl;
  cout << " Benchmark reference url: http://lim.ii.udc.es/mbsbenchmark/" << endl;
  cout << " Problem A02: N Four-Bar Mechanism Simulator" << endl;
  cout << " Copyright (C) 2013, 2014  Luca Tagliapietra, Michele Vivian, Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;

  if (argc != 2){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body Systems Benchmark in Opensim: Simulator for Model A01" << endl;
    cout << " Usage: ./NFourBarMechanismSimulate dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }

  const std::string dataDir = argv[1];
  cout << "Input data directory: " << dataDir << endl;

  const std::string outputDir = dataDir+"/SimulationResults";
  const std::string integratorName = "RungeKuttaMerson";

  // Load the Opensim Model
  OpenSim::Model nFourBarMechanism((dataDir+"/40-FourBarMechanism.osim").c_str());

  // Add System Energy Reporter
  OpenSim::SystemEnergyProbe *energyProbe = new OpenSim::SystemEnergyProbe(true, true);
  energyProbe->setName("ener");
  energyProbe->setGain(1.0);
  energyProbe->setOperation("value");
  energyProbe->setComputeKineticEnergy(true);
  energyProbe->setComputePotentialEnergy(true);
  nFourBarMechanism.addProbe(energyProbe);
  OpenSim::ProbeReporter *energyReporter = new OpenSim::ProbeReporter(&nFourBarMechanism);
  energyReporter->setName(std::string("energyReporter"));
  std::cout << energyReporter->getName() << std::endl;
  nFourBarMechanism.addAnalysis(energyReporter);

  // Add Force Reporter
  OpenSim::ForceReporter *forceReporter = new OpenSim::ForceReporter(&nFourBarMechanism);
  forceReporter->setName(std::string("forceReporter"));
  nFourBarMechanism.addAnalysis(forceReporter);

  // Add Kinematics Reporter
  OpenSim::PointKinematics *pointKinematicsReporter = new OpenSim::PointKinematics(&nFourBarMechanism);
  pointKinematicsReporter -> setBodyPoint(std::string("Link_1"), SimTK::Vec3(0,0.5,0));
  pointKinematicsReporter->setName(std::string("pointKinematicsReporter"));
  pointKinematicsReporter ->setDescription("3d Kinematics of the point B0 (state_0 = X Displacement, state_1 = Y Displacement, state_2 = Z Displacement)");
  nFourBarMechanism.addAnalysis(pointKinematicsReporter);

  // Read the configuration Parameter File
  std::map<std::string, double> parametersMap;
  try{
    const std::string cfgFilename = (dataDir+"/simulationParameters.txt");
    configurationInterpreter cfg(cfgFilename.c_str());
    cfg.getMap(parametersMap);
  }
  catch (std::exception& e){
    std::cerr << e.what() << std::endl;
    return -1;
  }

  SimTK::State fakedInitialState;
  simulationManager manager(fakedInitialState, nFourBarMechanism, parametersMap, integratorName, outputDir);
  manager.simulate();

  cout << "Simulation results stored in: " << outputDir << endl;
}
