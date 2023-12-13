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
   breedCount= false;
}

Zombie ::Zombie( City *city, int x, int y ) :Organism(city, x, y){
    //Figure out what's inside the default constructor
    this->city=city;
    starveCount=0;
    eaten= false;
    breedCount= false;
}

bool Zombie::isTurned() {
    return turned; //What's the difference of turned and
}


void Zombie ::move() {
    //USE A VECTOR TO RANDOM DIRECTION
    turned = true; //What's the fuction here?

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
    if((x+1 <GRID_WIDTH && y+1 <GRID_HEIGHT )&& (city->getOrganism(x+1,y+1)== nullptr||city->getOrganism(x+1,y+1)->getSpecies()==HUMAN)){
        directions.push_back(SOUTHEAST);
    }
    if(y+1 <GRID_HEIGHT && (city->getOrganism(x,y+1)== nullptr||city->getOrganism(x,y+1)->getSpecies()==HUMAN)){
        directions.push_back(SOUTH);
    }
    if((x-1 >=0 && y+1<GRID_HEIGHT)&& (city->getOrganism(x-1,y+1)== nullptr||city->getOrganism(x-1,y+1)->getSpecies()==HUMAN)){
        directions.push_back(SOUTHWEST);
    }
    if(x-1 >=0 && (city->getOrganism(x-1,y)== nullptr||city->getOrganism(x-1,y)->getSpecies()==HUMAN)){
        directions.push_back(WEST);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(directions.begin(),directions.end(),default_random_engine(seed));

    if(!directions.empty()){
        auto randomDirection = static_cast<Direction>(directions[0]);
        //set origianl positon null
        city->setOrganism(nullptr,x,y);
        switch (randomDirection) {
            case NORTH:
                if (city->getOrganism(x, y-1)!= nullptr&& city->getOrganism(x, y-1)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x,y-1);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x, y-1);
                this->y--;
                break;
            case NORTHEAST:
                if (city->getOrganism(x+1, y-1)!= nullptr&&city->getOrganism(x+1, y-1)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x+1,y-1);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x+1, y-1);
                this->x++, y--;
                break;
            case EAST:
                if (city->getOrganism(x+1, y)!= nullptr&&city->getOrganism(x+1, y)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x+1,y);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x+1, y);
                this->x++;
                break;
            case SOUTHEAST:
                if (city->getOrganism(x+1, y+1)!= nullptr&&city->getOrganism(x+1, y+1)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x+1,y+1);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x+1, y+1);
                this->x++,y++;

                break;
            case SOUTH:
                if (city->getOrganism(x, y+1)!= nullptr&&city->getOrganism(x, y+1)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x,y+1);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x, y+1);
                this->y++;
                break;
            case SOUTHWEST:
                if (city->getOrganism(x-1, y+1)!= nullptr&&city->getOrganism(x-1, y+1)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x-1,y+1);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x-1, y+1);
                this->x--,y++;
                break;
            case WEST:
                if (city->getOrganism(x-1, y)!= nullptr&&city->getOrganism(x-1, y)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x-1,y);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this, x-1, y);
                this->x--;
                break;
            case NORTHWEST:
                if (city->getOrganism(x-1, y-1)!= nullptr&&city->getOrganism(x-1, y-1)->getSpecies() == HUMAN) {
                    delete city->getOrganism(x-1,y-1);
                    eaten = true;
                    starveCount=0;
                }
                else{
                    starveCount++;
                }
                city->setOrganism(this,x-1,y-1);
                this->x--,y--;
                break;
        }//END SWITCH
        timeSteps++;
        moved = true;
        if(timeSteps>=8){
            breedCount= true;
        }
    }//END IF DIRECTIONS IS NOT EMPTY
    else{
        cout<<"nothing change"<<endl;
    }
}//END OF MOVE FUNCTION

int Zombie ::getSpecies() {
    return static_cast<int>(ZOMBIE);
}//END OF GETSPECIES FUNCTION

char Zombie ::getSpeciesCH() {
    return ZOMBIE_CH;
}//END GETSPECIESCH function

