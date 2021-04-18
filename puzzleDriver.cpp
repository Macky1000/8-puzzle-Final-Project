#include "puzzle.h"
/*#include <string>
#include <iostream>
#include <fstream>*/
//using namespace std;

//const int MATRIX_SIZE = 9;

vector<string> que;
string matrix;

int main(int argc, char *argv[]){
    //cout << "num of arguments: " << argc << endl;
    

    /*if(argc == 2){ //in case we wanna test stuff on the fly. Simply run the program with an argument of 9 characters to represent the matrix and it will take that for testing. Otherwise it will just use a default input file.
        string input = argv[1];
        if(input.length() == 9){
            for(int i = 0; i <= 9; i++){ //this formats the input 
                cout << input[i] << " ";
                if(i == 2 || i == 5) {cout << endl;}
            }
        } else {
            cout << "invalid argument." << endl; //just in case we mess up
            return 1; 
        }//still need to fix this up
        
    } else {*/
        
        read_input();

        cout << "Input matrix: \n";
        for (int i = 0; i < MATRIX_SIZE; ++i)
        {
            cout << matrix[i] << " ";
            if(i == 2 || i == 5) {cout << endl;}
        }
        cout << "\n\n";
        //cout << "string: "<< matrix << endl;

        find_adjacent();

        for (int i = 0; i < que.size(); ++i)
        {
            cout << "Possible move #" << i+1 << ": " << que[i] << endl;
            for (int j = 0; j < MATRIX_SIZE; ++j)
            {
                cout << que[i][j] << " ";
                if(j == 2 || j == 5) {cout << endl;}
            }
            cout << "\n\n";
            
            
        }
        //readInput("defaultInput.txt", matrix);
    //}
    return 0;

}