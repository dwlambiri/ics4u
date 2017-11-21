#include <iostream>
#include <apmatrix.h>
#include <fstream>
#include <string>
#include <apmatrix.h>
#include <ctype.h>
using namespace std;
struct node{
    char character;
    bool visited;
};
struct position{
    int x;
    int y;
};

bool readIn(string filename, int &rows, int &cols, apmatrix<node>& maze){
    fstream file;
    file.open(filename, fstream::in);

    if (!file){
        cerr << "could not open file" << filename;
        return false;
    }
    //gets the dimentions of the maze
    file >> rows;
    file >> cols;
    //rows += 2;
    //cols += 2;
    maze.resize(rows, cols);
    for (int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            //if (r == 0 || c == 0 || r == rows - 1 || c == cols - 1)
               // maze[r][c].character = '#';
            //else
                file >> maze[r][c].character;
        }
    }
    return true;
}

node* findStart(apmatrix<node> maze){
    node* startPoint = nullptr;
    bool foundStart = false;

    for (int r = 0; r < maze.numrows(); r++)
        for (int c = 0; c < maze.numcols(); c++){
            if (toupper(maze[r][c].character == 'S')){
                foundStart = true;
            }
        }
    if (foundStart){
        cout << "found the start" << endl;
        return startPoint;
    }
    cout << "could not find the start";
    return startPoint;
}

//1. if (x,y outside maze) return false
//2. if (x,y is goal) return true
//3. if (x,y not open) return false
//4. mark x,y as part of solution path
//5. if (FindPath(North of x,y) == true) return true
//6. if (FindPath(East of x,y) == true) return true
//7. if (FindPath(South of x,y) == true) return true
//8. if (FindPath(West of x,y) == true) return true
//9. unmark x,y as part of solution path
//10. return false
bool findPath(int x, int y){
}

int main(){
    int numRows;
    int numCols;
    string filename;
    apmatrix<node> maze;
    node* start;
    cout << "please enter name of file" << endl;
    cin >> filename;

    if(!readIn(filename, numRows, numCols, maze))
        return 1;
    start = findStart(maze);


    return 0;
}
