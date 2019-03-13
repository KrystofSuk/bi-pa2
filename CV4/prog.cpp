#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class BNumber{
    private:
        int _r;
        int _m;
        int _d;
        int _n;
        int _c;
    public:
        friend bool operator<(const BNumber& l, const BNumber& r)
        {
            if( l.GetDate() < r.GetDate())
                return true;
            if( l._n < r._n)
                return true;
            if( l._c < r._c)
                return true;
            return false;
        }
        friend bool operator>(const BNumber& l, const BNumber& r)
        {
            if( l.GetDate() > r.GetDate())
                return true;
            if( l._n > r._n)
                return true;
            if( l._c > r._c)
                return true;
            return false;
        }
        friend bool operator==(const BNumber& l, const BNumber& r)
        {
            if( l._r == l._r && l._m == l._m && l._d == l._d && l._n == r._n && l._c == r._c)
                return true;
            return false;
        }
        BNumber() {
            _r = 0;
            _m = 0;
            _d = 0;
            _n = 0;
            _c = 0;
        }
        BNumber(int r, int m, int d, int n, int c){
            if(r > 99 || r < 0){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;
            }
            else if((m < 1 || m > 12)&&(m < 71 || m > 82) && (m < 21 || m > 32)&&(m < 51 || m > 62)){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;   
            }
            else if(d < 0 || d > 31){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;
            }
            else if(n < 0 || n > 999 || c < 0 || c > 9){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;
            }
            else{  
                int t = (r/10) + (m/10) + (d/10) + (n/100) + (n % 100);
                int t2 = (r%10) + (m%10) + (d%10) + (n/10) + (c);
                cout << t << t2 << endl;
                if(t - t2 != 0){
                    _r = 0;
                    _m = 0;
                    _d = 0;
                    _n = 0;
                    _c = 0;
                }else{
                    _r = r;
                    _m = m;
                    _d = d;
                    _n = n;
                    _c = c;
                }

            }
        }
        void Set(int r, int m, int d, int n, int c){
            if(r > 99 || r < 0){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;
            }
            else if((m < 1 || m > 12)&&(m < 71 || m > 82) && (m < 21 || m > 32)&&(m < 51 || m > 62)){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;   
            }
            else if(d < 0 || d > 31){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;
            }
            else if(n < 0 || n > 999 || c < 0 || c > 9){
                _r = 0;
                _m = 0;
                _d = 0;
                _n = 0;
                _c = 0;
            }
            else{  
                int t = (r/10) + (m/10) + (d/10) + (n/100) + (n % 100);
                int t2 = (r%10) + (m%10) + (d%10) + (n/10) + (c);
                cout << t << t2 << endl;
                if(t - t2 != 0){
                    _r = 0;
                    _m = 0;
                    _d = 0;
                    _n = 0;
                    _c = 0;
                }else{
                    _r = r;
                    _m = m;
                    _d = d;
                    _n = n;
                    _c = c;
                }

            }
        }
        int GetGender() const{
            if((_m >= 1 && _m <= 12) || (_m >= 21 && _m <= 32)){
                return 1;  
            }
            if((_m >= 71 && _m <= 82) || (_m >= 51 && _m <= 62)){
                return 2;  
            }
            return 0;
        }
        int GetDate() const{
            int m = 0;
            if((_m >= 1 && _m <= 12))
                m = _m;
            if((_m >= 21 && _m <= 32)){
                m = _m - 20;  
            }
            if((_m >= 71 && _m <= 82)){
                m = _m - 70;  
            }
            if( (_m >= 51 && _m <= 62))
                m = _m - 50;  
            return _r * 10000 + m * 100 + _d;
        }
        friend std::ostream& operator<<(std::ostream& os, const BNumber& obj)
        {
            
            return os <<  obj._r <<  obj._m  <<  obj._d  <<  obj._n  <<  obj._c;
        }
        friend std::istream& operator>>(std::istream& is, BNumber& obj)
        {
            // read obj from stream
            return is >> obj. _r >>  obj._m >>  obj._d >>  obj._n >>  obj._c;
        }
        void Print() const{
            cout << setw(2) << setfill('0') << _r << setw(2) << setfill('0') << _m << setw(2) << setfill('0') << _d << "/" << setw(3) << setfill('0') << _n  << setw(1) << setfill('0') << _c;
            return;
        }
};

class Person{
    private:
        string _nameF;
        string _nameL;
        BNumber _bNum;
    public:
        Person() {
            _nameF = "";
            _nameL = "";
            _bNum = BNumber();
        }
        Person(string f, string l, int r, int m, int d, int n, int c) {
            _nameF = f;
            _nameL = l;
            _bNum = BNumber(r, m, d, n, c);
        }
        void Set(string f, string l, int r, int m, int d, int n, int c){
            _nameF = f;
            _nameL = l;
            _bNum.Set(r, m, d, n, c);
        }
        void Print() const{
            cout << _nameF << " " << _nameL << " ";
            _bNum.Print();
            cout << endl;
            return;
        }
        int GetGender() const{
            return _bNum.GetGender();
        }
        int GetDate() const{
            return _bNum.GetDate();
        }
        friend bool operator<(const Person& l, const Person& r)
        {
            if( l._nameF < r._nameF)
                return true;
            if( l._nameL < r._nameL)
                return true;
            if( l._bNum < r._bNum)
                return true;
            return false;
        }
        friend bool operator>(const Person& l, const Person& r)
        {
            if( l._nameF > r._nameF)
                return true;
            if( l._nameL > r._nameL)
                return true;
            if( l._bNum > r._bNum)
                return true;
            return false;
        }
        friend bool operator==(const Person& l, const Person& r)
        {
            if( l._nameF == r._nameF && l._nameL == r._nameL &&  l._bNum == r._bNum)
                return true;
            return false;
        }
        friend std::ostream& operator<<(std::ostream& os, const Person& obj)
        {
            
            return os << obj._nameF << "/" << obj._nameL << "/" << obj._bNum;
        }
        friend std::istream& operator>>(std::istream& is, Person& obj)
        {
            // read obj from stream
            return is >> obj._nameF >> obj._nameL >> obj._bNum;
        }
};

int main ( int argc, char* argv[] ) {
    Person a = Person("Dolor", "Ip", 0, 53, 20, 2, 0);
    Person b = Person("Dolor", "Ipsum", 1, 0, 1, 2, 0);
    Person c = Person("Dolor", "Ipsum", 1, 1, 33, 2, 0);
    Person d = Person("Dolor", "Ipsum", 1, 1, 1, -4, 0);
    Person e = Person("Dolor", "Ipsum", 1, 1, 1, 2000, 0);
    Person l = Person("Lorem", "Ipsum", 74, 4, 4, 5, 0);
    Person z = Person("Lorem", "Ipsum", 74, 54, 4, 5, 5);
    Person z2 = Person("Lorem", "Ipsum", 74, 54, 4, 5, 5);
    a.Print();
    b.Print();
    c.Print();
    d.Print();
    e.Print();
    l.Print();
    z.Print();
    cout << l.GetGender() << endl;
    cout << z.GetGender() << endl;
    cout << l.GetDate() << endl;
    cout << z.GetDate() << endl;
    cout << (l < z) << endl;
    cout << (l > z) << endl;
    cout << (z == l) << endl;
    cout << (z == z2) << endl;
    cout << z << endl;
    cin >> l;
    cout << l;
    
    return 0;
}