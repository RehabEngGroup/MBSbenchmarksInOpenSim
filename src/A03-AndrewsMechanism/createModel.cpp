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

void createPointCostraint(OpenSim::Model &aModel, std::string parentBodyName, SimTK::Vec3 locationInParent, std::string childBodyName, SimTK::Vec3 locationInChild ){
  OpenSim::PointConstraint *costr = new OpenSim::PointConstraint(aModel.updBodySet().get(parentBodyName), locationInParent, aModel.updBodySet().get(childBodyName), locationInChild);
  costr->setName(childBodyName+"To"+parentBodyName);
  aModel.addConstraint(costr);
}

int main(int argc, char **argv) {
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " Multi-Body System Benchmark in OpenSim" << endl;
  cout << " Benchmark reference url: http://lim.ii.udc.es/mbsbenchmark/" << endl;
  cout << " Problem A03: Andrew's Mechanism Model Creator" << endl;
  cout << " Copyright (C) 2013-2015 Luca Tagliapietra, Michele Vivian, Elena Ceseracciu, and Monica Reggiani" << endl;
  cout << "--------------------------------------------------------------------------------" << endl;

  if (argc != 2){
    cout << " ******************************************************************************" << endl;
    cout << " Multi-Body System Benchmark in OpenSim: Creator for Model A03" << endl;
    cout << " Usage: ./AndrewsMechanismCreateModel dataDirectory" << endl;
    cout << "       dataDirectory must contain a vtpFiles folder" << endl;
    cout << " ******************************************************************************" << endl;
    exit(EXIT_FAILURE);
  }

  const std::string dataDir = argv[1];
  cout << "Data directory: " + dataDir << endl;

  OpenSim::Model andrewsMechanism;
  andrewsMechanism.setName("Andrew's Mechanism");
  andrewsMechanism.setAuthors("L.Tagliapietra, M. Vivian, M.Reggiani");

  // Get a reference to the model's ground body
  OpenSim::Body& ground = andrewsMechanism.getGroundBody();
  andrewsMechanism.setGravity(gravityVector);

  //******************************
  // Create OF element
  //******************************
  SimTK::Inertia OFbarInertia(0.1,0.1,OFinertia);
  OpenSim::Body *OF = new OpenSim::Body("OF", OFmass, OFMassCenter, OFbarInertia);

  //Set transformation for visualization pourpose
  SimTK::Rotation rot(SimTK::Pi/2, SimTK::UnitVec3(0,0,1));
  SimTK::Transform trans = SimTK::Transform(rot);

  //Set visualization properties
  OF->addDisplayGeometry(rodGeometry);
  OpenSim::VisibleObject* visOF = OF->updDisplayer();
  visOF -> updTransform() =  trans;
  visOF -> setScaleFactors(SimTK::Vec3(0.001,OFlength, 0.001));
  visOF -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  SimTK::Vec3 orientationInParent(0), orientationInBody(0);
  OpenSim::PinJoint *OJoint = new OpenSim::PinJoint("joint_O", ground, SimTK::Vec3(0), orientationInParent, *OF, SimTK::Vec3(-OFlength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& OCoordinateSet = OJoint -> upd_CoordinateSet();
  OCoordinateSet[0].setName("joint_O");
  OCoordinateSet[0].setDefaultValue(OAngleAtZero);
  andrewsMechanism.addBody(OF);

  //********************************
  // Create FE element
  //********************************
  SimTK::Inertia EFbarInertia(0.1,0.1,EFinertia);
  OpenSim::Body *EF = new OpenSim::Body("EF", EFmass, EFMassCenter, EFbarInertia);

  //Set visualization properties
  EF->addDisplayGeometry(rodGeometry);
  OpenSim::VisibleObject* visEF = EF->updDisplayer();
  visEF -> updTransform() =  trans;
  visEF -> setScaleFactors(SimTK::Vec3(0.001,EFlength, 0.001));
  visEF -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  OpenSim::PinJoint *FJoint = new OpenSim::PinJoint("joint_F", *OF, SimTK::Vec3(OFlength/2,0,0), orientationInParent, *EF, SimTK::Vec3(EFlength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& FCoordinateSet = FJoint -> upd_CoordinateSet();
  FCoordinateSet[0].setName("joint_F");
  FCoordinateSet[0].setDefaultValue(FAngleAtZero);
  andrewsMechanism.addBody(EF);

  //********************************
  // Create EG element
  //********************************
  SimTK::Inertia GEbarInertia(0.1,0.1,GEinertia);
  OpenSim::Body *GE = new OpenSim::Body("GE", GEmass, GEMassCenter, GEbarInertia);

  //Set visualization properties
  GE->addDisplayGeometry(rodGeometry);
  OpenSim::VisibleObject* visGE = GE->updDisplayer();
  visGE -> updTransform() =  trans;
  visGE -> setScaleFactors(SimTK::Vec3(0.001,GElength, 0.001));
  visGE -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  OpenSim::PinJoint *E1Joint = new OpenSim::PinJoint("joint_E1", *EF, SimTK::Vec3(-EFlength/2,0,0), orientationInParent, *GE, SimTK::Vec3(GElength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& E1CoordinateSet = E1Joint -> upd_CoordinateSet();
  E1CoordinateSet[0].setName("joint_E1");
  E1CoordinateSet[0].setDefaultValue(E1AngleAtZero);
  andrewsMechanism.addBody(GE);

  //********************************
  // Create AG element
  //********************************
  SimTK::Inertia AGbarInertia(0.1,0.1,AGinertia);
  OpenSim::Body *AG = new OpenSim::Body("AG", AGmass, AGMassCenter, AGbarInertia);

  //Set visualization properties
  AG->addDisplayGeometry(rodGeometry);
  OpenSim::VisibleObject* visAG = AG->updDisplayer();
  visAG -> updTransform() =  trans;
  visAG -> setScaleFactors(SimTK::Vec3(0.001,AGlength, 0.001));
  visAG -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  OpenSim::PinJoint *GJoint = new OpenSim::PinJoint("joint_G", *GE, SimTK::Vec3(-GElength/2,0,0), orientationInParent, *AG, SimTK::Vec3(AGlength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& GCoordinateSet = GJoint -> upd_CoordinateSet();
  GCoordinateSet[0].setName("joint_G");
  GCoordinateSet[0].setDefaultValue(GAngleAtZero);
  andrewsMechanism.addBody(AG);

  //********************************
  // Create point constraint between AG element and ground to simulate joint A
  //********************************
   createPointCostraint(andrewsMechanism, std::string("ground"), SimTK::Vec3(-0.06934, -0.00227,0), std::string("AG"), SimTK::Vec3(-AGlength/2,0,0));

  //********************************
  // Create HE element
  //********************************
  SimTK::Inertia HEbarInertia(0.1,0.1,GEinertia);
  OpenSim::Body *HE = new OpenSim::Body("HE", HEmass, HEMassCenter, HEbarInertia);

  //Set visualization properties
  HE->addDisplayGeometry(rodGeometry);
  OpenSim::VisibleObject* visHE = HE->updDisplayer();
  visHE -> updTransform() =  trans;
  visHE -> setScaleFactors(SimTK::Vec3(0.001,HElength, 0.001));
  visHE -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  OpenSim::PinJoint *E2Joint = new OpenSim::PinJoint("joint_E2", *EF, SimTK::Vec3(-EFlength/2,0,0), orientationInParent, *HE, SimTK::Vec3(HElength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& E2CoordinateSet = E2Joint -> upd_CoordinateSet();
  E2CoordinateSet[0].setName("joint_E2");
  E2CoordinateSet[0].setDefaultValue(E2AngleAtZero);
  andrewsMechanism.addBody(HE);

  //********************************
  //Create AH element
  //********************************
  SimTK::Inertia AHbarInertia(0.1,0.1,AHinertia);
  OpenSim::Body *AH = new OpenSim::Body("AH", AHmass, AHMassCenter, AHbarInertia);

  //Set visualization properties
  AH->addDisplayGeometry(rodGeometry);
  OpenSim::VisibleObject* visAH = AH->updDisplayer();
  visAH -> updTransform() =  trans;
  visAH -> setScaleFactors(SimTK::Vec3(0.001,AHlength, 0.001));
  visAH -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  OpenSim::PinJoint *HJoint = new OpenSim::PinJoint("joint_H", *HE, SimTK::Vec3(-HElength/2,0,0), orientationInParent, *AH, SimTK::Vec3(AHlength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& HCoordinateSet = HJoint -> upd_CoordinateSet();
  HCoordinateSet[0].setName("joint_H");
  HCoordinateSet[0].setDefaultValue(HAngleAtZero);
  andrewsMechanism.addBody(AH);

  //********************************
  //Create point constraint between AH element and ground to simulate joint A
  //********************************
  createPointCostraint(andrewsMechanism, std::string("ground"), SimTK::Vec3(-0.06934, -0.00227,0), std::string("AH"), SimTK::Vec3(-AHlength/2,0,0));

  //********************************
  // Create BDE element
  //********************************
  SimTK::Inertia BDEInertia(0.1,0.1,BDEinertia);
  OpenSim::Body *BDE = new OpenSim::Body("BDE", BDEmass, BDEMassCenter, BDEInertia);

  //Set visualization properties
  BDE->addDisplayGeometry(triangleGeometry);
  OpenSim::VisibleObject* visBDE = BDE->updDisplayer();
  visBDE -> updTransform() =  trans;
  visBDE -> setScaleFactors(SimTK::Vec3(0.01, 0.01, 0.0005));
  visBDE -> setDisplayPreference(OpenSim::DisplayGeometry::DisplayPreference(1));

  OpenSim::PinJoint *E3Joint = new OpenSim::PinJoint("joint_E3", *EF, SimTK::Vec3(-EFlength/2,0,0), orientationInParent, *BDE, SimTK::Vec3(BElength/2,0,0), orientationInBody);
  OpenSim::CoordinateSet& E3CoordinateSet = E3Joint -> upd_CoordinateSet();
  E3CoordinateSet[0].setName("joint_E3");
  E3CoordinateSet[0].setDefaultValue(E3AngleAtZero);
  andrewsMechanism.addBody(BDE);

  //********************************
  // Create point constraint between BDE element and ground to simulate joint B
  //********************************
  createPointCostraint(andrewsMechanism, std::string("ground"), SimTK::Vec3(-0.03635, 0.03273,0), std::string("BDE"), SimTK::Vec3(-BElength/2,0,0));

  //********************************
  // Add the spring between BDE and ground
  //********************************
  OpenSim::PointToPointSpring *spring = new OpenSim::PointToPointSpring(std::string("ground"), SimTK::Vec3(0.014,0.072,0), std::string("BDE"), SimTK::Vec3(-BElength/2+0.018, 0.02,0), springK, springRestLength);
  andrewsMechanism.addComponent(spring);

  // Save to file the model
  andrewsMechanism.print((dataDir+"/"+modelName+std::string(".osim")).c_str());

  cout << "Model stored in: " << dataDir << "/" << modelName << ".osim" << endl;
}
