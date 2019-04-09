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
#endif


/**
 * @brief Crange Class representing interval.
 * 
 */
class CRange
{
  public:
    /**
     * @brief Construct a new CRange object
     * 
     * @param lo is lower number of interval.
     * @param hi is higher number of interval.
     */
    CRange(long long lo, long long hi)
    {
        if(lo > hi)
        {
            throw InvalidRangeException();
        }
        this->lo = lo;
        this->hi = hi;
    }
    /**
     * @brief return string representation of interval.
     * 
     * @return string representation of interval.
     */
    string ToString() const
    {
        if (lo == hi) {
            return std::to_string(lo);
        }
        else
        {
            return "<"+std::to_string(lo)+".."+std::to_string(hi)+">";
        }   
    }
    /**
     * @brief Set lower number of interval.
     * 
     * @param lo 
     */
    void SetLo(long long lo)
    {
        this->lo = lo;
    }
    /**
     * @brief Set higher number of interval.
     * 
     * @param hi 
     */
    void SetHi(long long hi)
    {
        this->hi = hi;
    }
    /**
     * @brief Get the lower number of interval.
     * 
     * @return long long 
     */
    long long GetLo() const
    {
        return lo;
    }
    /**
     * @brief Get the higher number of interval.
     * 
     * @return long long 
     */
    long long GetHi() const
    {
        return hi;
    }
    /**
     * @brief compare two CRanges.
     * 
     * @param range 
     * @return true when object has same values.
     * @return false when object douest have same values.
     */
    bool operator == (const CRange & range) const
    {
        return lo == range.lo && hi == range.hi ? true : false;
    }
  private:
    /**
     * @brief lower number.
     * 
     */
    long long lo;
    /**
     * @brief higher number.
     * 
     */
    long long hi;
};

/**
 * @brief Function for compare lower values of Crange.
 * 
 * @param r1
 * @param r2 
 * @return true 
 * @return false 
 */
bool LOCompareFunc(const CRange & r1, const CRange & r2)
{
    if(r1.GetLo()<r2.GetLo())
    {
        return true;
    }
    return false;
}
/**
 * @brief Function for compare higher values of Crange.
 * 
 * @param r1 
 * @param r2 
 * @return true 
 * @return false 
 */
bool HICompareFunc(const CRange & r1, const CRange & r2)
{
    if(r1.GetHi()<=r2.GetHi())
    {
        return true;
    }
    return false;
}

/**
 * @brief CRangeList is used to store and optimize workflow with many intervals.
 * 
 */
