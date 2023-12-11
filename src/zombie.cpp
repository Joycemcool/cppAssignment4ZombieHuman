//
// Created by joyce on 2023-12-10.
//

#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "../inc/Zombie.h"
#include "../inc/Organism.h"
#include "../inc/City.h"
#include "../inc/GameSpecs.h"

//Default Constructor
Zombie ::Zombie() :Organism() {
   //INTENTIONALLY LEFT BLANK
   starveCount=0;
   eaten = false;
}

Zombie ::Zombie( City *city, int x, int y ) :Organism(city, x, y){
    //Figure out what's inside the default constructor
    starveCount=0;
    eaten= false;
}


void Zombie ::move() {
    //USE A VECTOR TO RANDOM DIRECTION
    vector <int> directions;
    if(y-1 >=0 && (city->getOrganism(x,y-1)== nullptr||city->getOrganism(x,y-1)->getSpecies()==HUMAN)){
        directions.push_back(NORTH); //out of reach
    }
    if((x+1<GRID_WIDTH && y-1 >=0 )&& (city->getOrganism(x+1,y-1)== nullptr || city->getOrganism(x+1,y-1)->getSpecies()==HUMAN)){
        directions.push_back(NORTHEAST);
    }
    if(x+1 <GRID_WIDTH && (city->getOrganism(x+1,y)== nullptr||city->getOrganism(x+1,y)->getSpecies()==HUMAN)){
        directions.push_back(EAST);
    }
    if((x+1 <GRID_WIDTH && y+1 <GRID_HEIGHT )&& city->getOrganism(x+1,y+1)== nullptr||city->getOrganism(x+1,y+1)->getSpecies()==HUMAN){
        directions.push_back(SOUTHEAST);
    }
    if(y+1 >=GRID_HEIGHT && city->getOrganism(x,y+1)== nullptr||city->getOrganism(x,y+1)->getSpecies()==HUMAN){
        directions.push_back(SOUTH);
    }
    if((x-1 >=0 && y+1<GRID_HEIGHT)&&city->getOrganism(x-1,y+1)== nullptr||city->getOrganism(x-1,y-1)->getSpecies()==HUMAN){
        directions.push_back(SOUTHWEST);
    }
    if(x-1 >=0 && city->getOrganism(x-1,y)== nullptr||city->getOrganism(x-1,y)->getSpecies()==HUMAN){
        directions.push_back(WEST);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(directions.begin(),directions.end(),default_random_engine(seed));
    auto randomDirection = static_cast<Direction>(directions[0]);

    if(!directions.empty()){
        //Up check if human
        switch (randomDirection) {
            case NORTH:
                if (city->getOrganism(x, y - 1)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x][y - 1]);
                    eaten = true;
                }
                city->setOrganism(this, x, y - 1);
                city->grid[x][y - 1] = this; //is it duplicated?
                this->y--;
                break;
            case NORTHEAST:
                if (city->getOrganism(x + 1, y - 1)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x + 1][y - 1]);
                    eaten = true;
                }
                city->setOrganism(this, x+1, y - 1);
                city->grid[x+1][y - 1] = this; //is it duplicated?
                this->x++, y--;
                break;
            case EAST:
                if (city->getOrganism(x + 1, y)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x + 1][y]);
                    eaten = true;
                }
                city->setOrganism(this, x+1, y);
                city->grid[x+1][y - 1] = this;
                this->x++;
                break;
            case SOUTHEAST:
                if (city->getOrganism(x+1, y+1)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x+1][y+1]);
                    eaten = true;
                }
                city->setOrganism(this, x+1, y+1);
                city->grid[x+1][y+1] = this;
                this->x++,y++;
                break;
            case SOUTH:
                if (city->getOrganism(x, y+1)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x][y+1]);
                    eaten = true;
                }
                city->setOrganism(this, x, y+1);
                city->grid[x][y+1] = this;
                this->y++;
                break;
            case SOUTHWEST:
                if (city->getOrganism(x-1, y+1)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x-1][y+1]);
                    eaten = true;
                }
                city->setOrganism(this, x-1, y+1);
                city->grid[x-1][y+1] = this;
                this->x--,y++;
                break;
            case WEST:
                if (city->getOrganism(x-1, y)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x-1][y]);
                    eaten = true;
                }
                city->setOrganism(this, x-1, y);
                city->grid[x-1][y] = this;
                this->x--;
                break;
            case NORTHWEST:
                if (city->getOrganism(x-1, y-1)->getSpeciesCH() == HUMAN_CH) {
                    delete (city->grid[x-1][y-1]);
                    eaten = true;
                }
                city->setOrganism(this, x-1, y-1);
                city->grid[x-1][y-1] = this;
                this->x--;
                break;
        }
        city->setOrganism(nullptr, x, y);
        timeSteps++;
        starveCount++;
        //reset the moved flag
        moved = true;
    }//END IF DIRECTIONS IS NOT EMPTY

}//END OF MOVE FUNCTION

