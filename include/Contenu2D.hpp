#ifndef CONTENU2D_HPP
#define CONTENU2D_HPP

#include <vector>
#include <iostream>

template <typename T>
class Contenu2D
{
protected:
    std::vector<T> m_vValeurs;
    unsigned int m_uiLargeur;
    unsigned int m_uiHauteur;
    
    inline Contenu2D() {}
    inline Contenu2D(unsigned int width, unsigned int height) {m_uiLargeur = width; m_uiHauteur = height; m_vValeurs.resize(m_uiLargeur*m_uiHauteur);}
    inline Contenu2D(std::vector<T> valeurs, unsigned int width, unsigned int height) {m_vValeurs = valeurs; m_uiLargeur = width; m_uiHauteur = height;}
    inline Contenu2D(std::vector<T> valeurs) {m_vValeurs = valeurs;}
    
public:
    inline T at(const unsigned int x, const unsigned int y) const {return m_vValeurs.at(y*m_uiLargeur+x);}
    inline void set(const unsigned int x, const unsigned int y, const T value) {m_vValeurs.at(y*m_uiLargeur+x) = value;}
    inline void setTaille(const unsigned int width, const unsigned int height) {m_uiLargeur = width; m_uiHauteur = height; m_vValeurs.resize(m_uiLargeur*m_uiHauteur);}

    inline unsigned int getLargeur() const {return m_uiLargeur;}
    inline unsigned int getHauteur() const {return m_uiHauteur;}
    inline unsigned int getTaille() const {return m_uiLargeur*m_uiHauteur;}
    
    inline std::vector<T> getLigne(unsigned int l) const {std::vector<T> out; for(int i=0; i<m_uiLargeur; i++) out.push_back(this->at(i,l)); return out;}
    inline std::vector<T> getColonne(unsigned int l) const {std::vector<T> out; for(int i=0; i<m_uiHauteur; i++) out.push_back(this->at(l,i)); return out;}
    inline void setLigne(unsigned int l, std::vector<T> v) {for(int i=0; i<m_uiLargeur; i++) this->set(i, l, v.at(i));}
    inline void setColonne(unsigned int l, std::vector<T> v) {for(int i=0; i<m_uiHauteur; i++) this->set(l, i, v.at(i));}
};

#endif // CONTENU2D_HPP
