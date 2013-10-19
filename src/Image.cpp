#include "../include/Image.hpp"

Image::Image(): Contenu2D <unsigned int>(0, 0), m_uiType(PGM), m_uiValeurMax(0)
{

}

Image::Image(const unsigned int t, const unsigned int w, const unsigned int h): Contenu2D <unsigned int>(w, h), m_uiType(t), m_uiValeurMax(255)
{
    unsigned int taille = m_uiLargeur*m_uiHauteur;
    if(m_uiType == PPM)
    {
        taille = taille*3;
    }
    setTaille(taille, 0);
}

Image::Image(const std::string& path)
{
    importImage(path);
}

Image::Image(const Image& other): Contenu2D <unsigned int>(other.m_vValeurs, other.m_uiLargeur, other.m_uiHauteur), m_uiType(other.m_uiType), m_uiValeurMax(other.m_uiValeurMax)
{

}

Image::~Image()
{

}

unsigned int Image::importImage(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ios::in);

    if(file)
    {
        std::string line;
        std::getline(file, line);

        // ascii & binaire
        if(line == "P2" || line == "P5")
        {
            m_uiType = PGM;

            unsigned enAscii;
            if(line == "P2")
                enAscii = 1;
            else
                enAscii = 0;

            //On ignore les commentaires
            getline(file, line);
            while(!file.eof() && line[0]=='#')
                getline(file, line);

            //Sinon la derniere ligne lue contient des valeurs (hauteur, largeur)
            unsigned int width, height;
            sscanf(line.c_str(),"%d %d",&width, &height);
            setTaille(width, height);

            //On recupere la valeur maximale d'un pixel
            file >> m_uiValeurMax;

            unsigned int nbPixels = width * height;
            unsigned int i = 0;

            if(enAscii) //P2
            {
                //Premiere valeur
                int valeur;
                file >> valeur;

                //Valeurs pour chaque pixel
                while(!file.eof() && i < nbPixels)
                {
                    set(i, 0, valeur);
                    i++;
                    file >> valeur;
                }
                file.close();
            }
            else //Binaire P5
            {
                //Fermeture du fichier
                file.close();

                //Reouverture en mode binaire
                std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);

                if(file)
                {
                    //On ignore les commentaires et les 2 premieres lignes (dimensions et valeur maximum d'une couleur)
                    getline(file, line);
                    getline(file, line);
                    while(!file.eof() && line[0]=='#')
                        getline(file, line);
                    getline(file, line);

                    //Premiere valeur recuperee
                    unsigned char valeur;
                    file.read((char*) &valeur, sizeof(char));
                    unsigned int i = 0;

                    //Valeurs pour chaque pixel
                    while(!file.eof() && i < nbPixels)
                    {
                        set(i, 0, valeur);
                        i++;
                        file.read((char*) &valeur, sizeof(char));
                    }
                }
            }
        }
        else if(line == "P3")
            m_uiType = PPM;
        else if(line == "P6")
            m_uiType = PPM;
        else
        {
            std::cout << "Mauvais format" << std::endl;
            file.close();
            return 0;
        }
        file.close();
        return 1;
    }
    else
    {
        std::cout << "Impossible d'ouvrire" << path << std::endl;
        return 0;
    }
}

void Image::exportImage(const std::string& path, const int mod) const
{
    std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc);
    if(file)
    {
        if(mod == ASCII || mod == BINAIRE)
        {
            if(mod == ASCII)
                file << "P2" << std::endl;
            else
                file << "P5" << std::endl;

            file << "# Koujoukou" << std::endl;

            file << m_uiLargeur << " " << m_uiHauteur << std::endl;

            file << m_uiValeurMax << std::endl;

            unsigned int nbPixels = getTaille();
            if(mod == ASCII)
            {
                for(unsigned int i=0; i<nbPixels;i++)
                    file << m_vValeurs.at(i) << std::endl;
            }
            else
            {
                //Fermeture du fichier
                file.close();

                //Reouverture en mode binaire
                std::ofstream file(path.c_str(), std::ios::out | std::ios::app | std::ios::binary);

                unsigned char entier;
                for(unsigned int i=0; i<nbPixels;i++)
                {
                    entier = m_vValeurs.at(i);
                    file.write((char*) &entier, sizeof(entier));
                }
            }
        }
        file.close();
        std::cout << "Exportation fini" << std::endl;
    }
    else
        std::cout << "Impossible d'ouvrire" << path << std::endl;
}

unsigned int Image::getValeurMax() const
{
    return m_uiValeurMax;
}

Histogramme Image::getHistogramme() const
{
    Histogramme histo;

    if(!m_vValeurs.empty())
    {
        std::vector<unsigned int>::const_iterator it = m_vValeurs.begin();

        for(; it != m_vValeurs.end(); ++it)
            histo.setValeur(*it, histo.getValeur(*it)+1);
    }
    else
        std::cout << "Aucune valeur pour l'histogramme" << std::endl;

    return histo;
}

void Image::appliqueFC(FonctionCorrespondance &fc)
{
    for(unsigned int j = 0; j < m_uiHauteur; j++)
        for(unsigned int i = 0; i < m_uiLargeur; i++)
            set(i, j, fc.getValeur(at(i,j)));
}

