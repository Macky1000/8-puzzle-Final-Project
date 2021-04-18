#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>


using namespace std;

const int MATRIX_SIZE = 9;

extern vector<string> que;
extern string matrix;

class Vertex{
private:
    int depth;
    //string matrixString; //dont need because we already know from unordered map
    //bool visited;
    vector<string> neighbors; //needs to be strings to work with find_Adjcent()

public:
    Vertex();
    Vertex(const int& depth, const string& matrixString);
    ~Vertex();
};

Vertex::Vertex(){//default constructor (done)
    cout << "error in making vertex, aborting program" << endl;
    exit;

}

Vertex::Vertex(const int& depth, const string& matrixString){
    this->depth = depth;
    //needs work
    //call find_adjacent

}

Vertex::~Vertex()
{
}


class puzzleGraph
{
private:
    unordered_map<string, Vertex>* adjList; //string is the key that is equal to the matrixstring, Vertex is the stored value
public:
    puzzleGraph(const string& initialMatrix);
    ~puzzleGraph();
    //void addEdge(string u, string v); //need to do
    //void addVector();
};

//overloaded puzzleGraph constructor. Takes the initialMatrix string and add that to the map as a vertex (done) 
puzzleGraph::puzzleGraph(const string& initialMatrix){
    unordered_map<string, Vertex>* adjList = new unordered_map<string, Vertex>; //use unordered_map of Vertex pointers 
    Vertex* firstVertex = new Vertex(0, initialMatrix); //make first Vertex and get a pointer to it
    
    adjList->emplace(initialMatrix, firstVertex);// add the first matrix as a vertex to the map as a pointer.
    
}

//puzzleGraph destructor. Important for space. (NOT DONE!)
puzzleGraph::~puzzleGraph(){
    /*for (size_t i = 0; i < count; i++)
    {
        //iterate through map and call delete Vertex for all in the map
    }
    
    /*delete adjList;
    //call delete Vertex for all in the map*/
}


//extern list<int> adjList[4];// each entry in the list can only have 4 permutations and thus have a max size of 4

//gotta make a list for the graph


void read_input();
int get_zero_pos();
void find_adjacent();

#endif