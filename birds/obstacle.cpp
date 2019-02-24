//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//---------------------------- OBSTACLE ----------------------------//
//----------------------- CHILD OF BIRDPLAYER ----------------------//

//This class provides the essential functions of a neutral obstacle.

//-----------------------------------------------------------------//

#include "obstacle.h"

Obstacle::Obstacle(ThreeVector Mom,
                   ThreeVector Pos,
                   double MaxMom)
    :BirdPlayer(Neutral,
                Mom,
                Pos,
                MaxMom)
{}

void Obstacle::Move(BirdPlayer *ThisPlayer,
                    double NPlayers)
{
    //--Implementation of function that was pure virtual in BirdPlayer

    //--Declare unused parameters void to prevent compiler warnings
    (void) ThisPlayer;
    //--Assign weighting factor of movement based on number of times
    //--function will be called
    double ScaleFactor = 1.0/NPlayers;    
    //--Update the position of the obstacle
    SetPos(this->GetPos()+this->GetMom()*ScaleFactor);
    //--Constrain obstacle to virtual space defined in BirdPlayer
    BoundaryConditions();
}

Obstacle::~Obstacle()
{}

