#include "../include/FonctionCorresponance.hpp"
FonctionCorrespondance::FonctionCorrespondance()
{
}

FonctionCorrespondance::FonctionCorrespondance(unsigned int vMax)
{
    m_vValeurs.resize(vMax+1);
}

FonctionCorrespondance::FonctionCorrespondance(const std::vector<unsigned int> tableau):m_vValeurs(tableau)
{
}

FonctionCorrespondance::~FonctionCorrespondance()
{
}

unsigned int FonctionCorrespondance::getValeur(unsigned int a) const
{
    return m_vValeurs.at(a);
}


FonctionCorrespondance FonctionCorrespondance::identite(unsigned int vMax)
{
    FonctionCorrespondance fc(vMax);
    for(unsigned int i = 0; i <= vMax; i++)
        fc.m_vValeurs.at(i) = i;

    return fc;
}

FonctionCorrespondance FonctionCorrespondance::inverse(unsigned int vMax)
{
    FonctionCorrespondance fc(vMax);
    for(unsigned int i = 0; i <= vMax; i++)
        fc.m_vValeurs.at(i) = vMax - i;

    return fc;
}

FonctionCorrespondance FonctionCorrespondance::egalisation(Histogramme histo)
{
    unsigned int vMax = histo.getTaille() - 1;
    FonctionCorrespondance fc(vMax);
    Histogramme histoC = histo.getCumule();
    for(unsigned int i = 0; i <= vMax; i++)
    {
        fc.m_vValeurs.at(i) = (vMax * histoC.getValeur(i)) / histo.getNbPixel();
    }
    return fc;
}

FonctionCorrespondance FonctionCorrespondance::specification(Histogramme histo1, Histogramme histo2)
{
    unsigned int vMax = histo1.getTaille() - 1;
    if(histo1.getNbPixel() == histo2.getNbPixel())
    {
        FonctionCorrespondance fc(vMax);

        Histogramme histo1C = histo1.getCumule();
        Histogramme histo2C = histo2.getCumule();

        unsigned int i = 0;
        unsigned int j = 0;

        while(i <= vMax && j <= vMax)
        {
            while(i <= vMax && j <= vMax && histo2C.getValeur(j) >= histo1C.getValeur(i))
            {
                fc.m_vValeurs.at(i) = j;
                i++;
            }
            j++;
        }
        return fc;
    }
    else
    {
        std::cout << "Erreur: Nombre de pixels différents" << std::endl;
        FonctionCorrespondance fc = identite(vMax);
        return fc;
    }
}


