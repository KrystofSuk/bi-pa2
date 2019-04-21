#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;

struct CCoord
{
  CCoord(int x = 0, int y = 0)
  {
    m_X = x;
    m_Y = y;
  }
  int m_X;
  int m_Y;
  
  friend std::ostream &operator<<(std::ostream &os, const CCoord &obj)
  {
    os << "[" << obj.m_X << "," << obj.m_Y << "]";
    return os;
  }
};
#endif /* __PROGTEST__ */

struct CShape
{
protected:
  int _ID;
  CCoord * _centr;

public:
  CShape(int ID)
  {
    _ID = ID;
  };
  virtual CShape * Clone () const = 0;
  virtual void CalculateCentroid(CCoord * v) = 0;
  ~CShape(){
    if(_centr)
      delete _centr;
  };
};

class CRectangle : public CShape
{
public:
  CRectangle(int ID, int x1, int y1, int x2, int y2) : CShape(ID){
    CalculateCentroid(new CCoord((x1+x2)/2,(y1+y2)/2));
  };
  CRectangle * Clone () const {
    return new CRectangle(*this);
  }
  void CalculateCentroid(CCoord * v){
    _centr = v;
    cout << *_centr << endl;
  }
  // dalsi Vase implementace
};
class CCircle : public CShape
{

public:
  CCircle(int ID, int x, int y, int r) : CShape(ID){

                                         };
  CCircle * Clone () const {
    return new CCircle(*this);
  }
  void CalculateCentroid(CCoord * v){
    
  }
  // dalsi Vase implementace
};
class CPolygon : public CShape
{

public:
  CPolygon(int ID, int cnt, const CCoord *v) : CShape(ID){

                                               };
  CPolygon * Clone () const {
    return new CPolygon(*this);
  }
  void CalculateCentroid(CCoord * v){
    
  }
  // dalsi Vase implementace
};
class CTriangle : public CShape
{

public:
  CTriangle(int ID, CCoord a, CCoord b, CCoord c) : CShape(ID){
    CCoord coord[3] = { a, b, c};
    CalculateCentroid(coord);                                                  
  };
  CTriangle * Clone () const {
    return new CTriangle(*this);
  }
  void CalculateCentroid(CCoord * v){
    cout << "CC" << endl;
  }
  // dalsi Vase implementace
};
class CScreen
{
private:
  vector<CShape *> _shapes;
public:
  // implicitni konstruktor
  // destruktor (pokud je potreba)
  // metoda/metody Add
  void Add(const CShape & sh){
    CShape * shape = sh.Clone();
    cout << "ADD" << endl;
    _shapes.push_back(shape);
  }
  // metoda Test
  void Optimize(void){

  }
  void Test(int x, int y, int &len, int *&list) const{

  }
  // pripadne dalsi Vase metody
};

int main(void)
{
  int *res, resLen;
  CScreen S0;
  S0.Add(CRectangle(1, 10, 20, 30, 40));
  S0.Add(CRectangle(2, 20, 10, 40, 30));
  S0.Add(CTriangle(3, CCoord(10, 20), CCoord(20, 10), CCoord(30, 30)));
  S0.Optimize();
  /*
  S0.Test(0, 0, resLen, res);
  // resLen = 0, res = [ ]
  delete[] res;
  S0.Test(21, 21, resLen, res);
  // resLen = 3, res = [ 1 2 3 ]
  delete[] res;
  S0.Test(16, 17, resLen, res);
  // resLen = 1, res = [ 3 ]
  delete[] res;
  S0.Test(30, 22, resLen, res);
  // resLen = 2, res = [ 1 2 ]
  delete[] res;
  S0.Test(35, 25, resLen, res);
  // resLen = 1, res = [ 2 ]
  delete[] res;

  CScreen S1;
  S1.Add(CCircle(1, 10, 10, 15));
  S1.Add(CCircle(2, 30, 10, 15));
  S1.Add(CCircle(3, 20, 20, 15));
  S1.Optimize();
  S1.Test(0, 0, resLen, res);
  // resLen = 1, res = [ 1 ]
  delete[] res;
  S1.Test(15, 15, resLen, res);
  // resLen = 2, res = [ 1 3 ]
  delete[] res;
  S1.Test(20, 11, resLen, res);
  // resLen = 3, res = [ 1 2 3 ]
  delete[] res;
  S1.Test(32, 8, resLen, res);
  // resLen = 1, res = [ 2 ]
  delete[] res;

  CScreen S2;
  CCoord vertex1[4] = {CCoord(10, 0), CCoord(20, 20), CCoord(30, 20), CCoord(40, 0)};
  S2.Add(CPolygon(1, 4, vertex1));
  CCoord vertex2[5] = {CCoord(20, 10), CCoord(10, 20), CCoord(25, 30), CCoord(40, 20), CCoord(30, 10)};
  S2.Add(CPolygon(2, 5, vertex2));
  S2.Optimize();
  S2.Test(25, 15, resLen, res);
  // resLen = 2, res = [ 1 2 ]
  delete[] res;
  S2.Test(25, 25, resLen, res);
  // resLen = 1, res = [ 2 ]
  delete[] res;
  S2.Test(15, 3, resLen, res);
  // resLen = 1, res = [ 1 ]
  delete[] res;
  S2.Test(11, 10, resLen, res);
  // resLen = 0, res = [ ]
  delete[] res;
  */
}
