//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------------ BIRD ----------------------------//
//----------------------- VIRTUAL BASE CLASS ---------------------//
//----------------------- CHILD OF BIRDPLAYER --------------------//

//  This class provides the essential functions of a bird object.

//----------------------------------------------------------------//

#ifndef BIRD_H
#define BIRD_H

#include "birdplayer.h"

class Bird : public BirdPlayer
{
public:

    //--Enumerated list of possible bird types
    enum BirdType{Null,
                  Hawk,
                  Starling};

    //--The constructor
    Bird(PlayerType ThisPlayer,
         ThreeVector Mom,
         ThreeVector Pos,
         double MaxMom,
         BirdType ThisBird);

    //--Return the range of interest of the bird
    double GetSight(){ return fSight; }

    //--Assign the range of interest of the bird
    void SetSight(double Sight){ fSight = Sight; }

    //--Increment momentum by delMom and adjust position accordingly, constraining
    //--these variables within their allowed parameters
    void UpdateAndRestrict(ThreeVector delMom);

    //--Induce random momentum change
    void RandomMovement(double NPlayers);

    //--Cause bird to steer over, under or around a specified position
    void Avoid(ThreeVector Position,
               double NPlayers);

    //--Pure virtual function returning 0 means class is not instantiable
    virtual int GetBirdType() = 0;

    //--Virtual destructor
    virtual ~Bird();

private:

    //--The type of bird
    BirdType fBirdType;

    //--The range of interest of the bird
    double fSight;

};

#endif // BIRD_H
