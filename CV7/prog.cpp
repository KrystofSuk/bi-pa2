#include <iostream>
#include <string>
#include <iomanip>
using namespace std;



struct Fighter{
    public:
        enum Color{ White, Red};
        Fighter(Color col, string nam, int hp){
            _col = col;
            _name = nam;
            _hp = hp;
        }
        virtual void Attack(Fighter & victim) const = 0;
        virtual void GetHit(int damage) = 0;
        virtual void Print() const = 0;
        bool IsAlive() const{
            return _hp > 0 ? true : false;
        }
        friend ostream & operator<<(ostream& os, const Fighter& obj)
        {
            string col = "";
            if(obj._col == White){
                col = "\033[0;37m";
            }
            if(obj._col == Red){
                col = "\033[0;31m";
            }
            os << col << obj._name <<"\033[0;37m" << ": " << obj._hp << " [";    
            obj.Print();   
            os << "]";
            return os;
        };
    protected:
        Color _col;
        string _name;
        int _hp;
};

class Knight : public Fighter{
    private:
        int _sword;
        int _fists;
        int _half;
        int _shield;
    public:
        Knight(Fighter::Color col, string nam, int hp, int sword, int fists, int shield) : Fighter(col, nam, hp), _shield(shield){
            _half = hp / 2;
            _sword = sword;
            _fists = fists;
        }    
        void GetHit(int damage){
            damage -= _shield;
            if(damage < 0){
                damage = 0;
            }
            _hp -= damage;
            if(_hp < 0)
                _hp = 0;
            if(_shield > 0)
                _shield--;
        }
        void Attack(Fighter & victim) const{
            int dmg = 0;
            if(IsAlive()){
                if(_hp >= _half){
                    dmg = _sword;
                    dmg += _fists;
                }
                else{
                    dmg = _fists;
                }
            }
            if(dmg < 0){
                dmg = 0;
            }
            victim.GetHit(dmg);
        }
        void Print() const{
            cout << "K";
        }
};

class Archer : public Fighter{
    private:
        int _bow;
    public:
        Archer(Fighter::Color col, string nam, int hp, int bow) : Fighter(col, nam, hp*2){
            _bow = bow;
        }
        void Attack(Fighter & victim) const{
            int dmg = 0;
            if(IsAlive()){
                dmg = _bow;
            }
            if(dmg < 0){
                dmg = 0;
            }
            victim.GetHit(dmg);
        }  
        void GetHit(int damage){
            if(damage < 0){
                damage = 0;
            }
            _hp -= damage;
            if(_hp < 0)
                _hp = 0;
        }
        void Print() const{
            cout << "A";
        }
};

int main ( int argc, char* argv[] ) {
    Fighter * kn = new Knight (Fighter::White, "Knight White", 10, 3, 1, 3);
    Fighter * kn2 = new Knight (Fighter::Red, "Knight Red", 14, 2, 1, 4);
    cout << *kn << endl;      
    kn2 -> Attack(*kn);
    cout << *kn << endl;      
    kn2 -> Attack(*kn);
    cout << *kn << endl;      
    kn2 -> Attack(*kn);
    cout << *kn << endl; 
    cout << *kn2 << endl;
    Fighter * ar = new Archer(Fighter::Red, "Archer", 8, 4);
    cout << *ar << endl; 
    cout << *kn << endl; 
    kn -> Attack(*ar);  
    cout << *ar << endl; 
    ar -> Attack(*kn); 
    kn -> Attack(*ar);    
    cout << *kn << endl;  
    cout << *ar << endl; 
    return 0;
}