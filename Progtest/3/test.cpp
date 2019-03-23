#ifndef __PROGTEST__
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
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidRangeException
{
  
};
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRange
{
  public:
    // constructor
    CRange(long long int lo, long long int hi) : _lo(lo), _hi(hi) {
      if(_lo > _hi)
        throw InvalidRangeException();
    };

    CRange() : _lo(0), _hi(0) {};

    friend ostream & operator<<(ostream& os, const CRange & range)
    {
      if(range._lo != range._hi)
        os << "<" << range._lo << ".." << range._hi << ">";
      else
        os << range._lo ;
      return os;
    };


    friend bool operator==(const CRange& l, const CRange& r)
    {
      return (l._hi == r._hi && l._lo == r._lo);
    }

    // operator !=
    friend bool operator!=(const CRange& l, const CRange& r)
    {
      return !(l == r);
    }

    long long int GetLO() const {return _lo;};

    long long int GetHI() const {return _hi;};

    void Set(long long int lo, long long int hi){
      if(_lo > _hi)
        throw InvalidRangeException();
      _lo = lo;
      _hi = hi;
    };
  private:
    // todo
    long long int _lo;
    long long int _hi;
};

class CRangeList
{
  public:
    // constructor
    // Includes long long / range
    bool Includes(long long int x){
      
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = GetRangesCapacity();

      while (min < max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        if (x >= _ranges.at(guess).GetLO() && x <= _ranges.at(guess).GetHI()) 
          {
            return true;
          } else if (_ranges.at(guess).GetHI() < x) {
            min = guess + 1;
          } else if(_ranges.at(guess).GetLO() > x){
            max = guess - 1;
          }
      }
      return false;
    }

    bool Includes(const CRange & range){
      long long int x = range.GetLO();
      int min = 0;
      int max = GetRangesCapacity(); 
      int guess = 0;
      int l = -1;
      int r = GetRangesCapacity();

      while (min < max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        if (x >= _ranges.at(guess).GetLO() && x <= _ranges.at(guess).GetHI()) 
          {
            l = guess;
            break;
          } else if (_ranges.at(guess).GetHI() < x) {
            min = guess + 1;
          } else if(_ranges.at(guess).GetLO() > x){
            max = guess - 1;
          }
      }
      
      x = range.GetHI();
      min = 0;
      guess = 0;
      max = GetRangesCapacity();

      while (min < max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        if (x >= _ranges.at(guess).GetLO() && x <= _ranges.at(guess).GetHI()) 
          {
            r = guess;
            break;
          } else if (_ranges.at(guess).GetHI() < x) {
            min = guess + 1;
          } else if(_ranges.at(guess).GetLO() > x){
            max = guess - 1;
          }
      }

      return (l==r);
    }

    // += range / range list
    CRangeList & operator+=(const CRange & range){
      _ranges.push_back(range);
      Normalize();
      return *this;
    };

