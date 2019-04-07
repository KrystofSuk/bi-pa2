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
class CRange
{
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
    }

    /**
     * @brief Construct a new CRange object
     * 
     */
    CRange() : _lo(0), _hi(0) {}

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
    }

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
    long long int GetLO() const {return _lo;}

    /**
     * @brief Getter for higher bound
     * 
     * @return long long int Higher bound
     */
    long long int GetHI() const {return _hi;}

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
    }

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
    }

  private:
    long long int _lo;
    long long int _hi;
};

bool less_A_pointer (CRange lhs, CRange rhs)
{
  //cout << lhs << "as" << rhs << endl;
  return (lhs.GetLO() < rhs.GetLO());
}
bool less_B_pointer (CRange lhs, CRange rhs)
{
  return (lhs.GetHI() <= rhs.GetHI());
}

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
      max = GetRangesCapacity()-1;

      while (min <= max) 
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
      long long int x = 0;
      int min = 0;
      int max = GetRangesCapacity()-1; 
      int guess;
      int l = -1;
      int r = GetRangesCapacity();

      x = range.GetLO();
      min = 0;
      guess = 0;
      max = GetRangesCapacity()-1;
      while (min <= max) 
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
      max = GetRangesCapacity()-1;
      while (min <= max) 
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
      //cout << *this << endl;
      //cout << "Found " << range << " : " << l << "/" << r << endl;
      return (l==r);
    }

    /**
     * @brief Operator overload for += of CRange object
     * 
     * @param range CRange object
     * @return CRangeList& Modified CRangeList with added CRange
     */
    CRangeList & operator+=(const CRange & range){
      if(!Includes(range)){
        //cout << (*this) << endl;
        auto it = lower_bound( _ranges.begin(), _ranges.end(), range, less_B_pointer);
        int mx = (it - _ranges.begin());
        it = lower_bound( _ranges.begin(), _ranges.end(), range, less_A_pointer);
        int mn = (it - _ranges.begin());
        //cout << range << "Insert: " << mn  <<"." << mx << endl;
        _ranges.insert( it, range );
        Normalize(range, mn, mx);
      }
      return *this;
    }

    /**
     * @brief Operator overload for += of CRangeList object
     * 
     * @param list CRangeList with vector of intervals
     * @return CRangeList& Modified CRangeList with added intervals from input list
     */
    CRangeList & operator+=(const CRangeList & list){
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        *this += list._ranges.at(i);
      }
      return *this;
    }
    
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
      Shrink(range);
      return *this;
    }

    /**
     * @brief Operator overload for -= CRangeList
     * 
     * @param list CRangeList with intervals to remove from original
     * @return CRangeList& CRangeList with removed intervals
     */
    CRangeList & operator-=(const CRangeList & list){
      for(int i = 0; i < list.GetRangesCapacity(); i++){
        Shrink(list._ranges.at(i));
      }
      return *this;
    }
    
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
      *this += range;
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
        *this += list._ranges.at(i);
      }
      return *this;
    }

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
    }

    /**
     * @brief Get the number of intervals
     * 
     * @return int Number of intervals
     */
    int GetRangesCapacity() const {
      return _ranges.size();
    }
    
  private:
    vector<CRange> _ranges;
    vector<CRange> _rev;
    

    /**
     * @brief Normalization method for simplifiing intervals
     * 
     */
    void Normalize(const CRange & range, int min, int max){
      //cout << (*this) << endl;
      min ++;
      if(min != GetRangesCapacity()){  
        while(min <= max){
          //cout << "MIN: " <<  min << endl;
          _ranges.erase(_ranges.begin() + min);
          max--;
        }
      }
      min --;
      
      if(min != 0){
        if(_ranges.at(min-1).GetHI() >= range.GetLO()-1){
          //cout << "L" << endl;
          _ranges.at(min).Set(_ranges.at(min-1).GetLO(), _ranges.at(min).GetHI());
          _ranges.erase(_ranges.begin() + min-1);
          min --;
        }
      }
      //cout << (*this) << endl;
      if(min != GetRangesCapacity()-1){
        if(_ranges.at(min+1).GetLO() <= range.GetHI()+1){
          _ranges.at(min).Set(_ranges.at(min).GetLO(), _ranges.at(min+1).GetHI());
          _ranges.erase(_ranges.begin() + min+1);
          //cout << "R" << endl;
        }
      }
      //cout << (*this) << endl;
    }

    /**
     * @brief Method for shrinking intervals by interval
     * 
     * @param range Interval to shrink
     */
    void Shrink(const CRange & range){
      //sort( _ranges.begin(), _ranges.end(), CRange::Compare);
      auto it = lower_bound( _ranges.begin(), _ranges.end(), range, less_B_pointer);
      int mx = (it - _ranges.begin());
      it = lower_bound( _ranges.begin(), _ranges.end(), range, less_A_pointer);
      int mn = (it - _ranges.begin()-1);
      //cout << range << " Rem: " << mn  << "." << mx << endl;

      if(mn == mx){
        if(range.GetLO() == _ranges.at(mx).GetLO()){
          if(range.GetHI() == _ranges.at(mx).GetHI()){
            _ranges.erase(_ranges.begin() + mx);
          }
          else{
            _ranges.at(mx).Set(range.GetHI() + 1, _ranges.at(mx).GetHI());
          }
        }
        else{
          long long hi = _ranges.at(mx).GetHI();
          //cout << _ranges.at(mx).GetLO() << endl;
          _ranges.at(mx).Set(_ranges.at(mx).GetLO(), range.GetLO() - 1);
          if(range.GetHI() != hi){
            CRange cr = CRange(range.GetHI()+1, hi);
            _ranges.insert(_ranges.begin() + mx + 1, cr);
          }
        }
      }
      else if(mn < mx){

        if(mn != -1){
          if(range.GetLO() == _ranges.at(mn).GetLO())
            _ranges.erase(_ranges.begin() + mn);
          else if(range.GetLO() <= _ranges.at(mn).GetHI()){
            _ranges.at(mn).Set(_ranges.at(mn).GetLO(),range.GetLO() - 1);
          }
        }

        if(mx != GetRangesCapacity()){
          if(range.GetHI() == _ranges.at(mx).GetHI()){
            _ranges.erase(_ranges.begin() + mx);
          }else if(range.GetHI() >= _ranges.at(mx).GetLO()){
            _ranges.at(mx).Set(range.GetHI() + 1, _ranges.at(mx).GetHI());
          }
        }

        for(int i = mn + 1; i < mx; i++)
            _ranges.erase(_ranges.begin() + mn + 1);

      }
    }
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
  return oss . str ();
}

