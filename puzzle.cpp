#include "puzzle.h"

/* ~VERTEX~ */
//default constructor ✓
Vertex::Vertex(){ 
    cout << "error in making vertex, aborting program" << endl;
    exit;
}

//Vertex constructor. maybe done.
Vertex::Vertex(const int& depth, const string& matrixString){
    this->depth = depth;
    //maybe do that whole new thing for the vector
    find_adjacent(this->neighbors, matrixString);//call find_adjacent and set the adjacencies for the vertex
    
}

//Vertex destructor. VERY important for space. (NOT DONE!)~~~~~~~~~~~~~~~~ 🛇
Vertex::~Vertex(){
    
}



/* ~PUZZLEGRAPH~ */
//overloaded puzzleGraph constructor. Takes the initialMatrix string and add that to the map as a vertex. ✓
puzzleGraph::puzzleGraph(const string& initialMatrix){
    unordered_map<string, Vertex>* adjList = new unordered_map<string, Vertex>; //use unordered_map of Vertex pointers 
    Vertex * firstVertex = new Vertex(0, initialMatrix); //make first Vertex and get a pointer to it
    adjList->emplace(initialMatrix, firstVertex); //add the first matrix as a vertex to the map as a pointer.
    this->shortestDepth = 2147483647; //max size for int
}

//puzzleGraph destructor. Important for space. ✓
puzzleGraph::~puzzleGraph(){
    for (auto it = adjList->begin(); it != adjList->end(); it++){ //iterate through map and call delete Vertex for all pointers in the map
        delete it->second;
    }
    adjList->clear(); //idk why i do this but im paranoid and put it here just in case
    delete adjList;
}

//adds a vertex to the graph. Takes the string matrix and depth, makes a new vector, then adds it to the unordered_map. ✓
void puzzleGraph::addVertex(const string& newMatrix, const int& depth){ //AKA addEdge();
    Vertex * theVertexWeAreAboutToAdd = new Vertex(depth, newMatrix); //make a pointer to a new vertext
    adjList->emplace(newMatrix, theVertexWeAreAboutToAdd); //add the pointer to the vertex to the map with the key equal to the matrix string
}



// Read an input file and store each integer within an array ✓
void puzzleGraph::read_input()
{
    std::ifstream file{"input.txt"};
    if (!file.is_open()){
        cout << "Couldn't open input.txt for reading. Aborting program" << endl;
        exit;
    }
    if (file)
    {
        char ch, i = 0;
        while (file >> ch)
        {
            if (ch != '\n' && ch != ' ')
            {
                //matrix[i] = ch;
                this->initialMatrix += ch;
                
                ++i;
            }
        }
    }
    //cout << "matrix:" << matrix << endl;
    //matrix1 = matrix;
    //cout << "matrix1:" << matrix1 << endl; //debug stuff
}

// Get the index value of the zero tile from a matrix ✓
int get_zero_pos(const string& matrix)
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        if (matrix[i] == '0')
        {
            return i;
        }
    }
    cout << "No zero found in input matrix. Aborting program" << endl;
    exit; //return -1;
}

// Find and enqueue adjacent states. adjStates is a pass by reference vector you want the results of the function to be in. 
//matrix is the matrix you want to find the adjacent states of. ✓
void find_adjacent(vector<string>& adjStates, const string& matrix)
{
    vector<string>().swap(adjStates);//a cool way to clear the vector without deallocating it
    int pos = get_zero_pos(matrix);
    int row = pos / 3;
    int col = pos % 3;
    
    //cout << "matrix:" << matrix << endl; test

    if (row != 0)  // Try to move the zero tile up
    {
        string slide = matrix;
        swap(slide[pos], slide[pos-3]);
        adjStates.push_back(slide);
    }

    if (row != 2)  // Try to move the zero tile down
    {
        string slide = matrix;
        swap(slide[pos], slide[pos+3]);
        adjStates.push_back(slide);
    }

    if (col != 0)  // Try to move the zero tile left
    {
        string slide = matrix;
        swap(slide[pos], slide[pos-1]);
        adjStates.push_back(slide);
    }

    if (col != 2)  // Try to move the zero tile right
    {
        string slide = matrix;
        swap(slide[pos], slide[pos+1]);
        adjStates.push_back(slide);
    }

}

