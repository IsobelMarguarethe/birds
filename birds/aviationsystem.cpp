//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------- AVIATIONSYSTEM -----------------------//

//  This class holds information about the objects within the
//  airspace and allows objects to be added to or removed from
//  an airspace.

//----------------------------------------------------------------//

#include "aviationsystem.h"

#include <stdio.h>

AviationSystem::AviationSystem(int NPrey,
                               double PreyMaxMom,
                               int NPred,
                               double PredMaxMom,
                               int NObs,
                               double ObsMaxMom)
{
    //--Build initial Prey vector
    for(int i=0; i<NPrey; i++)
    {
        //--Create new instance of Prey object
        Prey *nextprey = new Prey(ThreeVector(),
                                  ThreeVector(),
                                  PreyMaxMom);
        //--Assign random position
        nextprey->SetPos(nextprey->RandPos());
        //--Insert pointer into Prey vector
        AddPrey(nextprey);
        //--Insert pointer into BirdPlayer vector
        fAllPlayers.push_back(nextprey);
    }

    //--Build initial Predator vector
    for(int j=0; j<NPred; j++)
    {
        //--Create new instance of Predator object
        Predator *nextpred = new Predator(ThreeVector(),
                                          ThreeVector(),
                                          PredMaxMom);
        //--Assign random position
        nextpred->SetPos(nextpred->RandPos());
        //--Insert pointer into Predator vector
        AddPred(nextpred);
        //--Insert pointer into BirdPlayer vector
        fAllPlayers.push_back(nextpred);
    }

    //--Build initial Obstacle vector
    for(int l=0; l<NObs; l++)
    {
        //--Create new instance of Obstacle object
        Obstacle *nextobs = new Obstacle(ThreeVector(),
                                         ThreeVector(),
                                          ObsMaxMom);
        //--Assign random position
        nextobs->SetPos(nextobs->RandPos());
        //--Assign random momentum scaled to maximum momentum
        //--of obstacle
        nextobs->SetMom(nextobs->RandomVector()*ObsMaxMom);
        //--Insert pointer into Obstacle vector
        fAllPlayers.push_back(nextobs);
        //--Insert pointer into BirdPlayer vector
        AddObs(nextobs);
    }

    //--Initialise goal for Prey to seek
    double GoalMaxMom = PreyMaxMom*50.0;
    fGoal = new Obstacle(ThreeVector(),
                         ThreeVector(),
                         GoalMaxMom);
    //--Assign random starting position
    fGoal->SetPos(fGoal->RandPos());
    //--Assign random momentum scaled to maximum momentum
    //--of goal
    fGoal->SetMom(fGoal->RandomVector()*GoalMaxMom);
}

void AviationSystem::AddPrey(Prey *newprey)
{
    //--Allow external addition of Prey pointers into the Prey vector
    fPreyFlock.push_back(newprey);
}

void AviationSystem::AddPred(Predator *newpred)
{
    //--Allow external addition of Predator pointers into the Predator vector
    fPredFlock.push_back(newpred);
}

void AviationSystem::AddObs(Obstacle *newobs)
{
    //--Allow external addition of Obstacle pointers into the Obstacle vector
    fObsFlock.push_back(newobs);
}

void AviationSystem::Simulate()
{
    //--Clear the BirdPlayer vector, causing it to have zero components at
    //--the start of every call to Simulate
    fAllPlayers.clear();

    double NPrey = fPreyFlock.size();
    double NPred = fPredFlock.size();
    double NObs = fObsFlock.size();

    //--Update the position of the goal
    fGoal->Move(fGoal, 1.0);

    //--Update the BirdPlayer vector with all current players:
    //--Current Prey
    for (int i=0; i<NPrey; i++)
    {
        this->GetPrey(i)->FlockWith(fGoal->GetPos(), NPrey);
        fAllPlayers.push_back(this->GetPrey(i));
    }
    //--Current Predators
    for (int i=0; i<NPred; i++)
    {
        fAllPlayers.push_back(this->GetPredator(i));
    }
    //--Current Objects
    for (int i=0; i< NObs; i++)
    {
        fAllPlayers.push_back(this->GetObstacle(i));
    }

    double NAll = fAllPlayers.size();

    //--Evolve the current system to its next state:
    for (int i=0; i< NAll; i++)
    {
        //--A Predator hunts only one Prey from the flock, so is passed only
        //--one Prey pointer
        if (fAllPlayers[i]->GetPlayerType() == BirdPlayer::Dangerous)
        {
            fAllPlayers[i]->Move(fAllPlayers[i - NPrey], NAll);

            for (int j = 0; j< NAll; j++)
            {
                //--A Predator avoids other Predators and Obstacles, so is
                //--passed all non-Prey pointers
                if (fAllPlayers[j]->GetPlayerType() != BirdPlayer::Friendly)
                {
                    fAllPlayers[i]->Move(fAllPlayers[j], NAll);
                }
            }
        }
        else
        {
            for(int j=0; j<NAll; j++)
            {
                    //--Move all Prey and Obstacles
                    this->fAllPlayers[i]->Move(this->fAllPlayers[j], NAll);
            }
        }
    }
}

void AviationSystem::ErasePrey(int ptr)
{
    //--Release the memory storing the Prey pointer
    delete fPreyFlock[ptr];
    //--Remove the pointer from the Prey vector component
    fPreyFlock.erase(fPreyFlock.begin() + ptr);
}

void AviationSystem::ErasePred(int ptr)
{
    //--Release the memory storing the Predator pointer
    delete fPredFlock[ptr];
    //--Remove the pointer from the Predator vector component
    fPredFlock.erase(fPredFlock.begin() + ptr);
}

void AviationSystem::EraseObs(int ptr)
{
    //--Release the memory storing the Obstacle pointer
    delete fObsFlock[ptr];
    //--Remove the pointer from the Obstacle vector component
    fObsFlock.erase(fObsFlock.begin() + ptr);
}

AviationSystem::~AviationSystem()
{
    int NPrey = fPreyFlock.size();
    //--Delete all Prey
    for (int i = 0; i < NPrey; i++)
    {
        ErasePrey(i);
    }

    int NPred = fPredFlock.size();
    //--Delete all Predators
    for (int i = 0; i < NPred; i++)
    {
        ErasePred(i);
    }

    int NObs = fObsFlock.size();
    //--Delete all Objects
    for (int i = 0; i < NObs; i++)
    {
        EraseObs(i);
    }

    int NAvSyst = fAllPlayers.size();
    //--Delete all players
    for (int i = 0; i < NAvSyst; i++)
    {
        //--Release the memory storing the pointer
        delete fAllPlayers[i];
        //--Remove the pointer from the vector
        fAllPlayers.erase(fAllPlayers.begin() + i);
    }

    delete fGoal;

}

