#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Vertex{
    private:
        string str;
        int depth;

    public:
        Vertex(const string& str, const int& depth){
            this -> str = str;
            this -> depth = depth;
        }
        void setStr(const string& newStr) { str = newStr; }
        void setDepth(const int& newDepth) { depth = newDepth; }
        string getStr() const { return str; }
        int getDepth() const { return depth; }
};

// Constant variables
const string INPUT_FILE = "input.txt";  // Name of input file
const int MATRIX_SIZE = 9;  // Number of matrix elements

// Static variables
static string initialMatrix;  // Initial state
static string goalMatrix = "123804765";  // Goal state
static vector<Vertex> adjStates;  // Vector of adjacent vertices
static int depthLimit = 32;  // Depth limit for DFS algorithm

// Function declarations
string readInput();
void printState(const Vertex& vert, const int& iter, bool goalFound);
int getZeroPos(const string& matrix);
vector<Vertex> findAdjacent(const Vertex& matrix);
void BFS(const string& initial, const string& goal);
void DFS(const string& initial, const string& goal);
void RecDFS(const Vertex& initial, const string& goal, unordered_map<string, Vertex>& visited, int& iter, bool& goalFound);
void Dijkstra(const string& initial, const string& goal);


int main(){
    initialMatrix = readInput();
    Vertex initialVertex(initialMatrix, 0);

    // quick and dirty user menu; unfinished
    int choice;
    cout << "Type a number corresponding to an option:" << endl;
    cout << "1 - BFS" << endl;
    cout << "2 - DFS (unfinished)" << endl;
    cout << "3 - Dijkstra (unfinished)" << endl;
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
vector<Vertex> findAdjacent(const Vertex& matrix){
    vector<Vertex> adj;
    int pos = getZeroPos(matrix.getStr());
    int row = pos / 3;
    int col = pos % 3;

    if (row != 0){  // Try to move the zero tile up
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos-3]);
        adj.push_back(Vertex(slide, matrix.getDepth() + 1));
    }

    if (row != 2){  // Try to move the zero tile down
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos+3]);
        adj.push_back(Vertex(slide, matrix.getDepth() + 1));
    }

    if (col != 0){  // Try to move the zero tile left
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos-1]);
        adj.push_back(Vertex(slide, matrix.getDepth() + 1));
    }

    if (col != 2){  // Try to move the zero tile right
        string slide = matrix.getStr();
        swap(slide[pos], slide[pos+1]);
        adj.push_back(Vertex(slide, matrix.getDepth() + 1));
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
    unordered_map<string, Vertex> visited;
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
                visited.insert({current.getStr(), current});    // Add the current vertex to the visited list
                if (current.getStr() == goal){    // Check if the goal has been found
                    printState(current, iter, true);
                    break;
                }
                append(que, findAdjacent(current));  // Append adjacent vertices to the queue
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
    unordered_map<string, Vertex> visited;
    visited.insert({initial, Vertex(initial, 0)});    // Add the initial vertex to the visited list
    RecDFS(Vertex(initial, 0), goal, visited, iter, goalFound);
}


// Recursive function for depth-first search
void RecDFS(const Vertex& current, const string& goal, unordered_map<string, Vertex>& visited, int& iter, bool& goalFound){
    iter += 1;
    if (goalFound){
        return;
    }
    printState(current, iter, false);
    visited.insert({current.getStr(), current});    // Add the current vertex to the visited list
    if (current.getStr() == goal){    // Check if the goal has been found
        goalFound = true;
        printState(current, iter, true);
    }
    vector<Vertex> adj = findAdjacent(current);
    for (unsigned i = adj.size()-1; i >= 0; i--){
        if (visited.count(adj[i].getStr()) == 0){    // If an adjacent vertex has not been visited yet...
            if (adj[i].getDepth() < depthLimit){    // And if its depth is less 32...
                RecDFS(adj[i], goal, visited, iter, goalFound);    // Recursively call DFS on the given vertex
            }
        }
    }
}


void Dijkstra(const string& initial, const string& goal){
    cout << "NYI" << endl;
}


//adj = findAdjacent(current);
//for (unsigned i = 0; i < adj.size(); ++i){
//    que.push_back(adj[i]);
//}
