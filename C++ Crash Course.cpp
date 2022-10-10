//Relevent Libraries
#include <iostream>
#include <string>
#include <map>
using namespace std;
//Preprocessor directive for enabling debug mode, leverages conditional compilation to help leave out unneeded debug code.
//Use cerr for the standard C++ error IO stream
#define DEBUGMODE true
#define MAXSIGTOKENS 10
#define MAXSIGCHARS 50
//Note: _CRT_SECURE_NO_WARNINGS has been applied to the preprocessor definitions to allow for strtok usage

//Program Goal: To take in a SIG code statement, and output it in plain english.
/*Example:
* 1-2BID WM PRN for pain (assuming the medication is tablet based)
* Take 1-2 tablets twice a day with meals as needed for pain
*
* SIG Codes are typically broken up like this:
* [amount per interval] [interval] [misc time of day] [other misc additons]
*
* Most prescription entry services used by pharmacies will automatically fill out portions related to entry such as "by mouth" based on the medicine selected.
*
* References:
* Doctor Jessica Roller
* https://pharmacytechniciantoday.com/pharmacy-abbreviations-sig-codes/
*/

/*
* Project Strategy
* 1. Create a map that will house each unique SIG code as the key with the plain english equivalent being mapped value.
* 2. At startup, have the program will read off these files and store them in a data structure.
* 3. The program will recieve a SIG statement from the user (command line for now).
* 4. The program will tokenize the provided string. Will throw an error if the resulting tokens to not match the expected structure.
* 5. The program will work through each token in order and build a return string of concatinated english equivalents.
* 6. The program will return the resulting string, and return to the initial state and wait for another SIG statement.
*
*/

//initialize methods
map<string, string> mapBuilder();
void printMap(map<string, string>);
void printTokens(string tokens[]);

int main()
{
    #ifdef DEBUGMODE
        cerr << "\nDEBUG: Starting in main\n";
    #endif
    //initialize important variables
    char sigInput[MAXSIGCHARS];
    //An array of string to house the SIG statement tokens, statements that I have seen are usually no longer than 5ish tokens. This will be adjusted after some research.
    string brokenUpInput[MAXSIGTOKENS];
    //A map data structure that will use the SIG codes as keys and the plain english equivalent as the mapped value
    map<string, string> SIGList = mapBuilder();
    //Context parameter for strtok_s, a pointer to help keep track of what string is read and where on the string is read next.
    //char *inputContext = NULL;


    //Prompt the user for a SIG statement
    cout << "Please enter your SIG statement. Please ensure there is a space between each part and that all caps are used.\n";
    cin.getline(sigInput, MAXSIGCHARS);
    cout << "Received statement: " << sigInput;
    //TODO input filtering of bad characters

    
    //Loop to break down the statement into an array of individual tokens.
    int iteration = 0;
    char *next = strtok(sigInput, " ");
    //iterate through the string until the current token is empty or null
    while (next != NULL) {
        brokenUpInput[iteration] = next;
        next = strtok(NULL, " ");
        iteration++;
    }//end while

    //If in debug mode, print out all tokens recieved
    #ifdef DEBUGMODE
        printTokens(brokenUpInput);
    #endif

    //Concatinate the equivalent english versions of SIG code tokens onto a final string for printout
    string prepOutput = "";
    //Map iterator
    auto it = SIGList.begin();
    for (int i = 0; brokenUpInput[i].empty() == false; i++) {
        //find the location of the key in the map. Will return a pointer to the end of the map if a result is not found.
        it = SIGList.find(brokenUpInput[i]);
        if(it != SIGList.end()) {
            //arrow operator gives access parts of the map
            //first is the, second is the value
            #ifdef DEBUGMODE
            cout << "\nDEBUG: Key value: " << it->first << " | Value: " << it->second;
            #endif
            prepOutput.append(it->second);
            prepOutput.append(" ");

        }//end if
        else
        {
            cout << "WARNING: Invalid SIG code given";
        }//end else

    }//end for

    //close the program, note the the final version will need to return the string at the end in the app.
    cout << "\nFinal output: " << prepOutput;
    return 0;
}//end main

//A function meant to construct the map and return it to main
map<string, string> mapBuilder() {
    #ifdef DEBUGMODE
        cerr << "\nDEBUG: Starting in mapBuilder\n";
    #endif
    map<string, string> temp;
    //TODO find a better way to import codes, scraping?
    
    //Interval codes
    temp["BID"] = "twice a day";
    temp["TID"] = "three times a day";

    //Drug Form, note that most pharmacy systems implement these automatically
    temp["SUPP"] = "suppository";
    temp["TAB"] = "tablet";
    temp["CAPS"] = "capsule";

    //Route
    temp["PO"] = "by mouth";
    temp["PR"] = "rectally";

    //Time of day
    temp["HS"] = "at bedtime";

    //Optional additions
    temp["PRN"] = "as needed";
    temp["UD"] = "as directed";

    return temp;
}//end mapBuilder

//A function to print out the contents of a map in a neat way for testing purposes
void printMap(map<string, string>) {
    #ifdef DEBUGMODE
        cerr << "\nDEBUG: Starting in printMap\n";
    #endif
    //TODO
    return;
}

//A function to print all found tokens for debug purposes.
void printTokens(string tokens[]) {
    #ifdef DEBUGMODE
        cerr << "\nDEBUG: Starting in printTokens\n";
    #endif
    for (int i = 0; i < sizeof(tokens); i++) {
        cout << "TOKEN: " << tokens[i] << "\n";

    }//end if
}//end function