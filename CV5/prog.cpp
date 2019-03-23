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
            _w = 0;
            _h = 0;
        };

        int _h = 0;
        int _w = 0;
        /**
         * @brief Construct a new Block object
         * 
         * @param x 
         * @param y 
         * @param v value
         */
        Block(int x, int y, int h, int w){
            _x = x;
            _y = y;
            _h = h;
            _w = w;
            _t = 1;
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
            
            for(int i = 0; i < b._h; i++)
                for(int t = 0; t < b._w; t++)
                    this->_arr[b.GetY()+i][b.GetX()+t].Set(b.GetVal());
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
                
            bool d = false;
            for(int i = 0; i < b._h; i++){
                for(int t = 0; t < b._w; t++){
                    if(this->_arr[b.GetY() + i][b.GetX() + t].GetVal() == b.GetVal()){
                        this->_arr[b.GetY() + i][b.GetX() + t].Set(0);
                        d = true;
                    }
                }
            }
            if(d)
                _cnt --;
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
            if(this == &p2)
                return *this;

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
    Block b(1, 1, 2 ,2);
    Block c(5, 3, 1,1);
    Block d(7, 1, 9,3);
    Block e(1, 1, 5,1);
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