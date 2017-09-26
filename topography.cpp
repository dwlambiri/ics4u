//includes
#include <iostream>
#include <fstream>

using namespace std;

const char[] fileName_c = "Colorado_480x480.dat"

int main() {
    apmatrix<int> mountainSize(480, 480, 99999);

	ifstream file;

	file.open(fileName_c);
	// todo: check if file opens successfully
	int in[100];
	int i=0;

	for (int y = 0; y < 480; y++){
        for (int x = 0; x < 480; x++){
            file >>  mountainSize[y][x];
            cout << mountainSize[y][x] << " ";
        }
        cout << '\n';
    }

	fin.close();

	return 0;
}
