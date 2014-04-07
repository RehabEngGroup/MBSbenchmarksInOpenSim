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

const std::string modelName = "BricardMechanism";
const std::string rodGeometry = "cylinder.vtp";

const double barMass = 1;
const double barLength = 1;
const double barRadius = 0.0;
const SimTK::Vec3 barMassCenter(0);

const std::string linkNamePrefix = "Link_";   
const std::string jointNamePrefix = "Pin_";

//Gravity vector
const SimTK::Vec3 gravityVector(0, -9.81, 0);

#endif
