/* 

Authors: Christian Guardiola, Jose Mayorga and KirkWade Polasek

Description: This program is designed to utilize artificial intelligence along with backward and 
             forward chaining to predict the type of attack and suggest methods of prevention, respectively.

Compile: g++ main.cpp

Run: ./a.out <input_file.txt>

*/
#include <iostream>
#include <fstream>

using namespace std;

string backward_chaining();
string forward_chaining();

int main(int argc,  char **argv){

    string inputFile = argv[1];
    
    cout << "Reading selected input file: " << inputFile << endl;

    // Read input file.
    ifstream dataFile;
    dataFile.open (inputFile);
    string text;
    // Reading the file line by line
    while (getline (dataFile, text)) {
    cout << text << endl;
    }
    
    dataFile.close();

    cout << "Performing backward chaining to identify the type of attack.\n";

    // Call backward chaining function.
    //string typeOfAttack = backward_chaining();

    cout << "Performing forward chaining to recommend possible preventions.\n";

    // Call forward chaining function.
    //string possiblePrev = forward_chaining();

    return 0;

}

/*
// Purpose: Utilize the backward chaining algorithm to identify the type of attack
// that has occured.
//
// Parameters:
//
// Return: String value containing the predicted type of attack.
string backward_chaining(){

}


// Purpose: Utilize the forward chaining algorithm to suggest preventative measures.
//
// Parameters:
//
// Return: String value containing the sluggested preventative measures.
string forward_chaining(){

}
*/