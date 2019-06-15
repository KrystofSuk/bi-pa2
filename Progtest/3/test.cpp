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
  CRange(long long int lo, long long int hi) : _lo(lo), _hi(hi)
  {
    if (_lo > _hi)
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
  friend ostream &operator<<(ostream &os, const CRange &range)
  {
    if (range._lo != range._hi)
      os << "<" << range._lo << ".." << range._hi << ">";
    else
      os << range._lo;
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
  friend bool operator==(const CRange &l, const CRange &r)
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
  friend bool operator!=(const CRange &l, const CRange &r)
  {
    return !(l == r);
  }

  /**
     * @brief Getter for lower bound
     * 
     * @return long long int Lower bound
     */
  long long int GetLO() const { return _lo; }

  /**
     * @brief Getter for higher bound
     * 
     * @return long long int Higher bound
     */
  long long int GetHI() const { return _hi; }

  /**
     * @brief Setter for new bounds
     * 
     * @param lo Lower bound
     * @param hi Higher bound
     */
  void Set(long long int lo, long long int hi)
  {
    if (_lo > _hi)
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
  static bool CompareLO(const CRange &i1, const CRange &i2)
  {
    return (i1.GetLO() < i2.GetLO());
  }

  /**
     * @brief Comparation fuction for two range objects by higher range
     * 
     * @param i1 first object
     * @param i2 second object
     * @return true i1 is smaller than i2
     * @return false i1 is equal or greater than i2
     */
  static bool CompareHI(const CRange &i1, const CRange &i2)
  {
    return (i1.GetHI() <= i2.GetHI());
  }

private:
  long long int _lo;
  long long int _hi;
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
  bool Includes(long long int x) const
  {

    int min = 0;
    int max = 0;
    int guess = 0;
    max = GetRangesCapacity() - 1;

    while (min <= max)
    {
      guess = (int)(((max + min) / 2) + 0.5);
      if (x >= _ranges.at(guess).GetLO() && x <= _ranges.at(guess).GetHI())
      {
        return true;
      }
      else if (_ranges.at(guess).GetHI() < x)
      {
        min = guess + 1;
      }
      else if (_ranges.at(guess).GetLO() > x)
      {
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
  bool Includes(const CRange &range) const
  {
    int min = 0;
    int max = GetRangesCapacity() - 1;
    int l = BinarySearch(range.GetLO(), min, max);
    int r = BinarySearch(range.GetHI(), min, max) == -1 ? GetRangesCapacity() : BinarySearch(range.GetHI(), min, max);
    return (l == r);
  }

  /**
     * @brief Operator overload for += of CRange object
     * 
     * @param range CRange object
     * @return CRangeList& Modified CRangeList with added CRange
     */
  CRangeList &operator+=(const CRange &range)
  {
    if (!Includes(range))
    {
      auto it = lower_bound(_ranges.begin(), _ranges.end(), range, CRange::CompareHI);
      int mx = (it - _ranges.begin());
      it = lower_bound(_ranges.begin(), _ranges.end(), range, CRange::CompareLO);
      int mn = (it - _ranges.begin());
      _ranges.insert(it, range);
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
  CRangeList &operator+=(const CRangeList &list)
  {
    for (int i = 0; i < list.GetRangesCapacity(); i++)
    {
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
  friend CRangeList operator+(CRangeList l, const CRange &r)
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
  CRangeList &operator-=(const CRange &range)
  {
    Shrink(range);
    return *this;
  }

  /**
     * @brief Operator overload for -= CRangeList
     * 
     * @param list CRangeList with intervals to remove from original
     * @return CRangeList& CRangeList with removed intervals
     */
  CRangeList &operator-=(const CRangeList &list)
  {
    for (int i = 0; i < list.GetRangesCapacity(); i++)
    {
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
  friend CRangeList operator-(CRangeList l, const CRange &r)
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
  CRangeList &operator=(const CRange &range)
  {
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
  CRangeList &operator=(const CRangeList &list)
  {
    _ranges.clear();
    for (int i = 0; i < list.GetRangesCapacity(); i++)
    {
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
  friend bool operator==(const CRangeList &l, const CRangeList &r)
  {
    if (l.GetRangesCapacity() != r.GetRangesCapacity())
      return false;
    for (int i = 0; i < l.GetRangesCapacity(); i++)
      if (l._ranges.at(i) != r._ranges.at(i))
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
  friend bool operator!=(const CRangeList &l, const CRangeList &r)
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
  friend ostream &operator<<(ostream &os, const CRangeList &rangeList)
  {
    size_t max = rangeList.GetRangesCapacity();
    os << "{";
    for (size_t c = 0; c < max; c++)
    {
      os << rangeList._ranges.at(c);
      if (c + 1 != max)
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
  int GetRangesCapacity() const
  {
    return _ranges.size();
  }

private:
  vector<CRange> _ranges;
  vector<CRange> _rev;

  /**
   * @brief Binary search for method
   * 
   * @param x wanted number
   * @param min minimal value
   * @param max maximal value
   * @return int index of interval  
   */
  int BinarySearch(const long long int &x, int min, int max) const
  {
    int guess = 0;
    while (min <= max)
    {
      guess = (int)(((max + min) / 2) + 0.5);
      if (x >= _ranges.at(guess).GetLO() && x <= _ranges.at(guess).GetHI())
      {
        return guess;
      }
      else if (_ranges.at(guess).GetHI() < x)
      {
        min = guess + 1;
      }
      else if (_ranges.at(guess).GetLO() > x)
      {
        max = guess - 1;
      }
    }
    return -1;
  }

  /**
     * @brief Normalization method for simplifiing intervals
     * 
     */
  void Normalize(const CRange &range, int min, int max)
  {
    //cout << (*this) << endl;
    min++;
    if (min != GetRangesCapacity())
    {
      while (min <= max)
      {
        _ranges.erase(_ranges.begin() + min);
        max--;
      }
    }
    min--;

    if (min != 0)
    {
      if (_ranges.at(min - 1).GetHI() >= range.GetLO() - 1)
      {
        _ranges.at(min).Set(_ranges.at(min - 1).GetLO(), _ranges.at(min).GetHI());
        _ranges.erase(_ranges.begin() + min - 1);
        min--;
      }
    }
    if (min != GetRangesCapacity() - 1)
    {
      if (_ranges.at(min + 1).GetLO() <= range.GetHI() + 1)
      {
        _ranges.at(min).Set(_ranges.at(min).GetLO(), _ranges.at(min + 1).GetHI());
        _ranges.erase(_ranges.begin() + min + 1);
      }
    }
  }

  /**
     * @brief Method for shrinking intervals by interval
     * 
     * @param range Interval to shrink
     */
  void Shrink(const CRange &range)
  {
    auto it = lower_bound(_ranges.begin(), _ranges.end(), range, CRange::CompareHI);
    int mx = (it - _ranges.begin());
    it = lower_bound(_ranges.begin(), _ranges.end(), range, CRange::CompareLO);
    int mn = (it - _ranges.begin() - 1);

    if (mn == mx)
    {
      if (range.GetLO() == _ranges.at(mx).GetLO())
      {
        if (range.GetHI() == _ranges.at(mx).GetHI())
        {
          _ranges.erase(_ranges.begin() + mx);
        }
        else
        {
          _ranges.at(mx).Set(range.GetHI() + 1, _ranges.at(mx).GetHI());
        }
      }
      else
      {
        long long hi = _ranges.at(mx).GetHI();
        _ranges.at(mx).Set(_ranges.at(mx).GetLO(), range.GetLO() - 1);
        if (range.GetHI() != hi)
        {
          CRange cr = CRange(range.GetHI() + 1, hi);
          _ranges.insert(_ranges.begin() + mx + 1, cr);
        }
      }
    }
    else if (mn < mx)
    {

      if (mn != -1)
      {
        if (range.GetLO() == _ranges.at(mn).GetLO())
          _ranges.erase(_ranges.begin() + mn);
        else if (range.GetLO() <= _ranges.at(mn).GetHI())
        {
          _ranges.at(mn).Set(_ranges.at(mn).GetLO(), range.GetLO() - 1);
        }
      }

      if (mx != GetRangesCapacity())
      {
        if (range.GetHI() == _ranges.at(mx).GetHI())
        {
          _ranges.erase(_ranges.begin() + mx);
        }
        else if (range.GetHI() >= _ranges.at(mx).GetLO())
        {
          _ranges.at(mx).Set(range.GetHI() + 1, _ranges.at(mx).GetHI());
        }
      }

      for (int i = mn + 1; i < mx; i++)
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
CRangeList operator+(const CRange &l, const CRange &r)
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
CRangeList operator-(const CRange &l, const CRange &r)
{
  CRangeList cl;
  cl += l;
  cl -= r;
  return cl;
}

#ifndef __PROGTEST__
string toString(const CRangeList &x)
{
  ostringstream oss;
  oss << x;
  return oss.str();
}

int main(void)
{
  return 0;
}
#endif /* __PROGTEST__ */
