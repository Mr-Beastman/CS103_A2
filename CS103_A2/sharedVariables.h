#pragma once

#include <iostream>
#include <string>

using namespace std;

struct insurancePolices {
    string insurer;
    string coverage;
    string description;
    float premiumn;
};

struct policyDetails {
    string insurerName;
    int policyNumber;
    string coverageType;
    float preniumAmount;
    string carMake;
    string carModel;
    int carYear;
    string licensePlate;

    //constructor
    policyDetails() : insurerName("empty"), policyNumber(0), coverageType("empty"), preniumAmount(0)
        , carMake("empty"), carModel("empty"), carYear(0), licensePlate("empty") {}
};

struct claimsDetails {
    int claimNumber;
    string claimDate;
    string incidentDate;
    string incidentLocation;
    string incidentDescription;
    string claimStatus;
    float claimAmount;

    //constructor
    claimsDetails() : claimNumber(0), claimDate("empty"), incidentDate("empty"), incidentLocation("empty")
        , incidentDescription("empty"), claimStatus("empty"), claimAmount(0) {}
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

    //constructor
    userDetails() : username("empty"), password("empty"), userType("user")
        , accountStatus("active"), firstName("blank"), lastName("blank"), emailAddress("blank")
        , contactNumber(0){}

};