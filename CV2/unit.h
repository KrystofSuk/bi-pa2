#ifndef UNIT_H
#define UNIT_H

#include <string>

class Unit{
    private:
        int utok;
        int obrana;
        int zivoty;
        std::string name;
    public:
        Unit();
        Unit(std::string nam);
        Unit(std::string nam, int u, int o, int z);
        std::string GetName();
        int GetUtok();
        int GetObrana();
        int GetZivoty();
        void SetType(std::string c);
        void SetUtok(int c);
        void SetObrana(int c);
        void SetZivoty(int c);
        void Print();
};

#endif