//
// Created by joyce on 2023-12-10.
//
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "../inc/Human.h"
#include "../inc/GameSpecs.h"
#include "../inc/Organism.h"
#include "../inc/City.h"

//Default constructor
Human ::Human() : Organism(){
   //INTENTIONALLY LEAVE BLANK
}

//Overloaded Constructor
Human ::Human(City *city, int x, int y) : Organism(city,x,y ){
    //INTENTIONALLY LEAVE BLANK
}
//Overloaded Move()
void Human ::move() {

    //USE A VECTOR TO RANDOM DIRECTION,HUMAN CAN ONLY MOVE TO EMPTY CELLS
    vector <int> direction;

    if(y-1 >=0 && city->getOrganism(x,y-1)== nullptr){
        direction.push_back(NORTH);
    }
    if(y+1 >=0 && city->getOrganism(x,y+1)== nullptr){
        direction.push_back(SOUTH);
    }
    if(x-1 >=0 && city->getOrganism(x-1,y)== nullptr){
        direction.push_back(WEST);
    }
    if(x+1 >=0 && city->getOrganism(x+1,y)== nullptr){
        direction.push_back(EAST);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(direction.begin(),direction.end(),default_random_engine(seed));
    auto randomDirection = static_cast<Direction>(direction[0]);

    switch (randomDirection) {
        case NORTH:
            if (y>0 && city->getOrganism(x, y-1) == nullptr){
                city->setOrganism(this,x,y-1);
                city->setOrganism(nullptr,x,y);
                y--;
            }
            break;
        case SOUTH:
            if (y < GRIDSIZE-1 && city->getOrganism(x, y+1) == nullptr){
                city->setOrganism(this,x,y+1);
                city->setOrganism(nullptr,x,y);
                y++;
            }
            break;

        case WEST:
            if (x > 0 && city->getOrganism(x-1, y) == nullptr){
                city->setOrganism(this,x-1,y);
                city->setOrganism(nullptr,x,y);
                x--;
            }
            break;
        case EAST:
            if (x < GRIDSIZE-1 && city->getOrganism(x+1, y) == nullptr){
                city->setOrganism(this,x+1,y);
                city->setOrganism(nullptr,x,y);
                x++;
            }
            break;
    }

} //END MOVE FUNCTION

int Human ::getSpecies() {
    return static_cast<int>(HUMAN);
}
char Human ::getSpeciesCH() {
    return HUMAN_CH;

}

//HUMAN RECRUIT
void Human ::spawn() {
    if (timeSteps >= HUMAN_BREED) {
        vector<int> direction;

        if (y - 1 >= 0 && city->getOrganism(x, y - 1) == nullptr) {
            direction.push_back(NORTH);
        }
        if (y + 1 >= 0 && city->getOrganism(x, y + 1) == nullptr) {
            direction.push_back(SOUTH);
        }
        if (x - 1 >= 0 && city->getOrganism(x - 1, y) == nullptr) {
            direction.push_back(WEST);
        }
        if (x + 1 >= 0 && city->getOrganism(x + 1, y) == nullptr) {
            direction.push_back(EAST);
        }

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(direction.begin(), direction.end(), default_random_engine(seed));
        auto randomDirection = static_cast<Direction>(direction[0]);

        if (!direction.empty()) {
            switch (randomDirection) {
                case NORTH:
                    new Human(city, x, y - 1);
                    break;
                case SOUTH:
                    new Human(city, x, y + 1);
                    break;
                case WEST:
                    new Human(city, x - 1, y);
                    break;
                case EAST:
                    new Human(city, x + 1, y);
                    break;
            }
        }
        timeSteps=0;
    }
} //END HUMAN MOVE METHOD

bool Human ::starved() {
    return false;
}

Human :: ~Human()  {

}