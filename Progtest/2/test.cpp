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


/**
 * @brief Class for holding property information like region, id, city, address and owner
 * 
 */
class CLand {
  public:
    /**
     * @brief Construct a new CLand object
     * 
     * @param r Region
     * @param i ID
     * @param c City
     * @param a Address
     */
    CLand(string r, unsigned i, string c, string a) {
      _region = r;
      _id = i;
      _city = c;
      _address = a;
      _owner = "";
    }

    /**
     * @brief Gets region name
     * 
     * @return string 
     */
    string Region() const{
      return _region;
    }
    
    /**
     * @brief Gets id
     * 
     * @return unsigned 
     */
    unsigned ID() const{
      return _id;
    }

    /**
     * @brief Gets city name
     * 
     * @return string 
     */
    string City() const{
      return _city;
    }

    /**
     * @brief Gets address name
     * 
     * @return string 
     */
    string Address() const{
      return _address;
    }

    /**
     * @brief Gets Owner name
     * 
     * @return string 
     */
    string Owner() const{
      return _owner;
    }

    /**
     * @brief Sets Owner name
     * 
     * @param n New name
     */
    void Set(string n){
      _owner = n;
    }

    /**
     * @brief Compares two properties by city and address names
     * 
     * @param i1 First property
     * @param i2 Second property
     * @return true i1 < i2
     * @return false i2 >= i1
     */
    static bool CompareAddress( const CLand * i1, const CLand * i2) 
    {
      
      return i1->City().compare(i2->City()) ? 
      i1->City().compare(i2->City()) < 0 :
      i1->Address().compare(i2->Address()) < 0;

    }

    /**
     * @brief Compares two properties by region and id names
     * 
     * @param i1 First property
     * @param i2 Second property
     * @return true i1 < i2
     * @return false i2 >= i1
     */
    static bool CompareRegion(const CLand * i1, const CLand * i2)
    { 
      return i1->Region().compare(i2->Region()) ? 
      i1->Region().compare(i2->Region()) < 0 :
      i1->ID() < i2->ID();
    }

  private:
    string _region;
    unsigned _id;
    string _city;
    string _address;
    string _owner;
};

/**
 * @brief Class for Owner which contains his owned properties and name 
 * 
 */
class COwner {
  private:
    vector<CLand *> _lands;
    string _name;
  public:
    /**
     * @brief Construct a new COwner object
     * 
     * @param n Name of owner
     */
    COwner(string n){
      _name = n;
    }

    /**
     * @brief Set the Ownership of specific property
     * 
     * @param land Property to own
     */
    void SetOwnership(CLand * land){
      _lands.insert(_lands.end(),land);
    }

    /**
     * @brief Get the count of his property
     * 
     * @return int Properties count
     */
    int GetCount() const{
      return _lands.size();
    }

    /**
     * @brief Removes ownership of specific property
     * 
     * @param land Property to remove
     */
    void RemoveOwnership(CLand * land){
      for(size_t i = 0; i < _lands.size(); i++)
        if(_lands.at(i) == land){
          _lands.erase(_lands.begin() + i);
          break;
        }
    }

    /**
     * @brief Get the name of owner
     * 
     * @return string 
     */
    string GetName() const{
      return _name;
    }

    /**
     * @brief Get owned properties
     * 
     * @return vector< CLand *>  
     */
    vector< CLand *> GetLands() const{
      return _lands;
    }

    /**
     * @brief Compares two owners by name
     * 
     * @param i1 First owner
     * @param i2 Second owner
     * @return true i1 < i2
     * @return false i2 >= i1
     */
    static bool Compare(const COwner * i1, const COwner * i2) 
    { 
      int t = i1 -> GetName().compare( i2 -> GetName());
      return (t <= 0); 
    }
};

/**
 * @brief Iterator class for specific properties
 * 
 */
class CIterator {
  public:
    /**
     * @brief Construct a new CIterator object
     * 
     */
    CIterator(){}

    /**
     * @brief Construct a new CIterator object with specific properties
     * 
     * @param vec Specific properties
     */
    CIterator(const vector<CLand * > & vec){
      _land = vec;
    }

