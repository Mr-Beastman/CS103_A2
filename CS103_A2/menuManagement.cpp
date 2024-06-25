// **This cpp file contains all menu displays and corrosponding logic**

//included libraries
#include <iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

//header file that allows us to call functions from a seperate file.
#include "userManagement.h"
#include "dataManagement.h"
#include "sharedVariables.h"

using namespace std;

//displays important userdata present in current structure
//parameters : structure with data to display.
//returns : none
void displayDataMenu(userDetails& toDisplay) {
    int userInput;
    bool menuLoop = 1;

    cout << "\n==== View Account Information ====\n";
    cout << "Which info do you wish to view?\n";
    cout << "1. Client Detials\n";
    cout << "2. Policy Detals\n";
    cout << "3. Current Claim\n";
    cout << "4. All Account Info\n";
    cout << "5. Return to Previous Menu\n";
    cout << "Selection: ";

    userInput = inputValidation();
    cout << "\n";

    if (userInput == 1 || userInput == 4) {
        displayAccountData(toDisplay);
    }
    if (userInput == 2 || userInput == 4) {
        displayAccountPolicy(toDisplay);
    }
    if (userInput == 3 || userInput == 4) {
        displayAccountClaim(toDisplay);
    }
    else if (userInput == 5) {
        cout << "\nReturning to Previous Menu\n";
        menuLoop = 0;
    }
}

//menu of claim edits
//parameters :  pntr to struct of user data to update.
//returns : none
void claimsEditMenu(userDetails& toUpdate){
    int userInput;
    char yesNoInput;
    bool menuLoop = 1;

    while (menuLoop == 1) {
        cout << "\n-- Edit Claims --\n";
        cout << "Please select an option:\n";
        cout << "1. Update Current Claim.\n";
        cout << "2. Create New Claim.\n";
        cout << "3. Return to Previous Menu\n";
        cout << "Selection : ";
        userInput = inputValidation();

        if (userInput == 1) {
            displayAccountClaim(toUpdate);
            
        }
        else if (userInput == 2) {
            cout << "\nThis will overwrite current claim details.\n";
            cout << "Do you wish to proceed (y/n)?: ";
            cin >> yesNoInput;

            if (tolower(yesNoInput) == 'y') {
                addClaim(toUpdate);
            }
            else if (tolower(yesNoInput) == 'n') {
                cout << "\nNo changes will be made. Returnting to previous Menu\n";
            }
            else {
                cout << "\nInvalid slection. Returning to previous Menu\n";
            }
        }
        else if (userInput == 3) {
            cout << "\nReturning to previous menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Selection. Please Try again\n";
        }
    }
}

//menu for Updating/adding Data
//parameters: Userdata to adjust
//returns: none
void profileEditMenu(userDetails& toUpdate) {
    const string userDatabase = "userDatabase.txt";
    bool menuLoop = 1;
    int userInput;

    while (menuLoop) {
        cout << "\n1. Update Account Detiails\n";
        cout << "2. Update Policy Details\n";
        cout << "3. Update Claim Details\n";
        cout << "4. Return to Previous Menu\n";
        cout << "Selection: ";

        userInput = inputValidation();

        if (userInput == 1) {
            userUpdate(toUpdate);
            storeUpdatedDetails(userDatabase, toUpdate);
        }
        else if (userInput == 2) {
            if (toUpdate.policy.policyNumber == 0) {
                cout << "\nNo Policy exists, creating new one.\n";
                addPolicy(toUpdate);
                storeUpdatedDetails(userDatabase, toUpdate);
            }
            else {
                
            }
        }
        else if (userInput == 3) {
            if (toUpdate.claims.claimNumber == 0) {
                cout << "\nNo current claim, creating new one.\n";
                addClaim(toUpdate);
                storeUpdatedDetails(userDatabase, toUpdate);
            }
            else {
                updateClaim(toUpdate);
                storeUpdatedDetails(userDatabase, toUpdate);
            }
        }
        else if (userInput == 4) {
            cout << "\nReturning to Previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Seclection. Please Try again.\n";
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
        cout << "1. View my Account\n";
        cout << "2. Add/Update Details\n";
        cout << "3. Log out\n";

        userInput = inputValidation();

        //selection logic for user input
        if (userInput == 1) {
            displayDataMenu(currentUser);
        }
        else if (userInput == 2) {
            cout << "\nAdd/Update\n";
            profileEditMenu(currentUser);
            storeUpdatedDetails(userDatabase, currentUser);
        }
        else if (userInput == 3) {
            cout << "\nLogging Out and returning to menu\n";
            menuLoop = 0;
        }
    }
}

void viewUser(userDetails& userDetails) {
    const string kUserDatabase = "userDatabase.txt";
    bool menuLoop = 1;
    int userInput;

    while (menuLoop == 1) {
        cout << "\n==== Options for Account: " << userDetails.username << " ====\n";
        cout << "1. View Account Details\n";
        cout << "2. Edit Account Details\n";
        cout << "3. Exit user account\n";
        cout << "Selection: ";
        userInput = inputValidation();

        if (userInput == 1) {
            displayDataMenu(userDetails);
        }
        else if (userInput == 2) {
            profileEditMenu(userDetails);
            storeUpdatedDetails(kUserDatabase, userDetails);
        }
        else if (userInput == 3) {
            cout << "\nReturning to Previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Selection\n";
        }
    }

    
}

//display menu for admin users.
//parameter :
//returns : none
void adminLogin(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;
    userDetails clientDetails;
    vector<userDetails> accountCheck;
    string username, userDatabase = "userDatabase.txt", policyDatabase = "policyDatabase.txt";


    while (menuLoop) {
        cout << "\n===== Staff Portal ====\n";

        cout << "1. Register New Client\n";
        cout << "2. Client Information\n";
        cout << "3. Generate Reports\n";
        cout << "4. Logout\n";
        cout << "Selection: ";

        userInput = inputValidation();

        if (userInput == 1) {
            //force struct to default constructor
            clientDetails = userDetails();

            cout << "\nCreating a new account\n";
            accountCheck = getLogins(userDatabase);
            registerUser(accountCheck, clientDetails);
            addPolicy(clientDetails);
            storeUserDetails(userDatabase, clientDetails);
            cout << "\nNew User Created\n";
            cout << "Returning to Menu\n";
        }
        else if (userInput == 2) {
            cout << "\nEnter client's username: ";
            cin >> username;
            transform(username.begin(), username.end(), username.begin(), ::tolower);

            accountCheck = getLogins(userDatabase);

            if (checkLogin(accountCheck, username)) {
                cout << "Account Found. Loading Options\n";
                getAccountDetails(userDatabase, clientDetails, username);
                viewUser(clientDetails);
            }
            else {
                cout << "Invalid Username\n";
            }
        }
        else if (userInput == 3) {
            cout << "\nGenerate a report\n";
        }
        else if (userInput == 4) {
            cout << "\nLogging Out and Returning to Main Menu\n";
            menuLoop = 0;
        }
    }
}