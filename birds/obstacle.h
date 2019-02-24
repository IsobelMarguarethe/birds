//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//---------------------------- OBSTACLE ----------------------------//
//----------------------- CHILD OF BIRDPLAYER ----------------------//

//This class provides the essential functions of a neutral obstacle.

//------------------------------------------------------------------//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "birdplayer.h"

class Obstacle : public BirdPlayer
{
public:

    //--The constructor
    Obstacle(ThreeVector Mom,
           ThreeVector Pos,
           double MaxMom);

    //--Explicitly implement functions defined pute virtual in parent
    //--class:
    //--Return Neutral player type
    virtual int GetPlayerType(){ return Neutral; }   
    //--Update position of obstacle
    virtual void Move(BirdPlayer * ThisPlayer,
                      double NPlayers);

    //--Virtual destructor
    virtual ~Obstacle();
};

#endif // OBSTACLE_H
