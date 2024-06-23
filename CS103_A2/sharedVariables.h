#pragma once

#include <iostream>
#include <string>

using namespace std;

struct policyDetails {
    string insurerName;
    int policyNumber;
    string coverageType;
    float preniumAmount;
    string carMake;
    string carModel;
    int carYear;
    string licensePlate;
};

struct claimsDetails {
    int claimNumber;
    string claimDate;
    string incidentDate;
    string incidentLocation;
    string incidentDescription;
    string claimStatus;
    float claimAmount;
};

/* easier to keep vehicle with policy rather then connect them later.
struct vehicleDetails {
    string carMake;
    string carModel;
    int carYear;
};
*/

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

    //constructor
    userDetails() : username("empty"), password("empty"), userType("user")
        , accountStatus("active"), firstName("blank"), lastName("blank"), emailAddress("blank")
        , contactNumber(0), policy({ "blank",0,"blank",0.0,"blank","blank",0,"blank"})
        , claims({0,"blank","blank","blank","blank","blank",0.0}) {}

};