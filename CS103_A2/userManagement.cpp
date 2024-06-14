//included libraries
#include<iostream>
#include <fstream>
#include<string>

//header file that allows us to call functions from a seperate file.
#include "userManagement.h"
#include "createdVariables.h"

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

//writes user deatails to the "userDatabase"
//Parameters: filename to store info and pntr to userDetails Variable.
//Returns: none
void storeUserDetails(string userDatabase, userDetails& newUser) {
    ofstream outfile(userDatabase, ios::app);

    if (outfile.is_open()) {
        outfile << newUser.username << ", " << newUser.password << ", " << newUser.userType << ", "
            << newUser.firstName << ", " << newUser.lastName << ", "
            << newUser.contactNumber << ", " << newUser.emailAddress << ", " 
            << newUser.policy.policyNumber << ", " << newUser.claims.claimNumber 
            << ", " << newUser.vehicle.carMake << ", " << newUser.vehicle.carModel 
            << ", " << newUser.vehicle.carYear << endl;
    }
    else {
        cerr << "Unable to store user details";
    }
}