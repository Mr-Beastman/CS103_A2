//included libraries
#include <iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>

//header file that allows us to call functions from a seperate file.
#include "userManagement.h"
#include "dataManagement.h"
#include "sharedVariables.h"

using namespace std;

//Request user input for basic account info.
//Parameters : pntr to userDetails variable to be populated.
//Returns : none.
void registerUser(userDetails& newUser) {
    cout << "Enter Username: ";
    cin >> newUser.username;
    cout << "Enter Password: ";
    cin >> newUser.password;
    cout << "Enter First Name: ";
    cin >> newUser.firstName;
    cout << "Enter Last Name: ";
    cin >> newUser.lastName;
    cout << "Enter contact number: ";
    cin >> newUser.contactNumber;
    cout << "Enter email Address: ";
    cin >> newUser.emailAddress;
    newUser.userType = "user";
}

//check if inputted username and password combination exists
//parameters : vecotr of all current combinations, user input for username and password.
//returns : none.
bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword) {
    for (size_t i = 0; i < userLogins.size(); ++i) {
        if (userLogins[i].username == username && userLogins[i].password == userPassword) {
            return 1;
        }
    }
    return 0;
}

void adminLogin(userDetails& currentUser) {
    cout << "\n===== Staff Portal ====\n";
    cout << "check program flow chart for options";
}

//function to display user/client menu and features.
//paramerters : struct containing logged in users details. pntr.
//returns : void
void userLogin(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;

    //menu loop for client menu
    do {
        cout << "\n==== Client Portal ====\n";
        cout << "1. View Polices\n";
        cout << "2. View/Update Details\n";
        cout << "3. Log out\n";

        userInput = inputValidation();

        //selection logic for user input
        if (userInput == 1) {
            cout << "\nDisplay polices\n";
        }
        else if (userInput == 2) {
            cout << "\nView/update\n";
            userUpdate(currentUser);
        }
        else if (userInput == 3) {
            cout << "\nLogging Out and returning to menu\n";
            menuLoop = 0;
        }

    } while (menuLoop == 1);


}

void updateInput(int Input, userDetails& currentUser) {
    cout << "\nWhat would you like to do?" << "\n(input 1-5 to change information, 6 to return to menu)";
    cin >> Input;
    switch (Input) {
    case (1):
        cout << "\nFirst Name: ";
        cin >> currentUser.firstName;
        updateInput(Input, currentUser);
    case (2):
        cout << "\nLast Name: ";
        cin >> currentUser.lastName;
        updateInput(Input, currentUser);
    case (3):
        cout << "\nContact Number: ";
        cin >> currentUser.contactNumber;
        updateInput(Input, currentUser);
    case (4):
        cout << "\nEmail Address: ";
        cin >> currentUser.emailAddress;
        updateInput(Input, currentUser);
    case (5):
        cout << "\nVehicle Information: ";

        cout << "\nCar Make:";
        cin >> currentUser.vehicle.carMake;

        cout << "\nCar Model: ";
        cin >> currentUser.vehicle.carModel;

        cout << "\nCar Year: ";
        cin >> currentUser.vehicle.carYear;
        updateInput(Input, currentUser);
    case (6):
        userLogin(currentUser);
    }
}

void userUpdate(userDetails& currentUser) {

    int userInput = 0;

    cout << "\n1: First Name: " << currentUser.firstName;
    cout << "\n2: Last Name: " << currentUser.lastName;
    cout << "\n3: Contact Number: " << currentUser.contactNumber;
    cout << "\n4: Email Address: " << currentUser.emailAddress;
    cout << "\n5: Vehicle Information: " << currentUser.vehicle.carMake << ", " << currentUser.vehicle.carModel << ", " << currentUser.vehicle.carYear;

    updateInput(userInput, currentUser);
}