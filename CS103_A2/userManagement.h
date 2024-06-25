#pragma once

#include <string>
#include "sharedVariables.h"

using namespace std;

void registerUser(vector<userDetails>& userLogins, userDetails& newUser);

bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword);

bool checkLogin(vector<userDetails>& userLogins, string username);

string loginSecurity();

void lockAccount(string username);

void adminLogin(userDetails& currentUser);

void addPolicy(userDetails& toUpdate);

void addClaim(userDetails& toUpdate);