#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;

class CTimeStamp
{
public:
  CTimeStamp(int year,
             int month,
             int day,
             int hour,
             int minute,
             double sec)
  {
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
    _sec = sec;
  }
  int Compare(const CTimeStamp &x) const
  {
    if (_year == x._year)
    {
      if (_month == x._month)
      {
        if (_day == (x._day))
        {
          if (_hour == (x._hour))
          {
            if (_minute == (x._minute))
            {
              if (_sec == (x._sec))
              {
                return 0;
              }
              return _sec > (x._sec) ? 1 : -1;
            }
            return _minute > (x._minute)? 1 : -1;
          }
          return _hour > (x._hour)? 1 : -1;
        }
        return _day > (x._day)? 1 : -1;
      }
      return _month > (x._month)? 1 : -1;
    }
    return _year > (x._year)? 1 : -1;
  }
  friend ostream &operator<<(ostream &os,
                             const CTimeStamp &x)
  {
    os << x._year << "-" << setw(2) << setfill('0') << x._month << "-" << setw(2) << setfill('0') << x._day << " "  << setw(2) << setfill('0')<< x._hour << ":" << setw(2) << setfill('0') << x._minute << ":" << setw(5) << fixed << setprecision(3) << setfill('0') <<  x._sec;
    return os;
  }

private:
  int _year;
  int _month;
  int _day;
  int _hour;
  int _minute;
  double _sec;
};
class CMail
{
public:
  CMail(const CTimeStamp &timeStamp,
        const string &from,
        const string &to,
        const string &subject) : _stamp(timeStamp)
  {
    _from = from;
    _to = to;
    _subj = subject;
  }
  int CompareByTime(const CTimeStamp &x) const
  {
    return _stamp.Compare(x);
  }
  int CompareByTime(const CMail &x) const
  {
    return CompareByTime(x.TimeStamp());
  }
  const string &From(void) const
  {
    return _from;
  }
  const string &To(void) const
  {
    return _to;
  }
  const string &Subject(void) const
  {
    return _subj;
  }
  const CTimeStamp &TimeStamp(void) const
  {
    return _stamp;
  }
  friend ostream &operator<<(ostream &os,
                             const CMail &x)
  {
    os << x._stamp << " " << x._from << " -> " << x._to << ", subject: " << x._subj ;
    return os;
  }

private:
  CTimeStamp _stamp;
  string _from;
  string _to;
  string _subj;
};
// your code will be compiled in a separate namespace
namespace MysteriousNamespace
{
#endif /* __PROGTEST__ */
//----------------------------------------------------------------------------------------

class Header
{
public:
  string from;
  string subj;
  Header(string f, string s)
  {
    from = f;
    subj = s;
  }
  void SetSubj(string sb)
  {
    subj = sb;
  }

  friend std::ostream &operator<<(std::ostream &os, const Header &obj)
  {
    os << obj.from << " :: " << obj.subj << "/";
    return os;
  }
};

struct CMP {
    bool operator()(const CTimeStamp& a, const CTimeStamp& b) const {
      if(a.Compare(b) < 0)
        return true;
      else
        return false;
    }
};

class CMailLog
{
public:
  int ParseLog(istream &in)
  {
    _mails.clear();
    cout << "Parsing" << endl;
    int year = -1;
    string month = "";
    int day = -1;
    int hour = -1;
    int minute = -1;
    double sec = -1;
    string dns = "";
    string id = "";

    vector<string> payload;
    map<string, Header> headers;
    string str;

    int cnt = 0;
    int index = 0;
    while (getline(in, str))
    {
      payload.clear();
      year = -1;
      month = "";
      day = -1;
      hour = 0;
      minute = 0;
      sec = 0;
      dns = "";
      id = "";
      index = 0;
      istringstream ss(str);
      string item;
      while (std::getline(ss, item, ':')){
        istringstream s2(item); 
        if(index == 0)
        {
          s2 >> month >> day >> year >> hour;
        }
        if(index == 1)
        {
          s2 >> minute;
        }
        if(index == 2)
        {
          if(s2 >> sec){
           s2 >> dns >> id;
          }
          else{
            s2.clear();
            s2 >> dns >> id;
          }
        }
        if(index == 3){
          int t = 0;
          while (std::getline(s2, item, '='))
          {
            payload.push_back(item);
            size_t start = payload[t].find_first_not_of(" \n\r\t\f\v");
            payload[t] = (start == std::string::npos) ? "" : payload[t].substr(start);
            size_t end = payload[t].find_last_not_of(" \n\r\t\f\v");
	          payload[t] = (end == std::string::npos) ? "" : payload[t].substr(0, end + 1);
            t++;
          }
        }
        index++;
      }
      if (payload.size() == 0)
        continue;

      int m = GetMonth(month);
      if (m == -1 || (payload[0] != "from" && payload[0] != "to" && payload[0] != "subject"))
      {
        cout << "wrong" << endl;
        continue;
      }

      if (payload[0] == "from")
      {
        
        if (payload.size() < 2){
          payload.push_back("");
        }
        Header h(payload[1], "");
        headers.insert(make_pair(id, h));
      }
      if (payload[0] == "subject")
      {
        string sub = "";
        cout << "Headers " << headers.size() << endl;
        if (payload.size() == 2)
        {
          sub = payload[1];
        }
        auto it = headers.find(id);
        it->second.SetSubj(sub);
      }
      if (payload[0] == "to")
      {
        if (payload.size() < 2){
          payload.push_back("");
        }
        cnt++;
        CTimeStamp tm (year, m, day, hour, minute, sec);
        auto it = headers.find(id);
        ;
        CMail m(tm, it->second.from , payload[1], it->second.subj);
        _mails.insert(make_pair(tm, m));
      }
    }
    cout << endl;

    for (auto it = headers.begin(); it != headers.end(); ++it)
      std::cout << it->first << "::" << it->second << endl;

    return cnt;
  }
  list<CMail> ListMail(const CTimeStamp &from,
                       const CTimeStamp &to) const
  {
    auto low = _mails.lower_bound (from);  
    auto up = _mails.upper_bound (to);   
    list<CMail> mailList;
    if(distance(_mails.begin(), up) < distance(_mails.begin(), low))
      return mailList;
    for (auto it = low; it!=up; it++){
      if(it != _mails.end())
        mailList.push_back((*it).second);
    }
    return mailList;
  }

