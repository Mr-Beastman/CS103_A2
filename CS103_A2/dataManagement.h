#pragma once
#include<vector>
#include"sharedVariables.h"

int inputValidationInt();

bool inputValidationYN();

int generatePolicyNum();

int generateClaimNum();

string creationDate();

void displayAccountData(userDetails& toDisplay);

void displayAccountPolicy(userDetails& toDisplay);

void displayAccountClaim(userDetails& toDisplay);

void displayDataMenu(userDetails& toDisplay);

void storeUserDetails(string userDatabase, userDetails& newUser);

void storeUpdatedDetails(userDetails& userUpdates);

void getAccountDetails(string userDatabase, userDetails& user, string searchUser);

void getPolicyDetails(string policyDatabase, vector<insurancePolices>& policies);

void displayPolicyDetails(insurancePolices policy);

void userUpdate(userDetails& currentUser);

vector<userDetails> getLogins(string userDatabase);

void deleteAccount(string searchUserName);

void deleteClaim(userDetails& toUpdate);

void deletePolicy(userDetails& toUpdate);