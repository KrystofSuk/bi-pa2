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









/**
 * @brief Range Class for holding specific interval with its lower and higher bound
 * 
 */
class CRange{
  public:
    /**
     * @brief Construct a new CRange object
     * 
     * @param lo lower bound
     * @param hi higher bound
     */
    CRange(long long int lo, long long int hi) : _lo(lo), _hi(hi) {
      if(_lo > _hi)
        throw InvalidRangeException();
    };

    /**
     * @brief Construct a new CRange object
     * 
     */
    CRange() : _lo(0), _hi(0) {};

    /**
     * @brief Output stream overload
     * 
     * @param os output stream
     * @param range range object
     * @return ostream& output stream
     */
    friend ostream & operator<<(ostream& os, const CRange & range)
    {
      if(range._lo != range._hi)
        os << "<" << range._lo << ".." << range._hi << ">";
      else
        os << range._lo ;
      return os;
    };

    /**
     * @brief Coparation operator between two range objects
     * 
     * @param l First range object
     * @param r Second range object
     * @return true Objects are identical
     * @return false Objects are not identical
     */
    friend bool operator==(const CRange& l, const CRange& r)
    {
      return (l._hi == r._hi && l._lo == r._lo);
    }

    /**
     * @brief Coparation operator between two range objects
     * 
     * @param l First range object
     * @param r Second range object
     * @return true Objects are not identical
     * @return false Objects are identical
     */
    friend bool operator!=(const CRange& l, const CRange& r)
    {
      return !(l == r);
    }

    /**
     * @brief Getter for lower bound
     * 
     * @return long long int Lower bound
     */
    long long int GetLO() const {return _lo;};

    /**
     * @brief Getter for higher bound
     * 
     * @return long long int Higher bound
     */
    long long int GetHI() const {return _hi;};

    /**
     * @brief Setter for new bounds
     * 
     * @param lo Lower bound
     * @param hi Higher bound
     */
    void Set(long long int lo, long long int hi){
      if(_lo > _hi)
        throw InvalidRangeException();
      _lo = lo;
      _hi = hi;
    };

    /**
     * @brief Comparation fuction for two range objects by lower range
     * 
     * @param i1 first object
     * @param i2 second object
     * @return true i1 is smaller than i2
     * @return false i1 is equal or greater than i2
     */
    static bool Compare(const CRange & i1, const CRange & i2) 
    { 
      return (i1.GetLO() < i2.GetLO()); 
    };

  private:
    long long int _lo;
    long long int _hi;
};


class CNode{
  private:
    CNode * _l;
    CNode * _r;
    int _max;
    int _min;
    CRange * _interval;
  public:
    CNode (){
      _l = NULL;
      _r = NULL;
      _interval = NULL;
      _max  = 0;
      _min  = 0;
    };
    /*
    ~CNode(){
      if(_l != NULL)
        delete[] _l;
      if(_r != NULL)
        delete[] _r;
      delete[] _interval;
    };*/
    void SetInterval(const CRange & interval){
      CRange * newRange = new CRange();
      newRange -> Set(interval.GetLO(), interval.GetHI());
      _interval = newRange;
    };   
    CNode * GetLeft() const{
      return _l;
    };
    CNode * GetRight() const{
      return _r;
    };
    CRange * GetInterval() const{
      return _interval;
    };
    CNode * GetOverRight(long long r){
      if(r > _min && r < _interval -> GetLO()){
        if(_l == NULL)
          return this;
        return _l -> GetOverRight(r);
      }
      if(r < _max && r > _interval -> GetHI()){
        if(_r == NULL)
          return this;
        return _r -> GetOverRight(r);
      }
      return this;
    };
    CNode * GetOverLeft(long long r){
      if(_r == NULL)
        return this;
      if(_interval -> GetLO() > r){
        if(_r -> GetOverLeft(r))
          return _r -> GetOverLeft(r);
        else
          return _r -> GetOverRight(r);
      }
    };
    void AddInterval(const CRange & interval){
      if(_interval == NULL){
        cout << "C" << endl;
        CRange * newRange = new CRange();
        newRange -> Set(interval.GetLO(), interval.GetHI());
        _interval = newRange;
        _max = interval.GetHI();
        _min = interval.GetLO();
        return;
      }
      if(interval.GetLO() < _interval -> GetLO()){
        if(_l == NULL){
          _l = new CNode();
        }
        _l -> AddInterval(interval);
        _l -> _max = _interval -> GetLO ();
        _min = _l -> GetInterval() -> GetHI();
        cout << "L" << endl;
      }
      else if(interval.GetLO() > _interval -> GetLO()){
        if(_r == NULL){
          _r = new CNode();
        }
        _r -> AddInterval(interval);
        _r -> _min = _interval -> GetHI ();
        _max = _r -> GetInterval() -> GetLO();
        cout << "R: " << _r -> _min << endl;
      }
      else if(interval.GetLO() >= _interval -> GetLO() && interval.GetHI() <= _interval -> GetHI()){
        cout << "S" << endl;
      }
    };

