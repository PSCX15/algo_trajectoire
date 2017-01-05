#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include <cstddef>
#include <list>
#include "Point.h"

class Pathfinder
{
    public:
        //const static int X;   //On va pas mettre un truc comme cela car sinon je dois travailler avec des vector car les matrices doivent savoir leur format a la cr�ation donc il faudrait utiliser des vector
        //const static int Y;
        Pathfinder();
        std::vector<std::pair<int,int>*> aStar(float x1, float y1, float x2, float y2, int angle);     //lorsque les coordonn�es sont absolues
        Point* getPointFromCoord(float x, float y);        //lorsque les coordonn�es sont en incr�ment
        Point* getPoint(int x, int y);   //
        Point* mapPoint[50][50];
        bool mapWalkable[50][50];                 //On a la table qu'on peut update, si d�tection d'obstacles, de l'accessibilit� des points
        bool pointIsWalkable(int x, int y);
        const static unsigned int MAX_ITERATION=100;

    protected:

    private:
        static int echelle;

};

#endif // PATHFINDER_H
