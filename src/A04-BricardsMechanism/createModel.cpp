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

namespace patch{
  template <typename T> std::string to_string(const T& n){
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

void createBar(OpenSim::Model &aModel, std::string bodyName, std::string jointName, double barMass, SimTK::Vec3 barMassCenter, double barLength, OpenSim::Body &parentBody,
               SimTK::Vec3 locationInParent, SimTK::Vec3 orientationInParent, SimTK::Vec3 locationInBody, SimTK::Vec3 orientationInBody, double defaultAngle,int index, int rotationAxis, SimTK::Vec3 graficTranslation, SimTK::Rotation graficRotation){
  SimTK::Inertia barInertia;
  if (rotationAxis==1)
    barInertia = barMass*SimTK::Inertia::brick(barLength/2, crossSectionLength/2, crossSectionLength/2);
  else if (rotationAxis==2)
    barInertia = barMass*SimTK::Inertia::brick(crossSectionLength/2, barLength/2, crossSectionLength/2);
    else
      barInertia = barMass*SimTK::Inertia::brick(crossSectionLength/2, crossSectionLength/2, barLength/2);

  OpenSim::Body *aBody = new OpenSim::Body(bodyName, barMass, barMassCenter, barInertia);

  OpenSim::DisplayGeometry geom2(rodGeometry);
  geom2.setScaleFactors(SimTK::Vec3(0.1,barLength,0.1));
  geom2.setName(bodyName);
  SimTK::Transform rotoTrans = SimTK::Transform(graficRotation, graficTranslation);
  geom2.setTransform(rotoTrans);
  aBody->updDisplayer()->updGeometrySet().insert(0,geom2);

  OpenSim::DisplayGeometry jointGeom(jointGeometry);
  jointGeom.setScaleFactors(SimTK::Vec3(0.2,0.4,0.2));
  jointGeom.setName(std::string("PinJoint"));
  if (index==0){
    SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(0, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(-barLength/2,0,0));
    jointGeom.setTransform(rotoTrans);
  }
  else if (index == 1){
    SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0,barLength/2,0));
    jointGeom.setTransform(rotoTrans);
  }
    else if (index==2){
      SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(0,0,1)), SimTK::Vec3(0,0,-barLength/2));
      jointGeom.setTransform(rotoTrans);
    }
    else if (index==3){
      SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(0, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(barLength/2,0,0));
      jointGeom.setTransform(rotoTrans);
    }
    else if (index==4){
      SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0,-barLength/2,0));
      jointGeom.setTransform(rotoTrans);
    }
    else if (index ==5){
      SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(0,0,1)), SimTK::Vec3(0,barLength/2,0));
      jointGeom.setTransform(rotoTrans);
    }
  aBody->updDisplayer()->updGeometrySet().insert(1,jointGeom);

  OpenSim::PinJoint *aJoint = new OpenSim::PinJoint(jointName, parentBody, locationInParent, orientationInParent, *aBody, locationInBody, orientationInBody);
  OpenSim::CoordinateSet& aCoordinateSet = aJoint -> upd_CoordinateSet();

  aCoordinateSet[0].setName(jointName);
  aCoordinateSet[0].setDefaultValue(defaultAngle);
  //aCoordinateSet[0].setDefaultSpeedValue(defaultSpeed);
  aModel.addBody(aBody);
  }


void createWeldCostraint(OpenSim::Model &aModel, std::string parentBodyName, SimTK::Vec3 locationInParent, std::string childBodyName, SimTK::Vec3 locationInChild ){
  std::string to = "To";
  OpenSim::WeldConstraint *costr = new OpenSim::WeldConstraint(childBodyName+to+parentBodyName, aModel.updBodySet().get(parentBodyName), locationInParent, SimTK::Vec3(0), aModel.updBodySet().get(childBodyName), locationInChild, SimTK::Vec3(0));
  aModel.addConstraint(costr);
}

