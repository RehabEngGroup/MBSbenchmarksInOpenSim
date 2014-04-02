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

int main(int argc, char **argv) {
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " Multi-Body System Benchmark in OpenSim" << endl;
  cout << " Benchmark reference url: http://lim.ii.udc.es/mbsbenchmark/" << endl;
  cout << " Problem A01: Simple Pendulum Mechanism Model Creator" << endl;
  cout << " v. 1.0  Mar 2014" << endl;
  cout << " Copyright (C) Luca Tagliapietra, Michele Vivian, Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  
  if (argc < 1){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A01" << endl;
    cout << " Usage: ./SimplePendulumCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }
  
  const std::string dataDir = argv[1];
  cout << "Starting modelling process using data directory:" + dataDir << endl;

  // Create model and set name and authors
  OpenSim::Model simplePendulum;
  simplePendulum.setName(modelName);
  simplePendulum.setAuthors("L.Tagliapietra, M. Vivian, M.Sartori, M.Reggiani");
  
  // Get a reference to the model's ground body
  OpenSim::Body& ground = simplePendulum.getGroundBody(); 
  simplePendulum.setGravity(gravityVector);

  SimTK::Inertia pointInertia = SimTK::Inertia(0,0,0);
  OpenSim::Body *point = new OpenSim::Body("Point", pointMass, pointMassCenter, pointInertia);
  
  OpenSim::DisplayGeometry geom1(sphereGeometry);
  geom1.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  geom1.setName("sphere");
  point->updDisplayer()->updGeometrySet().insert(0,geom1);  
  
  OpenSim::DisplayGeometry geom2(rodGeometry);
  geom2.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  geom2.setName("rod");
  SimTK::Transform trans = SimTK::Transform(SimTK::Vec3(0,pendulumLength/2,0));
  geom2.setTransform(trans);
  point->updDisplayer()->updGeometrySet().insert(1,geom2);  
 
  SimTK::Vec3 locationInParent(0), locationInBody(0, pendulumLength,0), orientationInParent(0), orientationInBody(0);
  
  OpenSim::PinJoint *aJoint = new OpenSim::PinJoint("theta", ground, locationInParent, orientationInParent, *point, locationInBody, orientationInBody); 
  OpenSim::CoordinateSet& aCoordinateSet = aJoint -> upd_CoordinateSet();
  aCoordinateSet[0].setName("theta");
  aCoordinateSet[0].setDefaultValue(defaultAngle);
  simplePendulum.addBody(point);

  cout << "Model creation process ends" << endl;
  
  // Save to file the model
  cout << "Model saving to file process starts" << endl;
  simplePendulum.print((dataDir+"/"+modelName+std::string(".osim")).c_str());
  cout << "Model saving to file process ends" << endl;
}

