#include "puzzle.h"

//static string matrix;
/*#include <iostream>
#include <fstream>
#include <vector>*/

//using namespace std;

//const int MATRIX_SIZE = 9;
//static string matrix;
//static vector<string> que;

/*void read_input();
int get_zero_pos();
void find_adjacent();
*/

/*int main()
{
    read_input();

    cout << "Input matrix: ";
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        cout << matrix[i];
    }
    cout << endl;
    find_adjacent();
    for (int i = 0; i < que.size(); ++i)
    {
        cout << "Possible move #" << i+1 << ": " << que[i] << endl;
    }
}*/


// Read an input file and store each integer within an array
void read_input()
{
    std::ifstream file{"input.txt"};
    if (!file.is_open()){
        cout << "Couldn't open input.txt for reading" << endl;
        return;
    }
    if (file)
    {
        char ch, i = 0;
        while (file >> ch)
        {
            if (ch != '\n' && ch != ' ')
            {
                //matrix[i] = ch;
                matrix += ch;
                
                ++i;
            }
        }
    }
    //cout << "matrix:" << matrix << endl;
    //matrix1 = matrix;
    //cout << "matrix1:" << matrix1 << endl;
}


// Get the index value of the zero tile
int get_zero_pos()
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        if (matrix[i] == '0')
        {
            return i;
        }
    }
    return -1;
}


// Find and enqueue adjacent states.
void find_adjacent()
{
    int pos = get_zero_pos();
    int row = pos / 3;
    int col = pos % 3;
    
    //cout << "matrix:" << matrix << endl; test

    if (row != 0)  // Try to move the zero tile up
    {
        string slide = matrix;
        swap(slide[pos], slide[pos-3]);
        que.push_back(slide);

        
    }

    if (row != 2)  // Try to move the zero tile down
    {
        string slide = matrix;
        swap(slide[pos], slide[pos+3]);
        que.push_back(slide);

    }

    if (col != 0)  // Try to move the zero tile left
    {
        string slide = matrix;
        swap(slide[pos], slide[pos-1]);
        que.push_back(slide);

    }

    if (col != 2)  // Try to move the zero tile right
    {
        string slide = matrix;
        swap(slide[pos], slide[pos+1]);
        que.push_back(slide);
        
    }

    
}

