#ifndef CONTOUR_H
#define CONTOUR_H

#include <complex>

template <typename T>
class Contour
{
private:
    std::vector<std::complex<T> > m_vComplex;
    std::vector<std::complex<T> > m_vFourier;
public:
    Contour();
    ~Contour();

    void addComplex(T x, T i);
    void fourier();
};

template <typename T>
Contour<T>::Contour()
{

}

template <typename T>
Contour<T>::~Contour()
{
    m_vComplex.clear();
}

template <typename T>
void Contour<T>::addComplex(T x, T i)
{
    m_vComplex.push_back(std::complex<T>(x, i));
}

template <typename T>
void Contour<T>::fourier()
{

}

#endif
