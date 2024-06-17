//included libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

//header file that allows us to call functions from a seperate file.
#include "dataManagement.h"
#include "sharedVariables.h"

using namespace std;

//function to confirm user input is a valid type. eg not char/float.
//parameter: None
//returns: integer
int inputValidation() {
    float userInput;
    bool valid;
    
    do {
        cin >> userInput;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a valid optio\n";
            cout << "New Selection: ";
            cin >> userInput;
        }

        if (floor(userInput) != userInput) {
            valid = 0;
            cout << "\nInvalid input. Please enter a valid option\n";
            cout<<"New Selection: ";
        }
        else {
            valid = 1;
        }

    } while (valid==0);


    return userInput;
}

//writes user deatails to the "userDatabase"
//Parameters: filename to store info and pntr to userDetails Variable.
//Returns: none
void storeUserDetails(string userDatabase, userDetails& newUser) {
    ofstream outfile(userDatabase, ios::app);

    if (outfile.is_open()) {
        outfile << newUser.username << "," << newUser.password << "," << newUser.userType << ","
            << newUser.firstName << "," << newUser.lastName << ","
            << newUser.contactNumber << "," << newUser.emailAddress << ","
            << newUser.policy.policyNumber << "," << newUser.claims.claimNumber
            << "," << newUser.vehicle.carMake << "," << newUser.vehicle.carModel
            << "," << newUser.vehicle.carYear << endl;
    }
    else {
        cout << "Unable to store user details";
    }
}

//collects usernames and passwords from userDatabase.txt.
//parameters : string containt name of text file to check
//returns : a vector containing all current usernames and passwords.
vector<userDetails> getLogins(string userDatabase) {
    vector<userDetails> usernames;
    string data;

    ifstream file(userDatabase);

    if (!file.is_open()) {
        cout << "Unable to open: " << userDatabase << "\n";
        return usernames;
    }

    while (getline(file, data)) {
        istringstream ss(data);
        string field;
        userDetails user;

        if (getline(ss, field, ',')) {
            user.username = field;
        }

        if (getline(ss, field, ',')) {
            user.password = field;
        }

        usernames.push_back(user);
    }
}