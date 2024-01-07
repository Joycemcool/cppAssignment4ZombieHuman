//
// Created by joyce on 2023-12-10.
//

#ifndef ZOMBIEHUMAN_ORGANISM_H
#define ZOMBIEHUMAN_ORGANISM_H

#include <iostream>
#include "../inc/City.h"

using namespace std;


class City;
class Human;
class Zombie;

class Organism
{
protected:
    City *city;
    int timeSteps;
    enum Direction { NORTH, NORTHEAST,EAST,SOUTHEAST, SOUTH,SOUTHWEST,WEST,NORTHWEST };
    bool turned;

public:
    int x;
    int y;
    Organism();
    Organism( City *city, int x, int y);
    virtual ~Organism();
    virtual void move() = 0;
    virtual bool starved()=0;
    virtual char getSpeciesCH() = 0;
    virtual void spawn() = 0; //CONVERT HUMAN TO ZOMBIE,RECRUIT NEW HUMAN
    virtual int getSpecies() = 0; //CODE IN DERIVED CLASS
    bool moved;
    enum Species {ZOMBIE, HUMAN, NUM_SPECIES};
    virtual bool isTurned()=0;
    friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif //ZOMBIEHUMAN_ORGANISM_H
