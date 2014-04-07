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

#include <string>
#include <iostream>
  using std::cout;
  using std::endl;
#include <vector>
  using std::vector;

#include <OpenSim/OpenSim.h>
#include "modelProperties.h"

namespace patch{
  template <typename T> std::string to_string(const T& n){
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

//********************************************************************************
// Utility function to create bar elements

void createBar(OpenSim::Model &aModel, std::string bodyName, std::string jointName, double barMass, double barLength, OpenSim::Body &parentBody, SimTK::Vec3 locationInParent, SimTK::Vec3 locationInBody, double defaultSpeed, bool isHorizontal){
  SimTK::Vec3 barMassCenter(0);
  SimTK::Inertia barInertia;
  if (isHorizontal)
    barInertia = barMass*SimTK::Inertia::cylinderAlongX(0, barLength/2);
  else
    barInertia = barMass*SimTK::Inertia::cylinderAlongY(0, barLength/2); 
  OpenSim::Body *aBody = new OpenSim::Body(bodyName, barMass, barMassCenter, barInertia);
  
  aBody->addDisplayGeometry("cylinder.vtp");
  OpenSim::VisibleObject* vis = aBody->updDisplayer(); 
  if (isHorizontal){
    SimTK::Rotation rot(SimTK::Pi/2, SimTK::UnitVec3(0,0,1));
    SimTK::Transform trans = SimTK::Transform(rot);
    vis -> updTransform() =  trans;
  }
  vis -> setScaleFactors(SimTK::Vec3(0.05, 1, 0.05));
  
  SimTK::Vec3 orientationInParent(0), orientationInBody(0);
  OpenSim::PinJoint *aJoint = new OpenSim::PinJoint(jointName, parentBody, locationInParent, orientationInParent, *aBody, locationInBody, orientationInBody); 
  OpenSim::CoordinateSet& aCoordinateSet = aJoint -> upd_CoordinateSet();
  aCoordinateSet[0].setName(jointName);
  aCoordinateSet[0].setDefaultValue(0);
  aCoordinateSet[0].setDefaultSpeedValue(defaultSpeed);
  aModel.addBody(aBody);
}

void createPointCostraint(OpenSim::Model &aModel, std::string parentBodyName, SimTK::Vec3 locationInParent, std::string childBodyName, SimTK::Vec3 locationInChild ){
  OpenSim::PointConstraint *costr = new OpenSim::PointConstraint(aModel.updBodySet().get(parentBodyName), locationInParent, aModel.updBodySet().get(childBodyName), locationInChild);
  costr->setName(childBodyName+"To"+parentBodyName);
  aModel.addConstraint(costr);
}

int main(int argc, char **argv) {
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " Multi-Body System Benchmark in OpenSim" << endl;
  cout << " Benchmark reference url: http://lim.ii.udc.es/mbsbenchmark/" << endl;
  cout << " Problem A02: N Four-Bar Mechanism Model Creator" << endl;
  cout << " v. 1.0  Mar 2014" << endl;
  cout << " Copyright (C) Luca Tagliapietra, Michele Vivian, Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  
  if (argc < 1){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A02" << endl;
    cout << " Usage: ./NFourBarMechanismCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }
  
  const std::string dataDir = argv[1];
  cout << "Starting modelling process using data directory:" + dataDir << endl;
  
  OpenSim::Model nFourBarMechanism;
  nFourBarMechanism.setName(modelName);
  nFourBarMechanism.setAuthors("L.Tagliapietra, M. Vivian, M.Sartori, M.Reggiani");
  
  // Get a reference to the model's ground body
  OpenSim::Body& ground = nFourBarMechanism.getGroundBody(); 
  nFourBarMechanism.setGravity(gravityVector);

  createBar(nFourBarMechanism,linkNamePrefix + patch::to_string(1), "A0",barMass, barLength, ground, SimTK::Vec3(0), SimTK::Vec3(0,-barLength/2,0), defaultSpeed, false);
  
    // Create all the other bars and set the point costraints (joints that close the loop)
  for (int i = 0; i<nWindow*2; i+=2) {
    createBar(nFourBarMechanism, linkNamePrefix+patch::to_string(i+2),fakeJointNamePrefix+patch::to_string(i/2), barMass, barLength,
      nFourBarMechanism.updBodySet().get(linkNamePrefix+patch::to_string(i+1)),SimTK::Vec3(0,barLength/2,0), SimTK::Vec3(-barLength/2, 0,0), -defaultSpeed, true);  
    createBar(nFourBarMechanism, (linkNamePrefix+patch::to_string(i+3)), realJointNamePrefix+patch::to_string(i/2+1), barMass, barLength,
      nFourBarMechanism.updBodySet().get(linkNamePrefix+patch::to_string(i+2)), SimTK::Vec3(barLength/2,0,0), SimTK::Vec3(0,barLength/2,0), defaultSpeed, false);    
    createPointCostraint(nFourBarMechanism, "ground", SimTK::Vec3(i/2+1,0,0), linkNamePrefix+patch::to_string(i+3), SimTK::Vec3(0,-barLength/2,0));
  };
  
  cout << "Model creation process ends" << endl;
  
  // Save to file the model
  cout << "Model saving to file process starts" << endl;
  nFourBarMechanism.print((dataDir+"/"+modelName+std::string(".osim")).c_str());
  cout << "Model saving to file process ends" << endl;
}
