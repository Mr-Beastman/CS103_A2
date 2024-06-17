#pragma once
#include<vector>
#include"sharedVariables.h"

int inputValidation();

void storeUserDetails(string userDatabase, userDetails& newUser);

vector<userDetails> getLogins(string userDatabase);