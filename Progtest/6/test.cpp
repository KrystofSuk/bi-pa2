#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */

struct CPart
{
protected:
  int _size;
  bool _last;
  bool _totalLast;
public:
  CPart(const int &s)
  {
    _last = true;
    _size = s;
    _totalLast = false;
  }
  void Set(bool t){
    _last = t;
  }
  virtual CPart * Clone () const = 0; 
  virtual void Print(ostream & os, string sep) const = 0;
  friend ostream &operator<<(ostream &os, const CPart &part)
  {
    part.Print(os, "");
    return os;
  }
  virtual ~CPart(){};
};

class CComputer
{
private:
  string _name;
  vector<string> _ips;
  vector<CPart *> _parts;
  bool _last;

public:
  CComputer(const string &n)
  {
    _name = n;
    _last = true;
  }

  void Set(bool t){
    _last = t;
  }

  CComputer(const CComputer& f) {
    _parts.clear();
    _ips.clear();
    for (size_t i = 0; i < f._parts.size(); i++)
    {
      CPart * n = f._parts.at(i)->Clone(); 
      _parts.push_back(n);
    }
    for (size_t i = 0; i < f._ips.size(); i++)
    {
      _ips.push_back(f._ips.at(i));
    }
    _last = f._last;
    _name = f._name;
  }   

  CComputer& operator=(const CComputer& f)
  {
      if (this != &f) { 
        for (auto it = begin(_parts); it != end(_parts); ++it)
        {
          delete *it;
        }
        _parts.clear();
        _ips.clear();
        for (size_t i = 0; i < f._parts.size(); i++)
        {
          CPart * n = f._parts.at(i)->Clone(); 
          _parts.push_back(n);
        }
        for (size_t i = 0; i < f._ips.size(); i++)
        {
          _ips.push_back(f._ips.at(i));
        }
        _last = f._last;
        _name = f._name;
      }
      return *this;
  }

  CComputer & AddComponent(const CPart & p)
  {
    if(_parts.size() > 0){
      _parts.at(_parts.size()-1) -> Set(false);
    }
    CPart * n = p.Clone();
    _parts.push_back(n);
    return *this;
  }

  CComputer & AddAddress(const string &a)
  {
    _ips.push_back(a);
    return *this;
  }

  friend bool operator==(const CComputer &lhs, const CComputer &rhs)
  {
    return lhs._name == rhs._name;
  }

  void Print(ostream &os, string const & tmp) const{
    os << tmp << "Host: " << _name << endl; 
    if(tmp == "+-"){
      for(size_t i = 0; i < _ips.size(); i++)
        os << "| +-" << _ips.at(i) << endl; 
      for(size_t i = 0; i <  _parts.size(); i++){
        if(i < _parts.size() -1){
          _parts.at(i) -> Print(os, "| +-");
        }else{
          _parts.at(i) -> Print(os, "| \\-");
        }
      }
    }else{
      for(size_t i = 0; i < _ips.size(); i++)
        os << "  +-" << _ips.at(i) << endl; 
      for(size_t i = 0; i <  _parts.size(); i++){
        if(i < _parts.size() -1){
          _parts.at(i) -> Print(os, "  +-");
        }else{
          _parts.at(i) -> Print(os, "  \\-");
        }
      }

    }
  }

  friend ostream &operator<<(ostream &os, const CComputer &computer)
  {    
    os << "Host: " << computer._name << endl; 
    for(size_t i = 0; i < computer._ips.size(); i++)
      os << "+-" <<computer._ips.at(i) << endl; 
    for(size_t i = 0; i < computer._parts.size(); i++){
      if(i < computer._parts.size() -1){
        computer._parts.at(i) -> Print(os, "+-");
      }else{
        computer._parts.at(i) -> Print(os, "\\-");
      }
    }
    return os;
  }

  ~CComputer(){
    for (auto it = begin(_parts); it != end(_parts); ++it)
    {
      delete *it;
    }
  }
};

class CNetwork
{
private:
  string _name;
  vector<CComputer> _comps;

public:
  CNetwork(const string &n)
  {
    _name = n;
  }

  CNetwork &AddComputer(const CComputer &comp)
  {
    if(_comps.size() > 0){
      _comps.at(_comps.size()-1).Set(false);
    }
    _comps.push_back(comp);
    return *this;
  }

