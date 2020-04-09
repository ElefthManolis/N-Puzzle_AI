#include <iostream>
#include "Npuzzle.h"
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>
#include <limits>
#include <unordered_set>

using namespace std;

char isExist(vector<Npuzzle*> a,Npuzzle *p)
{
    char found=0;
    for(unsigned int i=0;i<a.size();i++)
        if(a[i]==p)
            found=1;
    return (!found);
}

void showCase(Npuzzle &p)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            cout<<p.getBoardIndex(i,j)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

Npuzzle *DFS(Npuzzle *initial,Npuzzle *goal,long long &examined,long long &mem)
{
    stack<Npuzzle *> agenda;
    vector <Npuzzle> closed;
    agenda.push(initial);
    mem=1;
    examined=0;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
            mem=agenda.size()+closed.size();
        Npuzzle *s = agenda.top();
        agenda.pop();
        showCase(*s);
        if (find(closed.begin(), closed.end(), *s)==closed.end())
        {
            examined++;
            if (*s==*goal)
                return s;
            closed.push_back(*s);
            vector<Npuzzle *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (find(closed.begin(), closed.end(), *children[i])==closed.end())
                    agenda.push(children[i]);
        }
    }
    return NULL;
}

Npuzzle *BFS(Npuzzle *initial,Npuzzle *goal,long long &examined,long long &mem)
{
    queue<Npuzzle *> agenda;
    vector <Npuzzle> closed;
    agenda.push(initial);
    mem=1;
    examined=0;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
            mem=agenda.size()+closed.size();
        Npuzzle *s = agenda.front();
        agenda.pop();
        showCase(*s);
        if (find(closed.begin(), closed.end(), *s)==closed.end())
        {
            examined++;
            if (*s==*goal)
                return s;
            closed.push_back(*s);
            vector<Npuzzle *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (find(closed.begin(), closed.end(), *children[i])==closed.end())
                    agenda.push(children[i]);
        }
    }
    return NULL;
}

Npuzzle *BestFS(Npuzzle *initial,Npuzzle *goal,long long &examined,long long &mem)
{
    priority_queue <Npuzzle*, vector<Npuzzle *>, myComparator > agenda;
    unordered_map<unsigned long,Npuzzle*> closed;
    agenda.push(initial);
    mem=1;
    examined=0;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
            mem=agenda.size()+closed.size();
        Npuzzle *s = agenda.top();
        agenda.pop();
        showCase(*s);
        if (!closed.count(s->getKey()))
        {
            examined++;
            if (*s==*goal)
                return s;
            pair<unsigned long,Npuzzle*> k (s->getKey(),s);
            closed.insert(k);
            vector<Npuzzle *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (!closed.count(children[i]->getKey()))
                {
                    children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                    agenda.push(children.at(i));
                }
        }
    }
    return NULL;
}

Npuzzle *aStar(Npuzzle *initial,Npuzzle *goal,long long &examined,long long &mem)
{
    priority_queue <Npuzzle*, vector<Npuzzle*>, myComparator> agenda;
    vector<Npuzzle*> closed;
    vector<double> cost_so_far;
    agenda.push(initial);

    closed.resize(20 * 20, nullptr);
    cost_so_far.resize(20 * 20, 9999);
    cost_so_far[initial->getXZeroIndex(*initial)+ 20 * initial->getYZeroIndex(*initial)] = 0;
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
            mem=agenda.size()+closed.size();
        Npuzzle *s = agenda.top();
        agenda.pop();
        showCase(*s);
        examined++;
        if (*s==*goal)
            return s;

        vector<Npuzzle *> children = s->expand();
        for (unsigned int i=0;i<children.size();i++)
        {
            if(isExist(closed,children.at(i)))
            {
                double new_cost=cost_so_far[s->getXZeroIndex(*s) + 20 * s->getYZeroIndex(*s)]+ children.at(i)->getDepth();
                if(new_cost< cost_so_far[children.at(i)->getXZeroIndex(*children.at(i)) + 20 * children.at(i)->getYZeroIndex(*children.at(i))])
                {
                    cost_so_far[children.at(i)->getXZeroIndex(*children.at(i)) + 20 * children.at(i)->getYZeroIndex(*children.at(i))] = new_cost;
                    closed[children.at(i)->getXZeroIndex(*children.at(i)) + 20 * children.at(i)->getYZeroIndex(*children.at(i))] = s;
                    children.at(i)->setHvalue(children.at(i)->aStarHeuristic(goal)+new_cost);
                    agenda.push(children.at(i));

                }
            }
            children.at(i)->setHvalue(children.at(i)->aStarHeuristic(goal));
            agenda.push(children.at(i));
        }
    }
    return NULL;
}


int main()
{
    int choise;
    long long examined,mem;
    int startBoard[3][3]={1,3,6,4,0,2,7,5,8};
    int finalBoard[3][3]={1,2,3,4,5,6,7,8,0};
    Npuzzle *startPuzzle = new Npuzzle(startBoard);
    Npuzzle *finalPuzzle = new Npuzzle(finalBoard);
    Npuzzle *initial = startPuzzle;
    Npuzzle *goal =finalPuzzle;
    cout<<"Which algorithm to you want? 1)DFS 2)BFS 3)BestFS or 4)A*"<<endl;
    cout<<"Your choise: ";
    cin>>choise;
    if(choise==1)
    {
        Npuzzle *dsol = initial;
        dsol=DFS(initial,goal,examined,mem);
        if(dsol!=NULL)
            cout<<"DFS: depth = "<<dsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined;
        else
            cout<<"Problem unsolvable";
    }
    if(choise==2)
    {
        Npuzzle *bsol = initial;
        bsol=BFS(initial,goal,examined,mem);
        if(bsol!=NULL)
            cout<<"BFS: depth = "<<bsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined;
        else
            cout<<"Problem unsolvable";
    }
    if(choise==3)
    {
        Npuzzle *bestsol = initial;
        bestsol=BestFS(initial,goal,examined,mem);
        if(bestsol!=0)
            cout<<"BestFS: depth = "<<bestsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined;
        else
            cout<<"Problem unsolvable";
    }
    if(choise==4)
    {
        Npuzzle *astarsol = initial;
        astarsol=aStar(initial,goal,examined,mem);
        if(astarsol!=NULL)
            cout<<"A*: depth = "<<astarsol->getDepth()<<", Mem: "<<mem<<", Examined: "<<examined;
        else
            cout<<"Problem unsolvable";
    }

    return 0;
}
