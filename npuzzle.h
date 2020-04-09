#ifndef NPUZZLE_H
#define NPUZZLE_H
#define HEIGHT 3
#define WIDTH 3
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Npuzzle
{
    public:
        Npuzzle();
        Npuzzle(int A[HEIGHT][WIDTH]);
        int getDepth();
        bool operator==(const Npuzzle& o) const;
        Npuzzle operator= (Npuzzle o);
        int getBoardIndex(int a,int b);
        void setBoardIndex(int a,int b,int value);
        double getHvalue();
        void setHvalue(double h);
        bool goUp(Npuzzle &n,int a,int b);
        bool goDown(Npuzzle &n,int a,int b);
        bool goLeft(Npuzzle &n,int a,int b);
        bool goRight(Npuzzle &n,int a,int b);
        int getXZeroIndex(Npuzzle &n);
        int getYZeroIndex(Npuzzle &n);
        vector <Npuzzle *> expand();
        Npuzzle *getPrevious()const {return prev;}
        void setPrevious(Npuzzle *p) {prev=p;}
        int heuristic (Npuzzle *goal);
        int aStarHeuristic(Npuzzle *goal);
        unsigned long getKey()
        {
            int finalBoard[3][3]={1,2,3,4,5,6,7,8,0};
            Npuzzle *finalPuzzle = new Npuzzle(finalBoard);
            unsigned long k = this->heuristic(finalPuzzle)*10+(getXZeroIndex(*this)+getYZeroIndex(*this)) ;
            return k;
        }
    private:
        int board[HEIGHT][WIDTH];
        double Hvalue;
        Npuzzle *prev;
};
class myComparator
{
    public:
        int operator() (Npuzzle *p1 ,Npuzzle *p2) const
        {
            return p1->getHvalue()>p2->getHvalue();
        }
};




#endif // NPUZZLE_H
