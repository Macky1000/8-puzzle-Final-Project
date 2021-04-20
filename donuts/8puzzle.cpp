/****************************************************************
*   Algorithms Final Project                                    *
*                                                               *
*   Authors: Nhan Dang, Mackale Dickenson, James Mazzaro        *
*   Description: Outputs a solution to the 8-tile sliding       *
*       puzzle using breadth-first search, depth-first search,  *
*       or Dijkstra's algorithm                                 *
*****************************************************************/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Vertex{
    private:
        string str;
        int depth;

    public:
        Vertex(const string& st, const int& dep){
            this -> str = st;
            this -> depth = dep;
        }
        string getStr() const { return str; }
        int getStrValue() const { return stoi(str); }
        int getDepth() const { return depth; }
};

// Constant variables
const string INPUT_FILE = "input.txt";  // Name of input file
const int MATRIX_SIZE = 9;  // Number of matrix elements
const int NUMBER_OFFSET = 48;    // ASCII offset for converting characters to integers

// Static variables
static int depthLimit = 32;  // Depth limit for DFS algorithm

// Function declarations
string readInput();
void printMatrix(const string& matrix, const string& description);
void printState(const Vertex& vert, const int& iter, bool goalFound);
int getZeroPos(const string& matrix);
vector<Vertex> findAdjacent(const Vertex& matrix, const bool& tileDistance);
void BFS(const string& initial, const string& goal);
void DFS(const string& initial, const string& goal);
void RecDFS(Vertex current, const string& goal, unordered_map<string, int>& visited, int& iter, bool& goalFound);
void Dijkstra(const string& initial, const string& goal);


int main(){
    string initialMatrix = readInput();
    string goalMatrix = "123804765";

    printMatrix(initialMatrix, "INPUT MATRIX");
    printMatrix(goalMatrix, "GOAL MATRIX");

    // User menu
    int choice;
    cout << "Type a number corresponding to an option:" << endl;
    cout << "1 - BFS" << endl;
    cout << "2 - DFS" << endl;
    cout << "3 - Dijkstra" << endl;
    cin >> choice;
    if (choice == 1) BFS(initialMatrix, goalMatrix);
    else if (choice == 2) DFS(initialMatrix, goalMatrix);
    else if (choice == 3) Dijkstra(initialMatrix, goalMatrix);
    else{
        cout << "Invalid choice specified. Aborting program" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}


// Read an input file and store each integer within an array
string readInput(){
    string matrix = "";
    ifstream file(INPUT_FILE);
    if (!file.is_open()){
        cout << "Couldn't open \"input.txt\" for reading. Aborting program" << endl;
        exit(EXIT_FAILURE);
    }
    if (file){
        char ch, i = 0;
        while (file >> ch){
            if (ch != '\n' && ch != ' '){
                matrix += ch;
                ++i;
            }
        }
    }
    return matrix;
}


// Print out a string in matrix form
void printMatrix(const string& matrix, const string& description){
    cout << "----- " << description << " -----" << endl;
    for (int i = 0; i < MATRIX_SIZE; ++i){
        if (i % 3 == 0){
            if (i > 0){
                cout << endl;
            }
        }
        cout << matrix[i] << " ";
    }
    cout << endl << endl;
}


// Print out the current state of a given vertex
void printState(const Vertex& vert, const int& iter, bool goalFound){
    string matrixStr = vert.getStr();
    cout << "ITERATION: " << iter << endl;
    cout << "DEPTH: " << vert.getDepth() << endl;
    for (int i = 0; i < MATRIX_SIZE; ++i){
        if (i % 3 == 0){
            if (i > 0){
                cout << endl;
            }
            cout << "ROW " << (i/3)+1 << ": ";
        }
        cout << matrixStr[i] << " ";
    }
    cout << "\n--------------------" << endl;
    if (goalFound){
        cout << "Solution: Path cost = " << vert.getDepth() << endl;
    }
}


// Get the index value of the zero tile
int getZeroPos(const string& matrix){
    for (int i = 0; i < MATRIX_SIZE; ++i){
        if (matrix[i] == '0'){
            return i;
        }
    }
    cout << "No zero found in input matrix. Aborting program" << endl;
    exit(EXIT_FAILURE); //return -1;
}


// Find and enqueue adjacent states.
vector<Vertex> findAdjacent(const Vertex& matrix, const bool& tileCost){
    vector<Vertex> adj;
    int pos = getZeroPos(matrix.getStr());
    int row = pos / 3;
    int col = pos % 3;

    if (row != 0){  // Try to move the zero tile up
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos-3]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos-3] - NUMBER_OFFSET));
    }

    if (row != 2){  // Try to move the zero tile down
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos+3]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos+3] - NUMBER_OFFSET));
    }

    if (col != 0){  // Try to move the zero tile left
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos-1]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos-1] - NUMBER_OFFSET));
    }

    if (col != 2){  // Try to move the zero tile right
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos+1]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos+1] - NUMBER_OFFSET));
    }

    return adj;
}


