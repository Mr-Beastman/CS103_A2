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


//Pause to display information, before prompting any key to conintue.
//parameters : none
//returns : none
void pauseEnterKey() {
    cout<<"Please press Enter key to continue";
    cin.ignore();
    cin.get();
}

//request user input for basic account info.
//parameters : pntr to userDetails variable to be populated.
//returns : none.
void registerUser(vector<userDetails>& userLogins, userDetails& newUser) {
    bool repeatUsername=1;
    
    //doWhile to check if username is already taken and prompt re-entery.
    do {
        cout << "Enter Username: ";
        cin >> newUser.mUsername;

        //forcing input to lowercase
        transform(newUser.mUsername.begin(), newUser.mUsername.end(), newUser.mUsername.begin(), ::tolower);

        if (checkLogin(userLogins, newUser.mUsername)) {
            cout << "Username already taken, please enter a new one.\n";
        }
        else {
            repeatUsername = 0;
        }
    } while (repeatUsername==1);

    cout << "Enter Password: ";
    cin >> newUser.mPassword;
    cout << "Enter First Name: ";
    cin >> newUser.mFirstName;
    cout << "Enter Last Name: ";
    cin >> newUser.mLastName;
    cout << "Enter contact number: ";
    cin >> newUser.mContactNumber;
    cout << "Enter email Address: ";
    cin >> newUser.mEmailAddress;
    newUser.mUserType = "user";
}

//check if a username exist in data base.
//parameters : vector containing existing usernames
//returns : True if exists false if not.
bool checkLogin(vector<userDetails>& userLogins, string username) {
    for (size_t i = 0; i < userLogins.size(); ++i) {
        if (userLogins[i].mUsername == username) {
            return 1;
        }
    }
    return 0;
}

//check if inputted username and password combination exists
//parameters : vector of all current combinations, user input for username and password.
//returns : True if correct, false if not.
bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword) {
    for (size_t i = 0; i < userLogins.size(); ++i) {
        if (userLogins[i].mUsername == username && userLogins[i].mPassword == userPassword) {
            return 1;
        }
    }
    return 0;
}

//set account status to locked.
//parameters : username to be checked.
//returns : none
void lockAccount(string username){
    userDetails toLock;

    getAccountDetails(toLock,username);

    toLock.mAccountStatus = "locked";
    storeUpdatedDetails(toLock);
}

//check if account is locked or active
//parameters : username to check
//returns : 0 if locked 1 if active.
bool checkAccountStatus(string username) {
    userDetails toCheck;

    getAccountDetails(toCheck, username);
    
    if (toCheck.mAccountStatus == "locked") {
        return 0;
    }
    else {
        return 1;
    }
}

//used to prompt user log in and verify details.
//parameters: none
//returns : string of verified username or empty string.
string loginSecurity() {
    const string kUserDatabase = "userDatabase.txt";
    string username, password;
    vector<userDetails> accountCheck;
    const int kMaxAttempts = 3;
    int loginAttempts = 0;

    cout << "\n==== Login ====\n";
    cout << "Enter Username: ";
    cin >> username;
    
    accountCheck = getLogins();

    //force input into lowercase
    transform(username.begin(), username.end(), username.begin(), ::tolower);

    //checking if username exists
    if (!checkLogin(accountCheck,username)) {
        cout << "\nUsername not in system. Please create new accout or contact admin.\n";
        cout << "Returning to Previous Menu\n";
        return{};
    }

    //checking if account has been locked for failed login attempts
    if (!checkAccountStatus(username)) {
        cout << "\nThis account has been locked. Please contact admin team.\n";
        cout << "Returning to Previous Menu\n";
        return{};
    }

    //While loop to handle password attmpts
    while (loginAttempts < kMaxAttempts) {
        cout << "Enter Password: ";
        cin >> password;

        if (verifyLogin(accountCheck, username, password)) {
            cout << "\nLogin Successful\n";
            return username;
        }
        else {
            cout << "\nIncorrect Password. Attempt "<<(loginAttempts+1)<<" of 3\n";
            loginAttempts++;
        }
    }

    //display for max attempts reached and locking account
    cout << "\nMax number of attempts reached. This account has now been locked.\n";
    cout << "Please Contact Admin to unlock.\n";
    lockAccount(username);
    return{};
}

