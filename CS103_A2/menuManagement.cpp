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
        cout << "Which information do you wish to view?\n";
        cout << "1. Client Details\n";
        cout << "2. Policy Details\n";
        cout << "3. Current Claim\n";
        cout << "4. All Account Info\n";
        cout << "5. Return to Previous Menu\n";

        userInput = inputValidationInt();
        cout << "\n";

        if (userInput == 1) {
            cout << "\n==== Display Information ====\n";
            cout << "\n";
            displayAccountData(toDisplay);
            pauseEnterKey();
        }
        else if (userInput == 2) {
            cout << "\n==== Display Information ====\n";
            cout << "\n";
            displayAccountPolicy(toDisplay);
            pauseEnterKey();
        }
        else if (userInput == 3) {
            cout << "\n==== Display Information ====\n";
            cout << "\n";
            displayAccountClaim(toDisplay);
            pauseEnterKey();
        }
        else if (userInput == 4) {
            cout << "\n==== Display Information ====\n";
            cout << "\n";
            displayAccountData(toDisplay);
            displayAccountPolicy(toDisplay);
            displayAccountClaim(toDisplay);
            pauseEnterKey();
        }
        else if (userInput == 5) {
            cout << "Returning to Previous Menu\n";
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
    if (toUpdate.mPolicy.mPolicyNumber == 0) {
        cout << "\nNo Active Policy at this time. Please apply one before making claims\n";
        cout << "Returning to previous menu\n";
        return;
    }

    //checks if there is existing claim. prompts creation if not.
    if (toUpdate.mClaims.mClaimNumber == 0) {
        cout << "\nNo claim for current account.\n";
        cout << "Would you like to create one? (y/n)\n";
        if (inputValidationYN()) {
            cout << "\n";
            addClaim(toUpdate);
        }
        else {
            cout << "\nNo Claim to Edit. Returning to previous menu\n";
            return;
        }
    }

    //display options for claim
    while (menuLoop) {
        
        //force menu to close if claim has been deleted
        if (toUpdate.mPolicy.mPolicyNumber == 0) {
            return;
        }

        cout << "\n==== Claim Options ====\n";
        cout << "Please select an option:\n";
        cout << "1. Update Claim\n";
        cout << "2. Delete Claim\n";
        cout << "3. Return to Previous Menu\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            updateClaim(toUpdate);
        }
        else if (userInput == 2) {
            cout << "\n";
            if (deleteConfirmation()) {
                deleteClaim(toUpdate);
                storeUpdatedDetails(toUpdate);
                cout << "Claim deledted. Returning to previous menu";
                menuLoop = 0;
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

//menu for updating/adding policy information
//parameters: Userdata to adjust
//returns: none
void policyEditMenu(userDetails& toUpdate) {
    int userInput;
    bool menuLoop = 1;

    //checks if there is existing policy and prompts creation if not.
    if (toUpdate.mPolicy.mPolicyNumber == 0) {
        cout << "\nNo Active Policy at this time.\n";
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
        
        //force close menu after deleting policy
        if (toUpdate.mPolicy.mPolicyNumber == 0) {
            return;
        }

        cout << "\n==== Policy Options ====\n";
        cout << "Please select an option:\n";
        cout << "1. Update Current Policy\n";
        cout << "2. Delete Policy\n";
        cout << "3. Return to Previous Menu\n";
        userInput = inputValidationInt();

        if (userInput == 1) {
            updatePolicy(toUpdate);
        }
        else if (userInput == 2) {
            cout << "\nWarning - This will also delete any associated claim";
            if (deleteConfirmation()) {
                deletePolicy(toUpdate);
                deleteClaim(toUpdate);
                storeUpdatedDetails(toUpdate);
                cout << "\nPolicy deleted. Returning to Previous Menu\n";
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
        if (toUpdate.mUsername == "empty") {
            return;
        }

        cout << "\n==== Update Account ====\n";
        cout << "1. Update Account Details\n";
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
                deleteAccount(toUpdate.mUsername);
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

//function to display user menu and features.
//parameters : struct containing logged in users details. pntr.
//returns : none
void UserLoginMenu(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;
    string userDatabase = "userDatabase.txt";

    //menu loop for client menu
    while (menuLoop) {

        //forces close of menu after deleteing the account.
        if (currentUser.mUsername == "empty") {
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
        else {
            cout << "\nInvalid Seclection. Please Try again.\n";
        }
    }
}

//function to display Admin options when looking at a users account
//parameters : strut of users deatails
//returns : none
void viewUserMenu(userDetails& userDetails) {
    bool menuLoop = 1;
    int userInput;

    while (menuLoop == 1) {

        //forces close of menu after deleteing the account.
        if (userDetails.mUsername == "empty") {
            return;
        }

        cout << "\n==== Options for Account: " << userDetails.mUsername << " ====\n";
        cout << "1. View Account Details\n";
        cout << "2. Edit Account Details\n";
        cout << "3. Review Current Claim\n";
        cout << "4. Modify Account Status\n";
        cout << "5. Modify Account Type\n";
        cout << "6. Exit user account\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            displayDataMenu(userDetails);
        }
        else if (userInput == 2) {
            accountEditMenu(userDetails);
            storeUpdatedDetails(userDetails);
        }
        else if (userInput == 3) {
            changeClaimStatus(userDetails);
        }
        else if (userInput == 4) {
            changeAccountStatus(userDetails);
        }
        else if (userInput == 5) {
            changeAccountType(userDetails);
        }
        else if (userInput == 6) {
            cout << "\nReturning to Previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Seclection. Please Try again.\n";
        }
    }  
}

//display menu for managing available policies
//parameters : none
//returns : none
void policiesManagementMenu() {
    bool menuLoop = 1;
    int userInput;
    vector<insurancePolices> availablePolices;

    while (menuLoop == 1) {
        cout << "\n==== Policy Management ====\n";
        cout << "1. View Current Policies\n";
        cout << "2. Edit Existing Policy\n";
        cout << "3. Add New Policy\n";
        cout << "4. Remove Policy\n";
        cout << "5. Return to Previous Menu\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            getPolicyDetails(availablePolices);

            cout << "\n==== Policy Display ====\n";
            //dynamically populate list from policyDatabase
            for (size_t i = 0; i < availablePolices.size(); ++i) {
                cout << "Insurance Option " << (i + 1) << "\n";
                displayPolicyDetails(availablePolices[i]);
                cout << "\n";
            }
            pauseEnterKey();
        }
        else if (userInput == 2) {
            getPolicyDetails(availablePolices);

            cout << "\n==== Policy Update ====\n";
            //dynamically populate list from policyDatabase
            for (size_t i = 0; i < availablePolices.size(); ++i) {
                cout << "Insurance Option " << (i + 1) << "\n";
                displayPolicyDetails(availablePolices[i]);
                cout << "\n";
            }
            cout << "Enter Number of Policy to update\n";
            userInput = inputValidationInt();
            
            updatePolicyData(availablePolices[userInput - 1]);
        }
        else if (userInput == 3) {
            addNewPolicy();
            cout << "\nNew Policy Created\n";
        }
        else if (userInput == 4) {
            getPolicyDetails(availablePolices);

            cout << "\n==== Policy Removal ====\n";
            //dynamically populate list from policyDatabase
            for (size_t i = 0; i < availablePolices.size(); ++i) {
                cout << "Insurance Option " << (i + 1) << "\n";
                displayPolicyDetails(availablePolices[i]);
                cout << "\n";
            }
            cout << "Enter Number of Policy to remove\n";
            userInput = inputValidationInt();
            cout << "\nAre you sure you wish to delete :\n";
            cout << "\n";
            displayPolicyDetails(availablePolices[(userInput - 1)]);
            cout << "\n";
            if (deleteConfirmation()) {
                deletePolicyData(availablePolices[(userInput - 1)]);
                cout << "\nPolicy has been deleted\n";
                cout << "Exisitng users will retain coverage until cancelling\n";
                cout << "However new applications will not be eligible for it\n";
            }
            else {
                cout << "\nAction Cancelled. Returning to Previous Menu\n";
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

//display menu for admin users.
//parameter :
//returns : none
void adminLoginMenu(userDetails& currentUser) {
    bool menuLoop = 1;
    int userInput;
    userDetails clientDetails;
    vector<userDetails> accountCheck;
    string username;


    while (menuLoop) {
        cout << "\n===== Staff Portal ====\n";
        cout << "1. Register New Client\n";
        cout << "2. Client Information\n";
        cout << "3. Manage Policies\n";
        cout << "4. Logout\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            //force struct to default constructor
            clientDetails = userDetails();

            cout << "\nCreating a new account\n";
            accountCheck = getLogins();
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
            cout << "Acess via Clinet Information\n";
            cout << "Returning to Previous Menu\n";
        }
        else if (userInput == 2) {
            cout << "\n==== User Serach ====\n";
            cout << "Enter client's username: ";
            cin >> username;
            transform(username.begin(), username.end(), username.begin(), ::tolower);

            accountCheck = getLogins();

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
            policiesManagementMenu();
        }
        else if (userInput == 4) {
            cout << "\nLogging Out and Returning to Main Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Seclection. Please Try again.\n";
        }
    }
}