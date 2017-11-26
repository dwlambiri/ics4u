#include <iostream>
#include <fstream>
#include <cstdlib>

#include "RassamMaze.cpp"

using namespace std;

struct Coordinates {
    int x;
    int y;
};

bool readIn(apstring filename, apmatrix <char> &mazeinfo) {
    int numCols;
    int numRows;

    ifstream fin(filename.c_str());

    if (!fin) {
        cout << "Unable to open " << filename << endl;
        return false;
    }

    fin >> numRows;
    fin >> numCols;

    mazeinfo.resize(numRows + 2, numCols + 2);

    cout << mazeinfo.numrows() << " " << mazeinfo.numcols() << endl;

    for (int i = 0; i < mazeinfo.numrows(); i++) {
        for (int j = 0; j < mazeinfo.numcols(); j++) {
            if (i == 0 || i == mazeinfo.numrows() - 1)
                mazeinfo[i][j]  = '#';
            else if(j == 0 || j == mazeinfo.numcols() - 1)
                mazeinfo[i][j]  = '#';
            else
                fin >> mazeinfo[i][j] ;
            //cout << mazeinfo[i][j] ;
        }
        //cout << endl;
    }
    return true;
}


Coordinates findStart(apmatrix <char> &mazeinfo) {
    Coordinates startPos;
    bool foundStart = false;

    for (int i = 0; i < mazeinfo.numrows(); i++) {
        for (int j = 0; j < mazeinfo.numcols(); j++) {
            if (mazeinfo[i][j]  == 'S' || mazeinfo[i][j]  == 's') {
                startPos.y = j;
                startPos.x =  i;
                foundStart = true;
                cout << "start position found" << endl;
            }
        }
    }

    if (!foundStart) {
        cout << "start position not found";
    }

    return startPos;
}

bool findPath(int y, int x, apmatrix <char> &mazeinfo) {
    Coordinates position;

    position.y = x;
    position.x = y;
    printMaze(mazeinfo, 0);
     if (position.x <= -1 || position.y <= -1 || position.x >= mazeinfo.numrows() || position.y >= mazeinfo.numcols())
        return false;
    //Checks if it is at the maze goal
    else if (mazeinfo[position.x][position.y]  == 'G') {
        for (int i = 0; i < mazeinfo.numrows(); i++) {
			for (int j = 0; j < mazeinfo.numcols(); j++) {
				if (mazeinfo[i][j] == 'x')
					cout << '.';
				else cout << mazeinfo[i][j] ;
			}

        cout << endl;
    }
        return true;
    }

    //Checks if the maze location is a wall
    else if (mazeinfo[position.x][position.y]  == '#')
        return false;
    //Checks if the location in the path is already marked
    else if (mazeinfo[position.x][position.y]  == '+')
        return false;
    else if (mazeinfo[position.x][position.y]  == 'x')
        return false;

    //Marks the visited path with a + sign
     if(mazeinfo[position.x][position.y]  != 'S')
    	 mazeinfo[position.x][position.y]  = '+';
    //checking for the directions that the path can follow
    if(findPath(position.x-1, position.y, mazeinfo))
        return true;
    //WEST
    if(findPath(position.x, position.y-1, mazeinfo))
        return true;
    //EAST
    if(findPath(position.x, position.y+1, mazeinfo))
        return true;
    //SOUTH
    if(findPath(position.x+1, position.y, mazeinfo))
        return true;

    if (mazeinfo[position.x][position.y]  != 'S')
    	mazeinfo[position.x][position.y]  = 'x';

    return false;
}

int main (int argc, char* argv[]) {
    int counter = 0;
    apstring filename;
    apmatrix <char> mazeinfo(0,0);
    Coordinates startPosition;

    filename = "a.txt";

    //startscreen();

    //gathers maze information from textfile
    readIn(filename, mazeinfo);
    initAllegro(mazeinfo.numcols(), mazeinfo.numrows());
    printMaze(mazeinfo, counter);
    counter++;


    //shows solution or exits program at user's demand
    while (1) {
      if (spacekeyPressed()) {
        //figures out solution
        startPosition = findStart(mazeinfo);
        if(findPath(startPosition.x, startPosition.y, mazeinfo) == false) {
        	printMaze(mazeinfo, counter);
        	apstring err = "Could not find Exit";
        	errorBox(err);
        }
        else printMaze(mazeinfo, counter);
        break;
      }
    }
    al_rest(10.0);

    return 0;
}
