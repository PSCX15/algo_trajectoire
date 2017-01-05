#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include <cstddef>
#include <list>
#include "Point.h"

class Pathfinder
{
    public:
        //const static int X;   //On va pas mettre un truc comme cela car sinon je dois travailler avec des vector car les matrices doivent savoir leur format a la création donc il faudrait utiliser des vector
        //const static int Y;
        Pathfinder();
        std::vector<std::pair<int,int>*> aStar(float x1, float y1, float x2, float y2, int angle);     //lorsque les coordonnées sont absolues
        Point* getPointFromCoord(float x, float y);        //lorsque les coordonnées sont en incrément
        Point* getPoint(int x, int y);   //
        Point* mapPoint[50][50];
        bool mapWalkable[50][50];                 //On a la table qu'on peut update, si détection d'obstacles, de l'accessibilité des points
        bool pointIsWalkable(int x, int y);
        const static unsigned int MAX_ITERATION=100;

    protected:

    private:
        static int echelle;

};

#endif // PATHFINDER_H
