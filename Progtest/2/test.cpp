#ifndef __PROGTEST__

#include <cstring>

#include <cstdlib>

#include <cstdio>

#include <cctype>

#include <cmath>

#include <cassert>

#include <iostream>

#include <iomanip>

#include <string>

#include <vector>

#include <list>

#include <algorithm>

#include <functional>

#include <memory>

using namespace std;

#endif /* __PROGTEST__ */



class CLand {
  public:
    CLand() {
    };

    CLand(string r, unsigned i, string c, string a) {
      _region = r;
      _id = i;
      _city = c;
      _address = a;
      _owner = "";
    };

    string Region() const{
      return _region;
    };
    unsigned ID() const{
      return _id;
    };
    string City() const{
      return _city;
    };
    string Address() const{
      return _address;
    }; 
    string Owner() const{
      return _owner;
    }; 
    void Set(string n){
      _owner = n;
    };
  private:
    string _region;
    unsigned _id;
    string _city;
    string _address;
    string _owner;
};

class COwner {
  private:
    vector<CLand *> _lands;
    string _name;
    int _count;
  public:
    COwner(string n){
      _name = n;
      _count = 0;
    };
    void SetOwnership(CLand * land){
      _count ++;
      _lands.insert(_lands.end(),land);
    };
    int GetCount() const{
      return _count;
    };
    void RemoveOwnership(CLand * land){
      _count--;
      for(int i = 0; i < _lands.size(); i++)
        if(_lands.at(i) == land){
          _lands.erase(_lands.begin() + i);
          break;
        }
    };
    string GetName() const{
      return _name;
    };
    vector< CLand *> GetLands() const{
      return _lands;
    };
};

class CIterator {
  public:
    CIterator(const vector<CLand * > & vec){
      _land = vec;
    };

    bool AtEnd(void) const {
      return (_land.size() == i);
    };

    void Next(void) {
      i++;
      return;
    };

    string City(void) const {
      return _land.at(i) -> City();
    };

    string Addr(void) const {
      return _land.at(i) -> Address();
    };

    string Region(void) const {
      return _land.at(i) -> Region();
    };

    unsigned ID(void) const {
      return _land.at(i) -> ID();
    };

    string Owner(void) const {
      return _land.at(i)  -> Owner();
    };


  private:
    unsigned i = 0;
    vector<CLand *> _land;
};

bool compareCLandAddress( const CLand * i1, const CLand * i2) 
{ 
  if(i1 -> City() == i2 -> City()){
    return (i1 -> Address() < i2 -> Address());
  }
  return (i1 -> City() < i2 -> City()); 
}

bool compareCLandRegion(const CLand * i1, const CLand * i2) 
{ 
  if(i1 -> Region() == i2 -> Region()){
    return (i1 -> ID() < i2 -> ID());
  }
  return (i1 -> Region() < i2 -> Region()); 
}

bool compareCOwner(const COwner * i1, const COwner * i2) 
{ 
  return (i1 -> GetName() < i2 -> GetName()); 
}


class CLandRegister {
  private:
    vector<CLand *> _landVector;
    vector<CLand *> _cityVector;
    vector<CLand *> _regionVector;
    vector<COwner *> _owners;

  public:
    ~CLandRegister(){
      for ( auto p : _landVector )
        delete p;
      for ( auto p : _owners )
        delete p;
    };
    bool Add(const string & city, const string & addr, const string & region, unsigned int id) {

      COwner * co;
      if(_owners.size() == 0){
        co = new COwner("");
        _owners.push_back(co);
      }else{
        co = _owners.at(GetOwnerIndex(""));
      }
      CLand * cl = new CLand(region, id, city, addr);
      
      if(BinarySearchAddress(_cityVector, cl) != -1){
        delete cl;
        return false;
      }     
      
      auto it1 = lower_bound( _cityVector.begin(), _cityVector.end(), cl, compareCLandAddress);
      auto it2 = lower_bound( _regionVector.begin(), _regionVector.end(), cl, compareCLandRegion);
      _landVector.insert(_landVector.end() + 0, cl); 
      _cityVector.insert(it1, cl); 
      _regionVector.insert(it2, cl); 
      co -> SetOwnership(cl);
      return true;
    };

