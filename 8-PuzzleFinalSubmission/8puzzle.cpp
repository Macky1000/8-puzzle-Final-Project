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
        Vertex* prevVert;

    public:
        Vertex(const string st, const int& dep, Vertex* ptr){
            this -> str = st;
            this -> depth = dep;
            this -> prevVert = ptr;
            cout << "added vertex: " << ptr->getStr() << endl; //delete
        }
        string getStr() const { return str; }
        int getStrValue() const { return stoi(str); }
        int getDepth() const { return depth; }
        Vertex* getPrevVert() const { return prevVert; }
};

// Constant variables
const string INPUT_FILE = "input.txt";  // Name of input file
const int MATRIX_SIZE = 9;  // Number of matrix elements
const int NUMBER_OFFSET = 48;    // ASCII offset for converting characters to integers

// Static variables
static int depthLimit = 32;  // Depth limit for DFS algorithm
static bool debug = false;  // Flag to print out intermediate steps and debug information. Set to true to output information.

// Function declarations
string readInput();
void printMatrix(const string& matrix, const string& description);
void printState(const Vertex& vert, const int& iter, bool goalFound);
int getZeroPos(const string& matrix);
vector<Vertex> findAdjacent(Vertex& matrix, const bool& tileDistance);
void BFS(const string& initial, const string& goal);
void DFS(const string& initial, const string& goal);
void RecDFS(Vertex current, const string& goal, unordered_map<string, int>& visited, int& iter, bool& goalFound);
void Dijkstra(const string& initial, const string& goal);
void goalFound(Vertex* finalVert);


