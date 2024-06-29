//included libraries
#include <iostream>  
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>  
#include <vector>
#include <string>
#include <limits>
#include <ctime>

//header file that allows us to call functions from a separate file.
#include "dataManagement.h"
#include "sharedVariables.h"
#include "userManagement.h"

using namespace std;

//function to confirm user input is a valid type. eg not char/float.
//parameter: None
//returns: integer
int inputValidationInt() {
    float userInput;
    bool valid;
    
    do {
        cout << "Selection : ";
        cin >> userInput;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a valid option\n";
            cin >> userInput;
        }

        if (floor(userInput) != userInput) {
            valid = 0;
            cout << "\nInvalid input. Please enter a valid option\n";
        }
        else {
            valid = 1;
        }

    } while (valid==0);


    return userInput;
}

//function to confirm user input is a valid for y/n.
//parameters : none
//returns : 1 true, 0 false
bool inputValidationYN() {
    string userInput;

    while (true) {
        cout << "Selection: ";
        cin >> userInput;

        if (tolower(userInput[0]) == 'y') {
            return 1;
        }
        else if (tolower(userInput[0]) == 'n') {
            return 0;
        }
        else {
            cout << "\n Invalid Selection. Please try again";
        }
    }
}

//get todays date for recording creation dates.
//parameters : none
//returns : string containing the current date in dd/mm/yyyy format
string creationDate(){

    ostringstream currentDate;
    time_t t = time(0);
    tm now;
    
    localtime_s(&now, &t);
    
    currentDate << put_time(&now, "%d/%m/%y");

    return currentDate.str();
}

//generate a random policy Number
//parameters : None
//returns : random int value
int generatePolicyNum() {
    const int kMin = 1000;
    const int kMax = 9999;

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<>dis(kMin, kMax);

    return(dis(gen));
}

//generate a random claim Number
//parameters : None
//returns : random int value
int generateClaimNum() {
    const int kMin = 100;
    const int kMax = 999;

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<>dis(kMin, kMax);

    return(dis(gen));
}

//check if policy code already exists
//parameters : int to check
//returns : true if exists false if not
bool checkPolicyCode(int policyCode) {
    const string kPolicyDatabase = "policyDatabase.txt";
    ifstream inDatabase(kPolicyDatabase);
    string line;
    string policyCodeString;
    int codeToCheck;

    while (getline(inDatabase, line)) {
        istringstream iss(line);
        getline(iss, policyCodeString, ',');
        codeToCheck = stoi(policyCodeString);
        if (codeToCheck == policyCode) {
            return 1;
        }
    }
    inDatabase.close();
    return 0;
}

//generate a random Policy Code
//parameters : None
//returns : random int value
int generatePolicyCode() {
    const int kMin = 1;
    const int kMax = 99;

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<>dis(kMin, kMax);

    return(dis(gen));
}

//function to display account details in console.
//parameters : userDetails Structure with info to display
//returns : none
void displayAccountData(userDetails& toDisplay) {
    cout << "--- Client Details ---\n";
    cout << "Username: " << toDisplay.mUsername << "\n";
    cout << "User Type: " << toDisplay.mUserType << "\n";
    cout << "Account Status: " << toDisplay.mAccountStatus << "\n";
    cout << "First Name : " << toDisplay.mFirstName << "\n";
    cout << "Last Name : " << toDisplay.mLastName << "\n";
    cout << "Contact Number : 0" << toDisplay.mContactNumber << "\n";
    cout << "Email Address : " << toDisplay.mEmailAddress << "\n";
    cout << "\n";
}

