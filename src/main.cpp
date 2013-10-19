#include "../include/Image.hpp"

int main (int argc, char* argv[])
{
	// Initialisation
    std::string path1 = "./images/baboon.pgm";
    std::string path1Ecriture = "./images/photoEcriture.pgm";
    std::string path2 = "./images/photoBrut.pgm";
    std::string path2Ecriture = "./images/photoInvEcriture.pgm";
    std::string path3Ecriture = "./images/photoEgalEcriture.pgm";

    std::string path1Histo = "./histogrammes/Histo.txt";

    Image myImage1(path1);
    Image myImage2(myImage1);

    std::cout << "pixel at 0, 0 :" << myImage1.at(0, 0) << std::endl;
    std::cout << "pixel at 1, 0 :" << myImage1.at(1, 0) << std::endl;
    std::cout << "pixel at 2, 0 :" << myImage1.at(2, 0) << std::endl;
    std::cout << "pixel at 3, 0 :" << myImage1.at(3, 0) << std::endl;
    std::cout << "pixel at 4, 0 :" << myImage1.at(4, 0) << std::endl;
    std::cout << "pixel at 5, 0 :" << myImage1.at(5, 0) << std::endl;
    myImage1.set(0, 0, 205);
    std::cout << "pixel at 0, 0 :" << myImage1.at(0, 0) << std::endl;

    std::cout << "pixel at 0, 0 :" << myImage2.at(0, 0) << std::endl;
    std::cout << "pixel at 1, 0 :" << myImage2.at(1, 0) << std::endl;
    std::cout << "pixel at 2, 0 :" << myImage2.at(2, 0) << std::endl;
    std::cout << "pixel at 3, 0 :" << myImage2.at(3, 0) << std::endl;
    std::cout << "pixel at 4, 0 :" << myImage2.at(4, 0) << std::endl;
    std::cout << "pixel at 5, 0 :" << myImage2.at(5, 0) << std::endl;

    myImage1.exportImage(path1Ecriture,BINAIRE);

    Histogramme histo1 = myImage1.getHistogramme();
    histo1.exportHisto(path1Histo);

    FonctionCorrespondance egal = FonctionCorrespondance::egalisation(myImage2.getValeurMax(), myImage2.getHistogramme());

    myImage2.appliqueFC(egal);
    myImage2.exportImage(path2Ecriture,BINAIRE);

    Image myImage3(myImage2);
    FonctionCorrespondance inv = FonctionCorrespondance::inverse(myImage3.getValeurMax());

    myImage3.appliqueFC(inv);
    myImage3.exportImage(path3Ecriture,BINAIRE);

    return 0;
}
