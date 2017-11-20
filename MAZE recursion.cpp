#include <iostream>
#include <apmatrix.h>
#include <fstream>
#include <cstdlib>

#define NORTH maze[position.y-1][position.x]
#define SOUTH maze[position.y+1][position.x]
#define EAST maze[position.y][position.x+1]
#define WEST maze[position.y][position.x-1]

using namespace std;

#include "justinAllegro.h"

Coordinate findStart(apmatrix<mazePart> &maze){
    Coordinate toReturn;
    //flag
    toReturn.x = -1;
    bool foundStart = false;

    for (int y = 0; y < maze.numrows(); y++)
        for (int x = 0; x < maze.numcols(); x++){
            if (maze[y][x].character == 's' || maze[y][x].character == 'S'){
                toReturn.x = x;
                toReturn.y = y;
                foundStart = true;
            }
        }
    if (foundStart){
        cout << "found the start" << endl;
        return toReturn;
    }
    cout << "could not find the start";
    return toReturn;
}
void readIn(apmatrix<mazePart> &maze, fstream &file){
    for (int y = 0; y < maze.numrows(); y++)
        for (int x = 0; x < maze.numcols(); x++)
            //adds walls to the edges of the maze
            if (y == 0 || y == maze.numrows()-1)
                maze[y][x].character = '#';
            else if(x == 0 || x == maze.numcols()-1)
                maze[y][x].character = '#';
            else
                file >> maze[y][x].character;

}
string findPath(apmatrix<mazePart> &maze, Coordinate position){
    maze[position.y][position.x].visited = true;

    if (maze[position.y][position.x].character == 'G')
        return " ";

    if (SOUTH.character != '#' && !SOUTH.visited){
        position.y++;
        string temp = findPath(maze, position);
        if (temp != "")
            return "S" + temp;
        position.y--;
    }
    if (NORTH.character != '#' && !NORTH.visited){
        position.y--;
        string temp = findPath(maze, position);
        if (temp != "")
            return "N" + temp;
        position.y++;
    }
    if (EAST.character != '#' && !EAST.visited){
        position.x++;
        string temp = findPath(maze, position);
        if (temp != "")
            return "E" + temp;
        position.x--;
    }
    if (WEST.character != '#' && !WEST.visited){
        position.x--;
        string temp = findPath(maze, position);
        if (temp != "")
            return "W" + temp;
        position.x++;
    }

    return "";
}
void drawPath(apmatrix<mazePart> &maze, string path, Coordinate position){
    //checks which direction to go in
    switch(path[0]){
        case 'N':
            position.y--;
            break;
        case 'S':
            position.y++;
            break;
        case 'E':
            position.x++;
            break;
        case 'W':
            position.x--;
            break;
    }
    //changes the point it is at to a + sign
    if (maze[position.y][position.x].character != 'S' && maze[position.y][position.x].character != 'G'){
        maze[position.y][position.x].character = '+';
    }

    //resizes the string and calls the function again
    if (path.size() > 0){
        path = path.substr(1, path.size());
        drawPath(maze, path, position);
    }
}
int main(){
    fstream file;
    string fileName;
    int numRows;
    int numCols;
    Coordinate start;

    cout << "please enter name of file" << endl;
    cin >> fileName;
    //open file
    file.open(fileName, fstream::in);
    //check if file opened
    if (!file){
        cerr << "could not open file";
        return 0;
    }
    //gets the dimentions of the maze
    file >> numRows;
    file >> numCols;

    //matrix for maze. Two x two elements larger to create a border
    apmatrix<mazePart> maze(numRows+2, numCols+2);

    //reads maze into matrix
    readIn(maze,file);

    start = findStart(maze);
    if (start.x == -1)
        return 0;

    drawMaze(maze);
    //changes the matrix to include a path from the start to end
    drawPath(maze, findPath(maze, start), start);
    //draws maze using allegro
    drawMaze(maze);

    file.close();
}
