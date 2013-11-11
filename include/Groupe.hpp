#ifndef GROUPE_H
#define GROUPE_H

#include "Nuage.hpp"

template <typename T>
class Groupe
{
private:
    Point<T> centre;
    Nuage<T> nuage;

public:
    void ajoutPointNuage(const Point<T>&);
    void videNuage();

    Point<T> getCentre() const;
    Nuage<T> getNuage() const;
    unsigned int getNuageTaille() const;
    Point<T> getNuageValeur(const unsigned int) const;

    void setCentre(const Point<T>&);
};

template <typename T>
void Groupe<T>::ajoutPointNuage(const Point<T>& point)
{
    nuage.ajoutPoint(point);
}

template <typename T>
void Groupe<T>::videNuage()
{
    nuage.videNuagePoint();
}

template <typename T>
Point<T> Groupe<T>::getCentre() const
{
    return centre;
}

template <typename T>
Nuage<T> Groupe<T>::getNuage() const
{
    return nuage;
}

template <typename T>
unsigned int Groupe<T>::getNuageTaille() const
{
    return nuage.getTaille();
}

template <typename T>
Point<T> Groupe<T>::getNuageValeur(const unsigned int i) const
{
    return nuage.getValeur(i);
}

template <typename T>
void Groupe<T>::setCentre(const Point<T>& c)
{
    centre = c;
}

#endif
