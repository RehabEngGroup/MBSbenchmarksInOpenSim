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

#include <OpenSim/OpenSim.h>
#include <map>
#include <iostream>
using std::cout;
using std::endl;

#include "simulationManager.h"

//***************************************************
//    Public Constructors
//***************************************************

simulationManager::simulationManager(SimTK::State& fakedInitialState, OpenSim::Model& model, const std::map <std::string, double> parametersMap, const std::string integratorName, const std::string outDir)
:osimModel_(model), initialState_(fakedInitialState), parametersMap_(parametersMap), integratorName_(integratorName), outDir_(outDir){
  setParameters();
  initializeState();
}

//***************************************************
//    Public Functions
//***************************************************

double simulationManager::getParameter(std::string key) const {
  std::map<std::string, double>::const_iterator it = parametersMap_.find(key);
  return it->second;
}

void simulationManager::simulate() {
  // Create the integrator
  SimTK::Integrator* integrator;
  if (!integratorName_.compare(std::string("CPodes"))){
    integrator = new SimTK::CPodesIntegrator(osimModel_.getMultibodySystem(), SimTK::CPodes::BDF);
    std::cout << "Using CPodes integrator" << std::endl;
  }
  else if (!integratorName_.compare(std::string("RungeKuttaMerson"))){
    integrator = new SimTK::RungeKuttaMersonIntegrator(osimModel_.getMultibodySystem());
    std::cout << "Using RungeKuttaMerson integrator" << std::endl;
  }
  else {
    integrator =new SimTK::RungeKuttaFeldbergIntegrator(osimModel_.getMultibodySystem());
    std::cout << "Using RungeKuttaFeldberg integrator" << std::endl;
  }

  //integrator->setMinimumStepSize(minStepSize_);
  integrator->setMaximumStepSize(maxStepSize_);
  integrator->setAccuracy(accuracy_);
  integrator->setConstraintTolerance(tolerance_);
  integrator->setProjectEveryStep(true);
  integrator->setInternalStepLimit(internalStepLimit_);

  // Set number of decimal digits for output files
  OpenSim::IO::SetPrecision(15);

#ifndef MBS_BOS_USE_SIMULATION_MANAGER
  cout << "Working with Simbody TimeStepper & Co." << endl;

  SimTK::TimeStepper stepper(osimModel_.getMultibodySystem(), *integrator);
  stepper.initialize(initialState_);

  std::clock_t startTime = clock();

  std::vector<SimTK::State> states;
  std::vector<double> times;
  int step = 0;
  for (double time = initialTime_; stepper.getTime() < finalTime_ ; time = time + reportingStep_) {
    times.push_back(time);
    stepper.stepTo(time);
    osimModel_.updAnalysisSet().step(stepper.getState(), step);
    states.push_back(stepper.getState());
    step++;
  }

  cout << "Integrate routine time = " << 1.e3*(clock()-startTime)/CLOCKS_PER_SEC << " ms" << endl;
  cout << "The maximum allowed error was " << integrator->getAccuracyInUse();
  cout << " measured with " << integrator->getNumStepsTaken() << " output steps and";
  cout << " a treshold value of " << integrator->getAccuracyInUse() << endl;

  saveSimulationResults(states, times);

#else
    // Create the manager for the integrator
    OpenSim::Manager manager(osimModel_, *integrator);

    // Integrate from initial time to final time
    manager.setInitialTime(initialTime_);
    manager.setFinalTime(finalTime_);

    cout << "\n\nIntegrating from " << initialTime_ << " to " << finalTime_ << endl;

    std::clock_t startTime = clock();
    manager.integrate(initialState_);

    cout << "Integrate routine time = " << 1.e3*(clock()-startTime)/CLOCKS_PER_SEC << " ms" << endl;
    cout << "The maximum allowed error was " << integrator->getAccuracyInUse();
    cout << " measured with " << integrator->getNumStepsTaken() << " output steps and";
    cout << " a treshold value of " << integrator->getAccuracyInUse() << endl;

    saveSimulationResults(manager);
#endif
}


//***************************************************
//    Private Functions
//***************************************************

