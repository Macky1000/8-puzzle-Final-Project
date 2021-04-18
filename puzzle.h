#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

const int MATRIX_SIZE = 9;

//extern vector<string> que; //may need to get rid of these
//extern string matrix;

class Vertex{
    private:
        int depth; //may not need this 
        //string matrixString; //dont need because we already know from unordered map
        //bool visited;
        vector<string> neighbors; //needs to be strings to work with find_Adjcent()

    public:
        Vertex(); 
        Vertex(const int& depth, const string& matrixString);
        ~Vertex();
        int getDepth() const {return this->depth; } //Gets the depth, pretty self explainitory ✓
        const vector<string>& getNeighbors() const {return neighbors;} //returns a reference to the vertex's vector of neighbors  ✓
};


class puzzleGraph{
    private:
        unordered_map<string, Vertex*>* adjList; //string is the key that is equal to the matrixstring, Vertex is the stored value
        int shortestDepth; 
        string initialMatrix;
    public:
        puzzleGraph(const string& initialMatrix);
        ~puzzleGraph();
        //void addEdge(string u, string v); //need to do
        void addVertex(const string& newMatrix, const int& depth);
        int getShortestDepth()const {return shortestDepth; } //gets the shortest depth to the goal found so far 
        void setShortestDepth(const int& newShortDepth) {shortestDepth = newShortDepth; } //sets a new shortest depth
        void read_input();
};


void read_input();
int get_zero_pos(const string& matrix);
void find_adjacent(vector<string>& adjStates, const string& matrix);

//each entry in the list can only have 4 permutations and thus have a max size of 4
//find a way to cross out redundant moves (going south then returning north)

#endif