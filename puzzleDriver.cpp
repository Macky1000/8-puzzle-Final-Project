#include "puzzle.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;



int main(int argc, char *argv[]){
    //cout << "num of arguments: " << argc << endl;

    if(argc == 2){ //in case we wanna test stuff on the fly. Simply run the program with an argument of 9 characters to represent the matrix and it will take that for testing. Otherwise it will just use a default input file.
        string input = argv[1];
        if(input.length() == 9){
            for(int i = 0; i <= 9; i++){ //this formats the input 
                cout << input[i] << " ";
                if(i == 2 || i == 5) {cout << endl;}
            }
        } else {
            cout << "invalid argument." << endl; //just in case we mess up
            return 1; 
        }
        
    } else {
        //cout << "using default thing yo" << endl;
        //string input = ;
        readInput("defaultInput.txt");
        return 1;
        //ifstream in()
    }
    return 0;

}