void TST(){
  
    
    CRangeList a;
  a += CRange(-10000, 10000);
  a += CRange(10000000, 1000000000);
  a += CRange(LLONG_MAX - 1, LLONG_MAX);
  assert(toString(a) == "{<-10000..10000>,<10000000..1000000000>,<9223372036854775806..9223372036854775807>}");
  cout << "--------" << endl << toString(a) << endl;
  a += CRange(LLONG_MAX, LLONG_MAX) + CRange(LLONG_MIN, LLONG_MAX);
  cout << "--------" << endl << toString(a) << endl;
  assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
  a -= a;
  assert(toString(a) == "{}");
  a += CRange(-10000, 10000) + CRange(10000000, 1000000000) + CRange(LLONG_MIN, LLONG_MIN + 1);
  assert(toString(a) == "{<-9223372036854775808..-9223372036854775807>,<-10000..10000>,<10000000..1000000000>}");
  a += CRange(LLONG_MIN, LLONG_MAX);
  assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");

}

void TST2(){
   CRangeList a;
  a = CRange(10, 10) + CRange(20, 20) + CRange(12, 12) + CRange(18, 18);
  assert ( toString ( a ) == "{10,12,18,20}" );
  a -= CRange(11, 19);
  assert ( toString ( a ) == "{10,20}" );
  a = CRange(10, 10) + CRange(20, 20) + CRange(12, 12) + CRange(18, 18);
  assert ( toString ( a ) == "{10,12,18,20}" );
  a -= CRange(10, 20);
  assert ( toString ( a ) == "{}" );
  a = CRange(10, 100);
  a -= CRange(20, 80);
  assert(toString(a) == "{<10..19>,<81..100>}");
  a = CRange(10, 100);
  a -= CRange(11, 99);
  assert(toString(a) == "{10,100}");
  a = CRange(10, 100);
  a -= CRange(11, 101);
  assert(toString(a) == "{10}");
  a = CRange(10, 100);
  a -= CRange(50, 150);
  assert(toString(a) == "{<10..49>}");
  a = CRange(10, 100);
  a -= CRange(0, 50);
  assert(toString(a) == "{<51..100>}");
  a = CRange(10, 100);
  a -= CRange(0, 99);
  assert(toString(a) == "{100}");
  a = CRange(10, 100);
  a -= CRange(10, 100);
  assert(toString(a) == "{}");
  a = CRange(10, 100);
  a -= CRange(0, 80);
  assert(toString(a) == "{<81..100>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a -= CRange(11, 29);
  assert(toString(a) == "{<0..10>,<30..40>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a -= CRange(10, 30);
  assert(toString(a) == "{<0..9>,<31..40>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  cout << toString(a) << endl;
  a -= CRange(0, 40);
  cout << toString(a) << endl;
  assert ( toString ( a ) == "{<-10..-5>,<50..60>}" );
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(1, 39);
  assert ( toString ( a ) == "{<-10..-5>,0,40,<50..60>}" );
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(2, 38);
  assert ( toString ( a ) == "{<-10..-5>,<0..1>,<39..40>,<50..60>}" );
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-5, 50);
  assert ( toString ( a ) == "{<-10..-6>,<51..60>}" );
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-8, 55);
  assert ( toString ( a ) == "{<-10..-9>,<56..60>}" );
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-9, 59);
  assert ( toString ( a ) == "{-10,60}" );
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-10, 60);
  assert ( toString ( a ) == "{}" );
  a = CRange(2, 2);
  a += CRange(4, 4);
  a -= CRange(2, 2);
  a -= CRange(4, 4);
  assert ( toString ( a ) == "{}" );
  a = CRange(2, 2);
  a += CRange(4, 4);
  a += CRange(0, 0);
  a += CRange(6, 6);
  a -= CRange(2, 2);
  a -= CRange(4, 4);
  assert ( toString ( a ) == "{0,6}" );
  a = CRange(0, 0);
  a += CRange(10, 10);
  a += CRange(2, 8);
  a -= CRange(2, 2);
  a -= CRange(8, 8);
  assert ( toString ( a ) == "{0,<3..7>,10}" );
  a = CRange(0, 0);
  a += CRange(10, 10);
  a += CRange(5, 5);
  a -= CRange(5, 5);
  assert ( toString ( a ) == "{0,10}" );
  a = CRange(0, 10);
  a -= CRange(0, 0);
  a -= CRange(10, 10);
  assert ( toString ( a ) == "{<1..9>}" );
  a = CRange(0, 10);
  a += CRange(12, 20);
  a += CRange(22, 30);
  a -= CRange(11, 11);
  a -= CRange(21, 21);
  assert ( toString ( a ) == "{<0..10>,<12..20>,<22..30>}" );
  a = CRange(0, 10);
  a += CRange(12, 20);
  a += CRange(22, 30);
  a -= CRange(5, 5);
  a -= CRange(25, 25);
  assert ( toString ( a ) == "{<0..4>,<6..10>,<12..20>,<22..24>,<26..30>}" );
  a = CRange(0, 10);
  a += CRange(12, 20);
  a += CRange(22, 30);
  a -= CRange(-1, -1);
  a -= CRange(31, 31);
  assert ( toString ( a ) == "{<0..10>,<12..20>,<22..30>}" );
  a -= a;
  for (int sf = 0; sf <= 60; sf++) {
      if (sf % 2 == 0) {
          a -= CRange(sf, sf);
      } else {
          a += CRange(sf, sf);
      }
  }
  assert ( toString ( a ) == "{1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59}" );
  a -= CRange(2, 58);
  assert ( toString ( a ) == "{1,59}" );
  a = CRange(10, 50);
  a += CRange(0, 8);
  a += CRange(52, 60);
  a += CRange(9, 51);
  assert ( toString ( a ) == "{<0..60>}" );
}

