#ifndef IMAGE_HPP
#define IMAGE_HPP

#define ASCII 0
#define BINAIRE 1
#define PPM 0
#define PGM 1

#include "Histogramme.hpp"
#include "Contenu2D.hpp"
#include "FonctionCorresponance.hpp"

class Image : public Contenu2D <unsigned int>
{
private:
    unsigned int m_uiType;
    unsigned int m_uiValeurMax;

public:
    Image();
    Image(const unsigned int t, const unsigned int w, const unsigned int h);
    Image(const std::string& path);
    Image(const Image& other);
    ~Image();

    unsigned int importImage(const std::string& path);
    void exportImage(const std::string& path, const int mod) const;

    unsigned int getValeurMax() const;

    Histogramme getHistogramme() const;

    void appliqueFC(FonctionCorrespondance &fc);

    Image getZone(unsigned int i, unsigned int j, unsigned int largeur, unsigned int hauteur);
    Image specificationGlissante(Histogramme histo, unsigned int largeur, unsigned int hauteur);
    Image filtreMedian();

};

#endif // IMAGE_HPP