  CComputer *FindComputer(const string &n)
  {
    auto it = find(_comps.begin(), _comps.end(), CComputer(n));
    if (it != _comps.end())
      return &(*it);
    else
      return NULL;
  }

  friend ostream &operator<<(ostream &os, const CNetwork &network)
  {
    os << "Network: " << network._name << endl;
    for(size_t i = 0; i < network._comps.size(); i++){
      if(i < network._comps.size() - 1){
        network._comps.at(i).Print(os, "+-");
      }else{
        network._comps.at(i).Print(os, "\\-");
      }
    }
    return os;
  }

  ~CNetwork(){
  }
};

class CCPU : public CPart
{
private:
  int _freq;

public:
  CCPU(const int &s, const int &f) : CPart(s)
  {
    _freq = f;
  }
  void Print(ostream &os, string sep) const{
    os << sep << "CPU, " << _size << " cores @ " << _freq << "MHz" << endl;
  }
  CCPU * Clone () const{
    return new CCPU (*this);
  }
  ~CCPU(){

  }
};
class CMemory : public CPart
{
public:
  CMemory(const int &s) : CPart(s) {}
  void Print(ostream &os, string sep) const{
    os << sep << "Memory, " << _size << " MiB" << endl;
  }
  CMemory * Clone () const{
    return new CMemory (*this);
  }
  ~CMemory(){

  }
};
struct CPartition : public CPart
{
private:
  string _name;

public:
  CPartition(const int &s, const string &n) : CPart(s)
  {
    _name = n;
  }
  void Print(ostream &os, string sep) const{
    os << sep << ": " << _size << " GiB, " << _name  << endl;
  }
  CPartition * Clone () const{
    return new CPartition (*this);
  }
  ~CPartition(){

  }
};
class CDisk : public CPart
{
public:
  enum Type
  {
    MAGNETIC,
    SSD
  };
  CDisk(const Type &tpe, const int &s) : CPart(s)
  {
    _type = tpe;
  }
  CDisk &AddPartition(const int &s, const string &n)
  {
    _parts.push_back(CPartition(s, n));
    return *this;
  }
  void Print(ostream &os, string sep) const{
    string typ = "";
    if(_type == MAGNETIC)
      typ = "HDD";
    if(_type == SSD)
      typ = "SSD";
    os << sep << typ << ", " << _size << " GiB" << endl;
    if(sep == "+-"){
      for(size_t i = 0; i < _parts.size(); i++){
        os << "| ";
        if(i < _parts.size() -1){
          stringstream ss;
          ss << "+-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }else{
          stringstream ss;
          ss << "\\-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }
      }
    }
    if(sep == "\\-"){
      for(size_t i = 0; i < _parts.size(); i++){
        os << "  ";
        if(i < _parts.size() -1){
          stringstream ss;
          ss << "+-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }else{
          stringstream ss;
          ss << "\\-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }
      }
    }
    if(sep == "| +-"){
      for(size_t i = 0; i < _parts.size(); i++){
        os << "| | ";
        if(i < _parts.size() -1){
          stringstream ss;
          ss << "+-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }else{
          stringstream ss;
          ss << "\\-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }
      }
    }
    if(sep == "| \\-"){
      for(size_t i = 0; i < _parts.size(); i++){
        os << "|   ";
        if(i < _parts.size() -1){
          stringstream ss;
          ss << "+-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }else{
          stringstream ss;
          ss << "\\-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }
      }
    }
    if(sep == "  +-"){
      for(size_t i = 0; i < _parts.size(); i++){
        os << "  | ";
        if(i < _parts.size() -1){
          stringstream ss;
          ss << "+-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }else{
          stringstream ss;
          ss << "\\-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }
      }
    }
    if(sep == "  \\-"){
      for(size_t i = 0; i < _parts.size(); i++){
        os << "    ";
        if(i < _parts.size() -1){
          stringstream ss;
          ss << "+-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }else{
          stringstream ss;
          ss << "\\-[" << i << "]";
          _parts.at(i).Print(os, ss.str());
        }
      }
    }
  }
  CDisk * Clone () const{
    return new CDisk (*this);
  }
  ~CDisk(){

  }

private:
  vector<CPartition> _parts;
  Type _type;
};

#ifndef __PROGTEST__
template <typename _T>
string toString(const _T &x)
{
  ostringstream oss;
  oss << x;
  return oss.str();
}

int main(void)
{
  cout << "------" << endl;
  CNetwork n("FIT network");
  n.AddComputer(
       CComputer("progtest.fit.cvut.cz").AddAddress("147.32.232.142").AddComponent(CCPU(8, 2400)).AddComponent(CCPU(8, 1200)).AddComponent(CDisk(CDisk::MAGNETIC, 1500).AddPartition(50, "/").AddPartition(5, "/boot").AddPartition(1000, "/var")).AddComponent(CDisk(CDisk::SSD, 60).AddPartition(60, "/data")).AddComponent(CMemory(2000)).AddComponent(CMemory(2000)))
      .AddComputer(
          CComputer("edux.fit.cvut.cz").AddAddress("147.32.232.158").AddComponent(CCPU(4, 1600)).AddComponent(CMemory(4000)).AddComponent(CDisk(CDisk::MAGNETIC, 2000).AddPartition(100, "/").AddPartition(1900, "/data")))
      .AddComputer(
          CComputer("imap.fit.cvut.cz").AddAddress("147.32.232.238").AddComponent(CCPU(4, 2500)).AddAddress("2001:718:2:2901::238").AddComponent(CMemory(8000)));
  cout << endl << "------" << endl;
  cout << 
         "Network: FIT network\n"
         "+-Host: progtest.fit.cvut.cz\n"
         "| +-147.32.232.142\n"
         "| +-CPU, 8 cores @ 2400MHz\n"
         "| +-CPU, 8 cores @ 1200MHz\n"
         "| +-HDD, 1500 GiB\n"
         "| | +-[0]: 50 GiB, /\n"
         "| | +-[1]: 5 GiB, /boot\n"
         "| | \\-[2]: 1000 GiB, /var\n"
         "| +-SSD, 60 GiB\n"
         "| | \\-[0]: 60 GiB, /data\n"
         "| +-Memory, 2000 MiB\n"
         "| \\-Memory, 2000 MiB\n"
         "+-Host: edux.fit.cvut.cz\n"
         "| +-147.32.232.158\n"
         "| +-CPU, 4 cores @ 1600MHz\n"
         "| +-Memory, 4000 MiB\n"
         "| \\-HDD, 2000 GiB\n"
         "|   +-[0]: 100 GiB, /\n"
         "|   \\-[1]: 1900 GiB, /data\n"
         "\\-Host: imap.fit.cvut.cz\n"
         "  +-147.32.232.238\n"
         "  +-2001:718:2:2901::238\n"
         "  +-CPU, 4 cores @ 2500MHz\n"
         "  \\-Memory, 8000 MiB\n";
  cout << endl;
  cout << endl << "------" << endl;
  cout << toString(n) << endl;
  cout << endl << "------" << endl;
  cout << toString(CComputer("edux.fit.cvut.cz").AddAddress("147.32.232.158").AddComponent(CCPU(4, 1600)).AddComponent(CMemory(4000)).AddComponent(CDisk(CDisk::MAGNETIC, 2000).AddPartition(100, "/").AddPartition(1900, "/data"))) << endl;
  CNetwork x = n;
  auto c = x.FindComputer("imap.fit.cvut.cz");
  cout << endl << "------" << endl;
  cout << toString(*c);
  cout << "------" << endl;
  cout << 
         "Host: imap.fit.cvut.cz\n"
         "+-147.32.232.238\n"
         "+-2001:718:2:2901::238\n"
         "+-CPU, 4 cores @ 2500MHz\n"
         "\\-Memory, 8000 MiB\n";
  assert(toString(n) ==
         "Network: FIT network\n"
         "+-Host: progtest.fit.cvut.cz\n"
         "| +-147.32.232.142\n"
         "| +-CPU, 8 cores @ 2400MHz\n"
         "| +-CPU, 8 cores @ 1200MHz\n"
         "| +-HDD, 1500 GiB\n"
         "| | +-[0]: 50 GiB, /\n"
         "| | +-[1]: 5 GiB, /boot\n"
         "| | \\-[2]: 1000 GiB, /var\n"
         "| +-SSD, 60 GiB\n"
         "| | \\-[0]: 60 GiB, /data\n"
         "| +-Memory, 2000 MiB\n"
         "| \\-Memory, 2000 MiB\n"
         "+-Host: edux.fit.cvut.cz\n"
         "| +-147.32.232.158\n"
         "| +-CPU, 4 cores @ 1600MHz\n"
         "| +-Memory, 4000 MiB\n"
         "| \\-HDD, 2000 GiB\n"
         "|   +-[0]: 100 GiB, /\n"
         "|   \\-[1]: 1900 GiB, /data\n"
         "\\-Host: imap.fit.cvut.cz\n"
         "  +-147.32.232.238\n"
         "  +-2001:718:2:2901::238\n"
         "  +-CPU, 4 cores @ 2500MHz\n"
         "  \\-Memory, 8000 MiB\n");
  assert(toString(*c) ==
         "Host: imap.fit.cvut.cz\n"
         "+-147.32.232.238\n"
         "+-2001:718:2:2901::238\n"
         "+-CPU, 4 cores @ 2500MHz\n"
         "\\-Memory, 8000 MiB\n");
  c->AddComponent(CDisk(CDisk::MAGNETIC, 1000).AddPartition(100, "system").AddPartition(200, "WWW").AddPartition(700, "mail"));
  assert(toString(x) ==
         "Network: FIT network\n"
         "+-Host: progtest.fit.cvut.cz\n"
         "| +-147.32.232.142\n"
         "| +-CPU, 8 cores @ 2400MHz\n"
         "| +-CPU, 8 cores @ 1200MHz\n"
         "| +-HDD, 1500 GiB\n"
         "| | +-[0]: 50 GiB, /\n"
         "| | +-[1]: 5 GiB, /boot\n"
         "| | \\-[2]: 1000 GiB, /var\n"
         "| +-SSD, 60 GiB\n"
         "| | \\-[0]: 60 GiB, /data\n"
         "| +-Memory, 2000 MiB\n"
         "| \\-Memory, 2000 MiB\n"
         "+-Host: edux.fit.cvut.cz\n"
         "| +-147.32.232.158\n"
         "| +-CPU, 4 cores @ 1600MHz\n"
         "| +-Memory, 4000 MiB\n"
         "| \\-HDD, 2000 GiB\n"
         "|   +-[0]: 100 GiB, /\n"
         "|   \\-[1]: 1900 GiB, /data\n"
         "\\-Host: imap.fit.cvut.cz\n"
         "  +-147.32.232.238\n"
         "  +-2001:718:2:2901::238\n"
         "  +-CPU, 4 cores @ 2500MHz\n"
         "  +-Memory, 8000 MiB\n"
         "  \\-HDD, 1000 GiB\n"
         "    +-[0]: 100 GiB, system\n"
         "    +-[1]: 200 GiB, WWW\n"
         "    \\-[2]: 700 GiB, mail\n");
  assert(toString(n) ==
         "Network: FIT network\n"
         "+-Host: progtest.fit.cvut.cz\n"
         "| +-147.32.232.142\n"
         "| +-CPU, 8 cores @ 2400MHz\n"
         "| +-CPU, 8 cores @ 1200MHz\n"
         "| +-HDD, 1500 GiB\n"
         "| | +-[0]: 50 GiB, /\n"
         "| | +-[1]: 5 GiB, /boot\n"
         "| | \\-[2]: 1000 GiB, /var\n"
         "| +-SSD, 60 GiB\n"
         "| | \\-[0]: 60 GiB, /data\n"
         "| +-Memory, 2000 MiB\n"
         "| \\-Memory, 2000 MiB\n"
         "+-Host: edux.fit.cvut.cz\n"
         "| +-147.32.232.158\n"
         "| +-CPU, 4 cores @ 1600MHz\n"
         "| +-Memory, 4000 MiB\n"
         "| \\-HDD, 2000 GiB\n"
         "|   +-[0]: 100 GiB, /\n"
         "|   \\-[1]: 1900 GiB, /data\n"
         "\\-Host: imap.fit.cvut.cz\n"
         "  +-147.32.232.238\n"
         "  +-2001:718:2:2901::238\n"
         "  +-CPU, 4 cores @ 2500MHz\n"
         "  \\-Memory, 8000 MiB\n");


  CComputer c1 = CComputer("cz").AddAddress("147.32.232.158").AddComponent(CCPU(4, 1600)).AddComponent(CMemory(4000)).AddComponent(CDisk(CDisk::MAGNETIC, 2000).AddPartition(100, "/").AddPartition(1900, "/data"));
  CComputer c2("C2");
  c2 = c1;
  
  cout << toString(c2) << endl;
  return 0;
}
#endif /* __PROGTEST__ */