class CRangeList
{
  public:
    /**
     * @brief Construct a new CRangeList object
     * 
     */
    CRangeList()
    {
        list = vector<CRange>();
    }
    /**
     * @brief just for call internal Insert, added just for potencionaly controll of input.
     * 
     * @param range 
     */
    void AddTest(CRange range)
    {
        Insert(range);
    }
    /**
     * @brief just for call internal Remove, added just for potencionaly controll of input.
     * 
     * @param range 
     */
    void RemoveTest(CRange range)
    {
        Remove(range);
    }
    /**
     * @brief check if some number is contained in interval.
     * 
     * @param data number to check.
     * @return true is in intervals.
     * @return false not found in intervals.
     */
    bool Includes(long long data) const
    {
        if(list.size()==0)
        {
            return false;
        }
        CRange range = CRange(data,data);
        auto startIterator = lower_bound(list.begin(),list.end(),range,LOCompareFunc);
        auto endIterator = lower_bound(list.begin(),list.end(),range,HICompareFunc);
        //cout << "start:" << startIterator-list.begin()<<endl << "end:" << endIterator-list.begin()<<endl;
        
        if (startIterator == endIterator) {
            if (endIterator == list.end()) {
                endIterator--;
                startIterator--;
            }
            
            if (startIterator->GetLo() <= data && endIterator->GetHi() >= data) 
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (endIterator < startIterator) {
            return true;
        }
        else
        {
            return false;
        }
    }
    /**
     * @brief check if some interval is contained between intervals.
     * 
     * @param range interval to check.
     * @return true interval exist there.
     * @return false interval not found
     */
    bool Includes(CRange range) const
    {
        if(list.size()==0)
        {
            return false;
        }
        auto startIterator = lower_bound(list.begin(),list.end(),range,LOCompareFunc);
        auto endIterator = lower_bound(list.begin(),list.end(),range,HICompareFunc);
        //cout << "start:" << startIterator-list.begin()<<endl << "end:" << endIterator-list.begin()<<endl<< "first:"<<startIterator->ToString()<<endl;

        if (startIterator == endIterator) {
            if (endIterator == list.end()) {
                endIterator--;
                startIterator--;
            }
            if (startIterator->GetLo() <= range.GetLo() && endIterator->GetHi() >= range.GetHi()) 
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (endIterator < startIterator) {
            return true;
        }
        else
        {
            return false;
        }
    }
    /**
     * @brief return string representation of interval.
     * 
     * @return string strig representation.
     */
    string ToString() const
    {
        string toReturn = "";
        for(size_t i = 0; i < list.size(); i++)
        {
            toReturn += list.at(i).ToString();
            if(i < list.size()-1)
            {toReturn+=",";}
        }
        return toReturn;
    }
    /**
     * @brief can add CRange throwgh += operator.
     * 
     * @param range range to add.
     * @return CRangeList& 
     */
    CRangeList & operator +=(const CRange & range)
    {
        Insert(range);
        return *this;
    }
    /**
     * @brief can add CRangeList of Cranges throwgh += operator.
     * 
     * @param range CRangeList to add
     * @return CRangeList& 
     */
    CRangeList & operator +=(const CRangeList & range)
    {
        for(size_t i = 0; i < range.list.size(); i++)
        {
            this->Insert(range.list.at(i));
        }
        
        return *this;
    }
    /**
     * @brief can remove Crange from CRangeList throwgh -=.
     * 
     * @param range Crange to remove
     * @return CRangeList& 
     */
    CRangeList & operator -=(const CRange & range)
    {
        Remove(range);
        return *this;
    }
    /**
     * @brief can remove CRangeList of Cranges from CRangeList throwgh -=.
     * 
     * @param range list of CRanges to remove.
     * @return CRangeList& 
     */
    CRangeList & operator -=(const CRangeList & range)
    {
        for(size_t i = 0; i < range.list.size(); i++)
        {
            this->Remove(range.list.at(i));
        }
        return *this;
    }
    /**
     * @brief allow to get CrangeList to ostream.
     * 
     * @param out 
     * @param rangeList 
     * @return ostream& 
     */
    friend ostream & operator << (ostream& out, const CRangeList & rangeList)
    {
        out << "{" << rangeList.ToString() << "}";
        return out;
    }
    /**
     * @brief allow to compare two CRangeLists.
     * 
     * @param rangeList1 
     * @param rangeList2 
     * @return true lists are same.
     * @return false lists arent same.
     */
    friend bool operator ==(const CRangeList & rangeList1,const CRangeList & rangeList2)
    {
        return rangeList1.list == rangeList2.list ? true : false;
    }
    /**
     * @brief allow to compare two CRangeLists.
     * 
     * @param rangeList 
     * @return true lists arent same.
     * @return false lists are same.
     */
    friend bool operator !=(const CRangeList & rangeList1,const CRangeList & rangeList2)
    {
        return rangeList1.list == rangeList2.list ? false : true;
    }
    /**
     * @brief allow to set CrangeList to specific CrangeList (copy).
     * 
     * @param rangeList 
     * @return CRangeList& 
     */
    CRangeList & operator =(const CRangeList & rangeList)
    {
        //CRangeList lst = CRangeList();
        this->list = vector<CRange>();
        for(size_t i = 0; i < rangeList.list.size(); i++)
        {
            this->list.push_back(rangeList.list.at(i));
        }
        return *this;
    }
    /**
     * @brief allow to set CRangeList directly with one value.
     * 
     * @param range 
     * @return CRangeList& 
     */
    CRangeList & operator =(const CRange & range)
    {
        //CRangeList rangeList = CRangeList();
        //(*this) = CRangeList();
        this->list = vector<CRange>();
        this->AddTest(range);
        return *this;
    }
    /**
     * @brief allow to SUM list with range by + operator.
     * 
     * @param rangeList list with data to SUM.
     * @param range1 range to SUM to list.
     * @return CRangeList 
     */
    friend CRangeList operator + (CRangeList rangeList,const CRange & range1)
    {
        rangeList.Insert(range1);
        return rangeList;
    }
    /**
     * @brief allow to SUM multiple lists by + operator.
     * 
     * @param rangeList1 list with data to SUM.
     * @param rangeList2 list with data to SUM.
     * @return CRangeList 
     */
    friend CRangeList operator + (CRangeList & rangeList1,CRangeList & rangeList2)
    {
        for(size_t i = 0; i < rangeList2.list.size(); i++)
        {
            rangeList1.Insert(rangeList2.list.at(i));
        }
        return rangeList1;
    }
    /**
     * @brief allow to remove range from list by - operator.
     * 
     * @param rangeList list with data.
     * @param range1 data to remove.
     * @return CRangeList 
     */
    friend CRangeList operator - (CRangeList rangeList,const CRange & range1)
    {
        rangeList.Remove(range1);
        return rangeList;
    }
    /**
     * @brief allow to remove list from list by - operator;
     * 
     * @param rangeList1 list with data.
     * @param rangeList2 list with data to remove.
     * @return CRangeList 
     */
    friend CRangeList operator - (CRangeList rangeList1,CRangeList & rangeList2)
    {
        for(size_t i = 0; i < rangeList2.list.size(); i++)
        {
            rangeList1.Remove(rangeList2.list.at(i));
        }
        return rangeList1;
    }
  private:
    /**
     * @brief vector with Cranges
     * 
     */
    std::vector<CRange> list;
    /**
     * @brief private method to Insert Crange to vector
     * 
     * @param range 
     */
    void Insert(CRange range)
    {
        // find start and end iterator
        auto startIterator = lower_bound(list.begin(),list.end(),range,LOCompareFunc);
        auto endIterator = lower_bound(list.begin(),list.end(),range,HICompareFunc);

        
        
        // dont insert when range and iterator are same
        if (!(startIterator >= list.begin() && startIterator < list.end() && range == *startIterator)) 
        {
            list.insert(startIterator,range);
        }

        // erase unwanted ranges between
        list.erase(startIterator,endIterator);
        

        // lower_bound after insetr
        auto it = lower_bound(list.begin(),list.end(),range,LOCompareFunc);

        cout << "------" << *this<< endl;
        // correct lo and hi
        if(list.end() > it + 1)
        {
            if((it+1)->GetLo()-1<=range.GetHi())
            {
                // hi correction
                it->SetHi((it+1)->GetHi());
                list.erase(it+1);
            }
        }
        if (it > list.begin()) {
            if((it-1)->GetHi()+1>=range.GetLo())
            {
                // lo correction
                it->SetLo((it-1)->GetLo());
                list.erase(it-1);
            }
        }

    }
    /**
     * @brief private method to remove Crange from vector
     * 
     * @param range 
     */
    void Remove(CRange range)
    {
        // when is nothing in list there is nothing to remove
        if(list.size()==0)
        {
            return;
        }

        // find start and end iterator
        auto startIterator = lower_bound(list.begin(),list.end(),range,LOCompareFunc);
        auto endIterator = lower_bound(list.begin(),list.end(),range,HICompareFunc);
        
        // commented debug
        //cout<<"startIterator:"<<startIterator->ToString()<<endl<<"endIterator:"<<endIterator->ToString()<<endl;
        //cout << "start:" << startIterator-list.begin() << endl << "end:"<<endIterator-list.begin()<<endl;
        
        if(startIterator > endIterator)
        {
            // special case when range to remove is inside another element so element needed to be splitte
            long long hi = 0;
            if(endIterator <= list.end())
            {
                hi = endIterator->GetHi();
            }
            if( endIterator->GetHi() > range.GetHi())
            {
                // split element
                endIterator->SetHi(range.GetLo()-1);
                if(startIterator <= list.begin())
                {
                    list.insert(startIterator,CRange(range.GetHi()+1,hi));
                }
            }
            else
            {
                // just repair without split
                endIterator->SetHi(range.GetLo()-1);
            }
        }
        else if(startIterator == endIterator)
        {
            // there range to remove could be through one or two elements of vector
            if(startIterator == list.end())
            {
                // iterator is out of range
                if((startIterator-1)->GetLo() < range.GetLo() && (startIterator-1)->GetLo() <= range.GetHi() && (startIterator-1)->GetHi() <= range.GetHi() && (startIterator-1)->GetHi() > range.GetLo())
                {
                    (startIterator-1)->SetHi(range.GetLo()-1);
                    return;
                } 
                return;
            }
            else if(startIterator->GetLo() >= range.GetLo() && startIterator->GetHi() <= range.GetHi())
            {
                list.erase(startIterator);
                return;
            }

            // hi is needed for correction
            long long hi = startIterator->GetHi();


            if(startIterator->GetLo()>range.GetLo())
            {
                if(startIterator > list.begin())
                {
                    if(startIterator->GetLo() > range.GetLo() && (startIterator-1)->GetHi() >= range.GetLo())
                    {
                        (startIterator-1)->SetHi(range.GetLo()-1);
                    }                
                }
                startIterator->SetLo(range.GetLo()-1);
            }
            if(range.GetHi() < hi)
            {
                startIterator->SetLo(range.GetHi()+1);
                startIterator->SetHi(hi);
            }
        }
        else
        {
            // case where could be many ranges between two iterators
            // first correction of Lo and Hi values of border values
            if(startIterator > list.begin())
            {
                if((startIterator-1)->GetLo() < range.GetLo() && (startIterator-1)->GetHi() >= range.GetLo())
                {
                    (startIterator-1)->SetHi(range.GetLo()-1);
                }                
            }

            if (endIterator != list.end()) {
                if(endIterator->GetLo() <= range.GetHi())
                {
                    endIterator->SetLo(range.GetHi()+1);
                }
            }

            // then remove unwanted values
            if(endIterator != list.end())
            {
                if(endIterator->GetHi() == range.GetHi())
                {
                    if(endIterator+1 > list.end())
                    {
                        list.erase(startIterator,endIterator);
                    }
                    else
                    {
                        list.erase(startIterator,endIterator+1);
                    }
                }
                else
                {
                    list.erase(startIterator,endIterator);
                }
            }
            else
            {
                if(startIterator < list.begin())
                    startIterator = list.begin();
                if (endIterator > list.end())
                    endIterator = list.end();
                
                list.erase(startIterator,endIterator);
            }
        }
    }
};

/**
 * @brief operator witch allow to SUM two Cranges and create list
 * 
 * @param range1
 * @param range2 
 * @return CRangeList 
 */
CRangeList operator + (const CRange & range1 ,const CRange & range2)
{
    CRangeList newList = CRangeList();
    newList.AddTest(range1);
    newList.AddTest(range2);
    return newList;
}
/**
 * @brief operator witch allow to create list of first range and then remove second range.
 * 
 * @param range1 
 * @param range2 
 * @return CRangeList 
 */
CRangeList operator - (const CRange & range1 ,const CRange & range2)
{
    CRangeList newList = CRangeList();
    newList.AddTest(range1);
    newList.RemoveTest(range2);
    return newList;
}



#ifndef __PROGTEST__

string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}





#endif /* __PROGTEST__ */


void TST()
{

  CRangeList a;
  a += CRange(-10000, 10000);
  a += CRange(10000000, 1000000000);
  a += CRange(LLONG_MAX - 1, LLONG_MAX);
  assert(toString(a) == "{<-10000..10000>,<10000000..1000000000>,<9223372036854775806..9223372036854775807>}");
  cout << "--------" << endl
       << toString(a) << endl;
  a += CRange(LLONG_MAX, LLONG_MAX) + CRange(LLONG_MIN, LLONG_MAX);
  cout << "--------" << endl
       << toString(a) << endl;
  assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
  a -= a;
  assert(toString(a) == "{}");
  a += CRange(-10000, 10000) + CRange(10000000, 1000000000) + CRange(LLONG_MIN, LLONG_MIN + 1);
  assert(toString(a) == "{<-9223372036854775808..-9223372036854775807>,<-10000..10000>,<10000000..1000000000>}");
  a += CRange(LLONG_MIN, LLONG_MAX);
  assert(toString(a) == "{<-9223372036854775808..9223372036854775807>}");
}

void TST2()
{
  CRangeList a;
  a = CRange(10, 10) + CRange(20, 20) + CRange(12, 12) + CRange(18, 18);
  assert(toString(a) == "{10,12,18,20}");
  a -= CRange(11, 19);
  assert(toString(a) == "{10,20}");
  a = CRange(10, 10) + CRange(20, 20) + CRange(12, 12) + CRange(18, 18);
  assert(toString(a) == "{10,12,18,20}");
  a -= CRange(10, 20);
  assert(toString(a) == "{}");
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
  assert(toString(a) == "{<-10..-5>,<50..60>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(1, 39);
  assert(toString(a) == "{<-10..-5>,0,40,<50..60>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(2, 38);
  assert(toString(a) == "{<-10..-5>,<0..1>,<39..40>,<50..60>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-5, 50);
  assert(toString(a) == "{<-10..-6>,<51..60>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-8, 55);
  assert(toString(a) == "{<-10..-9>,<56..60>}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-9, 59);
  assert(toString(a) == "{-10,60}");
  a = CRange(0, 10);
  a += CRange(12, 28);
  a += CRange(30, 40);
  a += CRange(-10, -5);
  a += CRange(50, 60);
  a -= CRange(-10, 60);
  assert(toString(a) == "{}");
  a = CRange(2, 2);
  a += CRange(4, 4);
  a -= CRange(2, 2);
  a -= CRange(4, 4);
  assert(toString(a) == "{}");
  a = CRange(2, 2);
  a += CRange(4, 4);
  a += CRange(0, 0);
  a += CRange(6, 6);
  a -= CRange(2, 2);
  a -= CRange(4, 4);
  assert(toString(a) == "{0,6}");
  a = CRange(0, 0);
  a += CRange(10, 10);
  a += CRange(2, 8);
  a -= CRange(2, 2);
  a -= CRange(8, 8);
  assert(toString(a) == "{0,<3..7>,10}");
  a = CRange(0, 0);
  a += CRange(10, 10);
  a += CRange(5, 5);
  a -= CRange(5, 5);
  assert(toString(a) == "{0,10}");
  a = CRange(0, 10);
  a -= CRange(0, 0);
  a -= CRange(10, 10);
  assert(toString(a) == "{<1..9>}");
  a = CRange(0, 10);
  a += CRange(12, 20);
  a += CRange(22, 30);
  a -= CRange(11, 11);
  a -= CRange(21, 21);
  assert(toString(a) == "{<0..10>,<12..20>,<22..30>}");
  a = CRange(0, 10);
  a += CRange(12, 20);
  a += CRange(22, 30);
  a -= CRange(5, 5);
  a -= CRange(25, 25);
  assert(toString(a) == "{<0..4>,<6..10>,<12..20>,<22..24>,<26..30>}");
  a = CRange(0, 10);
  a += CRange(12, 20);
  a += CRange(22, 30);
  a -= CRange(-1, -1);
  a -= CRange(31, 31);
  assert(toString(a) == "{<0..10>,<12..20>,<22..30>}");
  a -= a;
  for (int sf = 0; sf <= 60; sf++)
  {
    if (sf % 2 == 0)
    {
      a -= CRange(sf, sf);
    }
    else
    {
      a += CRange(sf, sf);
    }
  }
  assert(toString(a) == "{1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59}");
  a -= CRange(2, 58);
  assert(toString(a) == "{1,59}");
  a = CRange(10, 50);
  a += CRange(0, 8);
  a += CRange(52, 60);
  a += CRange(9, 51);
  assert(toString(a) == "{<0..60>}");
}

void TST3()
{
  CRangeList a;
  a = CRange(LLONG_MIN + 1, LLONG_MAX - 1);
  assert(toString(a) == "{<" + to_string(LLONG_MIN + 1) + ".." + to_string(LLONG_MAX - 1) + ">}");
  a += CRange(LLONG_MIN, LLONG_MAX);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + ".." + to_string(LLONG_MAX) + ">}");
  a -= CRange(LLONG_MIN, LLONG_MIN);
  a -= CRange(LLONG_MAX, LLONG_MAX);
  assert(toString(a) == "{<" + to_string(LLONG_MIN + 1) + ".." + to_string(LLONG_MAX - 1) + ">}");
  a += CRange(LLONG_MIN, LLONG_MIN);
  a += CRange(LLONG_MAX, LLONG_MAX);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + ".." + to_string(LLONG_MAX) + ">}");
  a -= CRange(0, 0);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + "..-1>,<1.." + to_string(LLONG_MAX) + ">}");
  a += CRange(0, 0);
  assert(toString(a) == "{<" + to_string(LLONG_MIN) + ".." + to_string(LLONG_MAX) + ">}");
  a -= CRange(LLONG_MIN + 1, LLONG_MAX - 1);
  assert(toString(a) == "{" + to_string(LLONG_MIN) + "," + to_string(LLONG_MAX) + "}");
}

void TST4()
{
  CRangeList a;
  a = CRange(LLONG_MIN, LLONG_MAX);
  a -= CRange(10, 12);
  a += a;
}
void TST5()
{
  CRangeList a;
  assert(toString(CRange(-1595, 0) + CRange(0, LLONG_MAX) + CRange(LLONG_MAX, LLONG_MAX)) ==
         "{<-1595..9223372036854775807>}");
}
void TST6()
{
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
  cout << "O" << toString(a) << endl;
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
  cout << "---------" << endl
       << toString(a) << endl;
  a += CRange(2, 8) + CRange(22, 28);
  cout << toString(a) << endl;
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

void TST7()
{
  CRangeList a;
  a = CRange(LLONG_MIN, LLONG_MAX);
  a -= CRange(LLONG_MIN, LLONG_MIN) + CRange(LLONG_MAX, LLONG_MAX);
  assert(!a.Includes(LLONG_MIN));
  assert(!a.Includes(LLONG_MAX));
  assert(a.Includes(0));
  a = CRange(LLONG_MIN, LLONG_MAX);
  a -= CRange(LLONG_MIN, LLONG_MIN) + CRange(0, 0);
  assert(!a.Includes(LLONG_MIN));
  assert(!a.Includes(0));
  a = CRange(LLONG_MIN, LLONG_MAX);
  a -= CRange(LLONG_MAX, LLONG_MAX) + CRange(0, 0);
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
void TST8()
{
  CRangeList a;
  assert(!a.Includes(5));
  cout << "TEST 5.0 OK" << endl
       << endl
       << endl;
  assert(!a.Includes(CRange(5, 10)));
  cout << "TEST 5.1 OK" << endl
       << endl
       << endl;
  a = CRange(5, 10);
  assert(a.Includes(5));
  cout << "TEST 5.2 OK" << endl
       << endl
       << endl;
  assert(a.Includes(10));
  cout << "TEST 5.3 OK" << endl
       << endl
       << endl;
  assert(!a.Includes(4));
  cout << "TEST 5.4 OK" << endl
       << endl
       << endl;
  assert(!a.Includes(11));
  cout << "TEST 5.5 OK" << endl
       << endl
       << endl;
  assert(a.Includes(CRange(5, 10)));
  cout << "TEST 5.4 OK" << endl
       << endl
       << endl;
  assert(!a.Includes(CRange(4, 10)));
  cout << "TEST 5.5 OK" << endl
       << endl
       << endl;
  assert(!a.Includes(CRange(5, 11)));
  cout << "TEST 5.6 OK" << endl
       << endl
       << endl;
}
void TST9()
{
  CRangeList a = CRange(10, 20) + CRange(0, 9) + CRange(21, 30);
  cout << "a: " << a << endl;
  assert(toString(a) == "{<0..30>}");
  cout << "TEST 4.1 OK" << endl
       << endl
       << endl;
  a = CRange(10, 20) + CRange(0, 8) + CRange(22, 30);
  cout << "a: " << a << endl;
  assert(toString(a) == "{<0..8>,<10..20>,<22..30>}");
  cout << "TEST 4.2 OK" << endl
       << endl
       << endl;
  a = CRange(10, 20) + CRange(22, 30) + CRange(0, 50);
  cout << "a: " << a << endl;
  assert(toString(a) == "{<0..50>}");
  cout << "TEST 4.3 OK" << endl
       << endl
       << endl;
  a -= CRange(-5, 5) + CRange(25, 35) + CRange(45, 55);
  cout << "a: " << a << endl;
  assert(toString(a) == "{<6..24>,<36..44>}");
  cout << "TEST 4.4 OK" << endl
       << endl
       << endl;
  CRangeList b;
  b = CRange(0, 0);
  b -= CRange(0, 0);
  cout << "b: " << b << endl;
  assert(toString(b) == "{}");
  cout << "TEST 4.5 OK" << endl
       << endl
       << endl;
  b -= CRange(0, 10);
  cout << "b: " << b << endl;
  assert(toString(b) == "{}");
  cout << "TEST 4.6 OK" << endl
       << endl
       << endl;
  b += CRange(25, 100);
  cout << "b: " << b << endl;
  assert(toString(b) == "{<25..100>}");
  cout << "TEST 4.7 OK" << endl
       << endl
       << endl;
  b -= CRange(25, 25);
  cout << "b: " << b << endl;
  assert(toString(b) == "{<26..100>}");
  cout << "TEST 4.7 OK" << endl
       << endl
       << endl;
  b += CRange(1000, 1200);
  b -= CRange(1000, 1000);
  cout << "b: " << b << endl;
  assert(toString(b) == "{<26..100>,<1001..1200>}");
  cout << "TEST 4.8 OK" << endl
       << endl
       << endl;
  b -= CRange(1200, 1200);
  cout << "b: " << b << endl;
  assert(toString(b) == "{<26..100>,<1001..1199>}");
  cout << "TEST 4.9 OK" << endl
       << endl
       << endl;
  b += CRange(30, 1100);
  cout << "b: " << b << endl;
  assert(toString(b) == "{<26..1199>}");
  cout << "TEST 4.10 OK" << endl
       << endl
       << endl;
  b -= CRange(30, 1100);
  cout << "b: " << b << endl;
  assert(toString(b) == "{<26..29>,<1101..1199>}");
  cout << "TEST 4.11 OK" << endl
       << endl
       << endl;
}
void TST10()
{
  CRangeList a, b;
  a -= CRange(5, 10);
  assert(!a.Includes(5));
  cout << "TEST 2.1 OK" << endl
       << endl
       << endl;
  assert(!a.Includes(CRange(5, 10)));
  cout << "TEST 2.2 OK" << endl
       << endl
       << endl;
  a += b;
  a = CRange(LLONG_MIN, LLONG_MAX);
  assert(a.Includes(5));
  assert(a.Includes(LLONG_MIN));
  assert(a.Includes(LLONG_MAX));
  cout << "TEST 2.5 OK" << endl
       << endl
       << endl;
  cout << a << endl;
  a -= CRange(LLONG_MIN, 0);
  cout << a << endl;
  assert(a.Includes(5));
  assert(!a.Includes(-5));
  cout << "TEST 2.7 OK" << endl
       << endl
       << endl;
  a = CRange(LLONG_MIN, LLONG_MAX);
  a += CRange(LLONG_MIN, LLONG_MAX);
  assert(a.Includes(LLONG_MIN));
  assert(a.Includes(LLONG_MAX));
  cout << "TEST 2.9 OK" << endl
       << endl
       << endl;
  cout << "odebrání LLONG_MIN" << endl;
  cout << a << endl;
  a -= CRange(LLONG_MIN, LLONG_MIN);
  cout << a << endl;
  assert(!a.Includes(LLONG_MIN));
  cout << "TEST 2.10 OK" << endl
       << endl
       << endl;
  a += CRange(LLONG_MIN, LLONG_MIN);
  cout << a << endl;
  assert(a.Includes(LLONG_MIN));
  cout << "TEST 2.11 OK" << endl
       << endl
       << endl;
  a -= CRange(LLONG_MAX, LLONG_MAX);
  cout << a << endl;
  assert(!a.Includes(LLONG_MAX));
  cout << "TEST 2.12 OK" << endl
       << endl
       << endl;
  a += CRange(LLONG_MAX, LLONG_MAX);
  cout << a << endl;
  assert(a.Includes(LLONG_MAX));
  cout << "TEST 2.13 OK" << endl
       << endl
       << endl;
}
int main(void)
{
  //TST();
  CRangeList a, b, c;
  assert(sizeof(CRange) <= 2 * sizeof(long long));
  c -= CRange(LLONG_MIN, LLONG_MAX);
  /*
  for (int i = 0; i < 10000; i++)
    c += CRange(3 * i, 3 * i + 1);
  c += CRange(25, 100);
  c += CRange(225, 300);
  c += CRange(335, LLONG_MAX);
  c += CRange(LLONG_MIN, LLONG_MAX);
  cout << toString(c) << endl;
*/
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
  a = CRange(5, 10);
  a += CRange(25, 100);
  assert(toString(a) == "{<5..10>,<25..100>}");
  a += CRange(-5, 0);
  a += CRange(10, 50);
  assert(toString(a) == "{<-5..0>,<5..100>}");
  a += CRange(101, 105) + CRange(120, 150) + CRange(160, 180) + CRange(190, 210);

  assert(toString(a) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}");
  a += CRange(106, 119) + CRange(152, 158);
  assert(toString(a) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}");
  a += CRange(-3, 170);

  a += CRange(-30, 1000);

  assert(toString(a) == "{<-30..1000>}");
  b = CRange(-500, -300) + CRange(2000, 3000) + CRange(700, 1001);
  a += b;

  assert(toString(a) == "{<-500..-300>,<-30..1001>,<2000..3000>}");

  a -= CRange(-400, -400);
  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}");

  a -= CRange(10, 20) + CRange(900, 2500) + CRange(30, 40) + CRange(10000, 20000);

  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  try
  {
    a += CRange(15, 18) + CRange(10, 0) + CRange(35, 38);
    assert("Exception not thrown" == NULL);
  }
  catch (const InvalidRangeException &e)
  {
  }
  catch (...)
  {
    assert("Invalid exception thrown" == NULL);
  }
  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  b = a;
  cout << endl
       << endl;
  cout << endl
       << endl;
  cout << toString(b) << endl;
  assert(a == b);
  assert(!(a != b));
  b += CRange(2600, 2700);
  cout << endl
       << endl;
  cout << endl
       << endl;
  cout << toString(b) << endl;
  cout << endl
       << endl;
  cout << endl
       << endl;
  assert(toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  assert(a == b);
  assert(!(a != b));
  b += CRange(15, 15);
  assert(toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}");
  assert(!(a == b));
  assert(a != b);

  assert(b.Includes(15));
  assert(b.Includes(2900));
  assert(b.Includes(CRange(15, 15)));
  assert(b.Includes(CRange(-350, -350)));
  assert(b.Includes(CRange(100, 200)));
  assert(!b.Includes(CRange(800, 900)));
  assert(!b.Includes(CRange(-1000, -450)));
  assert(!b.Includes(CRange(0, 500)));
  assert(!b.Includes(CRange(-900, -900)));
  a += CRange(-10000, 10000) + CRange(10000000, 1000000000);
  assert(toString(a) == "{<-10000..10000>,<10000000..1000000000>}");

  b += a;
  assert(toString(b) == "{<-10000..10000>,<10000000..1000000000>}");
  b -= a;
  assert(toString(b) == "{}");
  b += CRange(0, 100) + CRange(200, 300) - CRange(150, 250) + CRange(160, 180) - CRange(170, 170);
  assert(toString(b) == "{<0..100>,<160..169>,<171..180>,<251..300>}");

  b = CRange(0, 100) + CRange(200, 300) - CRange(150, 250) + CRange(160, 180) - CRange(170, 170);
  cout << toString(b) << endl;
  b -= CRange(10, 90) - CRange(20, 30) - CRange(40, 50) - CRange(60, 90) + CRange(70, 80);

  cout << toString(b) << endl;
  assert(toString(b) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}");

  return 0;
}



