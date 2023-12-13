//
// Created by joyce on 2023-12-10.
//

#ifndef ZOMBIEHUMAN_ZOMBIE_H
#define ZOMBIEHUMAN_ZOMBIE_H

#include "Organism.h"
#include "City.h"

class Zombie : public Organism
{
public:
    Zombie();
    Zombie( City *city, int x, int y );
    ~Zombie() override;

    void move() override;
    char getSpeciesCH() override;
    int getSpecies() override;
    int starveCount;
    bool starved() override;
    void spawn() override;
    bool breedCount;
    bool isTurned();

private:
    bool eaten;

};
#endif //ZOMBIEHUMAN_ZOMBIE_H
