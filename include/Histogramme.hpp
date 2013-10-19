#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

class Histogramme
{
private:
    unsigned int m_uiNbPixel;
    std::vector<unsigned int> m_vSeuil;

public:
    Histogramme();
    Histogramme(const unsigned int taille);
    Histogramme(const Histogramme& histo);
    ~Histogramme();

    void importHisto(const std::string& path);
    void exportHisto(const std::string& path);

    Histogramme getCumule() const;

    void setValeur(const unsigned int i, const unsigned int valeur);
    unsigned int getValeur(unsigned int i) const;
    unsigned int getTaille() const;
    unsigned int getNbPixel() const;


};

#endif //HISTOGRAMME_HPP
