#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;
int * t;
void T(){
    delete[] t;
    int * b = new int(2);
    b[0] = 42;
    t = b;
}

int main () {
    t = new int(4);
    t[0] = 2;
    cout << t[0] << endl;
    T();
    cout << t[0] << endl;
    delete [] t;
    return 0;
}