  set<string> ActiveUsers(const CTimeStamp &from,
                          const CTimeStamp &to) const
  {
    auto low = _mails.lower_bound (from);  
    auto up = _mails.upper_bound (to);  
    set<string> userList;
    if(distance(_mails.begin(), up) < distance(_mails.begin(), low))
      return userList;
    for (auto it= low; it!=up; it++){
      if(it != _mails.end()){
        cout << (*it).second.From() << endl;
        userList.insert((*it).second.From());
        userList.insert((*it).second.To());
      }
    }
    return userList;
  }

private:
  int GetMonth(const string &m) const
  {
    if (m == "Jan")
      return 1;
    if (m == "Feb")
      return 2;
    if (m == "Mar")
      return 3;
    if (m == "Apr")
      return 4;
    if (m == "May")
      return 5;
    if (m == "Jun")
      return 6;
    if (m == "Jul")
      return 7;
    if (m == "Aug")
      return 8;
    if (m == "Sep")
      return 9;
    if (m == "Oct")
      return 10;
    if (m == "Nov")
      return 11;
    if (m == "Dec")
      return 12;
    return -1;
  }

  multimap<CTimeStamp, CMail, CMP> _mails;
};
//----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string printMail(const list<CMail> &all)
{
  ostringstream oss;
  for (const auto &mail : all)
    oss << mail << endl;
  return oss.str();
}
string printUsers(const set<string> &all)
{
  ostringstream oss;
  bool first = true;
  for (const auto &name : all)
  {
    if (!first)
      oss << ", ";
    else
      first = false;
    oss << name;
  }
  return oss.str();
}
int main(void)
{
  MysteriousNamespace::CMailLog m;
  list<CMail> mailList;
  set<string> users;
  istringstream iss;

  iss . clear ();
  iss . str (
    "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"
    "Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
    "Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=New progtest homework!\n"
    "Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
    "Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
    "Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
    "Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
    "Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
    "Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
    "Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
    "Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n" );
  assert ( m . ParseLog ( iss ) == 8 );
  mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                            CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );
  assert ( printMail ( mailList ) == 
    "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
    "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
    "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
    "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
    "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
    "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
    "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
    "2019-03-29 15:02:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n" );
  mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                            CTimeStamp ( 2019, 3, 29, 14, 58, 32 ) );
  assert ( printMail ( mailList ) == 
    "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
    "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
    "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n" );
  mailList = m . ListMail ( CTimeStamp ( 2019, 3, 30, 0, 0, 0 ),
                            CTimeStamp ( 2019, 3, 30, 23, 59, 59 ) );
  assert ( printMail ( mailList ) == "" );
  users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                            CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );
  assert ( printUsers ( users ) == "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz" );
  users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                            CTimeStamp ( 2019, 3, 29, 13, 59, 59 ) );
  assert ( printUsers ( users ) == "person3@fit.cvut.cz, user76@fit.cvut.cz" );
  return 0;
}
#endif /* __PROGTEST__ */
