#include <iostream>
using namespace std;


enum State {Water, Ship, Sunken};
class GameArea{
    private:
        int x;
        int y;
        bool started;
        State ** arr;
    public:
        GameArea(const int _x, const int _y);
        void Print();
        void AddShip(const int _y, const int _x, const int _w, const int _h);
        bool ShipExist(const int _y, const int _x);
        ~GameArea();
};

GameArea::GameArea(const int _x, const int _y){
    started = false;
    x = _x;
    y = _y;
    arr = new State*[y];
    for(int i = 0; i < y; i++){
        arr[i] = new State[x];
        for(int t = 0; t < x; t++){
            arr[i][t] = Water;
        }
    }
}

void GameArea::Print(){
    for(int i = 0; i < y; i++)
    {
        for(int z = 0; z < x; z++)
        {
            cout << arr[i][z];
        }
        cout << endl;
    }
}

bool GameArea::ShipExist(const int _y, const int _x){
    if(arr[_y][_x] != Water)
        return true;
    return false;
}

void GameArea::AddShip(const int _y, const int _x, const int _w, const int _h){
    if(_x >= 0 && _x < x && _y >= 0 && _y < y && !started && (_h == 1 || _w == 1) && _h != _w) {
        for(int i = 0; i < _w; i++){
            if(ShipExist(_y,_x+i))
                return;
        }
        for(int i = 0; i < _h; i++){
            if(ShipExist(_y+i,_x))
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
    GameArea ga(5,10);
    ga.AddShip(1,1,3,1);
    ga.AddShip(5,3,1,3);
    ga.AddShip(5,1,3,1);
    ga.Print();
    cout << ga.ShipExist(5,1)<<endl;
    cout << ga.ShipExist(5,3)<<endl;
    return 0;
}