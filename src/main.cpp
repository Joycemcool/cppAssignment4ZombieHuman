
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
    std::cout << "Hello, World!" << std::endl;

    //INSTANTIALIZE NEW CITY
    City city;
    cout<<city.humanCount()<<endl;
    cout<<city.zombieCount()<<endl;

    if(city.humanCount()>0&&city.zombieCount()>0){
        cout<<city<<endl;
    }

    city.move(); //It might need a time interval here

    //this_thread::sleep_for(3s);
    //chrono::seconds interval( 1 ) ; // 1 second
   // this_thread::sleep_for( interval ) ;

    cout<<city.humanCount()<<endl;
    cout<<city.zombieCount()<<endl;
    cout<<city<<endl;
    return 0;

} //SIGSEGV (Segmentation fault) at the end of the code

void gameRules(){
    string message =
            "1: stays in the current cell - . If the neighboring cell in the selected direction"
            " is occupied or would move the human out of the city "
            "2. Human"
            "Recruit(recruit counter): Survives three time-steps,  at the end of the time step the human will "
            "recruit a new human into an adjacent empty space,If there is no empty cell available, no recruiting occurs"
            "Once a recruit is produced, a human cannot recruit again until it has survived three more steps. "
            "3. Zombie"
            "For every time step, the zombie will move to an adjacent cell (including diagonal) "
            "containing a human and eat the human. "
            "Note that a zombie will not eat another zombie "
            "Zombie Breed count (Eaten human flag): 8 - If a zombie survives for eight time-steps, and after it has moved/eaten, it will convert a randomly selected adjacent (including diagonal) "
            "human into a zombie (i.e. replace the human with a new zombie)"
            "If a zombie is still alive and is unable to convert, their breed counter should retain a state so that they will"
            "convert a human provided the very next opportunity (post move/eat)."
            "Zombie time steps - 3 not eaten human -zombie will convert to a human  "
            "??This class should have a pure virtual function (aka abstract) named ‘turn’ overridden in the sub classes Human and Zombie. ";

}


