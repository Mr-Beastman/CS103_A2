#pragma once
#include<vector>
#include"sharedVariables.h"

int inputValidation();

void storeUserDetails(string userDatabase, userDetails& newUser);

void getAccountDetails(string userDatabase, userDetails& user, string searchUser);

vector<userDetails> getLogins(string userDatabase);