//function to display policy details in console.
//parameters : userDetails Structure with info to display
//returns : none
void displayAccountPolicy(userDetails& toDisplay) {
    cout << "--- Current Policy ---\n";
    if (toDisplay.mPolicy.mPolicyNumber == 0) {
        cout << "No active Policy at this time.\n";
        cout << "\n";
    }
    else {
        cout << "Insurer Name: " << toDisplay.mPolicy.mInsurerName << "\n";
        cout << "Policy Number: " << toDisplay.mPolicy.mPolicyNumber << "\n";
        cout << "Coverage Type: " << toDisplay.mPolicy.mCoverageType << "\n";
        cout << setprecision(2) << fixed;
        cout << "Premium Amount: $" << toDisplay.mPolicy.mPreniumAmount << "\n";
        cout << "Car Make: " << toDisplay.mPolicy.mCarMake << "\n";
        cout << "Car Model: " << toDisplay.mPolicy.mCarModel << "\n";
        cout << "Car Year: " << toDisplay.mPolicy.mCarYear << "\n";
        cout << "License Plate: " << toDisplay.mPolicy.mLicensePlate << "\n";
        cout << "\n";
    }
}

//function to display claim details in console.
//parameters : userDetails Structure with info to display
//returns : none
void displayAccountClaim(userDetails& toDisplay) {
    cout << "--- Current Claim ---\n";
    if (toDisplay.mClaims.mClaimNumber == 0) {
        cout << "No active claim at this time.\n";
        cout << "\n";
    }
    else {
        cout << "Claim Number: " << toDisplay.mClaims.mClaimNumber << "\n";
        cout << "Date Claim Filed: " << toDisplay.mClaims.mClaimDate << "\n";
        cout << "Incident Date: " << toDisplay.mClaims.mIncidentDate << "\n";
        cout << "Incident Location: " << toDisplay.mClaims.mIncidentLocation << "\n";
        cout << "Incident Description: " << toDisplay.mClaims.mIncidentDescription << "\n";
        cout << "Claim Status: " << toDisplay.mClaims.mClaimStatus << "\n";
        cout << setprecision(2) << fixed;
        cout << "Claim Amount: $" << toDisplay.mClaims.mClaimAmount << "\n";
        cout << "\n";
    }
}

//writes user details to the "userDatabase"
//Parameters : filename to store info and pntr to userDetails Variable.
//Returns : none
void storeUserDetails(userDetails& newUser) {
    const string kUserDatabase = "userDatabase.txt";
    ofstream outfile(kUserDatabase, ios::app);

    if (outfile.is_open()) {
        outfile << newUser.mUsername << "," 
            << newUser.mPassword << ","
            << newUser.mUserType << ","
            << newUser.mAccountStatus << ","
            << newUser.mFirstName << ","
            << newUser.mLastName << ","
            << newUser.mContactNumber << ","
            << newUser.mEmailAddress << "," 
            << newUser.mPolicy.mInsurerName << ","
            << newUser.mPolicy.mPolicyNumber << ","
            << newUser.mPolicy.mCoverageType << ","
            << newUser.mPolicy.mPreniumAmount << ","
            << newUser.mPolicy.mCarMake << ","
            << newUser.mPolicy.mCarModel << ","
            << newUser.mPolicy.mCarYear << ","
            << newUser.mPolicy.mLicensePlate << ","
            << newUser.mClaims.mClaimNumber << ","
            << newUser.mClaims.mClaimDate << ","
            << newUser.mClaims.mIncidentDate << ","
            << newUser.mClaims.mIncidentLocation << ","
            << newUser.mClaims.mIncidentDescription << ","
            << newUser.mClaims.mClaimStatus << ","
            << newUser.mClaims.mClaimAmount << endl;
    }
    else {
        cout << "Unable to store user details";
    }
}

