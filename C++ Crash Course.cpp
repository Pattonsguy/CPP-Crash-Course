//Relevent Libraries
#include <iostream>
#include <string>
#include <map>
using namespace std;
//Preprocessor directive for enabling debug mode, leverages conditional compilation to help leave out unneeded debug code.
//Use cerr for the standard C++ error IO stream
#define DEBUGMODE true
#define MAXSIGTOKENS 10

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
    char sigInput[] = "";
    //An array of string to house the SIG statement tokens, statements that I have seen are usually no longer than 5ish tokens. This will be adjusted after some research.
    string brokenUpInput[MAXSIGTOKENS];
    //A map data structure that will use the SIG codes as keys and the plain english equivalent as the mapped value
    map<string, string> SIGList = mapBuilder();
    //Context parameter for strtok_s, a pointer to help keep track of what string is read and where on the string is read next.
    char *inputContext = NULL;


    //Main loop of the program
    while (true) {
        //Prompt the user for a SIG statement
        cout << "Please enter your SIG statement. Please ensure there is a space between each part and that all caps are used.\n";
        cin >> sigInput;
        cout << "Received statement: " << sigInput;

        //Loop to break down the statement into an array of individual tokens.
        brokenUpInput[0] = strtok_s(sigInput, " ", &inputContext);
        int iteration = 1;
        while (sigInput != NULL) {
            brokenUpInput[iteration] = strtok_s(NULL, " ", &inputContext);
            iteration++;
        }//end while

        //If in debug mode, print out all tokens recieved
        #ifdef DEBUGMODE
            printTokens(brokenUpInput);
        #endif

    }//end while


    //close the program
    return 0;
}//end main

//A function meant to construct the map and return it to main
map<string, string> mapBuilder() {
    #ifdef DEBUGMODE
        cerr << "\nDEBUG: Starting in mapBuilder\n";
    #endif
    map<string, string> temp;
    //A testing example
    temp["BID"] = "twice a day";
    //TODO find a method to automate importing SIG codes.

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