#include "../include/Histogramme.hpp"

//constructeur par defaut
Histogramme::Histogramme()
{
    m_vSeuil.resize(256, 0);
    m_uiNbPixel = 0;
}

//constructeur
Histogramme::Histogramme(const unsigned int taille)
{
    m_vSeuil.resize(taille, 0);
    m_uiNbPixel = 0;
}

//constructeur par copie
Histogramme::Histogramme(const Histogramme& histo) : m_uiNbPixel(histo.m_uiNbPixel), m_vSeuil(histo.m_vSeuil)
{

}

//destructeur
Histogramme::~Histogramme()
{

}

//importation d'un histogramme depuis un fichier txt
void Histogramme::importHisto(const std::string& path)
{
    //déclaration du flux et ouverture du fichier
    std::ifstream file(path.c_str(), std::ios::in);

    if(file)
    {
        std::string line;
        getline(file, line);

        sscanf(line.c_str(),"# %d", &m_uiNbPixel); // recuperation du nombre de pixel

        if(m_vSeuil.size() != 256)
            m_vSeuil.resize(256);

        unsigned int i = 0;
        while(!file.eof())
        {
            getline(file, line);
            sscanf(line.c_str(),"%*d %d", &m_vSeuil.at(i));
            i++;
        }
        file.close();
        std::cout << "Importation fini" << path << std::endl;
    }
    else
        std::cout << "Impossible d'ouvrire" << path << std::endl;
}

//exportation d'un histogramme dans un fichier txt
void Histogramme::exportHisto(const std::string& path)
{
    //déclaration du flux et ouverture du fichier
    std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc);

    if(file)
    {
        file << "# " << m_uiNbPixel << std::endl;
        std::vector<unsigned int>::iterator it = m_vSeuil.begin();
        unsigned int i = 0;

        for(; it != m_vSeuil.end(); it++)
        {
            file << i << " " << *it << std::endl;
            i++;
        }

        file.close();
        std::cout << "Exportation fini" << std::endl;
    }
    else
        std::cout << "Impossible d'ouvrire" << path << std::endl;
}

Histogramme Histogramme::getCumule() const
{
    Histogramme histo(*this);
    unsigned int size = histo.getTaille();
    for(unsigned int i = 1; i < size; i++)
        histo.setValeur(i, histo.getValeur(i)+histo.getValeur(i-1));
    return histo;
}

Histogramme Histogramme::getPlat() const
{
    Histogramme histo(*this);
    unsigned int size = histo.getTaille();
    unsigned int nbPixRestant = histo.getNbPixel();
    unsigned int valeur;
    for(unsigned int i = 0; i < size; i++)
    {
        valeur = nbPixRestant / (size - i);
        histo.setValeur(i, valeur);
        nbPixRestant = nbPixRestant - valeur;
    }
    return histo;
}

Histogramme Histogramme::getDivise(unsigned int nouvNbPix)
{
    Histogramme histo(*this);
    Histogramme histoCumul(getCumule());
    unsigned int size = histo.getTaille();
    unsigned int nbPix = histo.getNbPixel();

    unsigned int nbPixSauv = 0;
    unsigned int valeur;

    for(unsigned int i = 0; i < size; i++)
    {
        valeur = ((histoCumul.getValeur(i) + (getNbPixel() / (nouvNbPix * 2))) * nouvNbPix) / nbPix - nbPixSauv ;
        histo.setValeur(i, valeur);
        nbPixSauv += valeur;
    }
    return histo;
}

void Histogramme::setValeur(const unsigned int i, const unsigned int valeur)
{
    m_uiNbPixel = m_uiNbPixel + valeur - m_vSeuil.at(i);
    m_vSeuil.at(i) = valeur;
}

unsigned int Histogramme::getValeur(unsigned int i) const
{
    return m_vSeuil.at(i);
}

unsigned int Histogramme::getTaille() const
{
    return m_vSeuil.size();
}

unsigned int Histogramme::getNbPixel() const
{
    return m_uiNbPixel;
}
