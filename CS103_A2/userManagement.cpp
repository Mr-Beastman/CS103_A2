//included libraries
#include <iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>

//header file that allows us to call functions from a seperate file.
#include "userManagement.h"
#include "dataManagement.h"
#include "menuManagement.h"
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
//returns : True if exists false if not.
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


//Add policy to users account
//parameters : vector of available polocies and the user to add selection to
//returns : none
void addPolicy(userDetails& toUpdate) {
    vector<insurancePolices> availablePolices;
    const string kPolicyDatabase = "policyDatabase.txt";
    int userInput, carYear;
    string carMake, carModel, licensePlate;

    cout << "\nPlease Select a Policy Option\n";

    getPolicyDetails(kPolicyDatabase, availablePolices);

    for (size_t i = 0; i < availablePolices.size(); ++i) {
        cout << "Insurance Option " << (i + 1) << "\n";
        displayPolicyDetails(availablePolices[i]);
        cout << "\n";
    }

    cout << "\nSelection: ";

    userInput = inputValidation();

    if (userInput == 1 || userInput == 2 || userInput == 3) {
        toUpdate.policy.insurerName = availablePolices[(userInput - 1)].insurer;
        toUpdate.policy.coverageType = availablePolices[(userInput - 1)].coverage;
        toUpdate.policy.preniumAmount = availablePolices[(userInput - 1)].premiumn;
    }

    toUpdate.policy.policyNumber = generatePolicyNum();

    cout << "\nPlease enter vehicle details:\n";
    cout << "Car Make: ";
    cin >> carMake;
    cout << "Car Model: ";
    cin >> carModel;
    cout << "Car Year: ";
    cin >> carYear;
    cout << "License Plare: ";
    cin >> licensePlate;

    toUpdate.policy.carMake = carMake;
    toUpdate.policy.carModel = carModel;
    toUpdate.policy.carYear = carYear;
    toUpdate.policy.licensePlate = licensePlate;
}

//add claim detials to a users account.
//paramters : user struct that is being updated.\
//returns : none;
void addClaim(userDetails& toUpdate) {
    string incidentDate;
    string incidentLocation;
    string incidentDescription;
    string claimStatus;
    float claimAmount=0.0;
    
    toUpdate.claims.claimNumber = generateClaimNum();
    toUpdate.claims.claimDate = creationDate();
    toUpdate.claims.claimStatus = "Pending Review";

    //prompting user to enter required information
    cout << "Please Enter the Date of the incident (dd/mm/yyyy): ";
    cin >> incidentDate;
    cin.ignore();
    cout << "Where did this happen?: ";
    getline(cin, incidentLocation);
    cout << "What Happened?: ";
    getline(cin,incidentDescription);
    cout << "Claim Amount: $";
    cin >> claimAmount;

    //populate struct with entered information
    toUpdate.claims.incidentDate = incidentDate;
    toUpdate.claims.incidentLocation = incidentLocation;
    toUpdate.claims.incidentDescription = incidentDescription;
    toUpdate.claims.claimAmount = claimAmount;
}

void updateClaim(userDetails& toUpdate) {

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