#pragma once

#include <iostream>
#include <string>

using namespace std;

struct insurancePolices {
    int mPolicyCode;
    string mInsurer;
    string mCoverage;
    string mDescription;
    float mPremiumn;
};

struct policyDetails {
    string mInsurerName;
    int mPolicyNumber;
    string mCoverageType;
    float mPreniumAmount;
    string mCarMake;
    string mCarModel;
    int mCarYear;
    string mLicensePlate;

    //constructor
    policyDetails() : mInsurerName("empty"), mPolicyNumber(0), mCoverageType("empty"), mPreniumAmount(0)
        , mCarMake("empty"), mCarModel("empty"), mCarYear(0), mLicensePlate("empty") {}
};

struct claimsDetails {
    int mClaimNumber;
    string mClaimDate;
    string mIncidentDate;
    string mIncidentLocation;
    string mIncidentDescription;
    string mClaimStatus;
    float mClaimAmount;

    //constructor
    claimsDetails() : mClaimNumber(0), mClaimDate("empty"), mIncidentDate("empty"), mIncidentLocation("empty")
        , mIncidentDescription("empty"), mClaimStatus("empty"), mClaimAmount(0) {}
};

//struct to hold key user information.
struct userDetails {
    string mUsername;
    string mPassword;
    string mUserType;
    string mAccountStatus;
    string mFirstName;
    string mLastName;
    int mContactNumber;
    string mEmailAddress;
    policyDetails mPolicy;
    claimsDetails mClaims;

    //constructor
    userDetails() : mUsername("empty"), mPassword("empty"), mUserType("user")
        , mAccountStatus("active"), mFirstName("blank"), mLastName("blank"), mEmailAddress("blank")
        , mContactNumber(0){}

};