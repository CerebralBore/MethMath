#ifndef ORGANISATION_H
#define ORGANISATION_H


#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Nuage.hpp"
#include "Groupe.hpp"

template <typename T>
class Organisation
{
private:
    Nuage<T> nuage;
    std::vector< Groupe<T> > groupes;

    typedef double (Organisation::*Fonction)(const Point<T>&, const Point<T>&);

    void randomCentres(const unsigned int);

    void calculNvCentre(Groupe<T>&);

    double euclidienneD(const Point<T>&, const Point<T>&);
    double manhattanD(const Point<T>&, const Point<T>&);

public:
    enum Distance{EUCLIDIENNE, MANHATTAN};

    Organisation();
    Organisation(const Nuage<T>&);
    Organisation(const Organisation& other);
    ~Organisation();

    void exportOrganisation(const std::string&);

    void kMoy(const unsigned int, const unsigned int, Distance);

    Nuage<T> getNuage() const;

    int getNbGroupe() const;
    Point<T>  getCentreGroupe(int i) const;
    Nuage<T> getNuageGroupe(int i) const;


};

template <typename T>
Organisation<T>::Organisation()
{

}

template <typename T>
Organisation<T>::Organisation(const Organisation& other) : nuage(other.getNuage())
{

}

template <typename T>
Organisation<T>::Organisation(const Nuage<T>& nuage)
{
    this->nuage = nuage;
}

template <typename T>
Organisation<T>::~Organisation()
{
    groupes.clear();
}

template <typename T>
void Organisation<T>::exportOrganisation(const std::string& path)
{
    std::ofstream file(path.c_str());

    if(file)
    {
        typename std::vector< Groupe<T> >::iterator it = groupes.begin();

        for(; it != groupes.end(); ++it)
        {
            file << "centre " << it->getCentre().x << " " << it->getCentre().y << std::endl;

            const unsigned int size = it->getNuageTaille();
            for(unsigned int i=0; i<size; i++)
                file << it->getNuageValeur(i).x << " " << it->getNuageValeur(i).y << std::endl;
        }
        file.close();
        std::cout << "Exportation fini" << std::endl;
    }
    else
        std::cout << "Impossible d'ouvrire" << path << std::endl;
}

template <typename T>
void Organisation<T>::kMoy(const unsigned int k, const unsigned int t, Distance choix)
{
    Fonction fonctionDistance;

    switch(choix)
    {
        case EUCLIDIENNE :
            fonctionDistance = &Organisation::euclidienneD;
            break;
        case MANHATTAN :
            fonctionDistance = &Organisation::manhattanD;
            break;
        default:
            break;
    }

    randomCentres(k);

    unsigned int iteration = 0;
    unsigned int nbPoints = nuage.getTaille();
    unsigned int nbClasses = groupes.size();
    unsigned int indice;
    double dist;
    double nvDist;

    std::cout << "nbPoints " << nbPoints << std::endl;

    do
    {
        for(unsigned int i=0; i<nbPoints; i++)
        {
            dist = ((*this).*fonctionDistance)(groupes[0].getCentre(), nuage.getValeur(i));
            indice = 0;

            for(unsigned int j=1; j<nbClasses; j++)
            {
                nvDist = ((*this).*fonctionDistance)(groupes[j].getCentre(), nuage.getValeur(i));

                if(nvDist < dist)
                {
                    dist = nvDist;
                    indice = j;
                }
            }

            groupes[indice].ajoutPointNuage(nuage.getValeur(i));
        }
        for(unsigned int i=0; i<nbClasses; i++)
            calculNvCentre(groupes[i]);

        iteration++;
    }
    while(iteration<t);
}

template <typename T>
void Organisation<T>::randomCentres(const unsigned int k)
{
    unsigned int position;

    srand(time(NULL));

    for(unsigned int i=0; i<k; i++)
    {
        position = rand()%(nuage.getTaille());

        Groupe<T> groupe;
        groupe.setCentre(nuage.getValeur(position));

        groupes.push_back(groupe);
    }
}

template <typename T>
void Organisation<T>::calculNvCentre(Groupe<T>& groupe)
{
    unsigned int nbPoints = groupe.getNuageTaille();
    double baryX = 0;
    double baryY = 0;

    for(unsigned int i=0; i<nbPoints; i++)
    {
        baryX += groupe.getNuageValeur(i).x;
        baryY += groupe.getNuageValeur(i).y;
    }

    Point<T> point;
    point.x = baryX/nbPoints;
    point.y = baryY/nbPoints;

    groupe.setCentre(point);
}

template <typename T>
double Organisation<T>::euclidienneD(const Point<T>& centre, const Point<T>& point)
{
    return (pow((centre.x-point.x), 2) + pow((centre.y-point.y), 2));
}

template <typename T>
double Organisation<T>::manhattanD(const Point< T >& centre, const Point< T >& point)
{
    return (abs(centre.x-point.x) + abs(centre.y-point.y));
}

template <typename T>
Nuage<T> Organisation<T>::getNuage() const
{
    return nuage;
}

template <typename T>
int Organisation<T>::getNbGroupe() const
{
    return groupes.size();
}

template <typename T>
Point<T>  Organisation<T>::getCentreGroupe(int i) const
{
    return groupes.at(i).getCentre();
}

template <typename T>
Nuage<T> Organisation<T>::getNuageGroupe(int i) const
{
    return groupes.at(i).getNuage();
}

#endif