    /**
     * @brief Checks if iterator is at end of his properties
     * 
     * @return true No properties left 
     * @return false Some properties left
     */
    bool AtEnd(void) const {
      return (_land.size() == i);
    }

    /**
     * @brief Changes position to next element
     * 
     */
    void Next(void) {
      i++;
      return;
    }

    /**
     * @brief Gets city of current property
     * 
     * @return string 
     */
    string City(void) const {
      return _land.at(i) -> City();
    }

    /**
     * @brief Gets address of current property
     * 
     * @return string 
     */
    string Addr(void) const {
      return _land.at(i) -> Address();
    }

    /**
     * @brief Gets region of current property
     * 
     * @return string 
     */
    string Region(void) const {
      return _land.at(i) -> Region();
    }

    /**
     * @brief Gets id of current property
     * 
     * @return unsigned 
     */
    unsigned ID(void) const {
      return _land.at(i) -> ID();
    }

    /**
     * @brief Gets owner name of current property
     * 
     * @return string 
     */
    string Owner(void) const {
      return _land.at(i)  -> Owner();
    }
    
  private:
    unsigned i = 0;
    vector<CLand *> _land;
};

/**
 * @brief Land register for storing properties and their owners
 * 
 */
class CLandRegister {
  private:
    vector<CLand *> _landVector;
    vector<CLand *> _cityVector;
    vector<CLand *> _regionVector;
    vector<COwner *> _owners;

  public:
    /**
     * @brief Add the new property to list if possible
     * 
     * @param city 
     * @param addr 
     * @param region 
     * @param id 
     * @return true Property was added
     * @return false Property was inside list already
     */
    bool Add(const string & city, const string & addr, const string & region, unsigned int id) {
      COwner * co;
      if(_owners.size() == 0){
        co = new COwner("");
        _owners.push_back(co);
      }else{
        co = _owners.at(GetOwnerIndex(""));
      }
      CLand * cl = new CLand(region, id, city, addr);
      
      if(_landVector.size() == 0)
      {
        _landVector.push_back(cl); 
        _cityVector.push_back(cl); 
        _regionVector.push_back(cl); 
        co -> SetOwnership(cl);
        return true;
      }else{
        auto it = lower_bound(_cityVector.begin(), _cityVector.end(), cl, CLand::CompareAddress);
        unsigned long int indexCity = it - _cityVector.begin();
        it = lower_bound(_regionVector.begin(), _regionVector.end(), cl, CLand::CompareRegion);
        unsigned long int indexRegion = it - _regionVector.begin();

        if(_cityVector.size() == indexCity || _cityVector[indexCity] -> Address().compare(cl -> Address()) != 0 || _cityVector[indexCity] -> City().compare(cl -> City()) != 0){
            if(_regionVector.size() == indexRegion || _regionVector[indexRegion] -> Region().compare(cl -> Region()) != 0 || _regionVector[indexRegion] -> ID() != cl -> ID()){

              _landVector.push_back(cl); 
              _cityVector.insert(_cityVector.begin() + indexCity, cl); 
              _regionVector.insert(_regionVector.begin() + indexRegion, cl); 
              co -> SetOwnership(cl);
              return true;
            }else{
              delete cl;
              return false;
            }
        }else{
          delete cl;
          return false;
        }
      }      
    }

