//included libraries
#include <iostream>
#include <string>

//header files that allows us to call functions/variables from seperate files.
#include "dataManagement.h"
#include "userManagement.h"
#include "sharedVariables.h"

using namespace std;

int main() {
    int userInput;
    userDetails currentUser;
    string userDatabase = "userDatabase.txt";
    string username, userPassword;
    bool menuLoop = 1;
    vector<userDetails> loginCheck;

    cout << "*******************************\n";
    cout << "* Ultra Insurance Manger 2024 *\n";
    cout << "*******************************\n";

    do {
        cout << "\nWelcome to the insurance portal\n";
        cout << "01. Login\n";
        cout << "02. Register\n";
        cout << "03. Exit\n";
        cout << "Selection: ";

        userInput = inputValidation();

        //if loop for navigating menu
        if (userInput == 1) {
            cout << "\nChoose to login\n";  //testing place holder
            cout << "Enter Username : ";
            cin >> username;
            cout << "Enter Password : ";
            cin >> userPassword;


            //collect current logins and corrosponding passwords.
            loginCheck = getLogins(userDatabase);
            
            //checking if entered details are correct
            if (verifyLogin(loginCheck, username, userPassword)) {
                cout << "\nlog in success\n";
                
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
                    cout << "User Type not defined. Please contact admin team";
                }
            }
            else {
                cout << "\nlog in fail\n";
            }

        }
        else if (userInput == 2) {
            cout << "\nSelected register\n";    //testing place holder
            registerUser(currentUser);
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