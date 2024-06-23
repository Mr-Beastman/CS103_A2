#pragma once
#include<vector>
#include"sharedVariables.h"

int inputValidation();

void storeUserDetails(string userDatabase, userDetails& newUser);

void storeUpdatedDetails(string userDatabase, userDetails& userUpdates);

void getAccountDetails(string userDatabase, userDetails& user, string searchUser);

void displayUserData(userDetails& toDisplay);

void userUpdate(userDetails& currentUser);

vector<userDetails> getLogins(string userDatabase);