    void Print() const{
      cout << (*_interval) << _max << "/" << _min;
      if(_l != NULL){
        cout << endl << "/ " << endl;
        _l -> Print();
        cout << endl;
      }
      if(_r != NULL){
        cout << endl << "\\ " << endl;
        _r -> Print();
        cout << endl;
      }
      
    };
    
    int GetMax() const {
      return _max;
    };
    int GetMin() const {
      return _min;
    };
};




/**
 * @brief List of intervals and performer of basic operations with them
 * 
 */
class CRangeList
{
  public:
    /**
     * @brief Include method for checking if number x is present in intervals
     * 
     * @param x Wanted number
     * @return true Number is present
     * @return false Number is not present
     */
    bool Includes(long long int x) const{
      
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

    /**
     * @brief Include method for checking if interval is present in intervals
     * 
     * @param range Wanted interval
     * @return true Interval is present
     * @return false Interval is not present
     */
    bool Includes(const CRange & range) const{
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

    /**
     * @brief Operator overload for += of CRange object
     * 
     * @param range CRange object
     * @return CRangeList& Modified CRangeList with added CRange
     */
    CRangeList & operator+=(const CRange & range){
      //_root = CNode::Insert(_root, range);
      if(!Includes(range)){
        _ranges.push_back(range);
        sort( _ranges.begin(), _ranges.end(), CRange::Compare);
      }else{
        _ranges.push_back(range);
        Normalize();
      }
      return *this;
    };

    /**
     * @brief Operator overload for += of CRangeList object
     * 
     * @param list CRangeList with vector of intervals
     * @return CRangeList& Modified CRangeList with added intervals from input list
     */
    CRangeList & operator+=(const CRangeList & list){
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        
        if(!Includes(list._ranges.at(i))){
          _ranges.push_back(list._ranges.at(i));
          sort( _ranges.begin(), _ranges.end(), CRange::Compare);
        }else{
          _ranges.push_back(list._ranges.at(i));
          Normalize();
        }
      }
      Normalize();
      return *this;
    };
    
    /**
     * @brief Operator overload for + of CRangeList and CRange objects
     * 
     * @param l CRangeList object
     * @param r CRange object
     * @return CRangeList CRangeList with added interval
     */
    friend CRangeList operator+(CRangeList l, const CRange& r) 
    {
      l += r;
      return l; 
    }
    
    /**
     * @brief Operator overload for -= CRange
     * 
     * @param range Interval to remove
     * @return CRangeList& CRangeList with removed interval
     */
    CRangeList & operator-=(const CRange & range){
      if(Includes(range)){
        Shrink(range);
        Normalize();
      }
      return *this;
    };

    /**
     * @brief Operator overload for -= CRangeList
     * 
     * @param list CRangeList with intervals to remove from original
     * @return CRangeList& CRangeList with removed intervals
     */
    CRangeList & operator-=(const CRangeList & list){
      bool t = false;
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        if(Includes(list._ranges.at(i))){
          Shrink(list._ranges.at(i));
           t = true;
        }
      }
      if(t)
      Normalize();
      return *this;
    };
    
    /**
     * @brief Operator overload for - CRangeList and CRange
     * 
     * @param l CRangeList with intervals
     * @param r Specific interval which will be removed
     * @return CRangeList CRangeList with removed interval
     */
    friend CRangeList operator-(CRangeList l, const CRange& r) 
    {
      l -= r;
      return l; 
    }

    /**
     * @brief Operator overload for = which resets intervals to specified interval
     * 
     * @param range Specific interval
     * @return CRangeList& Modified CRangeList with only specified interval
     */
    CRangeList & operator=(const CRange & range){
      _ranges.clear();
      _ranges.push_back(range);
      Normalize();
      return *this;
    }
    
