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
    return 0;
  }
  friend ostream &operator<<(ostream &os,
                             const CTimeStamp &x)
  {
    os << x._month << " " << x._day << " " << x._year << " " << x._hour << ":" << x._minute << ":" << x._sec;
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
    return 0;
  }
  int CompareByTime(const CMail &x) const
  {
    return 0;
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
    os << x._stamp << " " << x._from << " " << x._to << " " << x._subj << endl;
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
class CMailLog
{
public:
  int ParseLog(istream &in)
  {
    cout << "Parsing" << endl;
    int year = 0;
    string month = "";
    int day = 0;
    int hour = 0;
    int minute = 0;
    double sec = 0;
    char c1, c2;
    string dns;
    string id;
    string payload;

    string str;
    while(getline(in, str)) 
    {
      istringstream ss(str);
      in >> month >> day >> year >> hour >> c1 >> minute >> c2 >> sec >> dns >> id;
      payload = ss.str();
      cout << "Parsed:" <<  month << " " << day<< " " << year<< " " << hour << c1 << minute << c2 << sec << " " << dns << " " << id << " " << payload << endl;
    }
    return day;
  }
  list<CMail> ListMail(const CTimeStamp &from,
                       const CTimeStamp &to) const
  {
    return list<CMail>();
  }

  set<string> ActiveUsers(const CTimeStamp &from,
                          const CTimeStamp &to) const
  {
    return set<string>();
  }

private:
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

  iss.clear();
  iss.str(
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
      "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n");
  assert(m.ParseLog(iss) == 8);
  mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
                        CTimeStamp(2019, 3, 29, 23, 59, 59));
  assert(printMail(mailList) ==
         "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
         "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
         "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
         "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
         "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
         "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
         "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
         "2019-03-29 15:02:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n");
  mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
                        CTimeStamp(2019, 3, 29, 14, 58, 32));
  assert(printMail(mailList) ==
         "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
         "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
         "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n");
  mailList = m.ListMail(CTimeStamp(2019, 3, 30, 0, 0, 0),
                        CTimeStamp(2019, 3, 30, 23, 59, 59));
  assert(printMail(mailList) == "");
  users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
                        CTimeStamp(2019, 3, 29, 23, 59, 59));
  assert(printUsers(users) == "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz");
  users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
                        CTimeStamp(2019, 3, 29, 13, 59, 59));
  assert(printUsers(users) == "person3@fit.cvut.cz, user76@fit.cvut.cz");
  return 0;
}
#endif /* __PROGTEST__ */
