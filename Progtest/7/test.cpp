#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined(__cplusplus) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */

class NoRouteException
{
};

template <typename T>
int doMath(int x, int y)
{
  return 0;
}


template <typename _T, typename _E>
class CRoute
{
private:
  multimap<pair<string, string>, int > _nodes; 
  set<string> _node;
  vector<_E> _paths;
public:
  CRoute(){}
  ~CRoute(){}
  CRoute &Add(const _T & u1, const _T & u2, const _E & h)
  {
    cout << "Adding" << endl;
    _paths.push_back(h);
    _nodes.insert(make_pair(make_pair(u1, u2),_paths.size() - 1));
    _node.insert(u1);
    _node.insert(u2);
    return (*this);
  }
  list<string> Find(_T u1, _T u2, std::function<bool(const _E &)> f = [](const _E &t) {return true;})
  {
    
    for (auto it = _nodes.begin(); it != _nodes.end(); ++it){
      std::cout << it->first.first <<"-"<<it->first.second<< "::" << _paths.at(it->second)  << endl;
    }
    for(auto it = _node.begin(); it != _node.end(); it++)
    {
        cout << *it << endl;
    }


    list<string> t;
    int pred[_node.size()], dist[_node.size()]; 
    list<int> queue;
    bool visited[_node.size()]; 
    for (size_t i = 0; i < _node.size(); i++) { 
        visited[i] = false; 
        dist[i] = 2147483647; 
        pred[i] = -1; 
    }  
    visited[src] = true; 
    dist[src] = 0; 
    queue.push_back(src); 
  
    // standard BFS algorithm 
    while (!queue.empty()) { 
        int u = queue.front(); 
        queue.pop_front(); 
        for (int i = 0; i < adj[u].size(); i++) { 
            if (visited[adj[u][i]] == false) { 
                visited[adj[u][i]] = true; 
                dist[adj[u][i]] = dist[u] + 1; 
                pred[adj[u][i]] = u; 
                queue.push_back(adj[u][i]); 
  
                // We stop BFS when we find 
                // destination. 
                if (adj[u][i] == dest) 
                   return true; 
            } 
        } 
    } 
    return t;
  }
};

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
public:
  CTrain(const string &company,
         int speed)
      : m_Company(company),
        m_Speed(speed)
  {
  }
  //---------------------------------------------------------------------------------------------
  string m_Company;
  int m_Speed;

  
  friend ostream &operator<<(ostream &os,
                             const CTrain &x)
  {
    os << x.m_Company << "/" << x.m_Speed ;
    return os;
  }
};
//=================================================================================================
class TrainFilterCompany
{
public:
  TrainFilterCompany(const set<string> &companies)
      : m_Companies(companies)
  {
  }
  //---------------------------------------------------------------------------------------------
  bool operator()(const CTrain &train) const
  {
    return m_Companies.find(train.m_Company) != m_Companies.end();
  }
  //---------------------------------------------------------------------------------------------
private:
  set<string> m_Companies;
};
//=================================================================================================
class TrainFilterSpeed
{
public:
  TrainFilterSpeed(int min,
                   int max)
      : m_Min(min),
        m_Max(max)
  {
  }
  //---------------------------------------------------------------------------------------------
  bool operator()(const CTrain &train) const
  {
    return train.m_Speed >= m_Min && train.m_Speed <= m_Max;
  }
  //---------------------------------------------------------------------------------------------
private:
  int m_Min;
  int m_Max;
};
//=================================================================================================
bool NurSchnellzug(const CTrain &zug)
{
  return (zug.m_Company == "OBB" || zug.m_Company == "DB") && zug.m_Speed > 100;
}
//=================================================================================================
static string toText(const list<string> &l)
{
  ostringstream oss;

  auto it = l.cbegin();
  oss << *it;
  for (++it; it != l.cend(); ++it)
    oss << " > " << *it;
  return oss.str();
}
//=================================================================================================
int main(void)
{
  CRoute<string, CTrain> lines;

  lines.Add("Berlin", "Prague", CTrain("DB", 120))
      .Add("Berlin", "Prague", CTrain("CD", 80))
      .Add("Berlin", "Dresden", CTrain("DB", 160))
      .Add("Dresden", "Munchen", CTrain("DB", 160))
      .Add("Munchen", "Prague", CTrain("CD", 90))
      .Add("Munchen", "Linz", CTrain("DB", 200))
      .Add("Munchen", "Linz", CTrain("OBB", 90))
      .Add("Linz", "Prague", CTrain("CD", 50))
      .Add("Prague", "Wien", CTrain("CD", 100))
      .Add("Linz", "Wien", CTrain("OBB", 160))
      .Add("Paris", "Marseille", CTrain("SNCF", 300))
      .Add("Paris", "Dresden", CTrain("SNCF", 250));
  list<string> r1 = lines.Find("Berlin", "Linz");
  assert(toText(r1) == "Berlin > Prague > Linz");
  /*

  list<string> r2 = lines.Find("Linz", "Berlin");
  assert(toText(r2) == "Linz > Prague > Berlin");

  list<string> r3 = lines.Find("Wien", "Berlin");
  assert(toText(r3) == "Wien > Prague > Berlin");

  list<string> r4 = lines.Find("Wien", "Berlin", NurSchnellzug);
  assert(toText(r4) == "Wien > Linz > Munchen > Dresden > Berlin");

  list<string> r5 = lines.Find("Wien", "Munchen", TrainFilterCompany(set<string>{"CD", "DB"}));
  assert(toText(r5) == "Wien > Prague > Munchen");

  list<string> r6 = lines.Find("Wien", "Munchen", TrainFilterSpeed(120, 200));
  assert(toText(r6) == "Wien > Linz > Munchen");

  list<string> r7 = lines.Find("Wien", "Munchen", [](const CTrain &x) { return x.m_Company == "CD"; });
  assert(toText(r7) == "Wien > Prague > Munchen");

  list<string> r8 = lines.Find("Munchen", "Munchen");
  assert(toText(r8) == "Munchen");

  list<string> r9 = lines.Find("Marseille", "Prague");
  assert(toText(r9) == "Marseille > Paris > Dresden > Berlin > Prague" || toText(r9) == "Marseille > Paris > Dresden > Munchen > Prague");

  try
  {
    list<string> r10 = lines.Find("Marseille", "Prague", NurSchnellzug);
    assert("Marseille > Prague connection does not exist!!" == NULL);
  }
  catch (const NoRouteException &e)
  {
  }

  list<string> r11 = lines.Find("Salzburg", "Salzburg");
  assert(toText(r11) == "Salzburg");

  list<string> r12 = lines.Find("Salzburg", "Salzburg", [](const CTrain &x) { return x.m_Company == "SNCF"; });
  assert(toText(r12) == "Salzburg");

  try
  {
    list<string> r13 = lines.Find("London", "Oxford");
    assert("London > Oxford connection does not exist!!" == NULL);
  }
  catch (const NoRouteException &e)
  {
  }
  */
  return 0;
}
#endif /* __PROGTEST__ */
