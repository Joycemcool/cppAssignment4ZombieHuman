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

using namespace std;
class Organism;
class Human;
class Zombie;


#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void Col(int);

//int main() {
//    Col(12);
//    cout << "RED" << std::endl;
//    Col(7);
//    cout << "WHITE" << std::endl;
//    Col(3);
//    cout << "BLUE" << std::endl;
//    _getch();
//    return 0;
//}

void Col(int c)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
    return;
}

City ::City() {
    cout<<"City Default Constructor called, fill with nullptr and start organisms\n"<<endl;
    //fill the word with null objects (empty spaces)
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grid[i][j] = nullptr; //fills organism array (in world class) with null values
        }
    }
    int count=0;
    while (count < HUMAN_STARTCOUNT) {
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;
        if(grid[x][y]==nullptr){
            grid[x][y] = new Human(this,x,y);
            count++;
        }
    }

    count=0;
    // Fill the grid with Zombies, equally in the Grid
    while (count < ZOMBIE_STARTCOUNT) {
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;
        if(grid[x][y]==nullptr){
            grid[x][y] = new Zombie(this,x,y);
            count++;
        }
    }

} //END CITY DEFAULT CONSTRUCTOR

Organism* City ::getOrganism(int x, int y) {
    //check to make sure in the bounds of the world
    if (grid[x][y]!= nullptr) {
        return grid[x][y];
    }
    return nullptr;
}

//Fills the cell at coordinates x and y with an object
void City ::setOrganism(Organism *organism, int x, int y) {
        grid[x][y] = organism;
}

//Need move() and friend ostream& operator
void City ::move() {

    cout<<zombieCount()<<endl;
    vector <int> randomTable;
    for(int i = 0; i < 400; i++) {
        randomTable.push_back(i);
    }

    // using built-in random generator, shuffle the vector so its in a random order
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(randomTable.begin(),randomTable.end(),default_random_engine(seed));

    //(1) First reset all organisms so none of them have moved
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->moved = false;
            }
        }
    }


    //Random selection of Human/Zombie for movement, loop 400 times
    for(auto z = randomTable.begin(); z != randomTable.end(); ++z) {

        int i = *z / 20; //for row
        int j = *z % 20; //for column

        //HARD CODE THE VALUE OF ENUM
        if ((grid[i][j] != nullptr) && (grid[i][j]->getSpeciesCH() == HUMAN_CH)) {
            if (!grid[i][j]->moved) {
                grid[i][j]->move();//MOVE THE HUMAN
            }
        }

        if ((grid[i][j] != nullptr) && (grid[i][j]->getSpeciesCH()==ZOMBIE_CH)) {
            if (!grid[i][j]->moved) { //if they haven't moved
                grid[i][j]->move(); //First move the Zombie! aka eat
            }
        }
    }

    //Loop through the world to check for starving Zombie
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getSpeciesCH()==ZOMBIE_CH)) {
                if (grid[i][j]->starved()) {
                    setOrganism(nullptr,i,j);
                    new Human(this,i,j);
//                    grid[i][j] = new Human(this,i,j); //??  replace with an Human
                }
            }
        }
    }

    //(5) Loop through the world and check for breeding/recruiting
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            //make sure the organism moved
            if (grid[i][j] != nullptr && grid[i][j]->moved) {
                grid[i][j]->spawn(); //?? Is this right way for both species
            }
        }
    }
}

ostream& operator<<( ostream &output, City &city ){
    cout<<"\nCity Friend function to overload the << operator"<<endl;
    for (auto & i : city.grid) {
        for (auto & j : i) {
            if (j != nullptr)
            {
                if(j->getSpeciesCH()==ZOMBIE_CH){
                    Col(ZOMBIE_COLOR);
                    output <<"\033[38;5;"<<ZOMBIE_COLOR<<"m"<<j->getSpeciesCH() << "\033[0m"<<' ';
                }
                else{
                    Col(HUMAN_COLOR);
                    output <<"\033[38;5;"<<HUMAN_COLOR<<"m"<<j->getSpeciesCH() << "\033[0m"<<' ';
                }
            }
            else {
                output << SPACE_CH << ' ';
            }
        }
        output << '\n';
    }
    return output;
};

//DESTRUCTOR
City::~City() {
    // Iterate through each cell in the grid
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            // Delete the organism at the current cell
            delete grid[i][j];
            // Set the cell to nullptr to avoid accessing deleted memory
            grid[i][j] = nullptr;
        }
    }
}

//COUNT HUMAN
//int City::humanCount(City &city) {
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


