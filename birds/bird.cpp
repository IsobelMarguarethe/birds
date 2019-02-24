//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------------ BIRD ----------------------------//
//----------------------- VIRTUAL BASE CLASS ---------------------//
//----------------------- CHILD OF BIRDPLAYER --------------------//

//  This class provides the essential functions of a bird object.

//----------------------------------------------------------------//

#include "bird.h"

Bird::Bird(PlayerType ThisPlayer,
           ThreeVector Mom,
           ThreeVector Pos,
           double MaxMom,
           BirdType ThisBird)
    :BirdPlayer(ThisPlayer,
                Mom,
                Pos,
                MaxMom)
{
    //--Extend the original BirdPlayer construction to include a
    //--BirdType
    fBirdType = ThisBird;
}

void Bird::UpdateAndRestrict(ThreeVector delMom)
{
    //--Increment bird momentum
    this->SetMom(this->GetMom()+delMom);
    //--Perform maximum momentum restriction
    this->RestrictMom();
    //--Increment bird position
    this->SetPos(this->GetPos()+this->GetMom());
    //--Perform constraint of bird position to within virtual space
    //--parameters
    BoundaryConditions();
}


void Bird::RandomMovement(double NPlayers)
{
    //--Create a random vector, scaled both to the number of players
    //--the bird can react with and its maximum momentum
    ThreeVector delMom = RandomVector()*this->GetMaxMom()*(1.0/(2.0*NPlayers));

    //--Increment momentum and position
    this->UpdateAndRestrict(delMom);
}


void Bird::Avoid(ThreeVector ThingPos, double NPlayers)
{
    //--Scalar position difference
    double PosDiff = ThingPos.Mag() - this->GetPos().Mag();
    //--Vector position different
    ThreeVector PosDiffVect = ThingPos - this->GetPos();

    ThreeVector delMom = ThreeVector();
    //--Scale influence of behaviour to overall final motion
    double ScaleFactor = 1e-3/(2.0*NPlayers);

    //--Assign radius of sphere within which to steer away from
    //--obstacles
    double AvoidWithin = this->GetSight()/6.0;

    if (PosDiff == 0.0)
    {
        //--Move away with maximum momentum
        delMom = -this->GetMaxMom()*PosDiffVect*ScaleFactor;
    }
    else if (fabs(PosDiff) <= AvoidWithin)
    {
        //--Move away with momentum inversely proportional to position
        //--difference
        delMom = -PosDiffVect*fabs(AvoidWithin/PosDiff)*ScaleFactor;
    }

    //--Increment momentum and position
    this->UpdateAndRestrict(delMom);
}

Bird::~Bird()
{}