    bool Del(const string & city, const string & addr) {
      int i = BinarySearchAddress(_cityVector, addr, city);
      if( i == -1)
        return false;
      int old = GetOwnerIndex(_cityVector.at(i) -> Owner());
      _owners.at(old) -> RemoveOwnership( _cityVector.at(i));
      auto it = find (_regionVector.begin(), _regionVector.end(), _cityVector.at(i));
      auto i2 = find (_landVector.begin(), _landVector.end(), _cityVector.at(i));
      _regionVector.erase(it);
      _landVector.erase(i2);
      CLand * rem = _cityVector.at(i);
      _cityVector.erase(_cityVector.begin() + i);
      delete rem;
      return true;
    };

    bool Del(const string & region, unsigned int id) {
      
      int i = BinarySearchAddress(_regionVector, region, id);
      if( i == -1)
        return false;
      int old = GetOwnerIndex(_regionVector.at(i) -> Owner());
      _owners.at(old) -> RemoveOwnership( _regionVector.at(i));
      auto it = find (_cityVector.begin(), _cityVector.end(), _regionVector.at(i));
      auto i2 = find (_landVector.begin(), _landVector.end(), _regionVector.at(i));
      _cityVector.erase(it);
      _landVector.erase(i2);
      CLand * rem = _regionVector.at(i);
      _regionVector.erase(_regionVector.begin() + i);
      delete rem;
      return true;
    };

    bool GetOwner(const string & city, const string & addr, string & owner) const {
      int i = BinarySearchAddress(_cityVector, addr, city);
      if( i == -1)
        return false;
      owner = _cityVector.at(i) -> Owner();   
      return true;
    };

    bool GetOwner(const string & region, unsigned int id, string & owner) const {
      int i = BinarySearchAddress(_regionVector, region, id);
      if( i == -1)
        return false;
      owner = _regionVector.at(i) -> Owner();   
      return true;
    };

    bool NewOwner(const string & city, const string & addr, const string & owner) { 
      int i = BinarySearchAddress(_cityVector, addr, city);
      string nam = owner;
      transform(nam.begin(), nam.end(), nam.begin(), ::tolower); 
      if(i != -1){
        int own = GetOwnerIndex(nam);
        COwner * co;
        if(own == -1){
          co = new COwner(nam);
          auto it = lower_bound( _owners.begin(), _owners.end(), co, compareCOwner);
          _owners.insert(it, co);
        }
        else
          co = _owners.at(own);
        
        int old = GetOwnerIndex(_cityVector.at(i) -> Owner());
        _owners.at(old) -> RemoveOwnership( _cityVector.at(i));
        _cityVector.at(i) -> Set(owner);
        co -> SetOwnership(_cityVector.at(i));
        return true;
      }
      return false;
    };

    bool NewOwner(const string & region, unsigned int id, const string & owner) { 
      int i = BinarySearchAddress(_regionVector, region, id);
      string nam = owner;
      transform(nam.begin(), nam.end(), nam.begin(), ::tolower); 
      if(i != -1){
        int own = GetOwnerIndex(nam);
        COwner * co;
        if(own == -1){
          co = new COwner(nam);
          auto it = lower_bound( _owners.begin(), _owners.end(), co, compareCOwner);
          _owners.insert(it, co);
        }
        else
          co = _owners.at(own);
        
        int old = GetOwnerIndex(_regionVector.at(i) -> Owner());
        _owners.at(old) -> RemoveOwnership( _regionVector.at(i));
        _regionVector.at(i) -> Set(owner);
        co -> SetOwnership(_regionVector.at(i));
        return true;
      }
      return false;
    };

