#ifndef NUAGE_H
#define NUAGE_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Point.hpp"

template <typename T>
class Nuage
{
private:
    std::vector< Point<T> > points;

public:
    Nuage();
    Nuage(const Nuage<T>&);
    ~Nuage();

    void randNuage(unsigned int nbPoint);

    void importNuage(const std::string);
    void exportNuage(const std::string) const;

    void ajoutPoint(const T, const T);
    void ajoutPoint(const Point<T>&);
    void enlevePoint(const unsigned int);

    inline void setValeur(const unsigned int i, const Point<T>& point){ points[i] = point; }
    inline Point<T> getValeur(const int i) const { return points[i]; }
    inline unsigned int getTaille() const { return points.size(); }

    std::vector< Point<T> > getPoints() const;
};

template <typename T>
Nuage<T>::Nuage()
{
}

template <typename T>
Nuage<T>::Nuage(const Nuage<T>& other) : points(other.getPoints())
{

}

template <typename T>
Nuage<T>::~Nuage()
{
}

template <typename T>
void Nuage<T>::randNuage(unsigned int nbPoint)
{
    Point<T> p;

    srand (time(NULL));

    unsigned int i;
    for(i = 0; i < nbPoint; i++)
    {
        p.x = rand() % 200;
        p.y = rand() % 200;
        points.push_back(p);
    }
}

template <typename T>
void Nuage<T>::importNuage(const std::string path)
{
    std::ifstream file(path.c_str(), std::ios::in);

    Point<T> p;

    if(file)
    {
        std::string line;

        std::getline(file, line);
        std::stringstream ss(line);

        while(!file.eof())
        {
            ss >> p.x >> p.y;
            points.push_back(p);

            ss.clear();
            std::getline(file, line);
            ss.str(line);
        }

        file.close();
    }
    else
        std::cout << "Impossible d'ouvrire" << path << std::endl;
}

template <typename T>
void Nuage<T>::exportNuage(const std::string path) const
{
    std::ofstream file(path.c_str());

    if(file)
    {
        typename std::vector< Point<T> >::const_iterator it = points.begin();

        for(; it != points.end(); ++it)
        {
            file << (*it).x << " " << (*it).y << std::endl;
        }

        file.close();
        std::cout << "Exportation fini" << std::endl;
    }
    else
        std::cout << "Impossible d'ouvrire" << path << std::endl;
}

template <typename T>
void Nuage<T>::ajoutPoint(const T x, const T y)
{
    Point<T> point;
    point.x = x;
    point.y = y;

    points.push_back(point);
}

template <typename T>
void Nuage<T>::ajoutPoint(const Point<T>& point)
{
    points.push_back(point);
}

template <typename T>
void Nuage<T>::enlevePoint(const unsigned int position)
{
    points.erase(points.begin()+position);
}

template <typename T>
std::vector< Point<T> > Nuage<T>::getPoints() const
{
    return points;
}
#endif
