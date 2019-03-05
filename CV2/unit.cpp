#include "unit.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

Unit::Unit(){
    name = "";
    utok = 0;
    obrana = 0;
    zivoty = 0;
}

Unit::Unit(std::string nam){
    SetType(nam);
}

Unit::Unit(std::string nam, int u, int o, int z){
    name = nam;
    utok = u;
    obrana = o;
    zivoty = z;
}

/**
 * @brief Setting unit parameters preset by name
 * 
 * @param c name of unit
 */
void Unit::SetType(std::string c){
    if(c == "pesak"){
        name = c;
        SetUtok(1);
        SetObrana(2);
        SetZivoty(10);
    }
    else if(c == "hrdina"){
        name = c;
        SetUtok(6);
        SetObrana(2);
        SetZivoty(25);
    }
    else if(c == "kopitnik"){
        name = c;
        SetUtok(1);
        SetObrana(3);
        SetZivoty(8);
    }
    else if(c == "rytir"){
        name = c;
        SetUtok(5);
        SetObrana(5);
        SetZivoty(20);
    }
    else if(c == "zenista"){
        name = c;
        SetUtok(0);
        SetObrana(1);
        SetZivoty(15);
    }else{
        std::cout << "Unknown type!" << std::endl;
    }
}

//Setters and getters
void Unit::SetObrana(int c){
    obrana = c;
}
void Unit::SetUtok(int c){
    utok = c;
}
void Unit::SetZivoty(int c){
    zivoty = c;
}

std::string Unit::GetName(){
    return name;
}

int Unit::GetObrana(){
    return obrana;
}
int Unit::GetUtok(){
    return utok;
}
int Unit::GetZivoty(){
    return zivoty;
}

/**
 * @brief Prints Unit info
 * 
 */
void Unit::Print(){    
    std::cout << std::setw(10) << std::left << GetName() << std::setw(10) << std::left << GetUtok() << std::setw(10) << std::left << GetObrana() << std::setw(10) << std::left << GetZivoty() << std::endl;
    return;
}
