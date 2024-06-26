#pragma once

#include <string>
#include "sharedVariables.h"

using namespace std;

void registerUser(vector<userDetails>& userLogins, userDetails& newUser);

bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword);

bool checkLogin(vector<userDetails>& userLogins, string username);

string loginSecurity();

void lockAccount(string username);

void updateClaim(userDetails& toUpdate);

void updatePolicy(userDetails& toUpdate);

void adminLogin(userDetails& currentUser);

void enterCarDetails(userDetails& toUpdate);

void addPolicy(userDetails& toUpdate);

void addClaim(userDetails& toUpdate);

bool deleteConfirmation();