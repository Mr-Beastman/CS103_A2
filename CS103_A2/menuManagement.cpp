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
    
    while (menuLoop) {
        cout << "\n==== View Account Information ====\n";
        cout << "Which info do you wish to view?\n";
        cout << "1. Client Details\n";
        cout << "2. Policy Details\n";
        cout << "3. Current Claim\n";
        cout << "4. All Account Info\n";
        cout << "5. Return to Previous Menu\n";

        userInput = inputValidationInt();
        cout << "\n";

        if (userInput == 1) {
            displayAccountData(toDisplay);
            pauseAnyKey();
        }
        else if (userInput == 2) {
            displayAccountPolicy(toDisplay);
            pauseAnyKey();
        }
        else if (userInput == 3) {
            displayAccountClaim(toDisplay);
            pauseAnyKey();
        }
        else if (userInput == 4) {
            displayAccountData(toDisplay);
            displayAccountPolicy(toDisplay);
            displayAccountClaim(toDisplay);
            pauseAnyKey();
        }
        else if (userInput == 5) {
            cout << "\nReturning to Previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Selection. Please Try Again.\n";
        }
    }
}

//menu of claim edits
//parameters :  pntr to struct of user data to update.
//returns : none
void claimsEditMenu(userDetails& toUpdate){
    int userInput;
    bool menuLoop = 1;

    //if there is not policy there cant be a claim.
    if (toUpdate.policy.policyNumber == 0) {
        cout << "No Active Policy at this time. Please apply before making claims\n";
        cout << "Returning to previous menu\n";
        return;
    }

    //checks if there is existing claim. prompts creation if not.
    if (toUpdate.claims.claimNumber == 0) {
        cout << "\nNo claim for current account.\n";
        cout << "Would you like to create one? (y/n)\n";
        if (inputValidationYN()) {
            addClaim(toUpdate);
        }
        else {
            cout << "\nNo Claim to Edit. Returning to previous menu\n";
            return;
        }
    }

    //display options for claim
    while (menuLoop) {
        cout << "\n==== Edit Claims ====\n";
        cout << "Please select an option:\n";
        cout << "1. Update Claim\n";
        cout << "2. Delete Claim\n";
        cout << "3. Return to Previous Menu\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            updateClaim(toUpdate);
            
        }
        else if (userInput == 2) {
            if (deleteConfirmation()) {
                deleteClaim(toUpdate);
                storeUpdatedDetails(toUpdate);
            }
        }
        else if (userInput == 3) {
            cout << "\nReturning to Previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Selection. Please Try again\n";
        }
    }
}

