#pragma once

#include <iostream>
#include <string>

using namespace std;

struct policyDetails {
    string insurerName;
    int policyNumber;
};

struct claimsDetails {
    int claimNumber;
};

struct vehicleDetails {
    string carMake;
    string carModel;
    int carYear;
};

//struct to hold key user information.
struct userDetails {
    string username;
    string password;
    string userType;
    string accountStatus;
    string firstName;
    string lastName;
    int contactNumber;
    string emailAddress;
    policyDetails policy;
    claimsDetails claims;
    vehicleDetails vehicle;

    //constructor
    userDetails() : username("empty"), password("empty"), userType("user")
        , accountStatus("active"), firstName("blank"), lastName("blank"), emailAddress("blank")
        , contactNumber(0), policy({ "blank",0}), claims({0})
        , vehicle({ "blank","blank",0 }) {}

};