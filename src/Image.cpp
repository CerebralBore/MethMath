#include "../include/Image.hpp"

Image::Image(): Contenu2D <unsigned int>(0, 0), m_uiType(PGM), m_uiValeurMax(0)
{

}

Image::Image(const unsigned int t, const unsigned int w, const unsigned int h): Contenu2D <unsigned int>(w, h), m_uiType(t), m_uiValeurMax(255)
{
    if(m_uiType == PPM)
    {
        setTaille(m_uiLargeur*3, m_uiHauteur*3);
    }
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

Image Image::getZone(unsigned int i, unsigned int j, unsigned int largeur, unsigned int hauteur)
{
    unsigned int xMin = i < (largeur / 2) ? 0 : i - (largeur / 2);
    unsigned int yMin = j < (hauteur / 2) ? 0 : j - (hauteur / 2);
    unsigned int xMax = (i + (largeur / 2) >= m_uiLargeur) ? m_uiLargeur - 1 : i + (largeur / 2);
    unsigned int yMax = (j + (hauteur / 2) >= m_uiHauteur) ? m_uiHauteur - 1 : j + (hauteur / 2);

    unsigned int nouvelleLargeur = xMax - xMin + 1;
    unsigned int nouvelleHauteur = yMax - yMin + 1;


    Image imgZone(m_uiType, nouvelleLargeur, nouvelleHauteur);

    for(unsigned int j = 0; j < nouvelleHauteur; j++)
    {
        for(unsigned int i = 0; i < nouvelleLargeur; i++)
        {
            imgZone.set(i, j, at(xMin + i, yMin + j));
        }
    }

    return imgZone;
}

Image Image::specificationGlissante(Histogramme histo, unsigned int largeur, unsigned int hauteur)
{
    Image imgSortie(*this);
    Image imgZone;
    Histogramme histoZone;
    unsigned int nbPix = 0;
    FonctionCorrespondance fc;

    for(unsigned int j = 0; j < m_uiHauteur; j++)
    {
        for(unsigned int i = 0; i < m_uiLargeur; i++)
        {
            imgZone = getZone(i, j, largeur, hauteur);
            if(imgZone.getTaille() != nbPix)
            {
                histoZone = histo.getDivise(imgZone.getTaille());
                nbPix = imgZone.getTaille();
            }
            //fc = FonctionCorrespondance::egalisation(imgZone.getHistogramme());
            fc = FonctionCorrespondance::specification(imgZone.getHistogramme(), histoZone);
            imgSortie.set(i, j, fc.getValeur(at(i, j)));
        }
    }
    return imgSortie;
}

Image Image::filtreMedian()
{
    unsigned int largeur = 3;
    unsigned int hauteur = 3;
    Image imgSortie(*this);
    Image imgZone;
    unsigned int tableau[9];
    unsigned int modif = false;
    unsigned int tmp;
    unsigned int moy;
    for(unsigned int j = 0; j < m_uiHauteur; j++)
    {
        for(unsigned int i = 0; i < m_uiLargeur; i++)
        {
            moy = 0;
            imgZone = getZone(i, j, largeur, hauteur);
            for(unsigned int k = 0; k < imgZone.getHauteur(); k++)
            {
                for(unsigned int l = 0; l < imgZone.getLargeur(); l++)
                {
                    tableau[k*imgZone.getLargeur()+l] = imgZone.at(l,k);
                    moy += imgZone.at(l,k);
                }
            }

            if(abs((moy - at(i, j)) / (imgZone.getTaille() - 1) - at(i, j)) > 25)
            {
                do
                {
                    modif = false;
                    for(unsigned int m = 0; m < imgZone.getTaille() - 1; m++)
                    {
                        if(tableau[m] > tableau[m + 1])
                        {
                            tmp = tableau[m + 1];
                            tableau[m + 1] = tableau[m];
                            tableau[m] = tmp;
                            modif = true;
                        }
                    }

                }while(modif == true);
                imgSortie.set(i, j, tableau[imgZone.getTaille() / 2]);
            }
        }
    }
    return imgSortie;
}