//overwrite existing user details with ones currently stored in userDetails struct
//parameters : file name to change, update userdetails struct.
//returns : none 
void storeUpdatedDetails(userDetails& userUpdates) {
    const string kUserDatabase="userDatabase.txt";
    ifstream infile(kUserDatabase);
    vector<string> lines;
    string line,username;

    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, username, ',');

        if (username == userUpdates.mUsername) {
            stringstream newLine;
            newLine << userUpdates.mUsername << ","
                << userUpdates.mPassword << ","
                << userUpdates.mUserType << ","
                << userUpdates.mAccountStatus << ","
                << userUpdates.mFirstName << ","
                << userUpdates.mLastName << ","
                << userUpdates.mContactNumber << ","
                << userUpdates.mEmailAddress << ","
                << userUpdates.mPolicy.mInsurerName << ","
                << userUpdates.mPolicy.mPolicyNumber << ","
                << userUpdates.mPolicy.mCoverageType << ","
                << userUpdates.mPolicy.mPreniumAmount << ","
                << userUpdates.mPolicy.mCarMake << ","
                << userUpdates.mPolicy.mCarModel << ","
                << userUpdates.mPolicy.mCarYear << ","
                << userUpdates.mPolicy.mLicensePlate << ","
                << userUpdates.mClaims.mClaimNumber << ","
                << userUpdates.mClaims.mClaimDate << ","
                << userUpdates.mClaims.mIncidentDate << ","
                << userUpdates.mClaims.mIncidentLocation << ","
                << userUpdates.mClaims.mIncidentDescription << ","
                << userUpdates.mClaims.mClaimStatus << ","
                << userUpdates.mClaims.mClaimAmount << endl;

            lines.push_back(newLine.str());
        }
        else {
            lines.push_back(line);
        }
    }

    infile.close();
    
    ofstream outfile(kUserDatabase);
    for (auto & line : lines) {
        outfile << line << endl;
    }

    outfile.close();
    
    //remove empty lines left over from updating data to newline
    cleanDatabase(kUserDatabase);
}

//search via username to get account details and update userDetails pntr
//parameters : database filename, userDetail structure to store in, username to search with.
//Returns : none
void getAccountDetails(userDetails& user, string searchUser) {
    const string kUserDatabase = "userDatabase.txt";
    ifstream file(kUserDatabase);
    string line;
    userDetails account;
    string username;

    while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, username, ',');
        if (username == searchUser) {
            user.mUsername = username;
            getline(ss, user.mPassword, ',');
            getline(ss, user.mUserType, ',');
            getline(ss, user.mAccountStatus, ',');
            getline(ss, user.mFirstName, ',');
            getline(ss, user.mLastName, ',');
            ss >> user.mContactNumber;
            ss.ignore();
            getline(ss, user.mEmailAddress, ',');
            getline(ss, user.mPolicy.mInsurerName, ',');
            ss >> user.mPolicy.mPolicyNumber;
            ss.ignore();
            getline(ss, user.mPolicy.mCoverageType, ',');
            ss >> user.mPolicy.mPreniumAmount;
            ss.ignore();
            getline(ss, user.mPolicy.mCarMake, ',');
            getline(ss, user.mPolicy.mCarModel, ',');
            ss >> user.mPolicy.mCarYear;
            ss.ignore();
            getline(ss, user.mPolicy.mLicensePlate, ',');
            ss >> user.mClaims.mClaimNumber;
            ss.ignore();
            getline(ss, user.mClaims.mClaimDate, ',');
            getline(ss, user.mClaims.mIncidentDate, ',');
            getline(ss, user.mClaims.mIncidentLocation, ',');
            getline(ss, user.mClaims.mIncidentDescription, ',');
            getline(ss, user.mClaims.mClaimStatus, ',');
            ss >> user.mClaims.mClaimAmount;
            ss.ignore();
        }
    }
}

//function to save new policy to database
//parameters : struct to save to database
//return : none
void storePolicyDetails(insurancePolices newPolicy) {
    const string kPolicyDatabase = "policyDatabase.txt";
    ofstream outfile(kPolicyDatabase, ios::app);

    if (outfile.is_open()) {
        outfile << newPolicy.mPolicyCode << ","
            << newPolicy.mInsurer << ","
            << newPolicy.mCoverage << ","
            << newPolicy.mDescription << ","
            << newPolicy.mPremiumn << endl;
    }
    else {
        cout << "Unable to store user details";
    }

    outfile.close();
}

