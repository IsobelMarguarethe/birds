//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//----------------------------- PREY -----------------------------//
//------------------------- CHILD OF BIRD ------------------------//

// This class provides the essential functions of a prey bird.

//----------------------------------------------------------------//

#include "prey.h"

Prey::Prey(ThreeVector Mom,
           ThreeVector Pos,
           double MaxMom)
    :Bird(Friendly, Mom, Pos, MaxMom, Starling)
{
    //--Assign the radius of awareness of the Prey
    SetSight(200.0);
}

void Prey::Move(BirdPlayer * ThisPlayer, double NPlayers)
{
    //--Implementation of function that was pure virtual in BirdPlayer

    //--Give Prey motion some randomness
    this->RandomMovement(NPlayers);

    //--Alter behaviour of Prey depending on player type of object pointed
    //--to by ThisPlayer
    if (ThisPlayer->GetPlayerType() == Dangerous)
    {
        this->FleeFrom(ThisPlayer->GetPos(), NPlayers);
    }
    else if (ThisPlayer->GetPlayerType() == Friendly)
    {
       this->FlockWith(ThisPlayer->GetPos(), NPlayers);
    }
    else
    {
       //--Avoid anything not recognisable as Prey or Predator
       this->Avoid(ThisPlayer->GetPos(), NPlayers);
    }
}

void Prey::FlockWith(ThreeVector FriendPos, double NPlayers)
{
    //--Set the radii of the spheres within which the prey bird will react
    //--to Friendly neighbours in different ways:
    //--Distance within which to move away
    double TooClose = this->GetSight()/50.0;
    //--Distance within which to maintain separation
    double JustRight = this->GetSight()/30.0;
    //--Distance within which to move towards
    double TooFar = this->GetSight();

    //--Scalar position difference
    double PosDiff = FriendPos.Mag() - this->GetPos().Mag();
    //--Vector position difference
    ThreeVector PosDiffVect = FriendPos - this->GetPos();

    ThreeVector delMom;
    //--Assign weighting factor of movement based on number of times
    //--function will be called and desired influence of behaviour to
    //--overall motion
    double ScaleFactor = 1e-4/(2.0*NPlayers);

    if (fabs(PosDiff) <= TooFar)
    {
        if (fabs(PosDiff) <= TooClose)
        {
            if (PosDiff == 0.0)
            {
                //--Move on larger scale in the specific case where Prey
                //--are attempting to occupy the same position
                ScaleFactor *= 1e4;
                //--Move away with maximum momentum
                delMom = -this->
                         GetMaxMom()*PosDiffVect*ScaleFactor;
            }
            else
            {
                //--Move away with momentum inversely proportional
                //--to position difference
                delMom = -PosDiffVect*fabs(TooClose/PosDiff)*ScaleFactor;
            }

        }
        else if (fabs(PosDiff) <= JustRight)
        {
            //--If within comfortable range, simply continue moving
            //--without reference to other bird's location
            delMom = ThreeVector();

        }
        else
        {
            //--Move towards other bird with momentum inversely
            //--proportional to position difference
            delMom = PosDiffVect*fabs(TooFar/PosDiff)*ScaleFactor;
        }

        //--Increment momentum and position
        this->UpdateAndRestrict(delMom);

    }
}

void Prey::FleeFrom(ThreeVector PredPos, double NPlayers)
{
    //--Set radii of sphere within which a detected Predator will cause Prey
    //--to flee
    double ScaredDistance = this->GetSight()/1.5;

    //--Scalar position difference
    double PosDiff = PredPos.Mag() - this->GetPos().Mag();
    //--Vector position difference
    ThreeVector PosDiffVect = PredPos - this->GetPos();

    //--Assign weighting factor of movement based on number of times
    //--function will be called and desired influence of behaviour to
    //--overall motion
    double ScaleFactor = 1e-1/(2.0*NPlayers);

    ThreeVector delMom = ThreeVector();

    if (fabs(PosDiff) <= ScaredDistance)
    {
        if (PosDiff == 0.0)
        {
            //--Move on slightly larger scale in the specific case where Predator
            //--has caught Prey
            ScaleFactor *= 2.0;
            //--Move away with maximum momentum
            delMom = -this->
                    GetMaxMom()*PosDiffVect*ScaleFactor;
        }
        else
        {
            //--Move away with momentum inversely proportional to
            //--position difference
            delMom = -PosDiffVect*fabs(ScaredDistance/PosDiff)*this->
                                             GetMaxMom()*ScaleFactor;
        }
    }

    //--Increment momentum and position
    this->UpdateAndRestrict(delMom);
}

Prey::~Prey()
{}
