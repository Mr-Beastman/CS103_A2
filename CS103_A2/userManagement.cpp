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
void registerUser(vector<userDetails>& userLogins, userDetails& newUser) {
    bool repeatUsername=1;
    
    //doWhile to check if username is already taken and prompt re-entery.
    do {
        cout << "Enter Username: ";
        cin >> newUser.username;

        if (checkLogin(userLogins, newUser.username)) {
            cout << "Username already taken, please enter a new one.\n";
        }
        else {
            repeatUsername = 0;
        }
    } while (repeatUsername==1);

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

//check if a username exist in data base.
//parameters : vector containing existing usernames
//retursn : True if exists false if not.
bool checkLogin(vector<userDetails>& userLogins, string username) {
    for (size_t i = 0; i < userLogins.size(); ++i) {
        if (userLogins[i].username == username) {
            return 1;
        }
    }
    return 0;
}

//check if inputted username and password combination exists
//parameters : vecotr of all current combinations, user input for username and password.
//returns : True if correct false if not.
bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword) {
    for (size_t i = 0; i < userLogins.size(); ++i) {
        if (userLogins[i].username == username && userLogins[i].password == userPassword) {
            return 1;
        }
    }
    return 0;
}

//display menu for admin users.
//parameter :
//returns : none
void adminLogin(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;
    userDetails clientDetails;
    vector<userDetails> loginCheck;
    string username, userDatabase = "userDatabase.txt";
    
    while (menuLoop) {
        cout << "\n===== Staff Portal ====\n";
        cout << "1. Search for Client\n";
        cout << "2. Reports\n";
        cout << "3. Logout\n";
        cout << "Selection: ";

        userInput = inputValidation();

        if (userInput == 1) {
            cout << "\nEnter clinet's username: ";
            cin >> username;

            loginCheck = getLogins(userDatabase);

            if (checkLogin(loginCheck, username)) {
                cout << "\nAccount Found. Loading Details\n";
                getAccountDetails(userDatabase, clientDetails, username);
                displayUserData(clientDetails);
            }
            else {
                cout<<"\nInvalid Username\n";
            }
        }
        else if (userInput == 3) {
            cout << "\nLogging Out and returning to menu\n";
            menuLoop = 0;
        }
    }
}

//function to display user/client menu and features.
//paramerters : struct containing logged in users details. pntr.
//returns : void
void userLogin(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;
    string userDatabase = "userDatabase.txt";

    //menu loop for client menu
    while (menuLoop) {
        cout << "\n==== Client Portal ====\n";
        cout << "1. View my Polices\n";
        cout << "2. View/Update Details\n";
        cout << "3. Log out\n";

        userInput = inputValidation();

        //selection logic for user input
        if (userInput == 1) {
            displayUserData(currentUser);
        }
        else if (userInput == 2) {
            cout << "\nView/update\n";
            userUpdate(currentUser);
            storeUpdatedDetails(userDatabase, currentUser);
        }
        else if (userInput == 3) {
            cout << "\nLogging Out and returning to menu\n";
            menuLoop = 0;
        }
    }
}

void updateInput(int Input, userDetails& currentUser) {
    cout << "\nWhat would you like to do?" << "\n(input 1-5 to change information, 6 to return to menu)";
    cin >> Input;
    switch (Input) {
    case (1):
        cout << "\nFirst Name: ";
        cin >> currentUser.firstName;
        updateInput(Input, currentUser);
        break;
    case (2):
        cout << "\nLast Name: ";
        cin >> currentUser.lastName;
        updateInput(Input, currentUser);
        break;
    case (3):
        cout << "\nContact Number: ";
        cin >> currentUser.contactNumber;
        updateInput(Input, currentUser);
        break;
    case (4):
        cout << "\nEmail Address: ";
        cin >> currentUser.emailAddress;
        updateInput(Input, currentUser);
        break;
    case (5):
        cout << "\nVehicle Information: ";

        cout << "\nCar Make:";
        cin >> currentUser.policy.carMake;

        cout << "\nCar Model: ";
        cin >> currentUser.policy.carModel;

        cout << "\nCar Year: ";
        cin >> currentUser.policy.carYear;
        updateInput(Input, currentUser);
        break;
    case (6):
        userLogin(currentUser);
        break;
    }
}

void userUpdate(userDetails& currentUser) {

    int userInput = 0;

    cout << "\n1: First Name: " << currentUser.firstName;
    cout << "\n2: Last Name: " << currentUser.lastName;
    cout << "\n3: Contact Number: " << currentUser.contactNumber;
    cout << "\n4: Email Address: " << currentUser.emailAddress;
    cout << "\n5: Vehicle Information: " << currentUser.policy.carMake << ", " << currentUser.policy.carModel << ", " << currentUser.policy.carYear;

    updateInput(userInput, currentUser);
}