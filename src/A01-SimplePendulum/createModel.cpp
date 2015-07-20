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
  cout << " Copyright (C) 2013-2015 Luca Tagliapietra, Michele Vivian, Elena Ceseracciu, and Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;

  if (argc != 2){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A01" << endl;
    cout << " Usage: ./SimplePendulumCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }

  const std::string dataDir = argv[1];
  cout << "Data directory:" + dataDir << endl;

  // Create model and set name and authors
  OpenSim::Model simplePendulum;
  simplePendulum.setName(modelName);
  simplePendulum.setAuthors("L.Tagliapietra, M. Vivian, M.Reggiani");

  // Get a reference to the model's ground body
  OpenSim::Body& ground = simplePendulum.getGroundBody();
  simplePendulum.setGravity(gravityVector);

  SimTK::Inertia pointInertia = SimTK::Inertia(0,0,0);
  OpenSim::Body *point = new OpenSim::Body("Point", pointMass, pointMassCenter, pointInertia);

  OpenSim::DisplayGeometry pointGeom(sphereGeometry);
  pointGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  pointGeom.setName("pointMass");
  point->updDisplayer()->updGeometrySet().insert(0,pointGeom);

  OpenSim::DisplayGeometry rodGeom(rodGeometry);
  rodGeom.setScaleFactors(SimTK::Vec3(0.01,pendulumLength,0.01));
  rodGeom.setName("rod");
  SimTK::Transform trans = SimTK::Transform(SimTK::Vec3(0,pendulumLength/2,0));
  rodGeom.setTransform(trans);
  point->updDisplayer()->updGeometrySet().insert(1,rodGeom);

  SimTK::Vec3 locationInParent(0), locationInBody(0, pendulumLength,0), orientationInParent(0), orientationInBody(0);

  OpenSim::PinJoint *thetaJoint = new OpenSim::PinJoint("theta", ground, locationInParent, orientationInParent, *point, locationInBody, orientationInBody);
  OpenSim::CoordinateSet& thetaCoordinateSet = thetaJoint -> upd_CoordinateSet();
  thetaCoordinateSet[0].setName("theta");
  thetaCoordinateSet[0].setDefaultValue(defaultAngle);
  simplePendulum.addBody(point);

  // Save to file the model
  simplePendulum.print((dataDir+"/"+modelName+std::string(".osim")).c_str());

  cout << "Model stored in: " << dataDir << "/" << modelName << ".osim" << endl;
}