//menu for Updating/adding policy information
//parameters: Userdata to adjust
//returns: none
void policyEditMenu(userDetails& toUpdate) {
    int userInput;
    bool menuLoop = 1;

    //checks if there is existing policy and prompts creation if not.
    if (toUpdate.policy.policyNumber == 0) {
        cout << "No Active Policy at this time.\n";
        cout << "Would you like to create one? (y/n)\n";
        if (inputValidationYN()) {
            addPolicy(toUpdate);
        }
        else {
            cout << "\nNo Policy to Edit. Returning to previous menu\n";
            return;
        }
    }

    //display options on editing the existing policy.
    while (menuLoop == 1) {
        cout << "\n==== Edit Policy ====\n";
        cout << "Please select an option:\n";
        cout << "1. Update Current Policy\n";
        cout << "2. Delete Policy\n";
        cout << "3. Return to Previous Menu\n";
        userInput = inputValidationInt();

        if (userInput == 1) {
            updatePolicy(toUpdate);
        }
        else if (userInput == 2) {
            if (deleteConfirmation()) {
                deletePolicy(toUpdate);
                storeUpdatedDetails(toUpdate);
            }
        }
        else if (userInput == 3) {
            cout << "\nReturning to Previous Menu\n";
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
void accountEditMenu(userDetails& toUpdate) {
    bool menuLoop = 1;
    int userInput;

    while (menuLoop) {
        //forces close of menu after deleteing the account.
        if (toUpdate.username == "empty") {
            return;
        }

        cout << "\n==== Update Account ====\n";
        cout << "1. Update Account Detiails\n";
        cout << "2. Update Policy Details\n";
        cout << "3. Update Claim Details\n";
        cout << "4. Close Account\n";
        cout << "5. Return to Previous Menu\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            userUpdate(toUpdate);
            storeUpdatedDetails(toUpdate);
        }
        else if (userInput == 2) {
            policyEditMenu(toUpdate);
            storeUpdatedDetails(toUpdate);
        }
        else if (userInput == 3) {
            claimsEditMenu(toUpdate);
            storeUpdatedDetails(toUpdate);
        }
        else if (userInput == 4) {
            cout << "\nWARNING - This cannot be undone - WARNING\n";

            if (deleteConfirmation()) {
                deleteAccount(toUpdate.username);
                toUpdate = userDetails{};
                cout << "\nAccount has been deleted\n";
                menuLoop = 0;
            }
            else {
                cout << "\nAction Cancelled\n";
            }
        }
        else if (userInput == 5) {
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
void UserLoginMenu(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;
    string userDatabase = "userDatabase.txt";

    //menu loop for client menu
    while (menuLoop) {

        //forces close of menu after deleteing the account.
        if (currentUser.username == "empty") {
            return;
        }

        cout << "\n==== Client Portal ====\n";
        cout << "1. View my Account\n";
        cout << "2. Add/Update Details\n";
        cout << "3. Log out\n";

        userInput = inputValidationInt();

        //selection logic for user input
        if (userInput == 1) {
            displayDataMenu(currentUser);
        }
        else if (userInput == 2) {
            cout << "\nAdd/Update\n";
            accountEditMenu(currentUser);
            storeUpdatedDetails(currentUser);
        }
        else if (userInput == 3) {
            cout << "\nLogging Out and returning to menu\n";
            menuLoop = 0;
        }
    }
}

void viewUserMenu(userDetails& userDetails) {
    bool menuLoop = 1;
    int userInput;

    while (menuLoop == 1) {

        //forces close of menu after deleteing the account.
        if (userDetails.username == "empty") {
            return;
        }

        cout << "\n==== Options for Account: " << userDetails.username << " ====\n";
        cout << "1. View Account Details\n";
        cout << "2. Edit Account Details\n";
        cout << "3. Exit user account\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            displayDataMenu(userDetails);
        }
        else if (userInput == 2) {
            accountEditMenu(userDetails);
            storeUpdatedDetails(userDetails);
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
void adminLoginMenu(userDetails& currentUser) {
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

        userInput = inputValidationInt();

        if (userInput == 1) {
            //force struct to default constructor
            clientDetails = userDetails();

            cout << "\nCreating a new account\n";
            accountCheck = getLogins(userDatabase);
            registerUser(accountCheck, clientDetails);
            
            cout << "\nWould you like to add a policy now? (y/n)\n";
            
            if (inputValidationYN()) {
                addPolicy(clientDetails);
            }
            else {
                cout << "\nNo policy added";
            }
            
            storeUserDetails(clientDetails);
            cout << "\nNew User Created\n";
            
            cout << "\nWould you like to open the account now? (y/n)\n";
            if (inputValidationYN()) {
                viewUserMenu(clientDetails);
            }
            else {
                cout << "Returning to Menu\n";
            }
        }
        else if (userInput == 2) {
            cout << "\nEnter client's username: ";
            cin >> username;
            transform(username.begin(), username.end(), username.begin(), ::tolower);

            accountCheck = getLogins(userDatabase);

            if (checkLogin(accountCheck, username)) {
                cout << "Account Found. Loading Options\n";
                getAccountDetails(clientDetails, username);
                viewUserMenu(clientDetails);
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