//store updated policy details
//paramerers : struct with data to update
//returns : none
void storeUpdatedPolicy(insurancePolices policyUpdates) {
    const string kPolicyDatabase = "policyDatabase.txt";
    ifstream infile(kPolicyDatabase);
    vector<string> lines;
    string line, policyCodeString;
    int policyCode;

    while (getline(infile, line)) {
        stringstream ss(line);

        getline(ss, policyCodeString, ',');
        policyCode = stoi(policyCodeString);

        if (policyCode == policyUpdates.mPolicyCode) {
            stringstream newLine;
            newLine << policyUpdates.mPolicyCode << ","
                << policyUpdates.mInsurer << ","
                << policyUpdates.mCoverage << ","
                << policyUpdates.mDescription << ","
                << policyUpdates.mPremiumn << endl;

            lines.push_back(newLine.str());
        }
        else {
            lines.push_back(line);
        }
    }

    infile.close();

    ofstream outfile(kPolicyDatabase);
    for (auto& line : lines) {
        outfile << line << endl;
    }

    outfile.close();

    cleanDatabase(kPolicyDatabase);
}

void addNewPolicy() {
    insurancePolices newPolicy;
    string insurerName, coverage, description;
    bool policyCodeCheck = 1;
    float premiumn;

    //prompt entry from user
    cout << "\n==== Adding New Policy ====\n";
    cout << "Enter Insurer Name: ";
    cin.ignore();
    getline(cin, insurerName);
    cout << "Enter Type of Coverage: ";
    getline(cin, coverage);
    cout << "Enter Description: ";
    getline(cin, description);
    cout << "Enter Premiumn: ";
    cin >> premiumn;

    //assign random identifier code
    while (policyCodeCheck) {
        //generate random number
        newPolicy.mPolicyCode = generatePolicyCode();
        //check if number already exists
        policyCodeCheck = checkPolicyCode(newPolicy.mPolicyCode);
    }

    //populate struct with data
    newPolicy.mInsurer = insurerName;
    newPolicy.mCoverage = coverage;
    newPolicy.mDescription = description;
    newPolicy.mPremiumn = premiumn;

    storePolicyDetails(newPolicy);
}

//get policy details from policyDatabase.txt
//parameter : database filename, vector of struct to update with information
//retuns : none
void getPolicyDetails(vector<insurancePolices>& policies) {
    const string kPolicyDatabase = "policyDatabase.txt";
    ifstream file(kPolicyDatabase);
    string line;
    float premium;
    int policyCode;

    //insure vector is empty before loading data
    policies.clear();

    while (getline(file, line)) {
        istringstream ss(line);
        string policyCodeString, insurer, coverage, description, premiumString;

        getline(ss, policyCodeString, ',');
        getline(ss, insurer, ',');
        getline(ss, coverage, ',');
        getline(ss, description, ',');
        getline(ss, premiumString, ',');

        premium = stof(premiumString);
        policyCode = stoi(policyCodeString);

        insurancePolices policy = { policyCode,insurer,coverage,description,premium };
        policies.push_back(policy);
    }

    file.close();
}

//function for displaying policy info fromn a struct.
//parameters : Struct with info to view
//retutns : none
void displayPolicyDetails(insurancePolices policy) {
    cout << "Insurer : " << policy.mInsurer << "\n";
    cout << "Coverage Type : " << policy.mCoverage << "\n";
    cout << "Description : " << policy.mDescription << "\n";
    cout << "Premium : $" << policy.mPremiumn<<"\n";
}

//collects usernames and passwords from userDatabase.txt.
//parameters : string containt name of text file to check
//returns : a vector containing all current usernames and passwords.
vector<userDetails> getLogins() {
    const string kUserDatabase = "userDatabase.txt";
    vector<userDetails> usernames;
    string data;

    ifstream file(kUserDatabase);

    if (!file.is_open()) {
        cout << "Unable to open: " << kUserDatabase << "\n";
        return usernames;
    }

    while (getline(file, data)) {
        istringstream ss(data);
        string field;
        userDetails user;

        if (getline(ss, field, ',')) {
            user.mUsername = field;
        }

        if (getline(ss, field, ',')) {
            user.mPassword = field;
        }

        usernames.push_back(user);
    }
    return usernames;
}

