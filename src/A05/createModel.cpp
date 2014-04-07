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
#include <OpenSim/Simulation/Model/ExpressionBasedPointToPointForce.h>
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
    barInertia = barMass*SimTK::Inertia::cylinderAlongX(0, barLength/2);
  else if (rotationAxis==2)
    barInertia = barMass*SimTK::Inertia::cylinderAlongY(0, barLength/2);
    else
      barInertia = barMass*SimTK::Inertia::cylinderAlongZ(0, barLength/2);
  
  OpenSim::Body *aBody = new OpenSim::Body(bodyName, barMass, barMassCenter, barInertia);
  
  OpenSim::DisplayGeometry geom2("cylinder.vtp");
  geom2.setScaleFactors(SimTK::Vec3(0.03,barLength,0.03));
  geom2.setName(bodyName);
  SimTK::Transform rotoTrans = SimTK::Transform(graficRotation, graficTranslation);
  geom2.setTransform(rotoTrans);
  aBody->updDisplayer()->updGeometrySet().insert(0,geom2);    
  
  OpenSim::DisplayGeometry jointGeom("cylinder.vtp");
  jointGeom.setScaleFactors(SimTK::Vec3(0.1,0.2,0.1));
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

void createPointCostraint(OpenSim::Model &aModel, std::string parentBodyName, SimTK::Vec3 locationInParent, std::string childBodyName, SimTK::Vec3 locationInChild ){
  OpenSim::PointConstraint *costr = new OpenSim::PointConstraint(aModel.updBodySet().get(parentBodyName), locationInParent, aModel.updBodySet().get(childBodyName), locationInChild);
  std::string to = "To";
  costr->setName(childBodyName+to+parentBodyName);
  aModel.addConstraint(costr);
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
  cout << " Problem A05: Flyball Governor Model Creator" << endl;
  cout << " v. 1.0  Mar 2014" << endl;
  cout << " Copyright (C) Luca Tagliapietra, Michele Vivian, Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  
  if (argc < 1){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A05" << endl;
    cout << " Usage: ./FlyballGovernorCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }
  
  const std::string dataDir = argv[1];
  cout << "Starting modelling process using data directory:" + dataDir << endl;

  // Create model and set name and authors
  OpenSim::Model flyballGovernor;
  flyballGovernor.setName(modelName);
  flyballGovernor.setAuthors("L.Tagliapietra, M. Vivian, M.Sartori, M.Reggiani");
  
  // Get a reference to the model's ground body
  OpenSim::Body& ground = flyballGovernor.getGroundBody(); 
  flyballGovernor.setGravity(SimTK::Vec3(0, 0, -9.81));
  
  // Create axis element
  const double axisVolume = 1*0.01*0.01;

  SimTK::Inertia axisInertia = axisVolume*density*SimTK::Inertia::brick(0.005, 0.005,0.5);
  OpenSim::Body *axis = new OpenSim::Body("axis", axisVolume*density, barMassCenter, axisInertia);
  
  OpenSim::DisplayGeometry geom("box.vtp");
  geom.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  geom.setName("axis");
  SimTK::Transform rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  geom.setTransform(rotoTrans);
  axis->updDisplayer()->updGeometrySet().insert(0,geom);
  // add upper disk (visualization pourpose only)
  OpenSim::DisplayGeometry geom2("box.vtp");
  geom2.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  geom2.setName("axisHead");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0,0,0.5));
  geom2.setTransform(rotoTrans);
  axis->updDisplayer()->updGeometrySet().insert(1,geom2);    
   
  OpenSim::PinJoint *aJoint = new OpenSim::PinJoint("joint_0", ground, SimTK::Vec3(0), SimTK::Vec3(0), *axis, SimTK::Vec3(0,0,-0.5), SimTK::Vec3(0)); 
  OpenSim::CoordinateSet& aCoordinateSet = aJoint -> upd_CoordinateSet();

  aCoordinateSet[0].setName("joint_0");
  aCoordinateSet[0].setDefaultValue(0);
  aCoordinateSet[0].setDefaultSpeedValue(defaultSpeed);
  flyballGovernor.addBody(axis);
  // Create translating base element
  const double baseVolume = 0.1*0.1*0.1; // - 0.1*0.01*0.01; //base volume (total dimension volume - hole volume)

  SimTK::Inertia baseInertia = baseVolume*density*SimTK::Inertia::brick(0.05, 0.05,0.05);
  
  OpenSim::Body *base = new OpenSim::Body("base", baseVolume*density, barMassCenter, baseInertia);
  
  OpenSim::DisplayGeometry baseGeom("box.vtp");
  baseGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  baseGeom.setName("base");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  baseGeom.setTransform(rotoTrans);
  base->updDisplayer()->updGeometrySet().insert(0,baseGeom);    
   
  std::string baseName("base");
  OpenSim::SliderJoint baseJoint = OpenSim::SliderJoint(baseName, flyballGovernor.updBodySet().get("axis"), SimTK::Vec3(0,0,-0.5), SimTK::Vec3(0,-SimTK::Pi/2,0), *base, SimTK::Vec3(0), SimTK::Vec3(0,-SimTK::Pi/2,0)); 
  OpenSim::CoordinateSet & bCoordinateSet = baseJoint.upd_CoordinateSet();

  bCoordinateSet[0].setName("joint_1");
  bCoordinateSet[0].setDefaultValue(0.5);
  bCoordinateSet[0].setDefaultSpeedValue(0);
  bCoordinateSet[0].setRangeMin(0.0);
  bCoordinateSet[0].setRangeMax(1.0);
  bCoordinateSet[0].setDefaultClamped(true);
  flyballGovernor.addBody(base);
  
  //Create first rod
  SimTK::Inertia rodInertia = axisVolume*density*SimTK::Inertia::brick(0.005, 0.005,0.5);
  OpenSim::Body *firstRod = new OpenSim::Body("rod_1", axisVolume*density, barMassCenter, rodInertia);
  
  OpenSim::DisplayGeometry firstRodGeom("box.vtp");
  firstRodGeom.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  firstRodGeom.setName("firstRod");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  firstRodGeom.setTransform(rotoTrans);
  firstRod->updDisplayer()->updGeometrySet().insert(0,firstRodGeom);
   
  OpenSim::PinJoint *cJoint = new OpenSim::PinJoint("joint_2", flyballGovernor.updBodySet().get("axis"), SimTK::Vec3(0.05,0,0.5), SimTK::Vec3(SimTK::Pi/2,0,0), *firstRod, SimTK::Vec3(0,0,-0.5), SimTK::Vec3(SimTK::Pi/2,0,0)); 
  OpenSim::CoordinateSet& firstRodCoordinateSet = cJoint -> upd_CoordinateSet();

  firstRodCoordinateSet[0].setName("joint_2");
  firstRodCoordinateSet[0].setDefaultValue(-(SimTK::Pi)*2.0/3);
  firstRodCoordinateSet[0].setDefaultSpeedValue(0);
  flyballGovernor.addBody(firstRod);
  
  
  //Create first Point Mass
  const double pointMass = 5.0;
  
  OpenSim::Body *firstBallMass = new OpenSim::Body("pointMass_1", pointMass, SimTK::Vec3(0), SimTK::Inertia::pointMassAtOrigin());
  
  OpenSim::DisplayGeometry firstBallGeom("sphere.vtp");
  firstBallGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  firstBallGeom.setName("firstBall");
  rotoTrans = SimTK::Transform(SimTK::Rotation(0, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  firstBallGeom.setTransform(rotoTrans);
  firstBallMass->updDisplayer()->updGeometrySet().insert(0,firstBallGeom);
   
  OpenSim::WeldJoint *dJoint = new OpenSim::WeldJoint("fakeJoint_1", flyballGovernor.updBodySet().get("rod_1"), SimTK::Vec3(0,0,0.5), SimTK::Vec3(0), *firstBallMass, SimTK::Vec3(0,0,0), SimTK::Vec3(0));
  flyballGovernor.addBody(firstBallMass);
  
    //Create second rod
  OpenSim::Body *secondRod = new OpenSim::Body("rod_2", axisVolume*density, barMassCenter, rodInertia);
  
  OpenSim::DisplayGeometry secondRodGeom("box.vtp");
  secondRodGeom.setScaleFactors(SimTK::Vec3(0.01,1,0.01));
  secondRodGeom.setName("firstRod");
  rotoTrans = SimTK::Transform(SimTK::Rotation(-SimTK::Pi/2, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  secondRodGeom.setTransform(rotoTrans);
  secondRod->updDisplayer()->updGeometrySet().insert(0,secondRodGeom);
   
  OpenSim::PinJoint *eJoint = new OpenSim::PinJoint("joint_3", flyballGovernor.updBodySet().get("axis"), SimTK::Vec3(-0.05,0,0.5), SimTK::Vec3(SimTK::Pi/2,0,0), *secondRod, SimTK::Vec3(0,0,-0.5), SimTK::Vec3(SimTK::Pi/2,0,0)); 
  OpenSim::CoordinateSet& secondRodCoordinateSet = eJoint -> upd_CoordinateSet();

  secondRodCoordinateSet[0].setName("joint_2");
  secondRodCoordinateSet[0].setDefaultValue((SimTK::Pi)*2.0/3);
  secondRodCoordinateSet[0].setDefaultSpeedValue(0);
  flyballGovernor.addBody(secondRod);
  
  
  //Create second Point Mass
  OpenSim::Body *secondBallMass = new OpenSim::Body("pointMass_2", pointMass, SimTK::Vec3(0), SimTK::Inertia::pointMassAtOrigin());
  
  OpenSim::DisplayGeometry secondBallGeom("sphere.vtp");
  secondBallGeom.setScaleFactors(SimTK::Vec3(0.1,0.1,0.1));
  secondBallGeom.setName("secondBall");
  rotoTrans = SimTK::Transform(SimTK::Rotation(0, SimTK::UnitVec3(1,0,0)), SimTK::Vec3(0));
  secondBallGeom.setTransform(rotoTrans);
  secondBallMass->updDisplayer()->updGeometrySet().insert(0,secondBallGeom);
   
  OpenSim::WeldJoint *fJoint = new OpenSim::WeldJoint("fakeJoint", flyballGovernor.updBodySet().get("rod_2"), SimTK::Vec3(0,0,0.5), SimTK::Vec3(0), *secondBallMass, SimTK::Vec3(0,0,0), SimTK::Vec3(0));
  flyballGovernor.addBody(secondBallMass);
  
  const std::string springDamperExpression( patch::to_string(springK)+"*(d-"+patch::to_string(springNaturalLength)+
    ")+"+patch::to_string(damperC)+"*ddot");
  OpenSim::ExpressionBasedPointToPointForce *firstSpringDamperForce = new OpenSim::ExpressionBasedPointToPointForce(std::string("base"), SimTK::Vec3(0.05,0,0), std::string("rod_1"), SimTK::Vec3(0), springDamperExpression);
  firstSpringDamperForce->setName("Spring-Damper_01");
  flyballGovernor.addForce(firstSpringDamperForce);
  
  
  OpenSim::ExpressionBasedPointToPointForce *secondSpringDamperForce = new OpenSim::ExpressionBasedPointToPointForce(std::string("base"), SimTK::Vec3(-0.05,0,0), std::string("rod_2"), SimTK::Vec3(0), springDamperExpression);
  secondSpringDamperForce->setName("Spring-Damper_02");
  flyballGovernor.addForce(secondSpringDamperForce);
  
  
  cout << "Model creation process ends" << endl;
  
  // Save to file the model
  cout << "Model saving to file process starts" << endl;
  flyballGovernor.print((dataDir+"/"+modelName+std::string(".osim")));
  cout << "Model saving to file process ends" << endl;

}

