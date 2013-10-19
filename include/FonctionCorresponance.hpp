#ifndef FONCTIONCORRESPONDANCE
#define FONCTIONCORRESPONDANCE

#include <vector>
#include "Histogramme.hpp"

class FonctionCorrespondance
{
protected:
    std::vector<unsigned int> m_vValeurs;
public:
    FonctionCorrespondance(unsigned int vMax);
    FonctionCorrespondance(const std::vector<unsigned int> tableau);
    ~FonctionCorrespondance();
    unsigned int getValeur(unsigned int a) const;

    static FonctionCorrespondance inverse(unsigned int vMax);
    static FonctionCorrespondance egalisation(unsigned int vMax, Histogramme histo);
};

#endif