    CRangeList & operator+=(const CRangeList & list){
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        _ranges.push_back(list._ranges.at(i));
        Normalize();
      }
      return *this;
    };
    
    friend CRangeList operator+(CRangeList l, const CRange& r) 
    {
      l += r;
      return l; 
    }
    

    // -= range / range list
    CRangeList & operator-=(const CRange & range){
      Shrink(range);
      Normalize();
      return *this;
    };

    CRangeList & operator-=(const CRangeList & list){
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        Shrink(list._ranges.at(i));
        Normalize();
      }
      return *this;
    };
    
    friend CRangeList operator-(CRangeList l, const CRange& r) 
    {
      l -= r;
      return l; 
    }

    // = range / range list
    CRangeList & operator=(const CRange & range){
      _ranges.clear();
      _ranges.push_back(range);
      Normalize();
      return *this;
    }
    
    CRangeList & operator=(const CRangeList & list){
      _ranges.clear();
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        _ranges.push_back(list._ranges.at(i));
        Normalize();
      }
      return *this;
    };

    // operator ==
    friend bool operator==(const CRangeList& l, const CRangeList& r)
    {
      if(l.GetRangesCapacity() != r.GetRangesCapacity())
        return false;
      for(int i = 0; i < l.GetRangesCapacity(); i++)
        if(l._ranges.at(i) != r._ranges.at(i))
          return false;
      return true;
    }

    // operator !=
    friend bool operator!=(const CRangeList& l, const CRangeList& r)
    {
      return !(l == r);
    }

    // operator <<
    friend ostream & operator<<(ostream& os, const CRangeList & rangeList)
    {
      size_t max = rangeList.GetRangesCapacity();
      os << "{";   
      for(size_t c = 0; c < max; c++){
        os << rangeList._ranges.at(c);
        if(c + 1 != max)
          os << ",";
      }      
      os << "}";
      return os;
    };

    int GetRangesCapacity() const {
      return _ranges.size();
    };
    
  private:
    vector<CRange> _ranges;
    
    void Normalize(){
      sort( _ranges.begin(), _ranges.end(), compare);
      for(int c = 0; c < GetRangesCapacity(); c++){
        int max = -1;
        for(int i = c + 1; i < GetRangesCapacity(); i++)
        {
          if(_ranges.at(c).GetHI() >= _ranges.at(i).GetLO()-1){
            max = i;
          }
        }

        if(max != -1){
          if(_ranges.at(c).GetHI() <= _ranges.at(max).GetHI())
          _ranges.at(c).Set(_ranges.at(c).GetLO(), _ranges.at(max).GetHI());
          _ranges.erase(_ranges.begin() + max);
          c--;
        }        
      }
    }

    void Shrink(const CRange & range){
      sort( _ranges.begin(), _ranges.end(), compare);
      int l = -1;
      int r = _ranges.size();
      for(int c = 0; c < GetRangesCapacity(); c++){
        if(_ranges.at(c).GetLO() <= range.GetLO() && _ranges.at(c).GetHI() >= range.GetLO())
          l = c;
        if(_ranges.at(c).GetLO() <= range.GetHI() && _ranges.at(c).GetHI() >= range.GetHI())
          r = c;
      }
      cout <<"Shrinking: " << range.GetLO() <<".."<<range.GetHI() << " - " << l << "/" << r << endl;
      if(l == r){
        cout << "In one " <<_ranges.at(l).GetLO()<<"/"<< range.GetLO()-1 << endl;
        if(_ranges.at(l).GetLO() != range.GetLO()){
          CRange left (_ranges.at(l).GetLO(), range.GetLO()-1);
          _ranges.push_back(left);
        }
        if(_ranges.at(l).GetHI() != range.GetHI()){
          CRange right (range.GetHI()+1, _ranges.at(l).GetHI());
          _ranges.push_back(right);
        }
        _ranges.erase(_ranges.begin()+l);
      }

      else if(l == -1 && r != GetRangesCapacity()){
        int index = -1;
        for(int i = 0; i < r; i++)
          if(_ranges.at(i).GetLO() < range.GetLO())  
            index++;       
        
        if(_ranges.at(r).GetHI() != range.GetHI())
          _ranges.at(r).Set(range.GetHI()+1, _ranges.at(r).GetHI());
        else
          index++;

        cout << "Open Left " << r << index  << endl;

        for(int i = r; i > index; i--)
          _ranges.erase(_ranges.begin()+i);
        
      }

      else if(l != -1 && r == GetRangesCapacity()){
        cout << "Open Right" << r << endl;
      }

      else if(l != -1 && r != GetRangesCapacity() && l != r){
        cout << "Multiple intervals"<< endl;
        _ranges.at(l).Set(_ranges.at(l).GetLO(), range.GetLO()-1);
        _ranges.at(r).Set(range.GetHI()+1, _ranges.at(r).GetHI());
        for(int i = l+1; i < r; i++)         
          _ranges.erase(_ranges.begin()+i);
      }else if(l == -1 && r == GetRangesCapacity()){
        if(_ranges.at(0).GetLO() > range.GetLO() && _ranges.at(_ranges.size()-1).GetHI() < range.GetHI()){
          cout << "Whole" << endl;
        }
        else{
          cout << "NaN" << endl;
        }
      }
      cout << "Done" << endl;
    };
    
    static bool compare(const CRange & i1, const CRange & i2) 
    { 
      return (i1.GetLO() < i2.GetLO()); 
    }
};


CRangeList operator+(CRange l, const CRange& r) 
{
  CRangeList cl;
  cl += l;
  cl += r;
  return cl; 
}
CRangeList operator-(CRange l, const CRange& r) 
{
  CRangeList cl;
  cl -= l;
  cl -= r;
  return cl; 
}


#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
  CRangeList a, b, c;
  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  c = CRange(0, 100) + CRange(200, 300) + CRange(400, 500); 
  c -= CRange(-100,50);
  cout << toString(c)<< endl;
  c -= CRange(330,500);
  cout << toString(c)<< endl;
  /*
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 8, 30 );
  assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
  a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );

  assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
  a += CRange ( 106, 119 ) + CRange ( 152, 158 );
  assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
  a += CRange ( -3, 170 );
  a += CRange ( -30, 1000 );
  assert ( toString ( a ) == "{<-30..1000>}" );
  b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
  a += b;
  assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( -400, -400 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
  
  a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
  
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  try
  {
    a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
    assert ( "Exception not thrown" == NULL );
  }
  catch ( const InvalidRangeException & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown" == NULL );
  }
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  b = a;
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 2600, 2700 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 15, 15 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
  assert ( !( a == b ) );
  assert ( a != b );

  
  cout << toString(b)<< endl;
  assert ( b . Includes ( 15 ) );
  assert ( b . Includes ( 2900 ) );
  assert ( b . Includes ( CRange ( 15, 15 ) ) );
  assert ( b . Includes ( CRange ( -350, -350 ) ) );
  assert ( b . Includes ( CRange ( 100, 200 ) ) );
  assert ( !b . Includes ( CRange ( 800, 900 ) ) );
  assert ( !b . Includes ( CRange ( -1000, -450 ) ) );
  assert ( !b . Includes ( CRange ( 0, 500 ) ) );
  assert ( !b . Includes ( CRange ( -900, -900 ) ) );
  a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
  assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
  cout << toString(a)<< endl;
  
  b += a;
  assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b -= a;
  assert ( toString ( b ) == "{}" );
  b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );

  /*
  b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
  assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
#ifdef EXTENDED_SYNTAX
  CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
  return 0;
}
#endif /* __PROGTEST__ */
