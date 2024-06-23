//included libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

//header file that allows us to call functions from a separate file.
#include "dataManagement.h"
#include "sharedVariables.h"
#include "userManagement.h"

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

//displays important userdata present in current structure
//parameters : structure with data to display.
//returns : none
void displayUserData(userDetails& toDisplay) {
    int userInput;
    bool menuLoop=1;


    cout << "Which info do you wish to view?\n";
    cout << "1. Client Detials\n";
    cout << "2. Policy Detals\n";
    cout << "3. Current Claim\n";
    cout << "4. All Account Info\n";
    //cout << "5. Return to Previous Menu\n";
    cout << "Selection: ";

    userInput = inputValidation();
    cout << "\n";

    if (userInput == 1 || userInput == 4) {
        cout << "-- Client Details --\n";
        cout << "Username: " << toDisplay.username << "\n";
        cout << "User Type: " << toDisplay.userType << "\n";
        cout << "Account Status: " << toDisplay.accountStatus << "\n";
        cout << "First Name : " << toDisplay.firstName << "\n";
        cout << "Last Name : " << toDisplay.lastName << "\n";
        cout << "Contact Number : " << toDisplay.contactNumber << "\n";
        cout << "Email Address : " << toDisplay.emailAddress << "\n";
        cout << "\n";
    }
    if (userInput == 2 || userInput == 4) {
        cout << "-- Policy Details --\n";
        if (toDisplay.policy.policyNumber == 0) {
            cout << "No active policy at this time.\n";
            cout << "Please contact a reprsentative to create a new policy\n";
            cout << "\n";
        }
        else {
            cout << "Insurer Name: " << toDisplay.policy.insurerName << "\n";
            cout << "Policy Number: " << toDisplay.policy.policyNumber << "\n";
            cout << "Coverage Type: " << toDisplay.policy.insurerName << "\n";
            cout << "Premium Amount: $" << toDisplay.policy.preniumAmount << "\n";
            cout << "Car Make: " << toDisplay.policy.carMake << "\n";
            cout << "Car Model: " << toDisplay.policy.carModel << "\n";
            cout << "Car Year: " << toDisplay.policy.carYear << "\n";
            cout << "License Plate: " << toDisplay.policy.licensePlate << "\n";
            cout << "\n";
        }
    }
    if (userInput == 3 || userInput == 4) {
        cout << "-- Current Claim --\n";
        if (toDisplay.claims.claimNumber == 0) {
            cout << "No active claim at this time.\n";
            cout << "\n";
        }
        else {
            cout << "Claim Number: " << toDisplay.claims.claimNumber << "\n";
            cout << "Date Claim Filed: " << toDisplay.claims.claimDate << "\n";
            cout << "Incident Date: " << toDisplay.claims.incidentDate << "\n";
            cout << "Incident Location: " << toDisplay.claims.incidentLocation << "\n";
            cout << "Incident Description: " << toDisplay.claims.incidentDescription << "\n";
            cout << "Claim Status: " << toDisplay.claims.claimStatus << "\n";
            cout << "Claim Amount: $" << toDisplay.claims.claimAmount << "\n";
            cout << "\n";
        }
    }
}

//writes user details to the "userDatabase"
//Parameters : filename to store info and pntr to userDetails Variable.
//Returns : none
void storeUserDetails(string userDatabase, userDetails& newUser) {
    ofstream outfile(userDatabase, ios::app);

    if (outfile.is_open()) {
        outfile << newUser.username << "," 
            << newUser.password << ","
            << newUser.userType << ","
            << newUser.accountStatus << ","
            << newUser.firstName << ","
            << newUser.lastName << ","
            << newUser.contactNumber << ","
            << newUser.emailAddress << "," 
            << newUser.policy.policyNumber << ","
            << newUser.policy.insurerName << ","
            << newUser.policy.carMake << ","
            << newUser.policy.carModel << ","
            << newUser.policy.carYear << ","
            << newUser.policy.licensePlate << ","
            << newUser.claims.claimNumber << ","
            << newUser.claims.claimDate << ","
            << newUser.claims.incidentDate << ","
            << newUser.claims.incidentLocation << ","
            << newUser.claims.incidentDescription << ","
            << newUser.claims.claimStatus << ","
            << newUser.claims.claimAmount << endl;
    }
    else {
        cout << "Unable to store user details";
    }
}

//overwrite existing userdetails with ones currently stored in userDetails struct
//parameters : file name to change, update userdeatils struct.
//returns : none 
void storeUpdatedDetails(string userDatabase, userDetails& userUpdates) {
    
    ifstream infile(userDatabase);
    vector<string> lines;
    string line,username;

    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, username, ',');

        if (username == userUpdates.username) {
            stringstream newLine;
            newLine << userUpdates.username << ","
                << userUpdates.password << ","
                << userUpdates.userType << ","
                << userUpdates.accountStatus << ","
                << userUpdates.firstName << ","
                << userUpdates.lastName << ","
                << userUpdates.contactNumber << ","
                << userUpdates.emailAddress << ","
                << userUpdates.policy.insurerName << ","
                << userUpdates.policy.policyNumber << ","
                << userUpdates.policy.carMake << ","
                << userUpdates.policy.carModel << ","
                << userUpdates.policy.carYear << ","
                << userUpdates.policy.licensePlate << ","
                << userUpdates.claims.claimNumber << ","
                << userUpdates.claims.claimDate << ","
                << userUpdates.claims.incidentDate << ","
                << userUpdates.claims.incidentLocation << ","
                << userUpdates.claims.incidentDescription << ","
                << userUpdates.claims.claimStatus << ","
                << userUpdates.claims.claimAmount << endl;

            lines.push_back(newLine.str());
        }
        else {
            lines.push_back(line);
        }
    }

    infile.close();
    
    ofstream outfile(userDatabase);
    for (auto & line : lines) {
        outfile << line << endl;
    }

    outfile.close();
}

//search via username to get account details and update userDetails pntr
//Parameters : database filename, userDetail structure to store in, username to search with.
//Returns : none
void getAccountDetails(string userDatabase, userDetails& user, string searchUser) {
    ifstream file(userDatabase);
    string line;
    userDetails account;
    string username;

    while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, username, ',');
        if (username == searchUser) {
            user.username = username;
            getline(ss, user.password, ',');
            getline(ss, user.userType, ',');
            getline(ss, user.accountStatus, ',');
            getline(ss, user.firstName, ',');
            getline(ss, user.lastName, ',');
            ss >> user.contactNumber;
            ss.ignore();
            getline(ss, user.emailAddress, ',');
            getline(ss, user.policy.insurerName, ',');
            ss >> user.policy.policyNumber;
            ss.ignore();
            getline(ss, user.policy.carMake, ',');
            getline(ss, user.policy.carModel, ',');
            ss >> user.policy.carYear;
            ss.ignore();
            getline(ss, user.policy.licensePlate, ',');
            ss >> user.claims.claimNumber;
            ss.ignore();
            getline(ss, user.claims.claimDate, ',');
            getline(ss, user.claims.incidentDate, ',');
            getline(ss, user.claims.incidentLocation, ',');
            getline(ss, user.claims.incidentDescription, ',');
            getline(ss, user.claims.claimStatus, ',');
        }
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
    return usernames;
}