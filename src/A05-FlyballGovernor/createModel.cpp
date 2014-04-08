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

#include <string>
#include <iostream>
  using std::cout;
  using std::endl;
#include <vector>
  using std::vector;

#include <OpenSim/OpenSim.h>
#include <OpenSim/Simulation/Model/ExpressionBasedPointToPointForce.h>
#include "modelProperties.h"
  


namespace patch{
  template <typename T> std::string to_string(const T& n){
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

int main(int argc, char **argv) {
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " Multi-Body System Benchmark in OpenSim" << endl;
  cout << " Benchmark reference url: http://lim.ii.udc.es/mbsbenchmark/" << endl;
  cout << " Problem A05: Flyball Governor Model Creator" << endl;
  cout << " Copyright (C) 2013, 2014 Luca Tagliapietra, Michele Vivian, Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  
  if (argc != 2){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A05" << endl;
    cout << " Usage: ./FlyballGovernorCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }
  
  const std::string dataDir = argv[1];
  cout << "Data directory: " + dataDir << endl;

  // Create model and set name and authors
  OpenSim::Model flyballGovernor;
  flyballGovernor.setName(modelName);
  flyballGovernor.setAuthors("L.Tagliapietra, M. Vivian, M.Reggiani");
  
  // Get a reference to the model's ground body
  OpenSim::Body& ground = flyballGovernor.getGroundBody(); 
  flyballGovernor.setGravity(SimTK::Vec3(0, 0, -9.81));
  
  // ****************************************************************
  // Create Axis 
  // ****************************************************************
  const double axisVolume = 1*0.01*0.01;

  SimTK::Inertia axisInertia = axisVolume*density*SimTK::Inertia::brick(0.005, 0.005,0.5);
  OpenSim::Body *axis = new OpenSim::Body("axis", axisVolume*density, barMassCenter, axisInertia);
  
  OpenSim::DisplayGeometry squareRodGeom(boxGeometry);
  squareRodGeom.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  squareRodGeom.setName("axis");
  SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  squareRodGeom.setTransform(rotoTrans);
  axis->updDisplayer()->updGeometrySet().insert(0,squareRodGeom);
  // add upper square disk (visualization pourpose only)
  OpenSim::DisplayGeometry squareDiskGeom("box.vtp");
  squareDiskGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  squareDiskGeom.setName("axisTopSquareDisk");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0,0,0.5));
  squareDiskGeom.setTransform(rotoTrans);
  axis->updDisplayer()->updGeometrySet().insert(1,squareDiskGeom);    
   
  OpenSim::PinJoint *axisToGroundJoint = new OpenSim::PinJoint("axisToGround", ground, SimTK::Vec3(0), SimTK::Vec3(0), *axis, SimTK::Vec3(0,0,-0.5), SimTK::Vec3(0)); 
  OpenSim::CoordinateSet& axisToGroundCoordinateSet = axisToGroundJoint -> upd_CoordinateSet();

  axisToGroundCoordinateSet[0].setName("axisToGround");
  axisToGroundCoordinateSet[0].setDefaultValue(0);
  axisToGroundCoordinateSet[0].setDefaultSpeedValue(defaultSpeed);
  flyballGovernor.addBody(axis);
  
  // ****************************************************************
  // Create Translating Base Element 
  // ****************************************************************
  const double baseVolume = 0.1*0.1*0.1;

  SimTK::Inertia baseInertia = baseVolume*density*SimTK::Inertia::brick(0.05, 0.05,0.05);
  
  OpenSim::Body *base = new OpenSim::Body("base", baseVolume*density, barMassCenter, baseInertia);
  
  OpenSim::DisplayGeometry baseGeom(boxGeometry);
  baseGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  baseGeom.setName("base");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  baseGeom.setTransform(rotoTrans);
  base->updDisplayer()->updGeometrySet().insert(0,baseGeom);    
   
  std::string baseName("base");
  OpenSim::SliderJoint baseToAxisJoint = OpenSim::SliderJoint(baseName, flyballGovernor.updBodySet().get("axis"), SimTK::Vec3(0,0,-0.5), SimTK::Vec3(0,-SimTK::Pi/2,0), *base, SimTK::Vec3(0), SimTK::Vec3(0,-SimTK::Pi/2,0)); 
  OpenSim::CoordinateSet & baseToAxisCoordinateSet = baseToAxisJoint.upd_CoordinateSet();

  baseToAxisCoordinateSet[0].setName("baseToAxis");
  baseToAxisCoordinateSet[0].setDefaultValue(0.5);
  baseToAxisCoordinateSet[0].setDefaultSpeedValue(0);
  baseToAxisCoordinateSet[0].setRangeMin(0.0);
  baseToAxisCoordinateSet[0].setRangeMax(1.0);
  baseToAxisCoordinateSet[0].setDefaultClamped(true);
  flyballGovernor.addBody(base);
  
  // ****************************************************************
  // Create First Rod 
  // ****************************************************************
  SimTK::Inertia rodInertia = axisVolume*density*SimTK::Inertia::brick(0.005, 0.005,0.5);
  
  OpenSim::Body *firstRod = new OpenSim::Body("firstRod", axisVolume*density, barMassCenter, rodInertia);
  
  OpenSim::DisplayGeometry firstRodGeom(boxGeometry);
  firstRodGeom.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  firstRodGeom.setName("firstRod");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  firstRodGeom.setTransform(rotoTrans);
  firstRod->updDisplayer()->updGeometrySet().insert(0,firstRodGeom);
   
  OpenSim::PinJoint *firstRodToAxisJoint = new OpenSim::PinJoint("firstRodToAxis", flyballGovernor.updBodySet().get("axis"), SimTK::Vec3(0.05,0,0.5), SimTK::Vec3(SimTK::Pi/2,0,0), *firstRod, SimTK::Vec3(0,0,-0.5), SimTK::Vec3(SimTK::Pi/2,0,0)); 
  OpenSim::CoordinateSet& firstRodCoordinateSet = firstRodToAxisJoint -> upd_CoordinateSet();

  firstRodCoordinateSet[0].setName("firstRodToAxis");
  firstRodCoordinateSet[0].setDefaultValue(-(SimTK::Pi)*2.0/3);
  firstRodCoordinateSet[0].setDefaultSpeedValue(0);
  flyballGovernor.addBody(firstRod);
  
  // ****************************************************************
  // Create First Point Mass 
  // ****************************************************************
  OpenSim::Body *firstPointMass = new OpenSim::Body("firstPointMass", pointMass, SimTK::Vec3(0), SimTK::Inertia::pointMassAtOrigin());
  
  OpenSim::DisplayGeometry firstPointGeom(pointGeometry);
  firstPointGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  firstPointGeom.setName("firstBall");
  rotoTrans = SimTK::Transform(SimTK::Rotation(0, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  firstPointGeom.setTransform(rotoTrans);
  firstPointMass->updDisplayer()->updGeometrySet().insert(0,firstPointGeom);
   
  OpenSim::WeldJoint *firstMassTofirstBarJoint = new OpenSim::WeldJoint("firstMassTofirstBar", flyballGovernor.updBodySet().get("firstRod"), SimTK::Vec3(0,0,0.5), SimTK::Vec3(0), *firstPointMass, SimTK::Vec3(0,0,0), SimTK::Vec3(0));
  flyballGovernor.addBody(firstPointMass);
  
  // ****************************************************************
  // Create Second Rod 
  // ****************************************************************
  OpenSim::Body *secondRod = new OpenSim::Body("secondRod", axisVolume*density, barMassCenter, rodInertia);
  
  OpenSim::DisplayGeometry secondRodGeom(boxGeometry);
  secondRodGeom.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  secondRodGeom.setName("secondRod");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  secondRodGeom.setTransform(rotoTrans);
  secondRod->updDisplayer()->updGeometrySet().insert(0,secondRodGeom);
   
  OpenSim::PinJoint *secondRodToAxisJoint = new OpenSim::PinJoint("secondRodToAxis", flyballGovernor.updBodySet().get("axis"), SimTK::Vec3(-0.05,0,0.5), SimTK::Vec3(SimTK::Pi/2,0,0), *secondRod, SimTK::Vec3(0,0,-0.5), SimTK::Vec3(SimTK::Pi/2,0,0)); 
  OpenSim::CoordinateSet& secondRodToAxisCoordinateSet = secondRodToAxisJoint -> upd_CoordinateSet();

  secondRodToAxisCoordinateSet[0].setName("secondRodToAxis");
  secondRodToAxisCoordinateSet[0].setDefaultValue((SimTK::Pi)*2.0/3);
  secondRodToAxisCoordinateSet[0].setDefaultSpeedValue(0);
  flyballGovernor.addBody(secondRod);

  // ****************************************************************
  // Create Second Point Mass
  // ****************************************************************
  OpenSim::Body *secondPointMass = new OpenSim::Body("secondPointMass", pointMass, SimTK::Vec3(0), SimTK::Inertia::pointMassAtOrigin());
  
  OpenSim::DisplayGeometry secondPointGeom(pointGeometry);
  secondPointGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  secondPointGeom.setName("secondPointMass");
  rotoTrans = SimTK::Transform(SimTK::Rotation(0, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  secondPointGeom.setTransform(rotoTrans);
  secondPointMass->updDisplayer()->updGeometrySet().insert(0,secondPointGeom);
   
  OpenSim::WeldJoint *secondMassToSecondRodJoint = new OpenSim::WeldJoint("secondMassToSecondRod", flyballGovernor.updBodySet().get("secondRod"), SimTK::Vec3(0,0,0.5), SimTK::Vec3(0), *secondPointMass, SimTK::Vec3(0,0,0), SimTK::Vec3(0));
  flyballGovernor.addBody(secondPointMass);
  
  // ****************************************************************
  // Create Spring-Damper Elements
  // **************************************************************** 
  // Spring-Damper Force expression
  const std::string springDamperExpression( patch::to_string(springK)+"*(d-"+patch::to_string(springNaturalLength)+
    ")+"+patch::to_string(damperC)+"*ddot");
  
  OpenSim::ExpressionBasedPointToPointForce *firstSpringDamperForce = new OpenSim::ExpressionBasedPointToPointForce(std::string("base"), SimTK::Vec3(0.05,0,0), std::string("firstRod"), SimTK::Vec3(0), springDamperExpression);
  firstSpringDamperForce->setName("Spring-Damper_01");
  flyballGovernor.addForce(firstSpringDamperForce);
  
  OpenSim::ExpressionBasedPointToPointForce *secondSpringDamperForce = new OpenSim::ExpressionBasedPointToPointForce(std::string("base"), SimTK::Vec3(-0.05,0,0), std::string("secondRod"), SimTK::Vec3(0), springDamperExpression);
  secondSpringDamperForce->setName("Spring-Damper_02");
  flyballGovernor.addForce(secondSpringDamperForce);

  // Save to file the model
  flyballGovernor.print((dataDir+"/"+modelName+std::string(".osim")));
  
  cout << "Model stored in: " << dataDir << "/" << modelName << ".osim" << endl;
}

