//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//----------------------------- PREY -----------------------------//
//------------------------- CHILD OF BIRD ------------------------//

// This class provides the essential functions of a prey bird.

//----------------------------------------------------------------//

#ifndef PREY_H
#define PREY_H

#include "bird.h"

class Prey : public Bird
{
public:

    //--The constructor
    Prey(ThreeVector Mom,
         ThreeVector Pos,
         double MaxMom);

    //--Perform characteristic behaviours:
    //--Fleeing behaviour
    void FleeFrom(ThreeVector PredPos, double NPlayers);
    //--Flocking behaviour
    void FlockWith(ThreeVector FriendPos, double NPlayers);

    //--Explicitly implement functions defined pute virtual in parent
    //--class:
    //--Return Friendly player type
    virtual int GetPlayerType() { return Friendly; }
    //--Return Starling bird type
    virtual int GetBirdType(){ return Starling; }
    //--Update position of prey bird
    virtual void Move(BirdPlayer * ThisPlayer, double NPlayers);

    //--Virtual destructor
    virtual ~Prey();
};

#endif // PREY_H
