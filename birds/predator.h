//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------- PREDATOR -----------------------------//
//----------------------- CHILD OF BIRD --------------------------//

// This class provides the essential functions of a predator bird.

//----------------------------------------------------------------//

#ifndef PREDATOR_H
#define PREDATOR_H

#include "bird.h"

class Predator : public Bird
{
public:

    //--The constructor
    Predator(ThreeVector Mom,
             ThreeVector Pos,
             double MaxMom);

    //--Cause predator to accelerate towards position PreyPos
    void Hunt(ThreeVector PreyPos);

    //--Explicitly implement functions defined pute virtual in parent
    //--class:
    //--Return Dangerous player type
    virtual int GetPlayerType() { return Dangerous; }
    //--Return Hawk bird type
    virtual int GetBirdType() { return Hawk; }
    //--Update position of predator
    virtual void Move(BirdPlayer * ThisPlayer, double NPlayers);

    //--Virtual destructor
    virtual ~Predator();

};

#endif // PREDATOR_H
