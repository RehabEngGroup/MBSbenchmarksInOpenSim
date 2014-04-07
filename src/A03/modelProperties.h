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

#ifndef modelProperties_h
#define modelProperties_h

const std::string modelName = "AndrewsMechanism";
const std::string rodGeometry = "cylinder.vtp";
const std::string triangleGeometry = "triangle.vtp";

 // Mass of each body
  const double OFmass = 0.04325;
  const double EFmass = 0.00365;
  const double BDEmass = 0.02373;
  const double GEmass = 0.00706;
  const double AGmass = 0.07050;
  const double HEmass = 0.00706;
  const double AHmass = 0.05498;
  
  // Inertia moments of each body about its center of mass
  const double OFinertia = 2.194e-6;
  const double EFinertia = 4.410e-7;
  const double BDEinertia = 5.255e-6;
  const double GEinertia = 5.667e-7;
  const double AGinertia = 1.169e-5;
  const double HEinertia = 5.667e-7;
  const double AHinertia = 1.912e-5;
  
  // Lenght of each body
  const double OFlength = 0.007;
  const double EFlength = 0.028;
  const double BElength = 0.035;
  const double GElength = 0.02;
  const double AGlength = 0.04;
  const double HElength = 0.02;
  const double AHlength = 0.04;  
  
  const double OAngleAtZero = - 0.06934;
  const double FAngleAtZero = 0.0;
  const double E1AngleAtZero = -45.82/180*(SimTK::Pi);
  const double GAngleAtZero = 77.35/180*(SimTK::Pi);
  const double E2AngleAtZero = 61.30/180*(SimTK::Pi);
  const double HAngleAtZero = -77.24/180*(SimTK::Pi);
  const double E3AngleAtZero = -60.36/180*(SimTK::Pi);
  
  // Mass center of each body
  const SimTK::Vec3 OFMassCenter(0.00092 - OFlength/2, 0, 0);
  const SimTK::Vec3 EFMassCenter(0.0165 - EFlength/2, 0, 0);
  const SimTK::Vec3 BDEMassCenter(0.01874 - BElength/2, 0.01043, 0);   
  const SimTK::Vec3 GEMassCenter(0.00579 - GElength/2, 0, 0); 
  const SimTK::Vec3 AGMassCenter(0.02308 - AGlength/2, 0.00916, 0); 
  const SimTK::Vec3 HEMassCenter(0.00579 - HElength/2, 0, 0); 
  const SimTK::Vec3 AHMassCenter(0.01228 - AHlength/2, -0.00449, 0);  
  
//Gravity vector
const SimTK::Vec3 gravityVector(0, 0, 0);

//Spring Properties
 const double springK = 4530.0;
 const double springRestLength = 0.07785;

#endif
