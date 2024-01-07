
#include <iostream>
#include <thread>
#include <chrono>

#include "../inc/Organism.h"
using namespace std;

int main() {

    //DECLARE VARIABLES
    bool gameOver = false;
    string userInput = "placeHolder";
    string line = "*******************************************************************";
    string gameRule1 = "Human Recruit: Survives three time-steps,  a new human recruited into an adjacent empty space";
    string gameRule2 = "Zombie starved: 3 time steps and not eaten human, convert to a human";
    string gameRule3 = "Zombie Breed : survives for eight time-steps, and after it has moved/eaten,breed a new zombie";

    cout << "Welcome to Zombie and Human World" << endl;
    cout<<line<<endl;
    cout<<gameRule1<<endl;
    cout<<gameRule2<<endl;
    cout<<gameRule3<<endl;
    cout<<line<<endl;

    //INSTANTIALIZE NEW CITY
    City city;

//2024-1-6 update HumanCount<=0 or ZombieCount<=0, gameOver == true;

        int gameCount=1;
        do{
            cout<<endl<<"!!New Generation!!This is generation  " <<gameCount<<endl;
            cout<<"Human count in this generation "<<city.humanCount()<<endl;
            cout<<"Zombie count in this generation "<<city.zombieCount()<<endl;

            //New code
            city.move();

            //New code
            this_thread::sleep_for(0.5s);

            cout<<city;

            gameCount++;

//            Either organism disappears marks end of the game
            if(city.humanCount()<=0||city.zombieCount()<=0) gameOver= true;

        }while(!gameOver);

    return 0;

}



