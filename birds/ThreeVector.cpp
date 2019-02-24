/*
 * ThreeVector.cpp
 *
 *  Created on: Sep 25, 2015
 *      Author: AntoninoSergi
 */

//--edited by Isobel Romero-Shaw on 26.11.2016
//--this class has been stripped of all functions and comments not
//--relevant to the Birds program.

#include <math.h>
#include <iostream>

#include "ThreeVector.h"

ThreeVector::ThreeVector()
//--Assign 0.0 to all components
: fX(0.0), fY(0.0), fZ(0.0) {}

ThreeVector::ThreeVector(double xx, double yy, double zz)
//--Assign designated values to all components
: fX(xx), fY(yy), fZ(zz) {}

double ThreeVector::Mag() const
{
   //--Return magnitude of vector
   return sqrt(Mag2());
}

ThreeVector operator + (const ThreeVector & a, const ThreeVector & b) {
   //--Sum vectors a and b
   return ThreeVector(a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z());
}

ThreeVector operator - (const ThreeVector & a, const ThreeVector & b) {
   //--Subtract vector b from vector a
   return ThreeVector(a.X() - b.X(), a.Y() - b.Y(), a.Z() - b.Z());
}

ThreeVector operator * (const ThreeVector & p, double a) {
   //--Multiply all vector components by a
   return ThreeVector(a*p.X(), a*p.Y(), a*p.Z());
}


ThreeVector operator * (double a, const ThreeVector & p) {
   //--Multiply all vector components by a
   return ThreeVector(a*p.X(), a*p.Y(), a*p.Z());
}

void ThreeVector::Print()const
{
   //--Print all vector components
   std::cout << "(x,y,z)=(" << X() << "," << Y() << "," << Z() << ")" << std::endl;
}

ThreeVector::~ThreeVector() {
}