    int BinarySearchAddress(const vector<CLand *> & l, const CLand * region)const{
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = l.size()-1;

      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        if (region -> Address() == l.at(guess) -> Address() && region -> City() == l.at(guess) -> City() && region -> ID() == l.at(guess) -> ID() && region -> Region() == l.at(guess) -> Region()){
          return guess;
        } else if (l.at(guess) -> Address() < region -> Address()) {
          min = guess + 1;
        } else if(l.at(guess) -> Address() > region -> Address()){
          max = guess - 1;
        }else if (l.at(guess) -> City() < region -> City()) {
          min = guess + 1;
        } else{
          max = guess - 1;
        }
      }
      return -1;
    }
    
    int BinarySearchAddress(const vector<CLand *> & l, const string & addr, const string & city)const{
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = l.size()-1;

      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        if (addr == l.at(guess) -> Address() && city == l.at(guess) -> City()){
          return guess;
        }else if (l.at(guess) -> City() < city) {
          min = guess + 1;
        } else if(l.at(guess) -> City() > city){
          max = guess - 1;
        } else if (l.at(guess) -> Address() < addr) {
          min = guess + 1;
        } else {
          max = guess - 1;
        }
      }
      return -1;
    }
    
    int BinarySearchAddress(const vector<CLand *> & l, const string & region, const unsigned int & id)const{
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = l.size()-1;

      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        if (id == l.at(guess) -> ID() && region == l.at(guess) -> Region()){
          return guess;
        } else if (l.at(guess) -> Region() < region) {
          min = guess + 1;
        } else if(l.at(guess) -> Region() > region){
          max = guess - 1;
        }else if (l.at(guess) -> ID() < id) {
          min = guess + 1;
        } else {
          max = guess - 1;
        }
      }
      return -1;
    }

    unsigned Count(const string & owner) const {
      string temp = owner;
      int cnt = 0;
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower); 
      for(unsigned i = 0; i < _owners.size(); i++){
        string name = _owners.at(i) -> GetName();
        transform(name.begin(), name.end(), name.begin(), ::tolower); 
        if(name == temp)
          cnt += _owners.at(i) -> GetCount();
      }
      return cnt;
    };

    CIterator ListByAddr(void) const {   
      CIterator cit = CIterator(_cityVector);
      return cit;
    };


    int GetOwnerIndex(string const & owner)const{
      string tmp = owner;
      transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = _owners.size()-1;
      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        string nam =  _owners.at(guess) -> GetName();
        transform(nam.begin(), nam.end(), nam.begin(), ::tolower);
        if (tmp == nam) 
        {
          return guess;
        } else if (nam < tmp) {
          min = guess + 1;
        } else {
          max = guess - 1;
        }
      }
      return -1;
    };

    CIterator ListByOwner(const string & owner) const {
      if(GetOwnerIndex(owner) == -1)
        return CIterator();
      return CIterator(_owners.at(GetOwnerIndex(owner)) -> GetLands());
    };
    
    void Print(){
      cout << "--------" << endl;
      for(int i = 0; i < _landVector.size(); i++){
        cout << setw(10) << _landVector.at(i) -> City() << setw(10) << _landVector.at(i) -> Address() <<setw(10) << _landVector.at(i) -> Region() <<setw(10) << _landVector.at(i) -> ID() <<setw(5) << _landVector.at(i) -> Owner()<< endl;
      }
      cout << "--------" << endl;
      for(int i = 0; i < 5; i++){
        cout << setw(10) << _cityVector.at(i) -> City() << setw(10) << _cityVector.at(i) -> Address() <<setw(10) << _cityVector.at(i) -> Region() <<setw(10) << _cityVector.at(i) -> ID() <<setw(5) << _cityVector.at(i) ->Owner()<< endl;
      }
      cout << "--------" << endl;
      for(int i = 0; i < 5; i++){
        cout << setw(10) << _regionVector.at(i) -> City() << setw(10) << _regionVector.at(i) -> Address() <<setw(10) << _regionVector.at(i) -> Region() <<setw(10) << _regionVector.at(i) -> ID()<<setw(5) << _regionVector.at(i) ->Owner()<< endl;
      }
      
    };
};

#ifndef __PROGTEST__

