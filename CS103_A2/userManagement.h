#pragma once

#include <string>
#include "sharedVariables.h"

using namespace std;

void registerUser(vector<userDetails>& userLogins, userDetails& newUser);

bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword);

bool checkLogin(vector<userDetails>& userLogins, string username);

void adminLogin(userDetails& currentUser);

void userLogin(userDetails& currentUser);

void addPolicy(vector<insurancePolices>& availablePolices, userDetails& toUpdate);