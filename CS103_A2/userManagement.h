#pragma once

#include <string>
#include "createdVariables.h"

using namespace std;

void registerUser(userDetails& newUser);

void storeUserDetails(string userDatabase, userDetails& newUser);