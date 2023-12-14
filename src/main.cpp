
#include <iostream>
#include <thread>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "../inc/Organism.h"
#include "../inc/City.h"
using namespace std;

//Helper Function
void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"hello"<<endl;
}

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
//    chrono:: milliseconds interval(200);

    if(city.humanCount()>0&&city.zombieCount()>0){
        int gameCount=1;
//        this_thread::sleep_for(interval);
        do{
            cout<<endl<<"!!New Generation!!This is generation  " <<gameCount<<endl;
            cout<<"Human count in this generation "<<city.humanCount()<<endl;
            cout<<"Zombie count in this generation "<<city.zombieCount()<<endl;
            cout<<"Before move"<<endl;
            cout<<city<<endl;
            cout << "Enter [n] to see the next generation : Any other key to exit" << endl;
            cin >> userInput;
            if (userInput == "n") {
                //continue playing if user enters n
                gameOver = false;
            }
            else {
                //exit if user does not enter n
                gameOver = true;
            }
            city.move();
            cout<<"After move"<<endl;
            cout<<city;
            gameCount++;
            this_thread::sleep_for(2s);
        }while(!gameOver);
    } else{
        cout<<"Game over"<<endl;
    }

    //chrono::seconds interval( 1 ) ; // 1 second
   // this_thread::sleep_for( interval ) ;

    return 0;

} //SIGSEGV (Segmentation fault) at the end of the code