int main(int argc, char **argv) {
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " Multi-Body System Benchmark in OpenSim" << endl;
  cout << " Benchmark reference url: http://lim.ii.udc.es/mbsbenchmark/" << endl;
  cout << " Problem A04: Bricard's Mechanism Model Creator" << endl;
  cout << " Copyright (C) 2013-2015 Luca Tagliapietra, Michele Vivian, Elena Ceseracciu, and Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;

  if (argc != 2){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A04" << endl;
    cout << " Usage: ./BricardsMechanismCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }

  const std::string dataDir = argv[1];
  cout << "Data directory: " + dataDir << endl;

  // Create model and set name and authors
  OpenSim::Model bricardsMechanism;
  bricardsMechanism.setName(modelName);
  bricardsMechanism.setAuthors("L.Tagliapietra, M. Vivian, M.Reggiani");

  OpenSim::Body& ground = bricardsMechanism.getGroundBody();
  bricardsMechanism.setGravity(SimTK::Vec3(0, -9.81, 0));

  createBar(bricardsMechanism, linkNamePrefix+patch::to_string(1), jointNamePrefix+patch::to_string(1), barMass, barMassCenter, barLength, ground,
              SimTK::Vec3(0),SimTK::Vec3(SimTK::Pi/2,0,0), SimTK::Vec3 (-barLength/2,0,0),SimTK::Vec3(SimTK::Pi/2,0,0), 0, 0, 1, SimTK::Vec3(0),SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(0,0,1)));

  createBar(bricardsMechanism, linkNamePrefix+patch::to_string(2), jointNamePrefix+patch::to_string(2), barMass, barMassCenter, barLength, bricardsMechanism.updBodySet().get(linkNamePrefix+patch::to_string(1)),
              SimTK::Vec3(barLength/2,0,0),SimTK::Vec3(0), SimTK::Vec3 (0,barLength/2,0),SimTK::Vec3(0), 0, 1, 2, SimTK::Vec3(0),SimTK::Rotation(0, SimTK::UnitVec3(0,0,1)));

  createBar(bricardsMechanism, linkNamePrefix+patch::to_string(3), jointNamePrefix+patch::to_string(3), barMass, barMassCenter, barLength, bricardsMechanism.updBodySet().get(linkNamePrefix+patch::to_string(2)),
              SimTK::Vec3(0,-barLength/2,0), SimTK::Vec3(0,SimTK::Pi/2,0), SimTK::Vec3 (0,0,-barLength/2), SimTK::Vec3(0, SimTK::Pi/2,0), 0, 2, 3, SimTK::Vec3(0),SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(1,0,0)));

  createBar(bricardsMechanism, linkNamePrefix+patch::to_string(4), jointNamePrefix+patch::to_string(4), barMass, barMassCenter, barLength, bricardsMechanism.updBodySet().get(linkNamePrefix+patch::to_string(3)),
              SimTK::Vec3(0,0,barLength/2),SimTK::Vec3(SimTK::Pi/2,0,0), SimTK::Vec3 (barLength/2,0,0), SimTK::Vec3(SimTK::Pi/2,0,0), 0, 3, 1, SimTK::Vec3(0),SimTK::Rotation(SimTK::Pi/2, SimTK::UnitVec3(0,0,1)));

  createBar(bricardsMechanism, linkNamePrefix+patch::to_string(5), jointNamePrefix+patch::to_string(5), barMass/2, barMassCenter, barLength/2, bricardsMechanism.updBodySet().get(linkNamePrefix+patch::to_string(4)),
              SimTK::Vec3(-barLength/2,0,0), SimTK::Vec3(0), SimTK::Vec3 (0,-barLength/4,0), SimTK::Vec3(0), 0, 4, 2, SimTK::Vec3(0),SimTK::Rotation(0, SimTK::UnitVec3(0,0,1)));

  createBar(bricardsMechanism, linkNamePrefix+patch::to_string(6), jointNamePrefix+patch::to_string(6), barMass/2, barMassCenter, barLength/2, ground,
              SimTK::Vec3(0,0,barLength), SimTK::Vec3(0, SimTK::Pi/2,0), SimTK::Vec3 (0,barLength/4,0), SimTK::Vec3(0, SimTK::Pi/2,0), 0, 5, 2, SimTK::Vec3(0),SimTK::Rotation(0, SimTK::UnitVec3(0,0,1)));

  createWeldCostraint(bricardsMechanism, linkNamePrefix+patch::to_string(5), SimTK::Vec3(0, barLength/4,0), linkNamePrefix+patch::to_string(6), SimTK::Vec3(0,-barLength/4,0) );

  // Save to file the model
  bricardsMechanism.print((dataDir+"/"+modelName+std::string(".osim")).c_str());

  cout << "Model stored in: " << dataDir << "/" << modelName << ".osim" << endl;
}