    /**
     * @brief Operator overload for = which resets intervals to specific list of intervals
     * 
     * @param list CRangeList of specific interals
     * @return CRangeList& Modifiec CRangeList with same intervals as input list
     */
    CRangeList & operator=(const CRangeList & list){
      _ranges.clear();
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        _ranges.push_back(list._ranges.at(i));
      }
      Normalize();
      return *this;
    };

    /**
     * @brief Operator overload for == which compares two lists
     * 
     * @param l First CRangeList
     * @param r Second CRangeList
     * @return true Lists are same
     * @return false Lists are different
     */
    friend bool operator==(const CRangeList& l, const CRangeList& r)
    {
      if(l.GetRangesCapacity() != r.GetRangesCapacity())
        return false;
      for(int i = 0; i < l.GetRangesCapacity(); i++)
        if(l._ranges.at(i) != r._ranges.at(i))
          return false;
      return true;
    }

    /**
     * @brief Operator overload for != of two lists
     * 
     * @param l First CRangeList
     * @param r Second CRangeList
     * @return true Lists are not same
     * @return false Lists are same
     */
    friend bool operator!=(const CRangeList& l, const CRangeList& r)
    {
      return !(l == r);
    }

    /**
     * @brief Operator overload for << which prints intervals in specific format to stream
     * 
     * @param os Output stream
     * @param rangeList CRangeList to print 
     * @return ostream& Stream with content
     */
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

    /**
     * @brief Get the number of intervals
     * 
     * @return int Number of intervals
     */
    int GetRangesCapacity() const {
      return _ranges.size();
    };

    
  private:
    vector<CRange> _ranges;
    
    /**
     * @brief Normalization method for simplifiing intervals
     * 
     */
    void Normalize(){
      sort( _ranges.begin(), _ranges.end(), CRange::Compare);
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
    };

    /**
     * @brief Method for shrinking intervals by interval
     * 
     * @param range Interval to shrink
     */
    void Shrink(const CRange & range){
      sort( _ranges.begin(), _ranges.end(), CRange::Compare);
      int l = -1;
      int r = _ranges.size();
      int bR = r;
      vector<int> overlaping;
      for(int c = 0; c < GetRangesCapacity(); c++){
        if(_ranges.at(c).GetLO() <= range.GetLO() && _ranges.at(c).GetHI() >= range.GetLO())
          l = c;
        if(_ranges.at(c).GetLO() <= range.GetHI() && _ranges.at(c).GetHI() >= range.GetHI())
          r = c;
      }
      
      if(l == r){
        if(_ranges.at(l).GetLO() != range.GetLO()){
          CRange left (_ranges.at(l).GetLO(), range.GetLO()-1);
          _ranges.push_back(left);
        }
        if(_ranges.at(l).GetHI() != range.GetHI()){
          CRange right (range.GetHI()+1, _ranges.at(l).GetHI());
          _ranges.push_back(right);
        }
        _ranges.erase(_ranges.begin()+l);
      }else{
        if(l != -1){
          _ranges.at(l).Set(_ranges.at(l).GetLO(),range.GetLO()-1);
        }
        if(r != bR){
          _ranges.at(r).Set(range.GetHI()+1,_ranges.at(r).GetHI());
        }
      }

      for(int c = 0; c < GetRangesCapacity(); c++)
        if(_ranges.at(c).GetLO() >= range.GetLO() && _ranges.at(c).GetHI() <= range.GetHI())
          overlaping.push_back(c);

      for(size_t c = 0; c < overlaping.size(); c++){
        _ranges.erase(_ranges.begin()+overlaping.at(c));
      }
    };
};

/**
 * @brief Operator overload for + of two intervals which makes list of them
 * 
 * @param l First Interval
 * @param r Second Interval
 * @return CRangeList Lists of intervals
 */
CRangeList operator+(const CRange & l, const CRange& r) 
{
  CRangeList cl;
  cl += l;
  cl += r;
  return cl; 
}

/**
 * @brief Operator overload for - of two intervals which makes list of them
 * 
 * @param l First Interval
 * @param r Second Interval
 * @return CRangeList Lists of intervals
 */
CRangeList operator-(const CRange & l, const CRange& r) 
{
  CRangeList cl;
  cl += l;
  cl -= r;
  return cl; 
}


#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss.str();
}

int                main                                    ( void )
{
  CNode n;
  n.AddInterval(CRange(0,6));
  n.AddInterval(CRange(0,3));
  n.AddInterval(CRange(10,15));
  n.AddInterval(CRange(-5,-3));
  n.AddInterval(CRange(-1,5));
  n.AddInterval(CRange(3,7));
  n.AddInterval(CRange(-90, -6));
  n.AddInterval(CRange(90, 600));
  n.AddInterval(CRange(50, 60));
  n.AddInterval(CRange(16, 30));
  n.AddInterval(CRange(35, 42));
  n.AddInterval(CRange(70, 80));
  n.AddInterval(CRange(85, 87));
  n.AddInterval(CRange(90, 900));
  n.AddInterval(CRange(0, 40));
  n.Print();
  /*
  CRangeList a, b, c;
  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  c = CRange(0, 1);
  for(int i = 100; i < 10000; i++)
    c += CRange(i*3,i*3+1);
  cout << toString(c) << endl;
  for(int i = 0; i < 10000; i++)
    c.Includes(CRange(2*i,i*3));
  for(int i = 0; i < 10000; i++)
    c -= CRange(2*i,i*3);
  cout << toString(c) << endl;
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 8, 30 );
  cout << toString(a) << endl;
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
  
  b += a;
  assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b -= a;
  assert ( toString ( b ) == "{}" );
  b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );

  b = CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  cout << toString(b) << endl;
  b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
  
  cout << toString(b)<< endl;
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