    /**
     * @brief Deletes property from list identified by city and addr 
     * 
     * @param city 
     * @param addr 
     * @return true Property was deleted
     * @return false Property was not present
     */
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
    }

    /**
     * @brief Deletes property from list identified by region and id 
     * 
     * @param region 
     * @param id 
     * @return true Property was deleted
     * @return false Property was not present
     */
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
    }

    /**
     * @brief Get the owner of property identified by city and addr
     * 
     * @param city 
     * @param addr 
     * @param owner Sets owner to found owner
     * @return true Owner was found
     * @return false Owner wasn't found
     */
    bool GetOwner(const string & city, const string & addr, string & owner) const {
      int i = BinarySearchAddress(_cityVector, addr, city);
      if( i == -1)
        return false;
      owner = _cityVector.at(i) -> Owner();   
      return true;
    }

    /**
     * @brief Get the owner of property identified by id and region
     * 
     * @param region 
     * @param id 
     * @param owner Sets owner to found owner
     * @return true Owner was found
     * @return false Owner wasn't found
     */
    bool GetOwner(const string & region, unsigned int id, string & owner) const {
      int i = BinarySearchAddress(_regionVector, region, id);
      if( i == -1)
        return false;
      owner = _regionVector.at(i) -> Owner();   
      return true;
    }

    /**
     * @brief Sets owner
     * 
     * @param city 
     * @param addr 
     * @param owner 
     * @return true 
     * @return false 
     */
    bool NewOwner(const string & city, const string & addr, const string & owner) { 
      int i = BinarySearchAddress(_cityVector, addr, city);
      string nam = owner;
      transform(nam.begin(), nam.end(), nam.begin(), ::tolower); 
      if(i != -1){
        int own = GetOwnerIndex(nam);
        COwner * co;
        if(own == -1){
          co = new COwner(nam);
          auto it = lower_bound( _owners.begin(), _owners.end(), co, COwner::Compare);
          _owners.insert(it, co);
        }
        else
          co = _owners.at(own);
        
        int old = GetOwnerIndex(_cityVector.at(i) -> Owner());
        if(own == old)
          return false;
        _owners.at(old) -> RemoveOwnership( _cityVector.at(i));
        _cityVector.at(i) -> Set(owner);
        co -> SetOwnership(_cityVector.at(i));
        return true;
      }
      return false;
    }

    /**
     * @brief Sets owner
     * 
     * @param region 
     * @param id 
     * @param owner 
     * @return true 
     * @return false 
     */
    bool NewOwner(const string & region, unsigned int id, const string & owner) { 
      int i = BinarySearchAddress(_regionVector, region, id);
      cout << i<< endl;
      string nam = owner;
      transform(nam.begin(), nam.end(), nam.begin(), ::tolower); 
      if(i != -1){
        int own = GetOwnerIndex(nam);
        COwner * co;
        if(own == -1){
          co = new COwner(nam);
          auto it = lower_bound( _owners.begin(), _owners.end(), co, COwner::Compare);
          _owners.insert(it, co);
        }
        else
          co = _owners.at(own);
        
        int old = GetOwnerIndex(_regionVector.at(i) -> Owner());
        if(own == old)
          return false;
        _owners.at(old) -> RemoveOwnership( _regionVector.at(i));
        _regionVector.at(i) -> Set(owner);
        co -> SetOwnership(_regionVector.at(i));
        return true;
      }
      return false;
    }

    /**
     * @brief Binary search for specific property
     * 
     * @param l 
     * @param region 
     * @return int 
     */
    int BinarySearchAddress(const vector<CLand *> & l, const CLand * region)const{
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = l.size()-1;

      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        int a = region -> Address().compare(l.at(guess) -> Address());
        int c = region -> City().compare(l.at(guess) -> City());
        int r =  region -> Region().compare(l.at(guess) -> Region());
        if ((a==0 &&  c == 0)|| (region -> ID() == l.at(guess) -> ID() && r == 0)){
          return guess;
        } else if (a > 0) {
          min = guess + 1;
        } else if(a < 0){
          max = guess - 1;
        }else if (c > 0) {
          min = guess + 1;
        } else{
          max = guess - 1;
        }
      }
      return -1;
    }
    
    /**
     * @brief Binary search for land identified by addr and city
     * 
     * @param l 
     * @param addr 
     * @param city 
     * @return int 
     */
    int BinarySearchAddress(const vector<CLand *> & l, const string & addr, const string & city)const{
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = l.size()-1;

      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        int a = addr.compare(l.at(guess) -> Address()); 
        int c = city.compare(l.at(guess) -> City());
        if (a == 0 && c == 0){
          return guess;
        }else if (c > 0) {
          min = guess + 1;
        } else if(c < 0){
          max = guess - 1;
        } else if (a > 0) {
          min = guess + 1;
        } else {
          max = guess - 1;
        }
      }
      return -1;
    }
    
    /**
     * @brief Binary search for land identified by region and id
     * 
     * @param l 
     * @param region 
     * @param id 
     * @return int 
     */
    int BinarySearchAddress(const vector<CLand *> & l, const string & region, const unsigned int & id)const{
      int min = 0;
      int max = 0; 
      int guess = 0;
      max = l.size()-1;

      while (min <= max) 
      {
        guess = (int)(((max + min) / 2) + 0.5);
        int r = region.compare(l.at(guess) -> Region());
        if (id == l.at(guess) -> ID() && r == 0){
          return guess;
        } else if (r > 0) {
          min = guess + 1;
        } else if(r < 0){
          max = guess - 1;
        }else if (l.at(guess) -> ID() < id) {
          min = guess + 1;
        } else {
          max = guess - 1;
        }
      }
      return -1;
    }

    /**
     * @brief Gets cound of properties from specific owner
     * 
     * @param owner 
     * @return unsigned 
     */
    unsigned Count(const string & owner) const {
      string temp = owner;
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower); 
      int own = GetOwnerIndex(temp);
      if(own == -1)
        return 0;
      
      return _owners.at(own) -> GetCount();;
    }

    /**
     * @brief Creates iterator from address
     * 
     * @return CIterator 
     */
    CIterator ListByAddr(void) const {   
      CIterator cit = CIterator(_cityVector);
      return cit;
    }

    /**
     * @brief Get the Owner Index object
     * 
     * @param owner 
     * @return int 
     */
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
        if (tmp.compare(nam) == 0) 
        {
          return guess;
        } else if (tmp.compare(nam) > 0) {
          min = guess + 1;
        } else {
          max = guess - 1;
        }
      }
      return -1;
    }

    /**
     * @brief Creates iterator for specific owner
     * 
     * @param owner 
     * @return CIterator 
     */
    CIterator ListByOwner(const string & owner) const {
      if(GetOwnerIndex(owner) == -1)
        return CIterator();
      return CIterator(_owners.at(GetOwnerIndex(owner)) -> GetLands());
    }
    
    /**
     * @brief Print method for testing
     * 
     */
    void Print(){
      cout << "--------" << endl;
      for(size_t i = 0; i < _landVector.size(); i++){
        cout << setw(10) << _landVector.at(i) -> City() << setw(10) << _landVector.at(i) -> Address() <<setw(10) << _landVector.at(i) -> Region() <<setw(10) << _landVector.at(i) -> ID() <<setw(5) << _landVector.at(i) -> Owner()<< endl;
      }
      cout << "--------" << endl;
      for(size_t i = 0; i < _cityVector.size(); i++){
        cout << setw(10) << _cityVector.at(i) -> City() << setw(10) << _cityVector.at(i) -> Address() <<setw(10) << _cityVector.at(i) -> Region() <<setw(10) << _cityVector.at(i) -> ID() <<setw(5) << _cityVector.at(i) ->Owner()<< endl;
      }
      cout << "--------" << endl;
      for(size_t i = 0; i < _regionVector.size(); i++){
        cout << setw(10) << _regionVector.at(i) -> City() << setw(10) << _regionVector.at(i) -> Address() <<setw(10) << _regionVector.at(i) -> Region() <<setw(10) << _regionVector.at(i) -> ID()<<setw(5) << _regionVector.at(i) ->Owner()<< endl;
      }      
    }

    /**
     * @brief Destroy the CLandRegister object
     * 
     */
    ~CLandRegister(){
      for ( auto p : _landVector )
        delete p;
      for ( auto p : _owners )
        delete p;
    }
};

#ifndef __PROGTEST__

static void test0(void) {
  CLandRegister x;
  string owner;

  //assert(x.Add("prague", "Thakurova", "Dejvice", 12346));
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

  assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
  assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
  assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
  assert ( x . Add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
  assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );

  x.Print();
  CIterator i0 = x.ListByAddr();
  cout << i0.Addr() << endl;
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
  cout << x.Count("") << endl;
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

  x.Print();

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
  assert(!x.NewOwner("Dejvice", 12345, "CVuT"));
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
  
  assert(x.NewOwner ("Dejvice", 12345, "Mazbunjiqbba" ));
  assert(!x.NewOwner ("Dejvice", 12345, "Mazbunjiqbba" ));
}

int main(void) {
  test0();
  test1();
  return 0;
}
#endif /* __PROGTEST__ */