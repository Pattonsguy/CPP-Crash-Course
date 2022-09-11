//Relevent Libraries
#include <iostream>

//Program Goal: To take in a SIG code statement, and output it in plain english.
/*Example:
* 1-2BID WM PRN for pain (assuming the medication is tablet based)
* Take 1-2 tablets twice a day with meals as needed for pain
*
* SIG Codes are typically broken up like this:
* [amount per interval][interval] [misc time of day][other misc additons]
*
* Most prescription entry services used by pharmacies will automatically fill out portions related to entry such as "by mouth" based on the medicine selected.
* We can assume that SIG codes will remain static. However using csv files to contain definitions could be useful should a modification be needed without having to update the app itself.
*
* References:
* Doctor Jessica Roller
*/

/*
* Project Strategy
* 1. Create CSV files that contains SIG codes and their plain english equivalent. There should be a CSV file for each of the core parts of a SIG code statement.
* 2. At startup, have the program will read off these files and store them in a data structure.
* 3. The program will recieve a SIG statement from the user (command line for now).
* 4. The program will tokenize the provided string. Will throw an error if the resulting tokens to not match the expected structure.
* 5. The program will work through each token in order and build a return string of concatinated english equivalents.
* 6. The program will return the resulting string, and return to the initial state and wait for another SIG statement.
*
*/

int main()
{
    std::cout << "Hello World!\n";

    //close the program
    return 0;
}