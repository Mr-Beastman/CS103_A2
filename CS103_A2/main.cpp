//included libraries
#include<iostream>
#include<string>

//header files that allows us to call functions from seperate files.
#include "sharedFunctions.h"
#include "userManagement.h"
#include "createdVariables.h"

using namespace std;

int main() {
    int userInput;
    userDetails currentUser;
    string userDatabase = "userDatabase.txt";
    bool menuLoop;

    cout << "*******************************\n";
    cout << "* Ultra Insurance Manger 2024 *\n";
    cout << "*******************************\n";

    do{
        cout << "\nWelcome to the insurance portal\n";
        cout << "01. Login\n";
        cout << "02. Register\n";
        cout << "03. Exit\n";
        cout << "Selection: ";

        userInput = inputValidation();

        //if loop for navigating menu
        if (userInput == 1) {
            cout << "\nChoose to login\n";
        }
        else if (userInput == 2) {
            cout << "\nSelected register\n";
            registerUser(currentUser);
            storeUserDetails(userDatabase, currentUser);
            cout << "\nNew user created";
        }
        else if (userInput == 3) {
            cout << "\nChoose to exit\n";
            menuLoop = 0;
        }
        else {
            cout << "Invalid Selection please try again";
            menuLoop = 0;
        }
    }while(menuLoop = 1);

    //farewell message
    cout << "\nThank you for using the service. Have a great day!";
    
    return 0;
}