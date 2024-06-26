//included libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
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

        transform(newUser.username.begin(), newUser.username.end(), newUser.username.begin(), ::tolower);

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

//set account status to locked.
//paremeters : username to be checked.
//retutns : none
void lockAccount(string username){
    const string kUserDatabase = "userDatabase.txt";
    userDetails toLock;

    getAccountDetails(kUserDatabase, toLock,username);

    toLock.accountStatus = "locked";
    storeUpdatedDetails(toLock);
}

//check if account is locked or active
//parameters : username to check
//returns : 0 if locked 1 if active.
bool checkAccountStatus(string username) {
    const string kUserDatabase = "userDatabase.txt";
    userDetails toCheck;

    getAccountDetails(kUserDatabase, toCheck, username);
    
    if (toCheck.accountStatus == "locked") {
        return 0;
    }
    else {
        return 1;
    }
}

//Used to prompt user log in and verify details.
//parameters: none
//returns : string of verified username or empty string.
string loginSecurity() {
    const string kUserDatabase = "userDatabase.txt";
    string username, password;
    vector<userDetails> accountCheck;
    const int kMaxAttempts = 3;
    int loginAttempts = 0;

    cout << "Enter Username: ";
    cin >> username;
    
    accountCheck = getLogins(kUserDatabase);

    transform(username.begin(), username.end(), username.begin(), ::tolower);

    if (!checkLogin(accountCheck,username)) {
        cout << "\nUsername not in system. Please create new accout or contact admin.\n";
        cout << "Returning to Previous Menu\n";
        return{};
    }

    if (!checkAccountStatus(username)) {
        cout << "\nThis account has been locked. Please contact admin team.\n";
        cout << "Returning to Previous Menu\n";
        return{};
    }

    while (loginAttempts < kMaxAttempts) {
        cout << "Enter Password: ";
        cin >> password;

        if (verifyLogin(accountCheck, username, password)) {
            cout << "\nLogin Succesfull\n";
            return username;
        }
        else {
            cout << "\nIncorrect Password, Please try again\n";
            loginAttempts++;
        }
    }

    cout << "Max number of attempts reached. This account has now been locked.\n";
    cout << "Please Contact Admin to unlock.\n";
    lockAccount(username);
    return{};
}

//function to prompt entry of car details   
//paramerts : struct of account to update
//returns : none
void enterCarDetails(userDetails& toUpdate) {
    int carYear;
    string carMake, carModel, licensePlate;

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

//Add policy to users account
//parameters : vector of available polocies and the user to add selection to
//returns : none
void addPolicy(userDetails& toUpdate) {
    vector<insurancePolices> availablePolices;
    const string kPolicyDatabase = "policyDatabase.txt";
    int userInput;
    bool selectLoop=1;

    cout << "\nPlease Select a Policy Option\n";

    getPolicyDetails(kPolicyDatabase, availablePolices);

    //dynamically populate list form policyDatabase
    for (size_t i = 0; i < availablePolices.size(); ++i) {
        cout << "Insurance Option " << (i + 1) << "\n";
        displayPolicyDetails(availablePolices[i]);
        cout << "\n";
    }
    
    //dynamically adjust input options based on size of policyDatabase
    while (selectLoop) {
        userInput = inputValidationInt();

        if (userInput > 0 && userInput <= availablePolices.size()) {
            toUpdate.policy.insurerName = availablePolices[(userInput - 1)].insurer;
            toUpdate.policy.coverageType = availablePolices[(userInput - 1)].coverage;
            toUpdate.policy.preniumAmount = availablePolices[(userInput - 1)].premiumn;
            selectLoop = 0;
        }
        else {
            cout << "\nInvalid Selection. Please Try again.\n";
        }
    }

    toUpdate.policy.policyNumber = generatePolicyNum();

    enterCarDetails(toUpdate);
}

//add claim detials to a users account.
//paramters : user struct that is being updated.\
//returns : none;
void addClaim(userDetails& toUpdate) {
    string incidentDate;
    string incidentLocation;
    string incidentDescription;
    string claimStatus;
    float claimAmount;
    
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

    storeUpdatedDetails(toUpdate);
}

//Provide options for updating an existing claim
//parameters : struct of data to be updated
//returns : none
void updateClaim(userDetails& toUpdate) {
    bool menuLoop = 1;
    int userInput;
    string incidentUpdate;
    float monetaryAmount;

    while (menuLoop == 1) {
        cout << "\nWhich section would you like to update?\n";
        cout << "1. Incident Date\n";
        cout << "2. Incident Location\n";
        cout << "3. Incident Description\n";
        cout << "4. Claim Amount\n";
        cout << "5. Return to Previous Menu\n";
        userInput = inputValidationInt();

        if (userInput == 1) {
            cout << "Please Enter the Date of the incident (dd/mm/yyyy): ";
            cin >> incidentUpdate;
            cin.ignore();
            toUpdate.claims.incidentDate = incidentUpdate;
        }
        else if (userInput == 2) {
            cout << "Where did this happen?: ";
            getline(cin, incidentUpdate);
            toUpdate.claims.incidentLocation = incidentUpdate;
        }
        else if (userInput == 3) {
            cout << "What happened?: ";
            getline(cin, incidentUpdate);
            toUpdate.claims.incidentLocation = incidentUpdate;
        }
        else if (userInput == 4) {
            cout << "Claim Amount: $";
            cin >> monetaryAmount;
            toUpdate.claims.claimAmount = monetaryAmount;
        }
        else if (userInput == 5) {
            cout << "\nReturning to previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Selection Please Try Again";
        }
    }
}

//Provide options for updating an existing policy
//parameters : struct of data to be updated
//returns : none
void updatePolicy(userDetails& toUpdate) {
    bool menuLoop = 1;
    int userInput;

    while (menuLoop == 1) {
        cout << "\nWhich section would you like to update?\n";
        cout << "1. Change Policy\n";
        cout << "2. Car Details\n";
        cout << "3. Delete Policy\n";
        cout << "4. Return to Previous Menu\n";
        userInput = inputValidationInt();

        if (userInput == 1){
            cout << "\nThis overwrite your current coverage and remove connected claims.\n";
            cout << "Do you wish to proceed? (y/n)";
            if (inputValidationYN()) {
                addPolicy(toUpdate);
                deleteClaim(toUpdate);
                storeUpdatedDetails(toUpdate);
            }
        }
        else if (userInput == 2) {
            enterCarDetails(toUpdate);
            storeUpdatedDetails(toUpdate);
        }
        else if (userInput == 3) {
            cout << "\nThis remove your current coverage and connected claims.\n";
            cout << "Do you wish to proceed? (y/n)";
            if (inputValidationYN()) {
                deletePolicy(toUpdate);
                deleteClaim(toUpdate);
                storeUpdatedDetails(toUpdate);
            }
        }
    }
}

//Saftey function to comfirm delete request.
//parameters : none
//returns : none
bool deleteConfirmation() {
    string confirmation;

    cout << "Enter 'DELETE' to confirm or anything to cancel.\n";
    cout << "Confirmation: ";
    cin >> confirmation;

    if (confirmation == "DELETE") {
        return 1;
    }
    else {
        return 0;
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