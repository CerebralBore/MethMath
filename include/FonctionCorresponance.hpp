#ifndef FONCTIONCORRESPONDANCE
#define FONCTIONCORRESPONDANCE

#include <vector>
#include <stdio.h>
#include "Histogramme.hpp"

class FonctionCorrespondance
{
protected:
    std::vector<unsigned int> m_vValeurs;
public:
    FonctionCorrespondance();
    FonctionCorrespondance(unsigned int vMax);
    FonctionCorrespondance(const std::vector<unsigned int> tableau);
    ~FonctionCorrespondance();
    unsigned int getValeur(unsigned int a) const;

    static FonctionCorrespondance identite(unsigned int vMax);
    static FonctionCorrespondance inverse(unsigned int vMax);
    static FonctionCorrespondance egalisation(Histogramme histo);
    static FonctionCorrespondance specification(Histogramme histo1, Histogramme histo2);
};

#endif
