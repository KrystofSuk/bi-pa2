#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Block{
    private:
        int _t = 0;
        int _x = 0;
        int _y = 0;
    public:
        Block(){
            _t = 0;
            _x = 0;
            _y = 0;
        };

        /**
         * @brief Construct a new Block object
         * 
         * @param x 
         * @param y 
         * @param v value
         */
        Block(int x, int y, int v){
            _x = x;
            _y = y;
            _t = v;
        };

        /**
         * @brief Setting block value
         * 
         * @param t value
         */
        void Set(int t){
            _t = t;
        }

        int GetVal() const { return  _t; };
        int GetX()const{ return _x; };
        int GetY()const{ return _y; }; 
};

class World{
    private:
        Block ** _arr;
        int _n = 1000;
        int _cnt = 0;
        const int _y = 10;
        const int _x = 10;
        
    public:
        World(int n) {
            _n = n;
            _arr = new Block*[_y];
            for(int i = 0; i < _y; i++){
                _arr[i] = new Block[_x];
                for(int t = 0; t < _x; t++){
                    _arr[i][t] = Block();
                }
            }
        };

        /**
         * @brief Setting blocks to 0;
         * 
         * @param x 
         * @param y 
         */
        void Set(int x, int y){
            _arr[y][x].Set(0);
        };

        /**
         * @brief Construct a new World object
         * 
         * @param p2 
         */
        World(const World &p2){
            _n = p2.GetN();
            _cnt = p2._cnt;
            _arr = new Block*[_y];
            for(int i = 0; i < _y; i++){
                _arr[i] = new Block[_x];
                for(int t = 0; t < _x; t++){
                    _arr[i][t] = Block();
                }
            }

            for(int i = 0; i < _y; i++){
                for(int t = 0; t < _x; t++){
                    _arr[i][t].Set(p2._arr[i][t].GetVal());
                }
            }
        }; 

        /**
         * @brief Adds block b
         * 
         * @param b new block
         * @return World& 
         */
        World & operator+=(const Block & b){
            if(_cnt >= _n)
                return *this;
            this->_arr[b.GetY()][b.GetX()].Set(b.GetVal());
            _cnt ++;
            return *this;
        };

        /**
         * @brief Removes block b
         * 
         * @param b removable block
         * @return World& 
         */
        World & operator-=(const Block & b){
            if(_cnt <= 0)
                return *this;
            if(this->_arr[b.GetY()][b.GetX()].GetVal() == b.GetVal()){
                this->_arr[b.GetY()][b.GetX()].Set(0);
                _cnt --;
            }
                
            return *this;
        };

        /**
         * @brief Prints blocks
         * 
         * @param os 
         * @param obj 
         * @return ostream& 
         */
        friend ostream & operator<<(ostream& os, const World& obj)
        {
            for(int i = 0; i < obj._y; i++){
                for(int t = 0; t < obj._x; t++){
                    os << obj._arr[i][t].GetVal();
                }
                os << endl;
            }
            
            return os << endl;
        };

        World & operator=(const World &p2){
            
            _n = p2.GetN();
            _cnt = p2._cnt;
            _arr = new Block*[_y];
            for(int i = 0; i < _y; i++){
                _arr[i] = new Block[_x];
                for(int t = 0; t < _x; t++){
                    _arr[i][t] = Block();
                }
            }

            for(int i = 0; i < _y; i++){
                for(int t = 0; t < _x; t++){
                    _arr[i][t].Set(p2._arr[i][t].GetVal());
                }
            }

            return *this;
        }
        
        int GetN() const { return _n; };

        ~World(){
            for(int i = 0; i < _y; i++){
                delete[] _arr[i];
            }
            delete[] _arr;
        };
};

int main ( int argc, char* argv[] ) {
    World drk(3);
    Block b(2, 3, 3);
    Block c(5, 3, 1);
    Block d(7, 1, 9);
    Block e(1, 1, 5);
    drk += b;
    drk += c;
    drk += d;
    drk += e;
    cout << drk;
    
    World light(drk);
    light -= b;
    cout << light;
    
    World cpy(3);
    cpy = light;
    cout << cpy;
    
    return 0;
}