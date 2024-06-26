#pragma once

#include <string>
#include "sharedVariables.h"

using namespace std;

void UserLoginMenu(userDetails& currentUser);

void accountEditMenu(userDetails& toUpdate);

void policyEditMenu(userDetails& toUpdate);