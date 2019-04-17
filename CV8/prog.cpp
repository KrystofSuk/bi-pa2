#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Pos
{
  private:
    int _x;
    int _y;

  public:
    Pos(const int & x, const int & y) : _x(x), _y(y)
    {
    }
    int GetX() const
    {
        return _x;
    }
    int GetY() const
    {
        return _y;
    }
    void Mov(const int &x, const int &y)
    {
        _x += x;
        _y += y;
    }
    static int Dist(const int &x, const int &y)
    {
        return abs(x - y);
    }
    friend bool operator==(const Pos &lhs, const Pos &rhs)
    {
        return lhs._x == rhs._x && lhs._y == rhs._y;
    }
};

struct UI
{
  public:
    UI()
    {
    }
    virtual void Route(Pos &c, const Pos &e) = 0;
    virtual ~UI()
    {
    }
};

class BasicUI : public UI
{
  public:
    BasicUI() : UI()
    {
    }
    void Route(Pos &c, const Pos &e)
    {
        if (c.GetX() > e.GetX())
            c.Mov(-1, 0);
        if (c.GetX() < e.GetX())
            c.Mov(1, 0);
        if (c.GetY() > e.GetY())
            c.Mov(0, -1);
        if (c.GetY() < e.GetY())
            c.Mov(0, 1);
    }
};

class AdvancedUI : public UI
{
  public:
    AdvancedUI() : UI()
    {
    }
    void Route(Pos &c, const Pos &e)
    {
        if (Pos::Dist(c.GetX(), e.GetX()) > Pos::Dist(c.GetY(), e.GetY()))
        {
            if (c.GetX() > e.GetX())
                c.Mov(-1, 0);
            if (c.GetX() < e.GetX())
                c.Mov(1, 0);
        }
        else
        {
            if (c.GetY() > e.GetY())
                c.Mov(0, -1);
            if (c.GetY() < e.GetY())
                c.Mov(0, 1);
        }
    }
};

template <class T>
class Bot
{
  private:
    Pos _e;
    T _logic;
    Pos _c;

  public:
    Bot(const Pos &s, const Pos &e) : _e(e), _c(s)
    {
    }
    int GetX() const
    {
        return _c.GetX();
    }
    int GetY() const
    {
        return _c.GetY();
    }
    void Move()
    {
        _logic.Route(_c, _e);
    }
    bool Finished()
    {
        return _c == _e;
    }
    friend ostream &operator<<(ostream &out, const Bot &b)
    {
        out << "[" << b.GetX() << "," << b.GetY() << "]";
        return out;
    }
    Bot &operator++(int)
    {
        Move();
        return *this;
    }
};

int main2()
{
    Pos Goal = Pos(8, 6);
    Pos Start = Pos(4, 2);
    Bot<BasicUI> Anton(Start, Goal);
    Bot<AdvancedUI> Spelec(Start, Goal);
    std::cout << Anton << std::endl;
    while (!Anton.Finished()) // current == goal
    {
        std::cout << Anton++ << std::endl; //move + print current position
    }
    std::cout << std::endl;
    std::cout << Spelec << std::endl;
    while (!Spelec.Finished()) // current == goal
    {
        std::cout << Spelec++ << std::endl; //move + print current position
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Pos Goal = Pos(4, 2);
    Pos Start = Pos(8, 6);
    Bot<BasicUI> Anton(Start, Goal);
    Bot<AdvancedUI> Spelec(Start, Goal);
    std::cout << "Anton: " << Anton.GetX() << " " << Anton.GetY() << std::endl;
    for (int i = 0; i < 8; i++)
    {
        Anton.Move();
        std::cout << "Anton: " << Anton.GetX() << " " << Anton.GetY() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Spelec: " << Spelec.GetX() << " " << Spelec.GetY() << std::endl;
    for (int i = 0; i < 8; i++)
    {
        Spelec.Move();
        std::cout << "Spelec: " << Spelec.GetX() << " " << Spelec.GetY() << std::endl;
    }

    main2();

    return 0;
}