//function to prompt entry of car details   
//parameters : struct of account to update
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
    cout << "License Plate: ";
    cin >> licensePlate;

    toUpdate.mPolicy.mCarMake = carMake;
    toUpdate.mPolicy.mCarModel = carModel;
    toUpdate.mPolicy.mCarYear = carYear;
    toUpdate.mPolicy.mLicensePlate = licensePlate;
}

//Add policy to users account
//parameters : vector of available policies and the user to add selection to
//returns : none
void addPolicy(userDetails& toUpdate) {
    vector<insurancePolices> availablePolices;
    const string kPolicyDatabase = "policyDatabase.txt";
    int userInput;
    bool selectLoop=1;

    cout << "\n==== Policy Selection ====\n";
    cout << "Please Select a Policy Option\n";
    cout << "\n";
    getPolicyDetails(availablePolices);

    //dynamically populate list from policyDatabase
    for (size_t i = 0; i < availablePolices.size(); ++i) {
        cout << "Insurance Option " << (i + 1) << "\n";
        displayPolicyDetails(availablePolices[i]);
        cout << "\n";
    }
    
    //dynamically adjust input options based on size of policyDatabase
    while (selectLoop) {
        userInput = inputValidationInt();

        if (userInput > 0 && static_cast<size_t>(userInput) <= availablePolices.size()) {
            toUpdate.mPolicy.mInsurerName = availablePolices[(userInput - 1)].mInsurer;
            toUpdate.mPolicy.mCoverageType = availablePolices[(userInput - 1)].mCoverage;
            toUpdate.mPolicy.mPreniumAmount = availablePolices[(userInput - 1)].mPremiumn;
            selectLoop = 0;
        }
        else {
            cout << "\nInvalid selection, Please try again.\n";
        }
    }

    //generatea policy number
    toUpdate.mPolicy.mPolicyNumber = generatePolicyNum();
    
    //enter car details that policy applies to.
    enterCarDetails(toUpdate);
}

//add claim details to a users account.
//paramters : user struct that is being updated.
//returns : none;
void addClaim(userDetails& toUpdate) {
    string incidentDate;
    string incidentLocation;
    string incidentDescription;
    string claimStatus;
    float claimAmount;
    
    //set default information for claims.
    toUpdate.mClaims.mClaimNumber = generateClaimNum();
    toUpdate.mClaims.mClaimDate = creationDate();
    toUpdate.mClaims.mClaimStatus = "Pending Review";

    cout << "==== Enter Claim Details ====\n";
    //prompting user to enter required information
    cout << "Please enter the date of the incident (dd/mm/yyyy): ";
    cin >> incidentDate;
    cin.ignore();
    cout << "Where did this happen?: ";
    getline(cin, incidentLocation);
    cout << "What happened?: ";
    getline(cin,incidentDescription);
    cout << "Claim amount: $";
    cin >> claimAmount;

    //populate struct with entered information
    toUpdate.mClaims.mIncidentDate = incidentDate;
    toUpdate.mClaims.mIncidentLocation = incidentLocation;
    toUpdate.mClaims.mIncidentDescription = incidentDescription;
    toUpdate.mClaims.mClaimAmount = claimAmount;

    storeUpdatedDetails(toUpdate);
}

