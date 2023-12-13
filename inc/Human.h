//
// Created by joyce on 2023-12-10.
//

#ifndef ZOMBIEHUMAN_HUMAN_H
#define ZOMBIEHUMAN_HUMAN_H

#include "../inc//Organism.h"

class Human : public Organism
{
public:
    Human();
    Human( City *city, int x, int y );
    ~Human() override;

    void move() override;
    char getSpeciesCH() override;
    int getSpecies() override;
//    void turn();

    void spawn() override;

    bool starved() override;
//    void removeStarved();

    bool isTurned();
};
#endif //ZOMBIEHUMAN_HUMAN_H
