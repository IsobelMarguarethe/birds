//Isobel Romero-Shaw --------------------------------- 26.11.2016//

//-------------------------- BIRDPLAYER -------------------------//
//---------------------- VIRTUAL BASE CLASS ---------------------//

//   This class provides the essential functions of an object with
//                  which a bird might interact.

//---------------------------------------------------------------//

#include "birdplayer.h"
#include <iostream>

BirdPlayer::BirdPlayer(PlayerType Player,
                       ThreeVector Mom,
                       ThreeVector Pos,
                       double MaxMom)
{
    //--Assign private data members
    fPos = Pos;
    fMom = Mom;
    fPlayerType = Player;
    fMaxMom = MaxMom;
}

ThreeVector BirdPlayer::RandPos()
{
    //--Creates a random position vector scaled to the virtual
    //--space
    double Max = double( RAND_MAX );
    return ThreeVector((double(rand())/Max)*Width,
                       (double(rand())/Max)*Height,
                        Depth);
}

ThreeVector BirdPlayer::RandomVector()
{

    //--Creates a ThreeVector of random values between -.5 and .5
    double Max = double (RAND_MAX);
    ThreeVector New;
    New.SetXYZ((double(rand())/Max) - 0.5,
               (double(rand())/Max) - 0.5,
               (double(rand())/Max) - 0.5);
    return New;
}

void BirdPlayer::BoundaryConditions()
{
    double Origin = 0.0;

    //--Cause elastic reflection at the boundaries of the virtual
    //--space
    if (fPos.X() > Width)
    {
        fPos.SetX(Width);
        fMom.SetX(-fabs(fMom.X()));
    }
    else if (fPos.X() < Origin)
    {
        fPos.SetX(Origin);
        fMom.SetX(fabs(fMom.X()));
    }

    if (fPos.Y() > Height)
    {
        fPos.SetY(Height);
        fMom.SetY(-fabs(fMom.Y()));
    }
    else if (fPos.Y() < Origin)
    {
        fPos.SetY(Origin);
        fMom.SetY(fabs(fMom.Y()));
    }

    if (fPos.Z() > Depth)
    {
        fPos.SetZ(Depth);
        fMom.SetZ(-fabs(fMom.Z()));
    }
    else if (fPos.Z() < Origin)
    {
        fPos.SetZ(Origin);
        fMom.SetZ(fabs(fMom.Z()));
    }
}

void BirdPlayer::RestrictMom()
{
    if (fMom.Mag() > fMaxMom)
    {
        //--Prevent player from exceeding its maximum momentum
        ThreeVector NewMom = fMom*(1.0/fMom.Mag());
        fMom = NewMom*(fMaxMom);
    }
}

void BirdPlayer::Move(BirdPlayer *ThisPlayer,
                      double NPlayers)
{
    //--Declare unused parameters void to prevent compiler warnings
    (void) ThisPlayer;
    (void) NPlayers;
}

BirdPlayer::~BirdPlayer()
{}