void TST3(){
   CRangeList a;
  a = CRange(LLONG_MIN+1, LLONG_MAX-1);
  assert(toString(a) == "{<" + to_string(LLONG_MIN+1) + ".." + to_string(LLONG_MAX-1) + ">}");
  a += CRange(LLONG_MIN, LLONG_MAX);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + ".." + to_string(LLONG_MAX) + ">}");
  a -= CRange(LLONG_MIN, LLONG_MIN);
  a -= CRange(LLONG_MAX, LLONG_MAX);
  assert(toString(a) == "{<" + to_string(LLONG_MIN+1) + ".." + to_string(LLONG_MAX-1) + ">}");
  a += CRange(LLONG_MIN, LLONG_MIN);
  a += CRange(LLONG_MAX, LLONG_MAX);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + ".." + to_string(LLONG_MAX) + ">}");
  a -= CRange(0, 0);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + "..-1>,<1.." + to_string(LLONG_MAX) + ">}");
  a += CRange(0, 0);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + ".." + to_string(LLONG_MAX) + ">}");
  a -= CRange(LLONG_MIN+1, LLONG_MAX-1);
  assert(toString(a) == "{" + to_string(LLONG_MIN) + "," + to_string(LLONG_MAX) + "}");
}

void TST4(){
   CRangeList a;
  a = CRange(LLONG_MIN, LLONG_MAX);
  a -= CRange(10, 12);
  a += a;
}
void TST5(){
  CRangeList a;
assert(toString(CRange(-1595,0) + CRange(0,LLONG_MAX) + CRange(LLONG_MAX,LLONG_MAX)) ==
         "{<-1595..9223372036854775807>}");
}
void TST6(){
  CRangeList a;
a = CRange(0, 0) + CRange(6, 6);
a -= CRange(-1, 1);
a -= CRange(5, 7);
assert(toString(a) == "{}");
a = CRange(0, 0) + CRange(6, 6);
assert(toString(a) == "{0,6}");
a += CRange(1, 2) + CRange(3, 4) + CRange(5, 6) + CRange(7, 8) + CRange(9, 10);
a -= a;
assert(toString(a) == "{}");
a = CRange(1, 1);
a += CRange(2, 2);
a -= CRange(2, 2);
a -= CRange(2, 2) + CRange(1, 1);
assert(toString(a) == "{}");
a = CRange(10, 15);
a += CRange(1, 5);
assert(toString(a) == "{<1..5>,<10..15>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(1, 5);
assert(toString(a) == "{<1..5>,<10..15>,<20..25>}");
a = CRange(1, 5);
a += CRange(10, 15);
assert(toString(a) == "{<1..5>,<10..15>}");
a = CRange(1, 5) + CRange(10, 15);
a += CRange(20, 25);
assert(toString(a) == "{<1..5>,<10..15>,<20..25>}");
a = CRange(10, 15);
a -= CRange(1, 5);
assert(toString(a) == "{<10..15>}");
a = CRange(10, 15) + CRange(20, 25);
a -= CRange(1, 5);
assert(toString(a) == "{<10..15>,<20..25>}");
a = CRange(1, 5);
a -= CRange(10, 15);
assert(toString(a) == "{<1..5>}");
a = CRange(1, 5) + CRange(10, 15);
a -= CRange(20, 25);
assert(toString(a) == "{<1..5>,<10..15>}");
a = CRange(10, 15);
a += CRange(1, 9);
assert(toString(a) == "{<1..15>}");
a = CRange(10, 15);
a += CRange(1, 10);
assert(toString(a) == "{<1..15>}");
a = CRange(10, 15);
a += CRange(1, 11);
assert(toString(a) == "{<1..15>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(1, 9);
assert(toString(a) == "{<1..15>,<20..25>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(1, 10);
assert(toString(a) == "{<1..15>,<20..25>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(1, 11);
assert(toString(a) == "{<1..15>,<20..25>}");
a = CRange(1, 5);
a += CRange(6, 15);
assert(toString(a) == "{<1..15>}");
a = CRange(1, 5);
a += CRange(5, 15);
assert(toString(a) == "{<1..15>}");
a = CRange(1, 5);
a += CRange(4, 15);
assert(toString(a) == "{<1..15>}");
a = CRange(1, 5) + CRange(10, 15);
a += CRange(16, 25);
assert(toString(a) == "{<1..5>,<10..25>}");
a = CRange(1, 5) + CRange(10, 15);
a += CRange(15, 25);
assert(toString(a) == "{<1..5>,<10..25>}");
a = CRange(1, 5) + CRange(10, 15);
a += CRange(14, 25);
assert(toString(a) == "{<1..5>,<10..25>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(16, 19);
assert(toString(a) == "{<10..25>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(15, 20);
assert(toString(a) == "{<10..25>}");
a = CRange(10, 15) + CRange(20, 25);
a += CRange(14, 21);
assert(toString(a) == "{<10..25>}");
a = CRange(10, 15);
a -= CRange(1, 9);
assert(toString(a) == "{<10..15>}");
a = CRange(10, 15);
a -= CRange(1, 10);
assert(toString(a) == "{<11..15>}");
a = CRange(10, 15);
a -= CRange(1, 11);
assert(toString(a) == "{<12..15>}");
a = CRange(1, 5);
a -= CRange(6, 15);
assert(toString(a) == "{<1..5>}");
a = CRange(1, 5);
a -= CRange(5, 15);
assert(toString(a) == "{<1..4>}");
a = CRange(1, 5);
a -= CRange(4, 15);
assert(toString(a) == "{<1..3>}");
a = CRange(10, 15) + CRange(20, 25);
a -= CRange(16, 19);
assert(toString(a) == "{<10..15>,<20..25>}");
a = CRange(10, 15) + CRange(20, 25);
a -= CRange(15, 20);
assert(toString(a) == "{<10..14>,<21..25>}");
a = CRange(10, 15) + CRange(20, 25);
a -= CRange(14, 21);
assert(toString(a) == "{<10..13>,<22..25>}");
a = CRange(1, 10);
a += CRange(2, 8);
cout << "O" << toString(a)<< endl;
assert(toString(a) == "{<1..10>}");
a = CRange(1, 10);
a += CRange(1, 10);
assert(toString(a) == "{<1..10>}");
a = CRange(1, 10) + CRange(20, 30);
a += CRange(2, 8);
assert(toString(a) == "{<1..10>,<20..30>}");
a = CRange(1, 10) + CRange(20, 30);
a += CRange(1, 10);
assert(toString(a) == "{<1..10>,<20..30>}");
a = CRange(1, 10) + CRange(20, 30);
cout << "---------" << endl << toString(a)<< endl;
a += CRange(2, 8) + CRange(22, 28);
cout << toString(a)<< endl;
assert(toString(a) == "{<1..10>,<20..30>}");
a = CRange(1, 10) + CRange(20, 30);
a += CRange(1, 10) + CRange(20, 30);
assert(toString(a) == "{<1..10>,<20..30>}");
a = CRange(1, 10);
a -= CRange(2, 9);
assert(toString(a) == "{1,10}");
a = CRange(1, 10);
a -= CRange(3, 8);
assert(toString(a) == "{<1..2>,<9..10>}");
a = CRange(1, 10);
a -= CRange(1, 10);
assert(toString(a) == "{}");
a = CRange(1, 10);
a -= CRange(0, 11);
assert(toString(a) == "{}");
a = CRange(1, 10) + CRange(20, 30);
a -= CRange(1, 10);
assert(toString(a) == "{<20..30>}");
a = CRange(1, 10) + CRange(20, 30);
a -= CRange(2, 9);
assert(toString(a) == "{1,10,<20..30>}");
a = CRange(1, 10) + CRange(20, 30);
a -= CRange(3, 8);
assert(toString(a) == "{<1..2>,<9..10>,<20..30>}");
a = CRange(1, 10) + CRange(20, 30);
a -= CRange(1, 10) + CRange(20, 30);
assert(toString(a) == "{}");
a = CRange(1, 10) + CRange(20, 30);
a -= CRange(2, 9) + CRange(21, 29);
assert(toString(a) == "{1,10,20,30}");
a = CRange(1, 10) + CRange(20, 30);
a -= CRange(3, 8) + CRange(22, 28);
assert(toString(a) == "{<1..2>,<9..10>,<20..21>,<29..30>}");
}

void TST7(){
  CRangeList a;
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
assert(!a.Includes(LLONG_MIN));
assert(!a.Includes(LLONG_MAX));
assert(a.Includes(0));
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MIN) + CRange(0,0);
assert(!a.Includes(LLONG_MIN));
assert(!a.Includes(0));
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MAX, LLONG_MAX) + CRange(0,0);
assert(a.Includes(LLONG_MIN));
assert(!a.Includes(0));
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, 0);
assert(!a.Includes(LLONG_MIN));
assert(!a.Includes(0));
assert(!a.Includes(-100));
assert(a.Includes(100));
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, 0);
assert(!a.Includes(LLONG_MIN));
assert(!a.Includes(0));
assert(!a.Includes(-100));
assert(a.Includes(100));
assert(a.Includes(LLONG_MAX));
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(0, LLONG_MAX);
assert(!a.Includes(LLONG_MAX));
assert(!a.Includes(0));
assert(a.Includes(-100));
assert(!a.Includes(100));
assert(a.Includes(LLONG_MIN));
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{}");
a = CRange(LLONG_MIN, LLONG_MIN);
a += CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MIN);
assert(toString(a) == "{}");
a = CRange(LLONG_MAX, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MIN);
a -= CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MIN);
assert(toString(a) == "{}");
a = CRange(LLONG_MIN, LLONG_MIN);
a -= CRange(LLONG_MIN, LLONG_MIN);
assert(toString(a) == "{}");
a = CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MAX, LLONG_MAX);
assert(toString(a) == "{}");
a = CRange(LLONG_MAX, LLONG_MAX);
a += CRange(LLONG_MAX, LLONG_MAX);
assert(toString(a) == "{9223372036854775807}");
a = CRange(LLONG_MIN, LLONG_MIN);
a += CRange(LLONG_MIN, LLONG_MIN);
assert(toString(a) == "{-9223372036854775808}");
a = CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
a = CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
a = CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{}");
a = CRange(LLONG_MIN, LLONG_MAX);
a -= CRange(LLONG_MIN + 1, LLONG_MAX - 1);
assert(toString(a) == "{-9223372036854775808,9223372036854775807}");
a = CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
a += CRange(LLONG_MIN + 1, LLONG_MAX - 1);
assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
a = CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
a += CRange(LLONG_MIN + 2, LLONG_MAX - 2);
assert(toString(a) == "{-9223372036854775808,<-9223372036854775806..9223372036854775805>,9223372036854775807}");
a = CRange(LLONG_MAX, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX - 1);
assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
a = CRange(LLONG_MIN, LLONG_MIN);
a += CRange(LLONG_MIN + 1, LLONG_MAX);
assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
a = CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{}");
a = CRange(LLONG_MIN, LLONG_MIN);
a -= CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{}");
a = CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MIN, LLONG_MAX);
assert(toString(a) == "{}");
a = CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MIN + 1, LLONG_MAX - 1);
assert(toString(a) == "{-9223372036854775808,9223372036854775807}");
a = CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
a += CRange(LLONG_MIN + 1, LLONG_MAX - 1);
assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
a = CRange(LLONG_MIN, LLONG_MIN);
a -= CRange(LLONG_MIN + 1, LLONG_MAX - 1);
assert(toString(a) == "{-9223372036854775808}");
a = CRange(LLONG_MAX, LLONG_MAX);
a -= CRange(LLONG_MIN + 1, LLONG_MAX - 1);
assert(toString(a) == "{9223372036854775807}");
}
void TST8(){
  CRangeList a;
assert(!a.Includes(5));
cout << "TEST 5.0 OK" << endl << endl << endl;
assert(!a.Includes(CRange(5, 10)));
cout << "TEST 5.1 OK" << endl << endl << endl;
a = CRange(5, 10);
assert(a.Includes(5));
cout << "TEST 5.2 OK" << endl << endl << endl;
assert(a.Includes(10));
cout << "TEST 5.3 OK" << endl << endl << endl;
assert(!a.Includes(4));
cout << "TEST 5.4 OK" << endl << endl << endl;
assert(!a.Includes(11));
cout << "TEST 5.5 OK" << endl << endl << endl;
assert(a.Includes(CRange(5, 10)));
cout << "TEST 5.4 OK" << endl << endl << endl;
assert(!a.Includes(CRange(4, 10)));
cout << "TEST 5.5 OK" << endl << endl << endl;
assert(!a.Includes(CRange(5, 11)));
cout << "TEST 5.6 OK" << endl << endl << endl;
}
void TST9(){
  CRangeList a = CRange(10, 20) + CRange(0, 9) + CRange(21, 30);
cout << "a: " << a << endl;
assert ( toString ( a ) == "{<0..30>}" );
cout << "TEST 4.1 OK" << endl << endl << endl;
a = CRange(10, 20) + CRange(0, 8) + CRange(22, 30);
cout << "a: " << a << endl;
assert ( toString ( a ) == "{<0..8>,<10..20>,<22..30>}" );
cout << "TEST 4.2 OK" << endl << endl << endl;
a = CRange(10, 20) + CRange(22, 30) + CRange(0, 50);
cout << "a: " << a << endl;
assert ( toString ( a ) == "{<0..50>}" );
cout << "TEST 4.3 OK" << endl << endl << endl;
a -= CRange(-5, 5) + CRange(25, 35) + CRange(45, 55);
cout << "a: " << a << endl;
assert ( toString ( a ) == "{<6..24>,<36..44>}" );
cout << "TEST 4.4 OK" << endl << endl << endl;
CRangeList b;
b = CRange(0, 0);
b -= CRange(0, 0);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{}" );
cout << "TEST 4.5 OK" << endl << endl << endl;
b -= CRange(0, 10);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{}" );
cout << "TEST 4.6 OK" << endl << endl << endl;
b += CRange ( 25, 100 );
cout << "b: " << b << endl;
assert ( toString ( b ) == "{<25..100>}" );
cout << "TEST 4.7 OK" << endl << endl << endl;
b -= CRange(25, 25);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{<26..100>}" );
cout << "TEST 4.7 OK" << endl << endl << endl;
b += CRange(1000, 1200);
b -= CRange(1000, 1000);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{<26..100>,<1001..1200>}" );
cout << "TEST 4.8 OK" << endl << endl << endl;
b -= CRange(1200, 1200);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{<26..100>,<1001..1199>}" );
cout << "TEST 4.9 OK" << endl << endl << endl;
b += CRange(30, 1100);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{<26..1199>}" );
cout << "TEST 4.10 OK" << endl << endl << endl;
b -= CRange(30, 1100);
cout << "b: " << b << endl;
assert ( toString ( b ) == "{<26..29>,<1101..1199>}" );
cout << "TEST 4.11 OK" << endl << endl << endl;
}
void TST10(){
  CRangeList a, b;
a -= CRange(5, 10);
assert(!a.Includes(5));
cout << "TEST 2.1 OK" << endl << endl << endl;
assert(!a.Includes( CRange(5, 10) ));
cout << "TEST 2.2 OK" << endl << endl << endl;
a += b;
a = CRange(LLONG_MIN, LLONG_MAX);
assert(a.Includes(5));
assert(a.Includes(LLONG_MIN));
assert(a.Includes(LLONG_MAX));
cout << "TEST 2.5 OK" << endl << endl << endl;
cout << a << endl;
a -= CRange(LLONG_MIN, 0);
cout << a << endl;
assert(a.Includes(5));
assert(!a.Includes(-5));
cout << "TEST 2.7 OK" << endl << endl << endl;
a = CRange(LLONG_MIN, LLONG_MAX);
a += CRange(LLONG_MIN, LLONG_MAX);
assert(a.Includes(LLONG_MIN));
assert(a.Includes(LLONG_MAX));
cout << "TEST 2.9 OK" << endl << endl << endl;
cout << "odebrání LLONG_MIN" << endl;
cout << a << endl;
a -= CRange(LLONG_MIN, LLONG_MIN);
cout << a << endl;
assert(!a.Includes(LLONG_MIN));
cout << "TEST 2.10 OK" << endl << endl << endl;
a += CRange(LLONG_MIN, LLONG_MIN);
cout << a << endl;
assert(a.Includes(LLONG_MIN));
cout << "TEST 2.11 OK" << endl << endl << endl;
a -= CRange(LLONG_MAX, LLONG_MAX);
cout << a << endl;
assert(!a.Includes(LLONG_MAX));
cout << "TEST 2.12 OK" << endl << endl << endl;
a += CRange(LLONG_MAX, LLONG_MAX);
cout << a << endl;
assert(a.Includes(LLONG_MAX));
cout << "TEST 2.13 OK" << endl << endl << endl;
}
int                main                                    ( void )
{
  //TST();
  CRangeList a, b, c;
  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  c -= CRange(-9223372036854775808, 9223372036854775808);
  for(int i = 0; i < 10000; i ++)
    c+= CRange(3*i, 3*i+1);
  c += CRange ( 25, 100 );
  c += CRange ( 225, 300 );
  c += CRange ( 335, LLONG_MAX );
  c += CRange ( LLONG_MIN, LLONG_MAX );
  cout << toString(c) << endl;

  TST();
  TST2();
  TST3();
  TST4();
  TST5();
  TST6();
  TST7();
  TST8();
  TST9();
  TST10();
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 10, 50 );
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
  cout << endl << endl;
  cout << endl << endl;
  cout << toString(b) << endl;
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 2600, 2700 );
  cout << endl << endl;
  cout << endl << endl;
  cout << toString(b) << endl;
  cout << endl << endl;
  cout << endl << endl;
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