//function for updating policy details saved in policyDatabase.text
//parameters : a struct containing the policy to update
//returns : none
void updatePolicyData(insurancePolices toUpdate) {
    bool menuLoop = 1;
    int userInput;
    string updateText;
    float updateAmount;

    while (menuLoop) {
        cout << "\n==== Edit Policy Data ====\n";
        cout << "Which section would you like to update?\n";
        cout << "1. Change Insurer Name\n";
        cout << "2. Change Coverage Details\n";
        cout << "3. Change Description\n";
        cout << "4. Change Premium\n";
        cout << "5. Return to Previous Menu\n";

        userInput = inputValidationInt();

        if (userInput == 1) {
            cout<<"\nEnter New Insurer Name: ";
            cin.ignore();
            getline(cin, updateText);
            toUpdate.mInsurer = updateText;
            storeUpdatedPolicy(toUpdate);
        }
        else if (userInput == 2) {
            cout<<"\nEnter New Coverage Details: ";
            cin.ignore();
            getline(cin, updateText);
            toUpdate.mCoverage = updateText;
            storeUpdatedPolicy(toUpdate);
        }
        else if (userInput == 3) {
            cout<<"\nEnter New Coverage Description: ";
            cin.ignore();
            getline(cin, updateText);
            toUpdate.mDescription = updateText;
            storeUpdatedPolicy(toUpdate);
        }
        else if (userInput == 4) {
            cout<<"\nEnter New Coverage Description: ";
            cin >> updateAmount;
            toUpdate.mPremiumn = updateAmount;
            storeUpdatedPolicy(toUpdate);
        }
        else if (userInput == 5) {
            cout << "\nReturning to Previous Menu\n";
            menuLoop = 0;
        }
        else {
            cout << "\nInvalid Selection. Please Try Again\n";
        }
    }
}

//delete line containing userdata from userDatabase.txt
//parameters : username to delete
//returns : none
void deletePolicyData(insurancePolices toDelete) {
    const string kPolicyDatabase="policyDatabase.txt";
    ifstream inputDatabase(kPolicyDatabase);
    vector<string>lines;
    string policyCodeString, line;
    int policyCode;

    while (getline(inputDatabase, line)) {
        istringstream ss(line);
        if (getline(ss, policyCodeString, ',')) {
            policyCode = stoi(policyCodeString);
            if (policyCode != toDelete.mPolicyCode) {
                lines.push_back(line);
            }
        }
    }
    inputDatabase.close();

    ofstream outputDatabase(kPolicyDatabase);
    for (size_t i = 0; i < lines.size(); ++i) {
        outputDatabase << lines[i] << '\n';
    }

    outputDatabase.close();
}

//delete line containing userdata from userDatabase.txt
//parameters : username to delete
//returns : none
void deleteAccount(string searchUserName) {
    const string kUserDatabase = "userDatabase.txt";
    ifstream inputDatabase(kUserDatabase);
    vector<string>lines;
    string user, line;

    while (getline(inputDatabase, line)) {
        istringstream ss(line);
        if (getline(ss, user, ',')) {
            if (user != searchUserName) {
                lines.push_back(line);
            }
        }
    }
    inputDatabase.close();

    ofstream outputDatabase(kUserDatabase);
    for (size_t i = 0; i < lines.size(); ++i) {
        outputDatabase << lines[i] << '\n';
    }

    outputDatabase.close();
}

//Deletes claim info by resetting structure to default constructor
//parameters : userDetails struct to update
//returns : none
void deleteClaim(userDetails& toUpdate) {
    toUpdate.mClaims = claimsDetails{};
}

//Deletes policy info by resetting structure to default constructor
//parameters : userDetails struct to update
//returns : none
void deletePolicy(userDetails& toUpdate) {
    toUpdate.mPolicy = policyDetails{};
}

//cleans up database files by removing emptylines
//parameters : database to clean up
//returns : none
void cleanDatabase(string databaseFile) {
    ifstream database(databaseFile);
    vector<string> lines;
    string line;

    //get all the lines that aren't empty
    while (getline(database, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    database.close();

    ofstream outDatabase(databaseFile, ios::trunc);

    for (size_t i = 0; i < lines.size(); ++i) {
        outDatabase << lines[i] << endl;
    }

    outDatabase.close();
}