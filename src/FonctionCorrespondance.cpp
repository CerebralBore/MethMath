#include "../include/FonctionCorresponance.hpp"

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

FonctionCorrespondance FonctionCorrespondance::inverse(unsigned int vMax)
{
    FonctionCorrespondance fc(vMax);
    for(unsigned int i = 0; i <= vMax; i++)
        fc.m_vValeurs.at(i) = vMax - i;

    return fc;
}

FonctionCorrespondance FonctionCorrespondance::egalisation(unsigned int vMax, Histogramme histo)
{
    FonctionCorrespondance fc(vMax);
    Histogramme histoC = histo.getCumule();
    std::cout << "histo :" << histo.getValeur(30) << std::endl;
    std::cout << "histoC :" << histoC.getValeur(30) << std::endl;
    std::cout << "histoC :" << histoC.getValeur(255) << std::endl;
    std::cout << "nbPix :" << histo.getNbPixel() << std::endl;
    for(unsigned int i = 0; i <= vMax; i++)
    {
        fc.m_vValeurs.at(i) = (vMax * histoC.getValeur(i)) / histo.getNbPixel();
    }
    return fc;
}