int Zombie ::getSpecies() {
    return static_cast<int>(ZOMBIE);
}//END OF GETSPECIES FUNCTION

char Zombie ::getSpeciesCH() {
    return ZOMBIE_CH;
}//END GETSPECIESCH function

bool Zombie::starved() {
    //starve
    if (starveCount > ZOMBIE_STARVE && !eaten) {
        return true;
    }
        //survive
    else {
        return false;
    }
}
void Zombie::spawn() {
    if (timeSteps >= ZOMBIE_BREED && eaten){
        vector <int> directions;

        //BUILD THE VECTOR
        if(y-1 >=0 && city->getOrganism(x,y-1)->getSpecies()==HUMAN){
            directions.push_back(NORTH);
        }
        if((x+1<GRID_WIDTH && y-1 >=0 )&& city->getOrganism(x+1,y-1)->getSpecies()==HUMAN){
            directions.push_back(NORTHEAST);
        }
        if(x+1 <GRID_WIDTH && city->getOrganism(x+1,y)->getSpecies()==HUMAN){
            directions.push_back(EAST);
        }
        if((x+1 <GRID_WIDTH && y+1<GRID_WIDTH) && city->getOrganism(x+1,y+1)->getSpecies()==HUMAN){
            directions.push_back(SOUTHEAST);
        }
        if(y+1 >=GRID_HEIGHT && city->getOrganism(x,y+1)->getSpecies()==HUMAN){
            directions.push_back(SOUTH);
        }
        if((x-1 >=0 && y+1<GRID_HEIGHT)&&city->getOrganism(x-1,y-1)->getSpecies()==HUMAN){
            directions.push_back(SOUTHWEST);
        }
        if(x-1 >=0 && city->getOrganism(x-1,y)->getSpecies()==HUMAN){
            directions.push_back(WEST);
        }

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(directions.begin(),directions.end(),default_random_engine(seed));

        if(!directions.empty()){
            auto randomDirection = static_cast<Direction>(directions[0]);
            switch (randomDirection) {
                case NORTH:
                    delete city->grid[x][y-1];
                    new Zombie(city, x, y-1);
                    break;
                case NORTHEAST:
                    delete city->grid[x+1][y-1];
                    new Zombie(city, x+1, y-1);
                    break;
                case EAST:
                    delete city->grid[x+1][y];
                    new Zombie(city, x+1, y);
                    break;
                case SOUTHEAST:
                    delete city->grid[x+1][y+1];
                    new Zombie(city, x+1, y+1);
                    timeSteps = 0;
                    break;
                case SOUTH:
                    delete city->grid[x][y+1];
                    new Zombie(city, x, y+1);
                    break;
                case SOUTHWEST:
                    delete city->grid[x-1][y+1];
                    new Zombie(city, x-1, y+1);
                    break;
                case WEST:
                    delete city->grid[x-1][y];
                    new Zombie(city, x-1, y);
                    break;
                case NORTHWEST:
                    delete city->grid[x=1][y-1];
                    city->grid[x-1][y-1] = new Zombie(city, x-1, y-1);
                    break;
            }//END SWITCH
            timeSteps = 0; //DOUBLE CHECK IF TIMESTEPS INCREMENT OR NOT
        }//END DIRECTIONS EMPTY
        else{
            if(timeSteps<=9){
                timeSteps++;
            }
            else{
                timeSteps=0;
            }

        }
    }//END IF TIMESTEPS CONDITON

}//END SPAWN METHOD

Zombie :: ~Zombie()  {

}