static void test0(void) {
  CLandRegister x;
  string owner;

  assert(x.Add("Prague", "Thakurova", "Dejvice", 12345));
  assert(x.Add("Prague", "Evropska", "Vokovice", 12345));
  assert(x.Add("Prague", "Technicka", "Dejvice", 9873));
  assert(x.Add("Plzen", "Evropska", "Plzen mesto", 78901));
  for(int i = 0; i< 10000; i++ )
    x.Add("Liberec", "Evropska", "Librec", i);
  for(int i =00; i< 10000; i++ )
    x.NewOwner("Liberec", "Evropska", "Cvut");
  for(int i =00; i< 10000; i++ )
    x.GetOwner("Liberec", "Evropska", owner);
  for(int i =00; i< 10000000; i++ )
    x.Count("Cvut");
  for(int i =00; i< 10000; i++ )
    x.Del("Liberec", "Evropska");

  x.Add("Liberec", "Evropska", "Librec", 4552);

  x.Print();
  CIterator i0 = x.ListByAddr();
  
  assert(!i0.AtEnd() &&
    i0.City() == "Liberec" &&
    i0.Addr() == "Evropska" &&
    i0.Region() == "Librec" &&
    i0.ID() == 4552 &&
    i0.Owner() == "");
  i0.Next();
  assert(!i0.AtEnd() &&
    i0.City() == "Plzen" &&
    i0.Addr() == "Evropska" &&
    i0.Region() == "Plzen mesto" &&
    i0.ID() == 78901 &&
    i0.Owner() == "");
  i0.Next();
  assert(!i0.AtEnd() &&
    i0.City() == "Prague" &&
    i0.Addr() == "Evropska" &&
    i0.Region() == "Vokovice" &&
    i0.ID() == 12345 &&
    i0.Owner() == "");
  i0.Next();
  assert(!i0.AtEnd() &&
    i0.City() == "Prague" &&
    i0.Addr() == "Technicka" &&
    i0.Region() == "Dejvice" &&
    i0.ID() == 9873 &&
    i0.Owner() == "");
  i0.Next();
  assert(!i0.AtEnd() &&
    i0.City() == "Prague" &&
    i0.Addr() == "Thakurova" &&
    i0.Region() == "Dejvice" &&
    i0.ID() == 12345 &&
    i0.Owner() == "");
  i0.Next();  
  assert(i0.AtEnd());

  x.Print();
  assert(x.Count("") == 5);
  CIterator i1 = x.ListByOwner("");
  assert(!i1.AtEnd() &&
    i1.City() == "Prague" &&
    i1.Addr() == "Thakurova" &&
    i1.Region() == "Dejvice" &&
    i1.ID() == 12345 &&
    i1.Owner() == "");
  i1.Next();
  assert(!i1.AtEnd() &&
    i1.City() == "Prague" &&
    i1.Addr() == "Evropska" &&
    i1.Region() == "Vokovice" &&
    i1.ID() == 12345 &&
    i1.Owner() == "");
  i1.Next();
  assert(!i1.AtEnd() &&
    i1.City() == "Prague" &&
    i1.Addr() == "Technicka" &&
    i1.Region() == "Dejvice" &&
    i1.ID() == 9873 &&
    i1.Owner() == "");
  i1.Next();
  assert(!i1.AtEnd() &&
    i1.City() == "Plzen" &&
    i1.Addr() == "Evropska" &&
    i1.Region() == "Plzen mesto" &&
    i1.ID() == 78901 &&
    i1.Owner() == "");
  i1.Next();
  assert(!i1.AtEnd() &&
    i1.City() == "Liberec" &&
    i1.Addr() == "Evropska" &&
    i1.Region() == "Librec" &&
    i1.ID() == 4552 &&
    i1.Owner() == "");
  i1.Next();
  assert(i1.AtEnd());

  assert(x.Count("CVUT") == 0);
  CIterator i2 = x.ListByOwner("cvut");
  assert(i2.AtEnd());

  assert(x.NewOwner("Prague", "Thakurova", "CVUT"));
  assert(x.NewOwner("Dejvice", 9873, "CVUT"));
  assert(x.NewOwner("Plzen", "Evropska", "Anton Hrabis"));
  assert(x.NewOwner("Librec", 4552, "Cvut"));
  x.GetOwner("Prague", "Thakurova", owner);
  
  x.Print();

  assert(x.GetOwner("Prague", "Thakurova", owner) && owner == "CVUT");
  assert(x.GetOwner("Dejvice", 12345, owner) && owner == "CVUT");
  assert(x.GetOwner("Prague", "Evropska", owner) && owner == "");
  assert(x.GetOwner("Vokovice", 12345, owner) && owner == "");
  assert(x.GetOwner("Prague", "Technicka", owner) && owner == "CVUT");
  assert(x.GetOwner("Dejvice", 9873, owner) && owner == "CVUT");
  assert(x.GetOwner("Plzen", "Evropska", owner) && owner == "Anton Hrabis");
  assert(x.GetOwner("Plzen mesto", 78901, owner) && owner == "Anton Hrabis");
  assert(x.GetOwner("Liberec", "Evropska", owner) && owner == "Cvut");
  assert(x.GetOwner("Librec", 4552, owner) && owner == "Cvut");


  x.Print();


  CIterator i3 = x.ListByAddr();
  assert(!i3.AtEnd() &&
    i3.City() == "Liberec" &&
    i3.Addr() == "Evropska" &&
    i3.Region() == "Librec" &&
    i3.ID() == 4552 &&
    i3.Owner() == "Cvut");
  i3.Next();
  assert(!i3.AtEnd() &&
    i3.City() == "Plzen" &&
    i3.Addr() == "Evropska" &&
    i3.Region() == "Plzen mesto" &&
    i3.ID() == 78901 &&
    i3.Owner() == "Anton Hrabis");
  i3.Next();
  assert(!i3.AtEnd() &&
    i3.City() == "Prague" &&
    i3.Addr() == "Evropska" &&
    i3.Region() == "Vokovice" &&
    i3.ID() == 12345 &&
    i3.Owner() == "");
  i3.Next();
  assert(!i3.AtEnd() &&
    i3.City() == "Prague" &&
    i3.Addr() == "Technicka" &&
    i3.Region() == "Dejvice" &&
    i3.ID() == 9873 &&
    i3.Owner() == "CVUT");
  i3.Next();
  assert(!i3.AtEnd() &&
    i3.City() == "Prague" &&
    i3.Addr() == "Thakurova" &&
    i3.Region() == "Dejvice" &&
    i3.ID() == 12345 &&
    i3.Owner() == "CVUT");
  i3.Next();
  assert(i3.AtEnd());
  assert(x.Count("cvut") == 3);
  CIterator i4 = x.ListByOwner("cVuT");
  cout << i4 . City() << endl;
  assert(!i4.AtEnd() &&
    i4.City() == "Prague" &&
    i4.Addr() == "Thakurova" &&
    i4.Region() == "Dejvice" &&
    i4.ID() == 12345 &&
    i4.Owner() == "CVUT");
  i4.Next();
  assert(!i4.AtEnd() &&
    i4.City() == "Prague" &&
    i4.Addr() == "Technicka" &&
    i4.Region() == "Dejvice" &&
    i4.ID() == 9873 &&
    i4.Owner() == "CVUT");
  i4.Next();
  assert(!i4.AtEnd() &&
    i4.City() == "Liberec" &&
    i4.Addr() == "Evropska" &&
    i4.Region() == "Librec" &&
    i4.ID() == 4552 &&
    i4.Owner() == "Cvut");
  i4.Next();
  assert(i4.AtEnd());

  cout << "/////////" << endl;
  assert(x.NewOwner("Plzen mesto", 78901, "CVut"));
  cout << "/////////" << endl;
  assert(x.Count("CVUT") == 4);
  CIterator i5 = x.ListByOwner("CVUT");
  assert(!i5.AtEnd() &&
    i5.City() == "Prague" &&
    i5.Addr() == "Thakurova" &&
    i5.Region() == "Dejvice" &&
    i5.ID() == 12345 &&
    i5.Owner() == "CVUT");
  i5.Next();
  assert(!i5.AtEnd() &&
    i5.City() == "Prague" &&
    i5.Addr() == "Technicka" &&
    i5.Region() == "Dejvice" &&
    i5.ID() == 9873 &&
    i5.Owner() == "CVUT");
  i5.Next();
  assert(!i5.AtEnd() &&
    i5.City() == "Liberec" &&
    i5.Addr() == "Evropska" &&
    i5.Region() == "Librec" &&
    i5.ID() == 4552 &&
    i5.Owner() == "Cvut");
  i5.Next();
  assert(!i5.AtEnd() &&
    i5.City() == "Plzen" &&
    i5.Addr() == "Evropska" &&
    i5.Region() == "Plzen mesto" &&
    i5.ID() == 78901 &&
    i5.Owner() == "CVut");
  i5.Next();
  assert(i5.AtEnd());

  assert(x.Del("Liberec", "Evropska"));
  assert(x.Del("Plzen mesto", 78901));
  assert(x.Count("cvut") == 2);
  CIterator i6 = x.ListByOwner("cVuT");
  assert(!i6.AtEnd() &&
    i6.City() == "Prague" &&
    i6.Addr() == "Thakurova" &&
    i6.Region() == "Dejvice" &&
    i6.ID() == 12345 &&
    i6.Owner() == "CVUT");
  i6.Next();
  assert(!i6.AtEnd() &&
    i6.City() == "Prague" &&
    i6.Addr() == "Technicka" &&
    i6.Region() == "Dejvice" &&
    i6.ID() == 9873 &&
    i6.Owner() == "CVUT");
  i6.Next();
  assert(i6.AtEnd());

  assert(x.Add("Liberec", "Evropska", "Librec", 4552));
}

