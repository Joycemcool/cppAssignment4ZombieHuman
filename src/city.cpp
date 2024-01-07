//
// Created by joyce on 2023-12-10.
//

#include <windows.h>
#include <random>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../inc/City.h"
#include "../inc/GameSpecs.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"
#include "../inc/Organism.h"
#include <random>
using namespace std;
class Organism;
class Human;
class Zombie;
using namespace std;

//This doesn't work in laptop, works in lab machine
void Col(int);

void Col(int c)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

City ::City() {
    cout<<"City Default Constructor called, fill with nullptr and start organisms\n"<<endl;

    int count=0;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, GRID_WIDTH-1);
    while (count < HUMAN_STARTCOUNT) {

        int x = dist(mt);
        int y = dist(mt);
        if(grid[x][y] ==nullptr){
            setOrganism(new Human(this,x,y), x, y);
            count++;
        }
    }


    // Fill the grid with Zombies, equally in the Grid
    count=0;
    std::vector<int> targetRows = {4, 7, 11, 15, 19};
    int startJ = GRID_HEIGHT/2;
    for(int i=0;i<ZOMBIE_STARTCOUNT && count < ZOMBIE_STARTCOUNT;++i){
        int currentI = targetRows[i];
        int currentJ = startJ;

        while (currentJ < GRID_HEIGHT && grid[currentI][currentJ] != nullptr) {
            currentJ++;
        }
        // Check if we found an available position
        if (currentJ < GRID_HEIGHT) {
            setOrganism(new Zombie(this, currentI, currentJ), currentI, currentJ);
            count++;
        }

    }
} //END CITY DEFAULT CONSTRUCTOR

Organism* City ::getOrganism(int x, int y) {
        return this->grid[x][y];
}

//Fills the cell at coordinates x and y with an object
void City ::setOrganism(Organism *organism, int x, int y) {
        grid[x][y] = organism;
}

//Need move() and friend ostream& operator
void City ::move() {
    vector <int> randomTable;
    for(int i = 0; i < 400; i++) {
        randomTable.push_back(i);
    }

    // using built-in random generator, shuffle the vector so its in a random order
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(randomTable.begin(),randomTable.end(),default_random_engine(seed));

    //(1) First reset all organisms so none of them have moved
    //NEED TO SET TURNED HERE?
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            Organism *pOrganism = getOrganism(i,j);
            if (pOrganism != nullptr) {
                pOrganism->moved = false;
            }
        }
    }

    //Random selection of Human/Zombie for movement, loop 400 times
    for(auto z = randomTable.begin(); z != randomTable.end(); ++z) {

        int i = *z / 20; //for row
        int j = *z % 20; //for column


        Organism *pOrganism = getOrganism(i,j);
        //FIRST CHECK ZOMBIE STARVED
        if (pOrganism != nullptr) {
            if(pOrganism->starved())
            {
                this->setOrganism(nullptr,i,j);
                this->setOrganism(new Human(this, i,j),i,j);

            }

        //SECOND CHECK SPAWN THEN MOVE
            if (!pOrganism->moved) {
                pOrganism->spawn(); //THIRD CHECK BREED
                pOrganism->move();

            }
        }
    } //END OF FOR LOOP

}//END CITY MOVE FUNCTION

//
ostream& operator<<( ostream &output, City &city ){
    for (auto & i : city.grid) {
        for (auto & j : i) {
            if (j != nullptr)
            {
                if(j->getSpeciesCH()==ZOMBIE_CH){
//                    Col(ZOMBIE_COLOR);
//                  output <<"\033[38;5;"<<ZOMBIE_COLOR<<"m"<<j->getSpeciesCH() << "\033[0m"<<' ';
                    output <<"\033[38;5;"<<ZOMBIE_COLOR<<"m"<<j << "\033[0m"<<' ';

//
                }
                else{
                    Col(HUMAN_COLOR);
//                    output <<"\033[38;5;"<<HUMAN_COLOR<<"m"<<j->getSpeciesCH() << "\033[0m"<<' ';
                    output <<"\033[38;5;"<<HUMAN_COLOR<<"m"<<j<< "\033[0m"<<' ';

                }
            }
            else {
                 Col(HUMAN_COLOR);
//                output << SPACE_CH<< ' ';
                output << j<< ' ';

            }
//        output<<j<<" ";
        }
        output << '\n';
    }
    return output;
};

//DESTRUCTOR
City::~City() {
}

//COUNT HUMAN
int City::humanCount() {
    int count = 0;
//    char c;
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
//                c = city.grid[i][j]->getSpeciesCH();
                if(grid[i][j]->getSpeciesCH()==HUMAN_CH){
                count +=1;
                }
            }
        }

    }
    return count;
}

//COUNT ZOMBIE
int City::zombieCount() {
    int count = 0;
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
                if(grid[i][j]->getSpeciesCH()==ZOMBIE_CH){
                count +=1;
                }
            }
        }
    }
    return count;
}


