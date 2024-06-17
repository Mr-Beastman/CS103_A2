//included libraries
#include <iostream>
#include <string>
#include <vector>

//header file that allows us to call functions from a seperate file.
#include "userManagement.h"
#include "sharedVariables.h"

using namespace std;

//Request user input for basic account info.
//Parameters : pntr to userDetails variable to be populated.
//Returns : none.
void registerUser(userDetails& newUser) {
    cout << "Enter Username: ";
    cin >> newUser.username;
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

bool authenicateLogin(vector<userDetails>& userLogins, string username, string userPassword) {

    /*
    for (size_t i = 0; i < userLogins.size(); ++i) {
        cout << userLogins[i].username << " " << userLogins[i].password;
     }
     */

    for (size_t i = 0; i < userLogins.size(); ++i) {
        if (userLogins[i].username == username && userLogins[i].password == userPassword) {
            return 1;
        }
    }
    cout << "Invalid Credentials\n";
    return 0;
}

void adminLogin(userDetails& currentUser) {
    cout << "Admin Access";
}

void userLogin(userDetails& currentUser) {
    cout << "User Access";
}