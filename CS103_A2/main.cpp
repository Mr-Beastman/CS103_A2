//included libraries
#include <iostream>
#include <string>

//header files that allows us to call functions/variables from seperate files.
#include "dataManagement.h"
#include "userManagement.h"
#include "menuManagement.h"
#include "sharedVariables.h"

using namespace std;

int main() {
    const int kMaxAttempts = 3;
    int userInput, loginAttempts=0;
    userDetails currentUser;
    string userDatabase = "userDatabase.txt";
    string username, userPassword;
    bool menuLoop = 1,sercurityPass=0;
    vector<userDetails> loginCheck;

    cout << "********************************\n";
    cout << "* Ultra Insurance Manager 2024 *\n";
    cout << "********************************\n";

    do {
        cout << "\n=== Welcome to the insurance portal ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Selection: ";

        userInput = inputValidation();

        //if loop for navigating menu
        if (userInput == 1) {
            username=loginSecurity();

            if (!username.empty()) {
                //populate currentUser variable with account details mathcing the login.
                getAccountDetails(userDatabase, currentUser, username);

                //check user type and open accordingly
                if (currentUser.userType == "user") {
                    userLogin(currentUser);
                }
                else if (currentUser.userType == "admin") {
                    adminLogin(currentUser);
                }
                else {
                    //error message incase of data fault
                    cout << "User Type not defined. Please contact admin team";
                }
            }
        }
        else if (userInput == 2) {
            cout << "\nSelected register\n";

            //functions for registering, checking username available and saving new user.
            loginCheck = getLogins(userDatabase);
            registerUser(loginCheck,currentUser);
            storeUserDetails(userDatabase, currentUser);
            cout << "\nNew user created";
        }
        else if (userInput == 3) {
            cout << "\nChoose to exit\n";
            menuLoop = 0;
        }
        else {
            cout << "Invalid Selection please try again\n";
        }
    }while(menuLoop == 1);

    //farewell message
    cout << "\nThank you for using the service. Have a great day!\n";
    
    return 0;
}