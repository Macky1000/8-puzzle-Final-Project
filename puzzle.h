#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

const int MATRIX_SIZE = 9;

extern vector<string> que; //may need to get rid of these
extern string matrix;

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
    const vector<string> getNeighbors() const {return neighbors;} //returns a reference to the vertex's vector of neighbors  ✓
};

//default constructor ✓
Vertex::Vertex(){ 
    cout << "error in making vertex, aborting program" << endl;
    exit;

}

//Vertex constructor. NOT DONE ~~~~~~~~~~~ 🛇
Vertex::Vertex(const int& depth, const string& matrixString){
    this->depth = depth;

    //needs work
    //call find_adjacent

}

//Vertex destructor. VERY important for space. (NOT DONE!)~~~~~~~~~~~~~~~~ 🛇
Vertex::~Vertex()
{
}








class puzzleGraph
{
private:
    unordered_map<string, Vertex * > * adjList; //string is the key that is equal to the matrixstring, Vertex is the stored value
    int shortestDepth; //make getter 🛇
public:
    puzzleGraph(const string& initialMatrix);
    ~puzzleGraph();
    //void addEdge(string u, string v); //need to do
    void addVertex(const string& newMatrix, const int& depth);
    //int getShortestDepth
};

//overloaded puzzleGraph constructor. Takes the initialMatrix string and add that to the map as a vertex. ✓
puzzleGraph::puzzleGraph(const string& initialMatrix){
    unordered_map<string, Vertex>* adjList = new unordered_map<string, Vertex>; //use unordered_map of Vertex pointers 
    Vertex * firstVertex = new Vertex(0, initialMatrix); //make first Vertex and get a pointer to it
    adjList->emplace(initialMatrix, firstVertex); //add the first matrix as a vertex to the map as a pointer.
    
}

//puzzleGraph destructor. Important for space. 🛇
puzzleGraph::~puzzleGraph(){
    /*for (size_t i = 0; i < count; i++)
    {
        //iterate through map and call delete Vertex for all in the map
    }
    
    /*delete adjList;
    //call delete Vertex for all in the map*/
}

//adds a vertex to the graph. Takes the string matrix and depth, makes a new vector, then adds it to the unordered_map. ✓
void puzzleGraph::addVertex(const string& newMatrix, const int& depth){ //AKA addEdge();
    Vertex * theVertexWeAreAboutToAdd = new Vertex(depth, newMatrix); //make a pointer to a new vertext
    adjList->emplace(newMatrix, theVertexWeAreAboutToAdd); //add the pointer to the vertex to the map with the key equal to the matrix string

}


void read_input();
int get_zero_pos();
void find_adjacent();

//each entry in the list can only have 4 permutations and thus have a max size of 4
//find a way to cross out redundant moves (going south then returning north)

#endif