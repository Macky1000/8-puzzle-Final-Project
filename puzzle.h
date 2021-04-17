#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MATRIX_SIZE = 9;

extern vector<string> que;
extern string matrix;

//void readInput(const string& defaultInput, int& matrix);
void read_input();
int get_zero_pos();
void find_adjacent();

#endif