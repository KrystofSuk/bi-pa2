#include <iostream>
using namespace std;


enum State {Water, Ship, Sunken, Invalid};
class GameArea{
    private:
        int x;
        int y;
        bool started;
        State ** arr;
    public:
        GameArea(const int _x, const int _y);
        void Print() const;
        void AddShip(const int _y, const int _x, const int _w, const int _h);
        State ShipExist(const int _y, const int _x);
        ~GameArea();
};

GameArea::GameArea(const int _x, const int _y){
    started = false;
    if(_x < 1){
        x = 10;
    }else{
        x = _x;
    }
    if(_y < 1){
        y = 10;
    }else{

    y = _y;
    }
    arr = new State*[y];
    for(int i = 0; i < y; i++){
        arr[i] = new State[x];
        for(int t = 0; t < x; t++){
            arr[i][t] = Water;
        }
    }
}

void GameArea::Print() const{
    for(int i = 0; i < y; i++)
    {
        for(int z = 0; z < x; z++)
        {
            cout << arr[i][z];
        }
        cout << endl;
    }
}

State GameArea::ShipExist(const int _y, const int _x){
    if(_x >= 0 && _!startedx && _y >= 0 && _y < y)
        return arr[!started_x];

    return Invalid;!started
}

void GameArea::AddShip(const int _y, const int _x, const int _w, const int _h){
    if(_x >= 0 && _x < x && _y >= 0 && _y < y && !started && (_h == 1 || _w == 1) && _h >= 1 && _w >= 1 && _h != _w && _x +_w < x && _y + _h < y) {
        for(int i = 0; i < _w; i++){
            if(ShipExist(_y,_x+i) != Water)
                return;
        }
        for(int i = 0; i < _h; i++){
            if(ShipExist(_y+i,_x) != Water)
                return;
        }

        for(int i = 0; i < _w; i++){
            arr[_y][_x+i] = Ship;
        }
        for(int i = 0; i < _h; i++){
            arr[_y+i][_x] = Ship;
        }
    }
}

GameArea::~GameArea(){
    for(int i = 0; i < y; i++){
         delete[] arr[i];
    }
    delete[] arr;
}

int main ( int argc, char* argv[] ) {
    GameArea ga(-1,10);
    ga.AddShip(1,1,3,1);
    ga.AddShip(5,3,1,300);
    ga.AddShip(5,3,1,3);
    ga.AddShip(5,1,3,1);
    ga.Print();
    cout << ga.ShipExist(5,100)<<endl;
    cout << ga.ShipExist(5,3)<<endl;
    return 0;
}