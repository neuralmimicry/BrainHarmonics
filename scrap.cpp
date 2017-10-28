#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
/*  Purpose: testing out random shit 
 *   
 */
int main () {
    ifstream file; 
    file.open("../simple.vert");
    if(!file) {
        std::cout << "no dice, file not found " << std::endl;
    }
    string line;
    while(getline(file,line)) {
        std::cout << "line is " << line << std::endl;
    }
    return 0;
}

   