int main(){
    string initialMatrix = readInput();
    string goalMatrix = "123804765";

    printMatrix(initialMatrix, "INPUT MATRIX");
    printMatrix(goalMatrix, "GOAL MATRIX");

    // User menu
    int choice, choice2;
    cout << "Type a number corresponding to an option: " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1 - BFS" << endl;
    cout << "2 - DFS" << endl;
    cout << "3 - Dijkstra" << endl;
    cout << "Selection: ";
    cin >> choice;

    cout << "\nType a number corresponding to an option: " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1 - user mode: only output the final path cost" << endl;
    cout << "2 - debug mode: prints all intermediate matrices as they are visited !MUCH SLOWER!" << endl;
    cout << "Selection: ";
    cin >> choice2;
    cout << endl;

    if (choice2 == 2){debug = true; }; //debug is already set to false so it will automatically default to false in case of user error.

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
        cout << "Solution: The shortest path cost = " << vert.getDepth() << endl;
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
vector<Vertex> findAdjacent(Vertex& matrix, const bool& tileCost){
    vector<Vertex> adj;
    int pos = getZeroPos(matrix.getStr());
    int row = pos / 3;
    int col = pos % 3;

    cout << "bruh"<< endl;

    //Vertex *parent = &matrix;

    if (row != 0){  // Try to move the zero tile up
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos-3]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1, &matrix));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos-3] - NUMBER_OFFSET, &matrix));
    }

    if (row != 2){  // Try to move the zero tile down
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos+3]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1, &matrix));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos+3] - NUMBER_OFFSET, &matrix));
    }

    if (col != 0){  // Try to move the zero tile left
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos-1]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1, &matrix));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos-1] - NUMBER_OFFSET, &matrix));
    }

    if (col != 2){  // Try to move the zero tile right
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos+1]);
        if (!tileCost) adj.push_back(Vertex(slide, matrix.getDepth() + 1, &matrix));
        else adj.push_back(Vertex(slide, matrix.getDepth() + matrix.getStr()[pos+1] - NUMBER_OFFSET, &matrix));
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
    cout<< "sup1"<<endl;
    que.push_back(Vertex(initial, 0, nullptr));  // Add the initial vertex to the queue //SOMETHING IS WRONG WITH CREATING VECTORS AND IDK WHAT, IM TOO DUMB TO USE POINTERS I GUESS
    cout<< "sup2"<<endl; 
    while (true){
        iter += 1;
        if (que.size() > 0){    // If the queue is not empty...
            Vertex current(que[0].getStr(), que[0].getDepth(), &que[0]);    // Assign the "current" vertex to the element at the front of the queue
            que.erase(que.begin());    // Remove the element at the front of the queue
            if (visited.count(current.getStr()) != 0){    //  If the current vertex has already been visited...
                if(debug) printState(current, iter, false);
                continue;    // Start the next loop iteration
            }
            else{    // If the current vertex has not already been visited...
                visited.insert({current.getStr(), 1});    // Add the current vertex to the visited list
                if (current.getStr() == goal){    // Check if the goal has been found
                    if(debug) printState(current, iter, true);
                    goalFound(&current);
                    //cout << "Solution: The shortest path cost = " << current.getDepth() << endl;
                    break;
                }
                append(que, findAdjacent(current, false));  // Append adjacent vertices to the queue
                if(debug) printState(current, iter, false);
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
    RecDFS(Vertex(initial, 0, nullptr), goal, visited, iter, goalFound);
}


// Recursive function for depth-first search
void RecDFS(Vertex current, const string& goal, unordered_map<string, int>& visited, int& iter, bool& goalFoundFlag){
    if (goalFoundFlag){
        return;    // Terminate recursion if the goal has been found
    }
    iter += 1;
    visited.insert({current.getStr(), 1});    // Add the current vertex to the visited list
    if(debug) printState(current, iter, false);
    if (current.getStr() == goal){    // Check if the goal has been found
        goalFoundFlag = true;
        if(debug) printState(current, iter, true);
        goalFound(&current);
        //cout << "Solution: The shortest path cost = " << current.getDepth() << endl;
    }
    vector<Vertex> adj = findAdjacent(current, false);    // Find adjacent vertices
    for (unsigned i = 0; i < adj.size(); ++i){    // For each adjacent vertex...
        if (visited.count(adj[i].getStr()) == 0){    // If an adjacent vertex has not been visited yet...
            if (adj[i].getDepth() < depthLimit){    // And if its depth is less than 32...
                RecDFS(adj[i], goal, visited, iter, goalFoundFlag);    // Recursively call DFS on the given vertex
            }
        }
    }
}


void Dijkstra(const string& initial, const string& goal){
    int iter = 0;
    unordered_map<string, int> visited;
    vector<Vertex> adj;
    adj.push_back(Vertex(initial, 0, nullptr));
    while (adj.size() > 0){
        iter += 1;
        sort(adj.begin(), adj.end(), [](const Vertex& left, const Vertex& right){
            return left.getDepth() < right.getDepth();    // Sort vertices by ascending depth
        });
        Vertex current(adj[0]);    // Choose minimum depth vertex
        adj.erase(adj.begin());    // Pop the minimum depth vertex from the list
        visited.insert({current.getStr(), 1});    // Add the current vertex to the visited list
        if (current.getStr() == goal){
            if(debug) printState(current, iter, true);
            goalFound(&current);
            cout << "Solution: The shortest path cost = " << current.getDepth() << endl;
            break;
        }
        else{
            if(debug) printState(current, iter, false);
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

void goalFound(Vertex* LastV){
    cout << "\n\nPath found:" << endl;
    //int depth = LastV->getDepth();
    vector<Vertex*> finalPath;
    finalPath.push_back(LastV);
    //LastV.getPrevVert();
    cout<< "before LastV: " << LastV->getPrevVert()->getStr() << endl;
    for (Vertex* i = LastV->getPrevVert(); i != nullptr; i = i->getPrevVert()){
        cout << "adding vertex " << i << endl;
        finalPath.push_back(i);
    }
    for (int i = 0; i != LastV->getDepth() - 1; i++){
        printState(*finalPath[i], finalPath[i]->getDepth(), false);

        cout << "yup" << i <<endl;
        cout << "last depth = " << LastV->getDepth() << endl;
    }
    printState(*LastV, LastV->getDepth(), true);

}