bool Zombie::starved() {
    //starve
    if (starveCount >= ZOMBIE_STARVE && !eaten) {
        return true;
    }
        //survive
    else {
        return false;
    }
}

//void Zombie :: removeStarved(){
//    this= nullptr;
//}
void Zombie::spawn() {
    if (timeSteps >= ZOMBIE_BREED && eaten && breedCount){
        vector <int> directions;
        //BUILD THE VECTOR
        if(y-1 >=0 &&city->getOrganism(x,y-1)!= nullptr&& city->getOrganism(x,y-1)->getSpecies()==HUMAN){
            directions.push_back(NORTH);
        }
        if((x+1<GRID_WIDTH && y-1 >=0 )&& city->getOrganism(x+1,y-1)!= nullptr&&city->getOrganism(x+1,y-1)->getSpecies()==HUMAN){
            directions.push_back(NORTHEAST);
        }
        if(x+1 <GRID_WIDTH && city->getOrganism(x+1,y)!= nullptr&&city->getOrganism(x+1,y)->getSpecies()==HUMAN){
            directions.push_back(EAST);
        }
        if((x+1 <GRID_WIDTH && y+1<GRID_WIDTH) && city->getOrganism(x+1,y+1)!= nullptr&&city->getOrganism(x+1,y+1)->getSpecies()==HUMAN){
            directions.push_back(SOUTHEAST);
        }
        if(y+1 <GRID_HEIGHT && city->getOrganism(x,y+1)!= nullptr&&city->getOrganism(x,y+1)->getSpecies()==HUMAN){
            directions.push_back(SOUTH);
        }
        if((x-1 >=0 && y+1<GRID_HEIGHT)&&city->getOrganism(x-1,y+1)!= nullptr&&city->getOrganism(x-1,y+1)->getSpecies()==HUMAN){
            directions.push_back(SOUTHWEST);
        }
        if(x-1 >=0 && city->getOrganism(x-1,y)!= nullptr&&city->getOrganism(x-1,y)->getSpecies()==HUMAN){
            directions.push_back(WEST);
        }

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(directions.begin(),directions.end(),default_random_engine(seed));

        if(!directions.empty()){
            //Breed
            auto randomDirection = static_cast<Direction>(directions[0]);
            switch (randomDirection) {
                case NORTH:
                    city->setOrganism(nullptr,x,y-1);
                    city->setOrganism(new Zombie(city, x, y-1),x,y-1);
                    break;
                case NORTHEAST:
                    city->setOrganism(nullptr,x+1,y-1);
                    city->setOrganism(new Zombie(city, x+1, y-1),x+1,y-1);
                    break;
                case EAST:
                    city->setOrganism(nullptr,x+1,y);
                    city->setOrganism(new Zombie(city, x+1, y),x+1,y);
                    break;
                case SOUTHEAST:
                    city->setOrganism(nullptr,x+1,y+1);
                    city->setOrganism(new Zombie(city, x+1, y+1),x+1,y+1);
                    break;
                case SOUTH:
                    city->setOrganism(nullptr,x,y+1);
                    city->setOrganism(new Zombie(city, x, y+1),x,y+1);
                    break;
                case SOUTHWEST:
                    city->setOrganism(nullptr,x-1,y+1);
                    city->setOrganism(new Zombie(city, x-1, y+1),x-1,y+1);
                    break;
                case WEST:
                    city->setOrganism(nullptr,x-1,y);
                    city->setOrganism(new Zombie(city, x-1, y),x-1,y);
                    break;
                case NORTHWEST:
                    city->setOrganism(nullptr,x-1,y-1);
                    city->setOrganism(new Zombie(city, x-1, y-1),x-1,y-1);
                    break;
            }//END SWITCH
            breedCount= false;
            timeSteps = 0; //DOUBLE CHECK IF TIMESTEPS INCREMENT OR NOT
        }//END DIRECTIONS EMPTY
        else{
            //If no human around
            cout<<"Zombie no breed with breed count available"<<endl;
            }
        //BREED COUNT PROBLEM NOT SOLVED.

    }//END IF TIMESTEPS CONDITON
}//END SPAWN METHOD

Zombie :: ~Zombie()  = default;