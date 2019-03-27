
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

#include "inventory.h"

using namespace std;


int main ( int argc, char* argv[] ) {  
    Inventory i1;

    Item a (AGI, "Agi Bootz");
    Item b (AGI, "Agi Coat");
    Item c (STR, "BIG Sword");
    Item d (LUC, "Lucky Cube");
    Item e ("Life");
    Item f (AGI, "Lucky Cube");
    Item g (LUC, "Lucky Cube");
    Item h (LUC, "Lucky");

    i1 += a;
    i1 += b;
    i1 += c;
    i1 += d;
    cout << i1 << endl;

    i1 += e;    
    cout << i1 << endl;

    i1 -= f;
    i1 -= g;
    i1 -= h;
    cout << i1 << endl;

cout << t<< endl;
    for(int i = 0; i < 6; i++)
        i1 += c;
    cout << i1 << endl;

    return 0;
}