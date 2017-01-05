#include "Point.h"


using namespace std;

Point::Point()
{
    parent= NULL;
    closed=false;
    opened=false;
    walkable=true;
    x=y=z=f=g=h=0;
}

Point::Point(int x, int y, bool w)
{
    Point();
    this->walkable = w;
    this->x = x;
    this->y = y;
}

Point::~Point()
{
    parent=NULL;
}

int Point::Getx()
{
    return x;
}

int Point::Gety()
{
    return y;
}
int Point::Getz()
{
      return z;
}
void Point::Setz(int val)  // On a en général pas de hauteur mais on peut la mettre
{
    this->z=val;
}
bool Point::Getwalkable()
{
    return walkable;
}
void Point::Setwalkable(bool val)
{
    this->walkable=val;
}
Point* Point::Getparent()
{
    return parent;
}
void Point::Setparent(Point* val)
{
    this->parent=val;
}
int Point::Geth()
{
    return h;
}
int Point::Getg()
{
    return g;
}
int Point::Getf()
{
    return f;
}
bool Point::hasParent()
{
    return parent != NULL;
}
void Point::computeScores(Point *end)  //end est l'objectif à atteindre
{
    g = getGScore(parent);
    h = getHScore(end);
    f = g + h;
}

int Point::getGScore(Point *p)   //Cette fonction peut être adapter si on change de méthode de cout pour pénalisern  les chemins
{
    return p->g + ((x == p->x || y == p->y) ? 10 : 14);
}

int Point::getHScore(Point *p)   //Cette fonction peut être adapter si on change de méthode de cout pour pénalisern  les chemins
{
    return (abs(p->x - x) + abs(p->y - y)) * 10;
}

pair<int,int>* Point::getPosition()
{
    pair<int,int>* p = new pair<int,int>(x,y);
    return p;
}

