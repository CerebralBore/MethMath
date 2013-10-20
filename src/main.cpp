#include "../include/Image.hpp"
#include "../include/Organisation.hpp"

int main (int argc, char* argv[])
{
	// Initialisation
    std::string path1 = "./images/baboon.pgm";
    std::string path1Ecriture = "./images/photoEcriture.pgm";
    std::string path2 = "./images/photoBrut.pgm";
    std::string pathInv = "./images/photoInvEcriture.pgm";
    std::string pathEgal = "./images/photoEgalEcriture.pgm";
    std::string pathSpe = "./images/photoSpeEcriture.pgm";
    std::string pathSpeGli = "./images/photoSpeGliEcriture.pgm";
    std::string pathIdent = "./images/photoIdentEcriture.pgm";

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

    FonctionCorrespondance ident = FonctionCorrespondance::identite(myImage2.getValeurMax());
    myImage2.appliqueFC(ident);
    myImage2.exportImage(pathIdent,BINAIRE);

    Image myImage3(myImage1);
    Histogramme histo3 = myImage3.getHistogramme();
    FonctionCorrespondance spe = FonctionCorrespondance::specification(histo3, histo3.getPlat());
    myImage3.appliqueFC(spe);
    myImage3.exportImage(pathSpe,BINAIRE);

    myImage2 = myImage2.specificationGlissante(myImage2.getHistogramme().getPlat(), 21, 21);
    myImage2.exportImage(pathSpeGli,BINAIRE);

    Nuage<int> nuage;
    nuage.importNuage("./images/points.txt");
    Organisation<int> organisation(nuage);
    organisation.kMoy(2,1, Organisation<int>::EUCLIDIENNE);
    organisation.exportOrganisation("./images/classification.txt");

    return 0;
}
