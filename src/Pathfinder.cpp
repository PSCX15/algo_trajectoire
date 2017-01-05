#include "Pathfinder.h"


int Pathfinder::echelle = 60;   //rayon de braquage de 60cm qui va correspondre à un cran de 1 sur l'échelle
//int Pathfinder::X=50;   //cela nous donne une map de 30m x 30m
//int Pathfinder::Y=50;

using namespace std;

Pathfinder::Pathfinder()
{
    for (int i = 0; i < 50; i++)
    {              //On itinialise la mapWalkable: par défaut tout est accessible
        for (int j = 0; j < 50; j++)
            {
                mapWalkable[i][j] = true;
            }
    }


    for (int i = 0; i < 50; i++){              //Il me faut une map de point pour savoir les points que j'ai deja atteint
        for (int j = 0; j < 50; j++)
            {
                mapPoint[i][j] = NULL;
            }
    }
}

Point* Pathfinder::getPointFromCoord(float x, float y)
{
    int xc=(int) (x/echelle);
    int yc=(int) (y/echelle);
    if (mapPoint[xc][yc]==NULL){
        Point* p= new Point(xc,yc, mapWalkable[xc][yc]);
        mapPoint[xc][yc]==p;
    }
    return mapPoint[xc][yc];
}

Point* Pathfinder::getPoint(int x, int y)
{
    if (mapPoint[x][y]==NULL){
        Point* p= new Point(x,y, mapWalkable[x][x]);
        mapPoint[x][y]==p;
    }
    return mapPoint[x][y];
}

bool Pathfinder::pointIsWalkable(int x, int y)
{
    return mapWalkable[x][y];
}

vector<pair<int,int>*> Pathfinder::aStar(float x1, float y1, float x2, float y2, int angle)
{
    //Je n'ai pas encore utiliser l'info angle, il faut que je modifie

    vector<pair<int,int>*> path;

    // Define points to work with
    Point *start = getPointFromCoord(x1, y1);
    Point *end = getPointFromCoord(x2, y2);
    Point *current;
    Point *child;

    // Define the open and the close list
    list<Point*> openList;
    list<Point*> closedList;
    list<Point*>::iterator i;

    unsigned int n = 0;   //compteur de nombre d'itérations pour éviter qu'il tourne trop

    // Add the start point to the openList
    openList.push_back(start);
    start->opened = true;

    while (n == 0 || (current != end && n < MAX_ITERATION))
    {
        // Look for the smallest F value in the openList and make it the current point
        for (i = openList.begin(); i != openList.end(); ++ i)
        {
            if (i == openList.begin() || (*i)->Getf() <= current->Getf())
            {
                current = (*i);
            }
        }

        // Stop if we reached the end
        if (current == end)
        {
            break;
        }

        // Remove the current point from the openList
        openList.remove(current);
        current->opened = false;

        // Add the current point to the closedList
        closedList.push_back(current);
        current->closed = true;

        // Get all current's adjacent walkable points
        for (int x = -1; x < 2; x ++)
        {
            for (int y = -1; y < 2; y ++)
            {
                // If it's current point then pass
                if (x == 0 && y == 0)
                {
                    continue;
                }

                // Get this point
                child = getPoint(current->Getx() + x, current->Gety() + y);

                // If it's closed or not walkable then pass
                if (child->closed || !child->walkable)
                {
                    continue;
                }

                // If we are at a corner
                //Cette partie peut être à adapter: pour aller en diagonale je dois avoir les deux cases adjacentes et sur le chemin libre
                //On va la laisser pour le moment et on doit l'améliorer
                if (x != 0 && y != 0)
                {
                    // if the next horizontal point is not walkable or in the closed list then pass
                    if (!pointIsWalkable(current->Getx(), current->Gety() + y) || getPoint(current->Getx(), current->Gety() + y)->closed)
                    {
                        continue;
                    }
                    // if the next vertical point is not walkable or in the closed list then pass
                    if (!pointIsWalkable(current->Getx() + x, current->Gety()) || getPoint(current->Getx() + x, current->Gety())->closed)
                    {
                        continue;
                    }
                }

                // If it's already in the openList
                if (child->opened)
                {
                    // If it has a wroste g score than the one that pass through the current point
                    // then its path is improved when it's parent is the current point
                    if (child->Getg() > child->getGScore(current))
                    {
                        // Change its parent and g score
                        child->Setparent(current);
                        child->computeScores(end);
                    }
                }
                else
                {
                    // Add it to the openList with current point as parent
                    openList.push_back(child);
                    child->opened = true;

                    // Compute it's g, h and f score
                    child->Setparent(current);
                    child->computeScores(end);
                }
            }
        }

        n ++;
    }

    // Reset
    for (i = openList.begin(); i != openList.end(); ++ i)
    {
        (*i)->opened = false;
    }
    for (i = closedList.begin(); i != closedList.end(); ++ i)
    {
        (*i)->closed = false;
    }

    // Resolve the path starting from the end point
    while (current->hasParent() && current != start)
    {
        path.push_back(current->getPosition());
        current = current->Getparent();
        //n ++;
    }

    return path;
}
