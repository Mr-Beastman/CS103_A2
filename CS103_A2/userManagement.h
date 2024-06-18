#pragma once

#include <string>
#include "sharedVariables.h"

using namespace std;

void registerUser(userDetails& newUser);

bool verifyLogin(vector<userDetails>& userLogins, string username, string userPassword);

void adminLogin(userDetails& currentUser);

void userLogin(userDetails& currentUser);