static void test1(void) {
  CLandRegister x;
  string owner;

  assert(x.Add("Prague", "Thakurova", "Dejvice", 12345));
  assert(x.Add("Prague", "Evropska", "Vokovice", 12345));
  assert(x.Add("Prague", "Technicka", "Dejvice", 9873));
  assert(!x.Add("Prague", "Technicka", "Hradcany", 7344));
  assert(!x.Add("Brno", "Bozetechova", "Dejvice", 9873));
  assert(!x.GetOwner("Prague", "THAKUROVA", owner));
  assert(!x.GetOwner("Hradcany", 7343, owner));
  CIterator i0 = x.ListByAddr();
  assert(!i0.AtEnd() &&
    i0.City() == "Prague" &&
    i0.Addr() == "Evropska" &&
    i0.Region() == "Vokovice" &&
    i0.ID() == 12345 &&
    i0.Owner() == "");
  i0.Next();
  assert(!i0.AtEnd() &&
    i0.City() == "Prague" &&
    i0.Addr() == "Technicka" &&
    i0.Region() == "Dejvice" &&
    i0.ID() == 9873 &&
    i0.Owner() == "");
  i0.Next();
  assert(!i0.AtEnd() &&
    i0.City() == "Prague" &&
    i0.Addr() == "Thakurova" &&
    i0.Region() == "Dejvice" &&
    i0.ID() == 12345 &&
    i0.Owner() == "");
  i0.Next();
  assert(i0.AtEnd());

  assert(x.NewOwner("Prague", "Thakurova", "CVUT"));
  assert(!x.NewOwner("Prague", "technicka", "CVUT"));
  assert(!x.NewOwner("prague", "Technicka", "CVUT"));
  assert(!x.NewOwner("dejvice", 9873, "CVUT"));
  assert(!x.NewOwner("Dejvice", 9973, "CVUT"));
  assert(!x.NewOwner("Dejvice", 12345, "CVUT"));
  assert(x.Count("CVUT") == 1);
  CIterator i1 = x.ListByOwner("CVUT");
  assert(!i1.AtEnd() &&
    i1.City() == "Prague" &&
    i1.Addr() == "Thakurova" &&
    i1.Region() == "Dejvice" &&
    i1.ID() == 12345 &&
    i1.Owner() == "CVUT");
  i1.Next();
  assert(i1.AtEnd());

  assert(!x.Del("Brno", "Technicka"));
  assert(!x.Del("Karlin", 9873));
  assert(x.Del("Prague", "Technicka"));
  assert(!x.Del("Prague", "Technicka"));
  assert(!x.Del("Dejvice", 9873));
  /*
  */
}

int main(void) {
  test0();
  //test1();
  return 0;
}
#endif /* __PROGTEST__ */