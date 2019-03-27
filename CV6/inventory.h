#ifndef INVENTORY_H
#define INVENTORY_H

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
#include <algorithm>
#include <functional>
#include <memory>
#include <map>


using namespace std;

enum Stat {NaN, AGI, VIT, STR, DEX, LUC, INT};

class Item{
    public:
        Item(Stat stat, string name){
            _myStat = stat;
            _name = name;
        };    
        Item(string name){
            _myStat = NaN;
            _name = name;
        };
        friend ostream & operator<<(ostream& os, const Item& obj)
        {
            os << "Item: " << obj._name << " : ";
            switch (obj._myStat)
            {
                case AGI:
                    os << "AGI";
                    break;
                case VIT:
                    os << "VIT";
                    break;
                case STR:
                    os << "STR";
                    break;
                case DEX:
                    os << "DEX";
                    break;
                case LUC:
                    os << "LUC";
                    break;
                case INT:
                    os << "INT";
                    break;            
                default:
                    os << "NaN";
                    break;
            }
            return os;
        };


        friend bool operator==(const Item& l, const Item& r)
        {
            return (l._name == r._name && l._myStat == r._myStat);
        };

        friend bool operator!=(const Item& l, const Item& r)
        {
            return !(l == r);
        };

        friend bool operator<(const Item& l, const Item& r)
        {
            if(l._name == r._name)
                return (l._myStat < r._myStat);
            return (l._name < r._name);
        };

        friend bool operator>(const Item& l, const Item& r)
        {
            if(l._name == r._name)
                return (l._myStat > r._myStat);
            return (l._name > r._name);
        };
    private:
        Stat _myStat;
        string  _name;
};






class Inventory{
    private:
    int t =0;
        map<Item, int> _items;
        void AddItem(const Item & item){
            
            auto it = _items.find(item);
            if(it != _items.end()){
                it -> second ++;
            }
            else
                _items.insert(make_pair(item, 1));
        };

        int GetIndexOfElement(const Item & item){
            return -1;
        };
    public:
        const int Get() const{
            return t;
        };
        Inventory & operator+=(const Item & item){
            AddItem(item);
            return *this;
        };
        Inventory & operator-=(const Item & item){
            
            auto it = _items.find(item);
            if(it != _items.end()){
                cout << it->second << endl;
                it -> second --;
                cout << it->second << endl;
                if(it -> second == 0)
                    _items.erase(it);
            }
            else
                cerr << "I dont have this item" << endl;
            return *this;
        };
        friend ostream & operator<<(ostream& os, const Inventory& obj)
        {
            os << "----------------" <<endl << "I have in inventory: " << endl;
            for (auto it=obj._items.begin(); it!=obj._items.end(); ++it)
                std::cout << it->first << " - " << it->second << endl;

            os << "----------------" ;
            return os;
        };
};

#endif