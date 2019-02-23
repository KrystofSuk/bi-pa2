#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;


int main () {
    /*

    Z.1

    cout << "Vstup:" << endl;
    int x = 0;
    int tmp = 0;
    
    if(!(cin >> x)){
        cout << "ERR" << endl;
        return 0;
    }
    
    tmp = x;
    int **arr = new int*[tmp/2];

    for(int i = 0; i < x/2 + x%2; ++i) {
        arr[i] = new int[tmp];
        for(int t = 0; t < tmp; t++){
            arr[i][t] = t;
        }
        tmp /= 2;
    }

    cout << "Vystup:" << endl;
    tmp = x;

    for(int t = 0; t < x/2+ x%2; t++){
        cout << arr[t][0];
        for(int y = 1; y < tmp; y++)
            cout << "," << arr[t][y];
        tmp /= 2;
        cout << endl;
    }

    */

    cout << "Vstup:" << endl;
    string completed;
    string line;

    
    while(cin >> line){
        
        if(cin.eof())
            break;

        completed.append(line + "\n");
    }   


    cout << "Vystup:" << endl;
    ofstream os; 
    os.open("file.txt");
    os << completed;
    os.close();
    cout << completed;
    return 0;
}