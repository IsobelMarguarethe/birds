//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------- PREDATOR -----------------------------//
//----------------------- CHILD OF BIRD --------------------------//

// This class provides the essential functions of a predator bird.

//----------------------------------------------------------------//

#include "predator.h"

Predator::Predator(ThreeVector Mom,
                   ThreeVector Pos,
                   double MaxMom)
    :Bird(Dangerous, Mom, Pos, MaxMom, Hawk)
{
    //--Assign the radius of awareness of a Predator
    SetSight(400.0);
}

void Predator::Hunt(ThreeVector PreyPos)
{
    //--Scalar position difference
    double PosDiff = PreyPos.Mag() - this->GetPos().Mag();
    //--Vector position difference
    ThreeVector PosDiffVect = PreyPos - this->GetPos();

    ThreeVector delMom;
    //--Scale influence of behaviour to overall final motion
    double ScaleFactor = 1e-2;

    if (fabs(PosDiff) <= this->GetSight())
    {
        if (PosDiff == 0.0)
        {
            //--If at same position, do not change momentum
            delMom = ThreeVector();
        }
        else
        {
            //--Steer towards PreyPos with momentum change inversely proporitonal
            //--to distance
            delMom = PosDiffVect*fabs(this->GetSight()/PosDiff)*ScaleFactor;
        }
    }

    //--Increment momentum and position
    this->UpdateAndRestrict(delMom);
}

void Predator::Move(BirdPlayer *ThisPlayer, double NPlayers)
{
    //--Implementation of function that was pure virtual in BirdPlayer

    //--Give Predator motion some randomness
    this->RandomMovement(NPlayers);

    //--Alter behaviour of Predator depending on player type of object pointed
    //--to by ThisPlayer
    if (ThisPlayer->GetPlayerType() == Friendly)
    {
        this->Hunt(ThisPlayer->GetPos());
    }
    else
    {
        //--Avoid anything not recognisable as Prey
        this->Avoid(ThisPlayer->GetPos(), NPlayers);
    }
}

Predator::~Predator()
{}
