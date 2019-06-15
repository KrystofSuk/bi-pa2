#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <memory>
#include <functional>
#include <numeric>

using namespace std;

class SamePactException
{
};

class UnknownCountryException
{
};

class CNode
{
  public:
    vector<CNode *> nodes;
    CNode(const string &n, const int &a)
    {
        _name = n;
        _army = a;
    }

    string _name;
    int _army;

    void ChangeNode(CNode * node, bool t){
        if(t){
            for(size_t i = 0; i < nodes.size(); i++){
                if(nodes.at(i) == node){
                    return;
                }
            }
            nodes.push_back(node);
            cout << "Added" << endl;
        }else{
            for(size_t i = 0; i < nodes.size(); i++){
                if(nodes.at(i) == node){
                    nodes.erase(nodes.begin()+i);
                    return;
                }
            }
        }
    }

    set<CNode *> & BFS(set <CNode *> & visited){
        visited.insert(this);
        //cout << _name << endl;
        for(size_t i = 0; i < nodes.size(); i++){
            if(visited.find(nodes.at(i)) == visited.end()){
                nodes.at(i)->BFS(visited);
            }
        }
        return visited;
    }

  private:
};

class CPoliticalMap
{
  private:
    map<string, CNode *> nodes;

  public:
    CPoliticalMap()
    {
    }
    void Update(const std::string &name,
                int cnt)
    {
        if(nodes.find(name) == nodes.end()){
            CNode *nwNode = new CNode(name, cnt);
            nodes.insert(make_pair(name, nwNode));
        }else{            
            nodes.find(name)->second->_army = cnt;
        }
    }
    void Treaty(const std::string &name1,
                const std::string &name2,
                bool status)
    {
        cout << "Treaty" << endl;
        if(nodes.find(name1) == nodes.end()){
            Update(name1, -1);
        }
        if(nodes.find(name2) == nodes.end()){
            Update(name2, -1);
        }
        nodes.at(name1)->ChangeNode(nodes.at(name2), status);
        nodes.at(name2)->ChangeNode(nodes.at(name1), status);
    }
    int Compare(const std::string &name1,
                const std::string &name2) const
    {
        cout << "Compare" << endl;
        
        set<CNode *> a;
        set<CNode *> b;

        if(nodes.find(name1) == nodes.end()){
            throw(UnknownCountryException());
        }
        if(nodes.find(name2) == nodes.end()){
            throw(UnknownCountryException());
        }
        
        nodes.at(name1)->BFS(a);
        nodes.at(name2)->BFS(b);

        int aN = 0;
        int bN = 0;
        
        for(auto f : a) {
            if(b.find(f) != b.end())
                throw(SamePactException());
        }
        for(auto f : b) {
            if(a.find(f)!= a.end())
                throw(SamePactException());
        }
        
        for(auto f : a) {
            if(f->_army == -1)
                throw(UnknownCountryException());
            aN += f->_army;
        }
        for(auto f : b) {
            if(f->_army == -1)
                throw(UnknownCountryException());
            bN += f->_army;
        }
        //cout << aN << "," << bN << endl;   
        return (aN - bN);
    }
    friend ostream &operator<<(ostream &os, const CPoliticalMap &obj)
    {
        for (auto it = obj.nodes.begin(); it != obj.nodes.end(); ++it)
        {
            os << it->first;
            os << endl
               << "Ma smlouvu s:" << endl;
            for (size_t t = 0; t < it->second->nodes.size(); t++)
            {
                os << it->second->nodes.at(t)->_name << endl;
            }
            os << "-------" << endl;
        }
        return os;
    }
    ~CPoliticalMap()
    {
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            delete it->second;
        }
    }
};

int main(void)
{

    CPoliticalMap x;

    x.Update("A", 1000);
    x.Update("B", 2000);
    x.Update("C", 1500);
    x.Update("D", 1500);
    assert(x.Compare("C", "D") == 0);
    assert(x.Compare("A", "B") == -1000);
    x.Treaty("A", "B", true);
    x.Treaty("C", "D", true);
    cout << x;
    assert(x.Compare("A", "C") == 0);
    x.Treaty("E", "B", true);
    
    
    try
    {
        x.Compare("A", "E");
        assert("Missing an exception" == NULL);
    }
    catch (const SamePactException &e)
    {
    }
    try
    {
        x.Compare("C", "E");
        assert("Missing an exception" == NULL);
    }
    catch (const UnknownCountryException &e)
    {
    }
    x.Update("E", 2000);
    assert(x.Compare("C", "E") == -2000);
    x.Treaty("A", "E", true);
    x.Treaty("A", "B", true);
    x.Treaty("A", "B", false);
    assert(x.Compare("A", "D") == 2000);
    x.Update("C", 3000);
    assert(x.Compare("A", "D") == 500);
    x.Treaty("A", "B", false);
    x.Treaty("D", "B", true);
    try
    {
    //cout << "xxxxxxxxxxxxxx" << endl;
        x.Compare("A", "F");
        assert("Missing an exception" == NULL);
    }
    catch (const UnknownCountryException &e)
    {
    }
    x.Update("F", 12000);
    x.Update("A", 0);
    assert(x.Compare("A", "F") == -3500);
    x.Update("A", 6000);
    assert(x.Compare("A", "F") == 2500);
    try
    {
        x.Compare("A", "A");
        assert("Missing an exception" == NULL);
    }
    catch (const SamePactException &e)
    {
    }
    return 0;
}