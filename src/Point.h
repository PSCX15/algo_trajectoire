#ifndef POINT_H
#define POINT_H
#include <utility>
#include <cmath>
#include <cstddef>

class Point
{
    public:
        Point();
        Point(int x, int y, bool w);
        virtual ~Point();
        int Getx();
        int Gety();
        int Getz();
        void Setz(int val);  // On a en général pas de hauteur mais on peut la mettre
        bool Getwalkable();
        void Setwalkable(bool val);
        Point* Getparent();
        void Setparent(Point* val);
        int Geth();
        int Getg();
        int Getf();
        bool hasParent();
        void computeScores(Point *end);
        int getGScore(Point *p);
        int getHScore(Point *p);
        std::pair<int,int>* getPosition();
        bool hasParent() const;
        bool opened;
        bool closed;
        bool walkable;

    protected:

    private:
        int x;
        int y;
        int z;
        Point* parent;
        int h;
        int g;
        int f;
};

#endif // POINT_H
