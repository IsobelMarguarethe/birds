/*
 * ThreeVector.h
 *
 *  Created on: Sep 25, 2015
 *      Author: AntoninoSergi
 */

//--edited by Isobel Romero-Shaw on 26.11.2016
//--this class has been stripped of all functions and comments not
//--relevant to the Birds program.

#ifndef THREEVECTOR_H_
#define THREEVECTOR_H_

#include <cmath>

class ThreeVector {
public:
    //--The constructors:
    //--Creates a ThreeVector of (0.0, 0.0, 0.0)
	ThreeVector();
    //--Creates a ThreeVector of (x, y, z)
	ThreeVector(double x, double y, double z);

    //--Note on Inline: Compiler replicates machine code for inline
    //--functions whenever called.

    //--Declaring methods constant indicates that object is not altered
    //--by their execution.

    //--Return corresponding vector component:
	inline double X()  const;
	inline double Y()  const;
	inline double Z()  const;

    //--Assign corresponding vector component:
	inline void SetX(double);
	inline void SetY(double);
	inline void SetZ(double);

    //--Assign all three vector components
	inline void SetXYZ(double x, double y, double z);

    //--Return vector magnitude squared
	inline double Mag2() const;

    //--Return vector magnitude
	double Mag() const;

    //--Operator declaration:

    //--Assignment
	inline ThreeVector & operator = (const ThreeVector &);
    //--Addition
	inline ThreeVector & operator += (const ThreeVector &);
    //--Subtraction
	inline ThreeVector & operator -= (const ThreeVector &);
    //--Division
    inline ThreeVector & operator / (const ThreeVector & p);
    //--Unary minus
	inline ThreeVector operator - () const;
    //--Multiplication by a scalar
	inline ThreeVector & operator *= (double);

    //--Print vector components
	void Print() const;

    //--Virtual destructor
    virtual ~ThreeVector();

private:

    //--Vector components
	double fX, fY, fZ;
};

//--Operators declared outside of class scope in order to be global

//--Addition
ThreeVector operator + (const ThreeVector &, const ThreeVector &);
//--Subtraction
ThreeVector operator - (const ThreeVector &, const ThreeVector &);
//--Multiplication
ThreeVector operator * (const ThreeVector &, double a);
ThreeVector operator * (double a, const ThreeVector &);

//--Inline methods must be implemented within file of their declaration

//--Return corresponding vector component:
inline double ThreeVector::X()  const { return fX; }
inline double ThreeVector::Y()  const { return fY; }
inline double ThreeVector::Z()  const { return fZ; }

//--Assign corresponding vector component:
inline void ThreeVector::SetX(double xx) { fX = xx; }
inline void ThreeVector::SetY(double yy) { fY = yy; }
inline void ThreeVector::SetZ(double zz) { fZ = zz; }

//--Assign all vector components
inline void ThreeVector::SetXYZ(double xx, double yy, double zz) {
   fX = xx;
   fY = yy;
   fZ = zz;
}

//--Return vector magnitude squared
inline double ThreeVector::Mag2() const { return fX*fX + fY*fY + fZ*fZ; }

//--Operators that alter the ThreeVector value must return the invoking instance
//--themselves by dereferencing the pointer to 'this' ThreeVector
//--Assignment
inline ThreeVector & ThreeVector::operator = (const ThreeVector & p) {
   fX = p.fX;
   fY = p.fY;
   fZ = p.fZ;
   return *this;
}

//--Addition
inline ThreeVector& ThreeVector::operator += (const ThreeVector & p) {
   fX += p.fX;
   fY += p.fY;
   fZ += p.fZ;
   return *this;
}

//--Division
inline ThreeVector& ThreeVector::operator / (const ThreeVector & p) {
    fX = fX/p.fX;
    fY = fY/p.fY;
    fZ = fZ/p.fZ;
    return *this;
}

//--Unary minus
inline ThreeVector ThreeVector::operator - () const {
   return ThreeVector(-fX, -fY, -fZ);
}

#endif /* THREEVECTOR_H_ */
