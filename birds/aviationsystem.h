//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------- AVIATIONSYSTEM -----------------------//

//  This class holds information about the objects within the
//  airspace and allows objects to be added to or removed from
//  an airspace.

//----------------------------------------------------------------//
#ifndef AVIATIONSYSTEM_H
#define AVIATIONSYSTEM_H

#include "prey.h"
#include "predator.h"
#include "obstacle.h"

#include <vector>

class AviationSystem
{
public:
    //--The constructor
    AviationSystem(int NPrey,
                   double PreyMaxMom,
                   int NPred,
                   double PredMaxMom,
                   int NObs,
                   double ObsMaxMom);

    //--Return specific element from a vector of real object pointers
    Prey *GetPrey(int ptr){ return fPreyFlock[ptr]; }
    Predator *GetPredator(int ptr){ return fPredFlock[ptr]; }
    Obstacle *GetObstacle(int ptr){ return fObsFlock[ptr]; }

    //--Return the integer number of elements in each array of real
    //--object pointers
    int PreyNumber(){ return fPreyFlock.size(); }
    int PredNumber(){ return fPredFlock.size(); }
    int ObsNumber(){ return fObsFlock.size(); }

    //--Assign new object of specific real class to system by providing
    //--pointer to instance of this class
    void AddPrey(Prey * newprey);
    void AddPred(Predator * newpred);
    void AddObs(Obstacle * newobs);

    //--Evolve the system forwards over a unit time step
    void Simulate();

    //--Remove specific element from a vector of real object pointers
    void ErasePrey(int ptr);
    void ErasePred(int ptr);
    void EraseObs(int ptr);

    //--Real desctructor
    ~AviationSystem();

private:

    //--Vectors of real object pointers
    std::vector< Prey* > fPreyFlock;
    std::vector< Predator* > fPredFlock;
    std::vector< Obstacle* > fObsFlock;

    //--Vector of pointers to objects inheriting from virtual base class
    std::vector< BirdPlayer* > fAllPlayers;

    //--Goal for prey to seek
    Obstacle *fGoal;

};

#endif // AVIATIONSYSTEM_H