//provide options for updating an existing claim
//parameters : struct of data to be updated
//returns : none
void updateClaim(userDetails& toUpdate) {
    bool menuLoop = 1;
    int userInput;
    string incidentUpdate;
    float monetaryAmount;
    const string pendingStatus = "Pending Review";

    if (toUpdate.mClaims.mClaimStatus != pendingStatus) {
        cout << "\nCurrent claim has already been " << toUpdate.mClaims.mClaimStatus << "\n";
        cout << "No further edits can be made, please delete and file a new claim\n";
        cout << "Returning to previous menu\n";
        return;
    }

    while (menuLoop == 1) {
        cout << "\n==== Edit Claim ====\n";
        displayAccountClaim(toUpdate);
        cout << "\nWhich section would you like to update?\n";
        cout << "1. Incident Date\n";
        cout << "2. Incident Location\n";
        cout << "3. Incident Description\n";
        cout << "4. Claim Amount\n";
        cout << "5. Return to Previous Menu\n";
        userInput = inputValidationInt();

        if (userInput == 1) {
            cout << "Please enter the date of the incident (dd/mm/yyyy): ";
            cin >> incidentUpdate;
            cin.ignore();
            toUpdate.mClaims.mIncidentDate = incidentUpdate;
        }
        else if (userInput == 2) {
            cout << "Where did this happen?: ";
            getline(cin, incidentUpdate);
            toUpdate.mClaims.mIncidentLocation = incidentUpdate;
        }
        else if (userInput == 3) {
            cout << "What happened?: ";
            getline(cin, incidentUpdate);
            toUpdate.mClaims.mIncidentLocation = incidentUpdate;
        }
        else if (userInput == 4) {
            cout << "Claim amount: $";
            cin >> monetaryAmount;
            toUpdate.mClaims.mClaimAmount = monetaryAmount;
        }
        else if (userInput == 5) {
            cout << "\nReturning to previous menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid selection, please try again";
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
        cout << "\n==== Edit Policy ====\n";
        displayAccountPolicy(toUpdate);
        cout << "Which section would you like to update?\n";
        cout << "1. Change Policy\n";
        cout << "2. Car Details\n";
        cout << "3. Return to Previous Menu\n";
        userInput = inputValidationInt();

        if (userInput == 1){
            cout << "\nThis will overwrite your current coverage and remove connected claims.\n";
            cout << "Do you wish to proceed? (y/n)\n";
            if (inputValidationYN()) {
                addPolicy(toUpdate);
                deleteClaim(toUpdate);
                storeUpdatedDetails(toUpdate);
                cout << "\nNew Policy has been applied\n";
            }
            else {
                cout << "\nNo changes have been made\n";
            }
        }
        else if (userInput == 2) {
            enterCarDetails(toUpdate);
            storeUpdatedDetails(toUpdate);
            cout << "\nCar Details have been Updated\n";
        }
        else if (userInput == 3) {
            cout << "\nReturning to previous menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid selection, please try again";
        }
    }
}

//saftey function to comfirm delete request.
//parameters : none
//returns : none
bool deleteConfirmation() {
    string confirmation;

    cout << "Enter 'DELETE' to confirm, anything else to cancel.\n";
    cout << "Confirmation: ";
    cin >> confirmation;

    if (confirmation == "DELETE") {
        return 1;
    }
    else {
        return 0;
    }
}

//change claim status from pending to approved/cancelled.
//parameters : struct containing userDetails
//return : none
void changeClaimStatus(userDetails& toUpdate) {
    int userInput;
    const string approveStatus = "Approved";
    const string declineStatus = "Declined";
    const string pendingStatus = "Pending Review";
    bool menuLoop = 1;

    if (toUpdate.mClaims.mClaimNumber == 0) {
        cout << "\nNo claim has been made for this account\n";
        cout << "Returning to Previous Menu\n";
        return;
    }
    else if (toUpdate.mClaims.mClaimStatus == approveStatus || toUpdate.mClaims.mClaimStatus == declineStatus) {
        cout << "\nCurrent claim has already be processed and was " << toUpdate.mClaims.mClaimStatus << "\n";
        cout << "Please create a new claim if further assitance required\n";
        cout << "Returning to previous menu\n";
    }
    else if (toUpdate.mClaims.mClaimStatus == pendingStatus) {
        while (menuLoop) {
            cout << "\n==== Claim Review ====\n";
            cout << "\n";
            displayAccountClaim(toUpdate);
            cout << "What would you like to change the claim status too?\n";
            cout << "1. Approved\n";
            cout << "2. Declined\n";
            cout << "3. Return to previous menu\n";

            userInput = inputValidationInt();

            if (userInput == 1) {
                cout << "\nAre you sure to want to approve this cliam (y/n)?\n";
                cout << "This cannot be undone.\n";
                if (inputValidationYN()) {
                    toUpdate.mClaims.mClaimStatus = approveStatus;
                    storeUpdatedDetails(toUpdate);
                    cout << "Claim has been approved. Returning to previous Menu\n";
                    menuLoop = 0;
                }
                else {
                    cout << "\nNo changes made. Returning to options\n";
                }
            }
            else if (userInput == 2) {
                cout << "\nAre you sure to want to delcine this cliam (y/n)?\n";
                cout << "This cannot be undone.\n";
                if (inputValidationYN()) {
                    toUpdate.mClaims.mClaimStatus = declineStatus;
                    cout << "Claim has been declined. Returning to previous menu\n";
                    storeUpdatedDetails(toUpdate);
                    menuLoop = 0;
                }
                else {
                    cout << "\nNo changes made. Returning to options\n";
                }
            }
            else if (userInput == 3) {
                cout << "\nNo changes made. Returning to previous menu\n";
                menuLoop = 0;
            }
            else {
                cout << "\nInvalid selection please try again";
            }
        }
    }
}

//change an account status depending on current state
//parameters : struct containing userDetails
//return : none
void changeAccountStatus(userDetails& toUpdate) {
    const string kUserDatabase = "userDatabase.txt";

    cout << "\n==== Modify Account Status ====\n";
    cout << toUpdate.mUsername << " current type is " << toUpdate.mAccountStatus << "\n";

    if (toUpdate.mAccountStatus == "active") {
        cout << "\nDo you wish to change it to Locked? (y/n)\n";
        if (inputValidationYN()) {
            toUpdate.mAccountStatus = "locked";
            storeUpdatedDetails(toUpdate);
        }
        else {
            cout << "\nAccount status unchanged\n";
        }
    }
    else if (toUpdate.mAccountStatus == "locked") {
        cout << "\nDo you wish to change it to Active? (y/n)\n";
        if (inputValidationYN()) {
            toUpdate.mAccountStatus = "active";
            storeUpdatedDetails(toUpdate);
        }
        else {
            cout << "\nAccount status unchanged\n";
        }
    }
    else {
        cout << "\nUser status undefined. Setting to Active\n";
        toUpdate.mAccountStatus = "active";
        storeUpdatedDetails(toUpdate);
    }
}

//change an account type depending on current state
//parameters : struct containing userDetails
//return : none
void changeAccountType(userDetails& toUpdate) {
    const string kUserDatabase = "userDatabase.txt";
    
    cout << "\n==== Modify Account Type ====\n";
    cout <<toUpdate.mUsername << " current type is " << toUpdate.mUserType << "\n";

    if (toUpdate.mUserType == "user") {
        cout << "\nDo you wish to change it to Admin? (y/n)\n";
        if (inputValidationYN()) {
            toUpdate.mUserType = "admin";
            storeUpdatedDetails(toUpdate);
        }
        else {
            cout << "\nAccount type unchanged\n";
        }
    }
    else if (toUpdate.mUserType == "admin") {
        cout << "\nDo you wish to change it to User? (y/n)\n";
        if (inputValidationYN()) {
            toUpdate.mUserType = "admin";
            storeUpdatedDetails(toUpdate);
        }
        else {
            cout << "\nAccount type unchanged\n";
        }
    }
    else {
        cout << "\nUser type undefined. Setting to User\n";
        toUpdate.mUserType = "user";
        storeUpdatedDetails(toUpdate);
    }
}

//update user details depening on input
//paramters : int input and userDetails to change
//returns : true if user enters new input. false if user wishes to end editting
bool updateInput(int Input, userDetails& currentUser) {
    switch (Input) {
    case (1):
        cout << "\nFirst Name: ";
        cin >> currentUser.mFirstName;
        return 1;
    case (2):
        cout << "\nLast Name: ";
        cin >> currentUser.mLastName;
        return 1;
    case (3):
        cout << "\nContact Number: ";
        cin >> currentUser.mContactNumber;
        return 1;
    case (4):
        cout << "\nEmail Address: ";
        cin >> currentUser.mEmailAddress;
        return 1;
    case (5):
        cout << "\nReturning to Previous Menu\n";
        return 0;
    default:
        cout << "\nInvalid Selection. Returning to Previous Menu.";
        return 1;
    }
}

//display for updating user data
//parameters : struct containing userDetails to change
//returns : none
void userUpdate(userDetails& toUpdate) {
    int userInput = 0;
    bool menuLoop = 1;

    while (menuLoop) {
        cout << "\n==== Edit Account Details ====\n";
        displayAccountData(toUpdate);
        cout << "Please select an option:";
        cout << "\n1. First Name";
        cout << "\n2. Last Name";
        cout << "\n3. Contact Number";
        cout << "\n4. Email Address";
        cout << "\n5. Return to Previous Menu\n";

        userInput = inputValidationInt();

        menuLoop = updateInput(userInput, toUpdate);
    }
}