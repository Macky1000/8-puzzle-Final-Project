#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

const int MATRIX_SIZE = 9;

extern vector<string> que;
extern string matrix;

struct vertex
{
    string newMatrix;
    int depth;
    
};


//extern list<int> adjList[4];// each entry in the list can only have 4 permutations and thus have a max size of 4

//gotta make a list for the graph
extern list<vector<string>> adjLists;


//void addEdge(int u, int v){ //need to do



void read_input();
int get_zero_pos();
void find_adjacent();

#endif