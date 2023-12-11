//
// Created by joyce on 2023-12-10.
//

#ifndef ZOMBIEHUMAN_CITY_H
#define ZOMBIEHUMAN_CITY_H

#include <iostream>
#include "../inc/Organism.h"
using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City
{

public:
    City();
    int humanCount();
    int zombieCount();
    static void Col(int);
    virtual ~City();
    Organism *getOrganism( int x, int y );
    void setOrganism( Organism *organism, int x, int y );
    void move();
    friend ostream& operator<<( ostream &output, City &city );
    void cityPrint();


    Organism *grid[GRID_HEIGHT][GRID_WIDTH];
};

#endif //ZOMBIEHUMAN_CITY_H
