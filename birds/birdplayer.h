//Isobel Romero-Shaw --------------------------------- 26.11.2016//

//-------------------------- BIRDPLAYER -------------------------//
//---------------------- VIRTUAL BASE CLASS ---------------------//

//   This class provides the essential functions of an object with
//                  which a bird might interact.

//---------------------------------------------------------------//

#ifndef BIRDPLAYER_H
#define BIRDPLAYER_H

#include "ThreeVector.h"

//--Set the parameters of the space within which players interact
#define Width 800.0
#define Height 600.0
#define Depth 300.0

class BirdPlayer
{
public:

    //--Enumerated list of possible player types
    enum PlayerType {Neutral,
                     Dangerous,
                     Friendly};

    //--The constructor
    BirdPlayer(PlayerType Player,
               ThreeVector Mom,
               ThreeVector Pos,
               double MaxMom);

    //--Return a random ThreeVector scaled to the width and height
    //--of the space, with a z-component of maximum value
    //--This is used to initialise player positions and causes them
    //--to be always initially in the foreground
    ThreeVector RandPos();

    //--Return a random ThreeVector with element values in the
    //--range -0.5 to 0.5
    ThreeVector RandomVector();

    //--Return the three-dimensional position vector of the player
    ThreeVector GetPos(){ return fPos; }

    //--Return the three-dimentional momentum vector of the player
    ThreeVector GetMom(){ return fMom; }

    //--Return the maximum allowed magnitude of the momentum vector
    //--of the player
    double GetMaxMom(){ return fMaxMom; }

    //--Assign the position of the player
    void SetPos(ThreeVector Pos){ fPos = Pos; }

    //--Assign the momentum of the player
    void SetMom(ThreeVector Mom){ fMom = Mom; }

    //--Assign the type of player
    void SetPlayerType(PlayerType Player){fPlayerType = Player; }

    //--Assign the maximum momentum
    void SetMaxMom(double MaxMom){ fMaxMom = MaxMom; }

    //--Restrict position of player to within the parameters of the
    //--defined space
    void BoundaryConditions();

    //--Restrict magnitude of player momentum to below allowed maximum
    void RestrictMom();

    //--Virtual functions set equal to 0, which are explicitly
    //--defined in instantiable inheriting classes
    virtual void Move(BirdPlayer * ThisPlayer,
                      double NPlayers) = 0;
    virtual int GetPlayerType() = 0;

    //--Virtual destructor
    virtual ~BirdPlayer();

private:

    //--The type of player
    PlayerType fPlayerType;

    //--Momentum of player
    ThreeVector fMom;

    //--Position of player
    ThreeVector fPos;

    //--Maximum magnitude of player momentum
    double fMaxMom;

};

#endif // BIRDPLAYER_H
