#include "Npuzzle.h"
#define HEIGHT 3
#define WIDTH 3
#include <cmath>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

Npuzzle::Npuzzle()
{
    for (int i=0;i<HEIGHT;i++)
        for (int j=0;j<WIDTH;j++)
            board[i][j]=0;
    setPrevious(NULL);
}

Npuzzle::Npuzzle(int A[WIDTH][HEIGHT])
{
    for(int i=0;i<HEIGHT;i++)
        for(int j=0;j<WIDTH;j++)
            board[i][j]=A[i][j];
    setPrevious(NULL);
}

int Npuzzle::getDepth()
{
    int counter =0;
    Npuzzle *p = this;
    while (p->prev!=NULL)
    {
        p=p->prev;
        counter++;
    }
    return counter;
    //return path.size();
}


bool Npuzzle::operator==(const Npuzzle& s) const
{
    char found=0;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(board[i][j]!=s.board[i][j])
                found=1;
        }
    }
    return (!found);
}

Npuzzle Npuzzle::operator= (Npuzzle o)
{
    board[HEIGHT][WIDTH]=o.board[HEIGHT][WIDTH];
    prev = o.prev;
    return *this;
}

int Npuzzle::getBoardIndex(int a,int b)
{
    return board[a][b];
}

void Npuzzle::setBoardIndex(int a,int b,int value)
{
    board[a][b]=value;
}

void Npuzzle::setHvalue(double h)
{
    Hvalue = h;
}

double Npuzzle::getHvalue()
{
    return Hvalue;
}

bool Npuzzle::goUp(Npuzzle &n,int a,int b)
{
    if (a>0)
    {
        int temp=n.getBoardIndex(a-1,b);
        int x=n.getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a-1,b,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    return false;
}

bool Npuzzle::goDown(Npuzzle &n,int a,int b)
{
    if (a<2)
    {
        int temp=getBoardIndex(a+1,b);
        int x=getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a+1,b,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Npuzzle::goLeft(Npuzzle &n,int a,int b)
{
    if (b>0)
    {
        int temp=getBoardIndex(a,b-1);
        int x=getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a,b-1,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Npuzzle::goRight(Npuzzle &n,int a,int b)
{
    if (b<2)
    {
        int temp=getBoardIndex(a,b+1);
        int x=getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a,b+1,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    return false;
}

int Npuzzle::getXZeroIndex(Npuzzle &n)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(n.board[i][j]==0)
                return i;
        }
    }
}

int Npuzzle::getYZeroIndex(Npuzzle &n)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(n.board[i][j]==0)
                return j;
        }
    }
}

vector <Npuzzle *> Npuzzle::expand()
{
    vector <Npuzzle *> children;
    Npuzzle *child;
    child = new Npuzzle(*this);
    if (goUp(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
        children.push_back(child);
    else
        delete child;
    child = new Npuzzle(*this);
    if (goRight(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
        children.push_back(child);
    else
        delete child;
    child = new Npuzzle(*this);
    if (goDown(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
        children.push_back(child);
    else
        delete child;
    child = new Npuzzle(*this);
    if (goLeft(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
        children.push_back(child);
    else
        delete child;
    return children;
}



int Npuzzle::heuristic (Npuzzle *goal)
{
    int dist=0;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            for(int q=0;q<HEIGHT;q++)
            {
                for(int p=0;p<WIDTH;p++)
                {
                    if(goal->board[q][p]==board[i][j])
                        dist+=abs(i-q)+abs(j-p);

                }
            }
        }

    }
    return dist;
}


int Npuzzle::aStarHeuristic(Npuzzle *goal)
{
    int dist=0;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            for(int q=0;q<HEIGHT;q++)
            {
                for(int p=0;p<WIDTH;p++)
                {
                    if(goal->board[q][p]==board[i][j])
                        dist+=abs(i-q)+abs(j-p);

                }
            }
        }

    }
    return dist+this->getDepth();
}
