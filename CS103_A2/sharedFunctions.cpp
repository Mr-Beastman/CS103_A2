//included libraries
#include<iostream>
#include<string>
#include<limits>

//header file that allows us to call functions from a seperate file.
#include "sharedFunctions.h"

using namespace std;


int inputValidation() {
    float userInput;
    bool valid;
    
    do {
        cin >> userInput;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a valid option";
            cin >> userInput;
        }

        if (floor(userInput) != userInput) {
            valid = 0;
            cout << "\nInvalid input. Please enter a valid option\n";
            cout<<"Selection: ";
        }
        else {
            valid = 1;
        }

    } while (valid==0);



    return userInput;
}

