#pragma once
#include<vector>
#include"sharedVariables.h"

int inputValidationInt();

bool inputValidationYN();

int generatePolicyNum();

int generateClaimNum();

bool checkPolicyCode(int policyCode);

int generatePolicyCode();

string creationDate();

void displayAccountData(userDetails& toDisplay);

void displayAccountPolicy(userDetails& toDisplay);

void displayAccountClaim(userDetails& toDisplay);

void displayDataMenu(userDetails& toDisplay);

void storeUserDetails(userDetails& newUser);

void storeUpdatedDetails(userDetails& userUpdates);

void getAccountDetails(userDetails& user, string searchUser);

void addNewPolicy();

void storePolicyDetails(insurancePolices newPolicy);

void getPolicyDetails(vector<insurancePolices>& policies);

void displayPolicyDetails(insurancePolices policy);

void updatePolicyData(insurancePolices toUpdate);

void storeUpdatedPolicy(insurancePolices policyUpdates);

void userUpdate(userDetails& currentUser);

vector<userDetails> getLogins();

void deletePolicyData(insurancePolices toDelete);

void deleteAccount(string searchUserName);

void deleteClaim(userDetails& toUpdate);

void deletePolicy(userDetails& toUpdate);

void cleanDatabase(string databaseFile);