// Append vertices from one vector to another
void append(vector<Vertex>& vertexList, vector<Vertex> verticesToAdd){
    for (unsigned i = 0; i < verticesToAdd.size(); ++i){
        vertexList.push_back(verticesToAdd[i]);
    }
}


void BFS(const string& initial, const string& goal){
    int iter = 0;
    vector<Vertex> que, adj;
    unordered_map<string, int> visited;
    que.push_back(Vertex(initial, 0));  // Add the initial vertex to the queue
    while (true){
        iter += 1;
        if (que.size() > 0){    // If the queue is not empty...
            Vertex current(que[0].getStr(), que[0].getDepth());    // Assign the "current" vertex to the element at the front of the queue
            que.erase(que.begin());    // Remove the element at the front of the queue
            if (visited.count(current.getStr()) != 0){    //  If the current vertex has already been visited...
                printState(current, iter, false);
                continue;    // Start the next loop iteration
            }
            else{    // If the current vertex has not already been visited...
                visited.insert({current.getStr(), 1});    // Add the current vertex to the visited list
                if (current.getStr() == goal){    // Check if the goal has been found
                    printState(current, iter, true);
                    break;
                }
                append(que, findAdjacent(current, false));  // Append adjacent vertices to the queue
                printState(current, iter, false);
            }
        }
    }
    return;
}


// Initialization function for depth-first search
void DFS(const string& initial, const string& goal){
    int iter = 0;
    bool goalFound = false;
    unordered_map<string, int> visited;
    RecDFS(Vertex(initial, 0), goal, visited, iter, goalFound);
}


// Recursive function for depth-first search
void RecDFS(Vertex current, const string& goal, unordered_map<string, int>& visited, int& iter, bool& goalFound){
    if (goalFound){
        return;    // Terminate recursion if the goal has been found
    }
    iter += 1;
    visited.insert({current.getStr(), 1});    // Add the current vertex to the visited list
    printState(current, iter, false);
    if (current.getStr() == goal){    // Check if the goal has been found
        goalFound = true;
        printState(current, iter, true);
    }
    vector<Vertex> adj = findAdjacent(current, false);    // Find adjacent vertices
    for (unsigned i = 0; i < adj.size(); ++i){    // For each adjacent vertex...
        if (visited.count(adj[i].getStr()) == 0){    // If an adjacent vertex has not been visited yet...
            if (adj[i].getDepth() < depthLimit){    // And if its depth is less than 32...
                RecDFS(adj[i], goal, visited, iter, goalFound);    // Recursively call DFS on the given vertex
            }
        }
    }
}


void Dijkstra(const string& initial, const string& goal){
    int iter = 0;
    unordered_map<string, int> visited;
    vector<Vertex> adj;
    adj.push_back(Vertex(initial, 0));
    while (adj.size() > 0){
        iter += 1;
        sort(adj.begin(), adj.end(), [](const Vertex& left, const Vertex& right){
            return left.getDepth() < right.getDepth();    // Sort vertices by ascending depth
        });
        Vertex current(adj[0]);    // Choose minimum depth vertex
        adj.erase(adj.begin());    // Pop the minimum depth vertex from the list
        visited.insert({current.getStr(), 1});    // Add the current vertex to the visited list
        if (current.getStr() == goal){
            printState(current, iter, true);
            break;
        }
        else{
            printState(current, iter, false);
            int adjInitialSize = adj.size() - 1;    // Keep track of the current size of adj
            append(adj, findAdjacent(current, true));    // Append adjacent vertices to adj
            for (unsigned i = adjInitialSize; i < adj.size(); ++i){    // For each newly appended adjacent vertex...
                if (visited.count(adj[i].getStr()) != 0){    // If the vertex has already been visited...
                    adj.erase(adj.begin() + i);    // Remove it from adj
                }
            }
        }
    }
}
