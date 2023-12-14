//
// Created by joyce on 2023-12-10.
//

#include "../inc/Organism.h"
#include "../inc/City.h"
#include "../inc/GameSpecs.h"

//Creates a default organism
Organism ::Organism() {
    x=0;
    y=0;
    city = nullptr;
    moved = false;
    timeSteps=0;
    turned= false;
}

//OVERLOADED CONSTRUCTOR CREATE AND ORGANISM IN THE GRID ARRAY
Organism ::Organism(City *city, int x, int y) {
//    this ->width = width;
//    this->height = height;
    this->x =x;
    this->y =y;
    this->city = city;
//    city->setOrganism(this,x,y);
    moved = false;
    timeSteps=0;
}

ostream& operator<<( ostream &output, Organism *organism ){
    if(organism!= nullptr){
        output << organism->getSpeciesCH();

    }
    else{
        output << '_';
    }
    return output;
}

Organism :: ~Organism() {};
