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
  std::clock_t startTime = clock();
  SimTK::Integrator* integrator;
  // Create the integrator
  if (!integratorName_.compare(std::string("RungeKuttaMerson")))
    integrator = new SimTK::RungeKuttaMersonIntegrator(osimModel_.getMultibodySystem());
  else //if(!integratorName_.compare(std::string("RungeKuttaFeldberg")))
      integrator =new SimTK::RungeKuttaFeldbergIntegrator(osimModel_.getMultibodySystem());
  
  integrator->setMinimumStepSize(minStepSize_);
  integrator->setMaximumStepSize(maxStepSize_);
  integrator->setAccuracy(accuracy_);
  integrator->setConstraintTolerance(tolerance_);
  integrator->setProjectEveryStep(true);
  
  // Create the manager for the integrator
  OpenSim::Manager manager(osimModel_, *integrator);
  
  // Integrate from initial time to final time
  manager.setInitialTime(initialTime_);
  manager.setFinalTime(finalTime_);
  
  cout << "\n\nIntegrating from " << initialTime_ << " to " << finalTime_ << endl;
  
  manager.integrate(initialState_);
  
  cout << "Integrate routine time = " << 1.e3*(clock()-startTime)/CLOCKS_PER_SEC << " ms" << endl;
  cout << "The maximum allowed error was " << integrator->getAccuracyInUse();
  cout << " measured with " << integrator->getNumStepsTaken() << " output steps and";
  cout << " a treshold value of " << integrator->getAccuracyInUse() << endl;

  saveSimulationResults(manager);
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
}

void simulationManager::initializeState() {
  initialState_ = osimModel_.initSystem();
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Position);
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Velocity);
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Acceleration);
}

void simulationManager::saveSimulationResults(const OpenSim::Manager& manager){
  // Save the model to a file: now we save the modified model 
  cout<<"Saving files..."<<endl;
  osimModel_.getMultibodySystem().realize(initialState_, SimTK::Stage::Position);
  
  OpenSim::Storage statesDegrees(manager.getStateStorage());
  OpenSim::Storage statesRadians(manager.getStateStorage());
  statesDegrees.print(outDir_ + "/StatesResults.sto");
  osimModel_.updSimbodyEngine().convertRadiansToDegrees(statesDegrees);
 
  statesDegrees.setWriteSIMMHeader(true);
  statesDegrees.print(outDir_ + "/StatesResults_Degree.mot");
  
  // Save the Point Kinematic Position
  OpenSim::Analysis &tmp = const_cast<OpenSim::Analysis&>(osimModel_.getAnalysisSet().get(std::string("pointKinematicsReporter")));
  OpenSim::PointKinematics* pointKinematicReporter=dynamic_cast<OpenSim::PointKinematics*>(&tmp);
  pointKinematicReporter->getPositionStorage()->print(outDir_+"/pointKinematicsPositionResults.mot");
  
  // Save the forces
  OpenSim::Analysis &tmp2 = const_cast<OpenSim::Analysis&>(osimModel_.getAnalysisSet().get(std::string("forceReporter")));
  OpenSim::ForceReporter* forceReporter = dynamic_cast<OpenSim::ForceReporter*>(&tmp2);
  forceReporter->getForceStorage().print(outDir_ + "/forcesResults.mot");
}
