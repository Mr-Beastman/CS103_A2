#pragma once
#include<vector>
#include"sharedVariables.h"

int inputValidation();

int generatePolicyNum();

void storeUserDetails(string userDatabase, userDetails& newUser);

void storeUpdatedDetails(string userDatabase, userDetails& userUpdates);

void getAccountDetails(string userDatabase, userDetails& user, string searchUser);

void displayUserData(userDetails& toDisplay);

void getPolicyDetails(string policyDatabase, vector<insurancePolices>& policies);

void displayPolicyDetails(insurancePolices policy);

void userUpdate(userDetails& currentUser);

vector<userDetails> getLogins(string userDatabase);