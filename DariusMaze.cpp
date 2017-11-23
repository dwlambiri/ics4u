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
    int r;
    int c;
};

bool readIn(string filename, int &rows, int &cols, apmatrix<char>& maze){
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
                file >> maze[r][c];
        }
    }
    return true;
}

position findStart(apmatrix<char>& maze){
    position startPoint;
    startPoint.r = -1;
    startPoint.c = -1;
    bool foundStart = false;

    for (int r = 0; r < maze.numrows(); r++)
        for (int c = 0; c < maze.numcols(); c++){
            if (toupper(maze[r][c]) == 'S'){
                foundStart = true;
                startPoint.r = r;
                startPoint.c = c;
            }
        }
    if (foundStart){
        cout << "Start is found " << startPoint.r << " " << startPoint.c << endl;
        return startPoint;
    }
    cout << "Start Not Found";
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
    //mark it with a '.'
//10. return false
bool findPath(int curR, int curC, apmatrix<char>& maze){
    //Check for exceeding the bounds of the maze
    if (curR <= -1 || curC <= -1 || curR >= maze.numrows() || curC >= maze.numcols())
        return false;
    //Checks if it is at the maze exit
    else if (toupper(maze[curR][curC]) == 'G')
        return true;
    //Checks if the maze location is a wall
    else if (maze[curR][curC] == '#')
        return false;
    //Checks if the location in the path is already marked
    else if (maze[curR][curC] == '+')
        return false;

    //Marks the path as visited with a + sign
    maze[curR][curC] = '+';
    //NORTH
    if(findPath(curR-1, curC, maze))
        return true;
    //WEST
    if(findPath(curR, curC-1, maze))
        return true;
    //EAST
    if(findPath(curR, curC+1, maze))
        return true;
    //SOUTH
    if(findPath(curR+1, curC, maze))
        return true;

    maze[curR][curC] = '.';
    return false;
}

printmaze(apmatrix<char> &maze){
    //cout << maze.numcols() << endl;
    //cout << maze.numrows() << endl;
    for (int i = 0; i < maze.numrows(); i++){
        for (int j = 0; j < maze.numcols(); j++)
            cout << maze[i][j];
        cout << endl;
    }
}
int main(){
    int numRows;
    int numCols;
    string filename;
    apmatrix<char> maze;
    position start;
    cout << "please enter name of file" << endl;
    cin >> filename;

    if(!readIn(filename, numRows, numCols, maze))
        return 1;
    start = findStart(maze);
    printmaze(maze);
    cout << endl << "Now Solving Maze" << endl << endl;
    findPath(start.r, start.c, maze);
    maze[start.r][start.c] = 'S';
    printmaze(maze);
    return 0;
}
