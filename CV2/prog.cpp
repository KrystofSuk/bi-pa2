

#include <algorithm>
#include <functional>
#include "unit.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


/**
 * @brief Method to load units from file
 * 
 * @param unitList list of units to save 
 * @param s size reference
 */
void loadFiles(Unit* & unitList, int& s){
    string name;
    string c1;
    string c2;
    string c3;
    int c1v;
    int c2v;
    int c3v;
    int z;
    int u;
    int o;

    int currentUnit = 0;
    ifstream inFile;
    
    inFile.open("units.txt");
    if (!inFile) {
        cout << "Unable to open file";
        return; 
    }

    while(inFile >> name >> c1 >> c1v >> c2 >> c2v >> c3 >> c3v){   
        if(c1 == "utok")
            u = c1v;
        if(c1 == "obrana")
            o = c1v;
        if(c1 == "zivoty")
            z = c1v;
        if(c2 == "utok")
            u = c2v;
        if(c2 == "obrana")
            o = c2v;
        if(c2 == "zivoty")
            z = c2v;
        if(c3 == "utok")
            u = c3v;
        if(c3 == "obrana")
            o = c3v;
        if(c3 == "zivoty")
            z = c3v;
        unitList[currentUnit] = Unit(name, u, o, z);
        currentUnit++;
    }
    s = currentUnit;
    inFile.close();
}

/**
 * @brief Helper function to switch two units values
 * 
 * @param A first
 * @param B second
 */
void switchUnits(Unit &A, Unit &B){    
    Unit tmp(A.GetName(), A.GetUtok(), A.GetObrana(), A.GetZivoty());
    A.SetType(B.GetName());
    B.SetType(tmp.GetName());
    A.SetObrana(B.GetObrana());
    B.SetObrana(tmp.GetObrana());
    A.SetZivoty(B.GetZivoty());
    B.SetZivoty(tmp.GetZivoty());
    A.SetUtok(B.GetUtok());
    B.SetUtok(tmp.GetUtok());
}

/**
 * @brief Prints list of units alphabeticaly by name
 * 
 * @param unitList list of units
 * @param size size of list
 */
void printUnitsAlp(Unit* unitList, int size){
    cout << std::setw(10) << left << "name" << std::setw(10) << std::left << "utok" << std::setw(10) << std::left << "obrana" << std::setw(10) << std::left << "zivoty" << std::endl;
    cout << setw(40) << setfill('-') << "" << endl << setfill(' ');
    

    for(int z = 0; (z) < size-1;z++){
        for(int i = 0; (i) < size-1;i++){
            if(unitList[i].GetName() > unitList[i+1].GetName()){
                switchUnits(unitList[i], unitList[i+1]);
            }
        }
    }
                
    for(int i = 0; i < size;i++)
        unitList[i].Print();
    
    cout << endl;
}

/**
 * @brief Prints sorted units
 * 
 * @param unitList list of units
 * @param size size of list
 * @param col by which column is print sorted starting from 0
 */
void printUnitsSort(Unit* unitList, int size, int col){
    cout << std::setw(10) << left << "name" << std::setw(10) << std::left << "utok" << std::setw(10) << std::left << "obrana" << std::setw(10) << std::left << "zivoty" << std::endl;
    cout << setw(40) << setfill('-') << "" << endl << setfill(' ');
    
    switch(col){
        case 0:
            for(int z = 0; (z) < size-1;z++){
                for(int i = 0; (i) < size-1;i++){
                    if(unitList[i].GetName() > unitList[i+1].GetName()){
                        switchUnits(unitList[i], unitList[i+1]);
                    }
                }
            }
            break;
        case 1:
            for(int z = 0; (z) < size-1;z++){
                for(int i = 0; (i) < size-1;i++){
                    if(unitList[i].GetUtok() < unitList[i+1].GetUtok()){
                        switchUnits(unitList[i], unitList[i+1]);
                    }
                }
            }
            break;
        case 2:
            for(int z = 0; (z) < size-1;z++){
                for(int i = 0; (i) < size-1;i++){
                    if(unitList[i].GetObrana() < unitList[i+1].GetObrana()){
                        switchUnits(unitList[i], unitList[i+1]);
                    }
                }
            }
            break;
        case 3:
            for(int z = 0; (z) < size-1;z++){
                for(int i = 0; (i) < size-1;i++){
                    if(unitList[i].GetZivoty() < unitList[i+1].GetZivoty()){
                        switchUnits(unitList[i], unitList[i+1]);
                    }
                }
            }
            break;
    }
                
    for(int i = 0; i < size;i++)
        unitList[i].Print();
    cout << endl;
}

/**
 * @brief Fight function of two units
 * 
 * @param A First Unit
 * @param B Second Unit
 */
void fight(Unit &A, Unit &B){
    while(A.GetZivoty() > 0 && B.GetZivoty() > 0){
        cout << A.GetName() << " " << A.GetZivoty() << "-" << "(" << B.GetUtok() << "-" << A.GetObrana() << ") = ";
        int tmpO = A.GetObrana();
        int tmpU = B.GetUtok();
        int tmpZ = A.GetZivoty();
        int nw = tmpZ - (tmpU - tmpO);

        A.SetZivoty(nw);
        cout << A.GetZivoty() << endl;

        tmpO = B.GetObrana();
        tmpU = A.GetUtok();
        tmpZ = B.GetZivoty();
        nw = tmpZ - (tmpU - tmpO);

        cout << B.GetName() << " " << B.GetZivoty() << "-" << "(" << A.GetUtok() << "-" << B.GetObrana() << ") = ";
        B.SetZivoty(nw);
        cout << B.GetZivoty() << endl;
    }
}

int main () {

    Unit *unitList = new Unit[100];
    int size = 0;
    loadFiles(unitList, size);
    printUnitsAlp(unitList, size); 
    printUnitsSort(unitList, size, 1);
    Unit * A = new Unit();
    A->SetType("pesak");
    //A->SetName("bojovnik");
    A->Print();
    Unit * B = new Unit("rytir");
    B->Print();
    fight(A[0], B[0]);  

    delete[] unitList;  
    delete A;  
    delete B;  
    
    return 0;
}