void simulationManager::setParameters(){
  initialTime_ = parametersMap_.find("Initial Time")->second;
  finalTime_   = parametersMap_.find("Final Time")->second;
  accuracy_    = parametersMap_.find("Accuracy")->second;
  tolerance_   = parametersMap_.find("Tolerance")->second;
  minStepSize_ = parametersMap_.find("Minimum Step Size")->second;
  maxStepSize_ = parametersMap_.find("Maximum Step Size")->second;
	internalStepLimit_ = parametersMap_.find("Internal Step Limit")->second;
	reportingStep_ = parametersMap_.find("Reporting Step")->second;
}

void simulationManager::initializeState() {
  initialState_ = osimModel_.initSystem();
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Position);
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Velocity);
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Acceleration);
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Report);
}

void simulationManager::saveSimulationResults(const OpenSim::Manager& manager){
  // Save the model to a file: now we save the modified model
  std::cout<<"Saving files..."<<std::endl;
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Report);

  OpenSim::Storage statesRadians(manager.getStateStorage());
  OpenSim::Storage::printResult(&statesRadians, "states", outDir_, reportingStep_, ".sto");

	OpenSim::Storage statesDegrees(manager.getStateStorage());
	osimModel_.updSimbodyEngine().convertRadiansToDegrees(statesDegrees);
  statesDegrees.setWriteSIMMHeader(true);
	OpenSim::Storage::printResult(&statesDegrees, "statesDeg", outDir_, reportingStep_, ".sto");

  // Save the Point Kinematic Position
	osimModel_.updAnalysisSet().get("pointKinematicsReporter").printResults("pointKinematics", outDir_, reportingStep_);

  // Save the Point Kinematic Position
  osimModel_.updAnalysisSet().get("energyReporter").printResults("energy", outDir_, reportingStep_);

  // Save the forces
	osimModel_.updAnalysisSet().get("forceReporter").printResults("forces", outDir_, reportingStep_);
}

void simulationManager::saveSimulationResults(const std::vector<SimTK::State> states,const std::vector<double> times ){
  OpenSim::StateVector stateVector;
  OpenSim::Storage stateStorage;

  //  ***  Uncomment to get in-depth logging of system energy  -  1 of 3
  //  OpenSim::Storage energyStorage;
  //  OpenSim::Array<std::string> energyLabels;
  //  energyLabels.append("Time");
  //  energyLabels.append("KinEnergy");
  //  energyLabels.append("PotEnergy");
  //  energyLabels.append("TotalEnergy");
  //  energyStorage.setColumnLabels(energyLabels);

  for (int i = 0; i<times.size(); i++){
    OpenSim::Array<double> stateValues;
    osimModel_.getMultibodySystem().realize(states.at(i), SimTK::Stage::Report);
    osimModel_.getStateValues(states.at(i), stateValues);
    stateVector.setStates(times.at(i), stateValues.getSize(), &stateValues[0]);
    stateStorage.append(stateVector);

    //  ***  Uncomment to get in-depth logging of system energy  -   2 of 3
    //  SimTK::Real kinEnergy = osimModel_.getMultibodySystem().calcKineticEnergy(states.at(i));
    //  SimTK::Real potEnergy = osimModel_.getMultibodySystem().calcPotentialEnergy(states.at(i));
    //  OpenSim::Array<double> tmpEnergy(3);
    //  tmpEnergy.set(0, kinEnergy);
    //  tmpEnergy.set(1, potEnergy);
    //  tmpEnergy.set(2, kinEnergy+potEnergy);
    //  energyStorage.append(times.at(i), tmpEnergy);
  }

  //  ***  Uncomment to get in-depth logging of system energy   -   3 of 3
  //  energyStorage.print(outDir_+"/DetailedSystemEnergy.sto");

  // Save system States
  stateStorage.print(outDir_+"/StateStorage.sto");

  // Save Point Kinematics
  osimModel_.updAnalysisSet().get("pointKinematicsReporter").printResults("pointKinematics", outDir_, reportingStep_);

  // Save System Energy
  osimModel_.updAnalysisSet().get("energyReporter").printResults("energy", outDir_, reportingStep_);

  // Save Forces
  osimModel_.updAnalysisSet().get("forceReporter").printResults("forces", outDir_, reportingStep_);
}
