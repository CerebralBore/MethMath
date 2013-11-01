#include "../include/Image.hpp"
#include "../include/Organisation.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <time.h>

/*void dessineP(cv::mat& img, int x, int y, cv::Vec3f coul)
{
    img.at<cv::Vec3f>(x * 3, i * 3) = coul;

    img.at<cv::Vec3f>(x * 3 + 2, y * 3) = coul;

    img.at<cv::Vec3f>(x * 3, y * 3 + 2) = coul;

    img.at<cv::Vec3f>(x * 3 + 2, y * 3 + 2) = coul;

    img.at<cv::Vec3f>(x * 3 + 1, y * 3 + 1) = coul;
}*/

int main (int argc, char* argv[])
{
	// Initialisation
    std::string path1 = "./images/casablanca.pgm";
    std::string pathInv = "./images/photoInvEcriture.pgm";
    std::string pathEgal = "./images/photoEgalEcriture.pgm";
    std::string pathSpe = "./images/photoSpeEcriture.pgm";
    std::string pathSpeGli = "./images/photoSpeGliEcriture.pgm";
    std::string pathIdent = "./images/photoIdentEcriture.pgm";
    std::string pathMed = "./images/photoMedEcriture.pgm";

    std::string path1Histo = "./histogrammes/Histo.txt";

    char key = '-';

//-----------------------------------------------------------------------------

    Image myImage1(path1);
    Image myImage2;
    FonctionCorrespondance fc;

    int w = 600;

    cv::Mat img = cv::imread(path1);
    cv::Mat imgNuage(w, w, CV_32FC3);
    cv::Scalar coul;

    cv::imshow("original", img);

    while(key != 'q' && key != 'Q')
    {
        key = '-';
        std::cout << "i : modification d'image" << std::endl << "n : nuage de points" << std::endl;
        while(key != 'q' && key != 'Q' && key != 'i' && key != 'n') key = cvWaitKey(50);
        if(key == 'i')
        {
            std::cout << "a : fc identite" << std::endl << "z : fc inverse" << std::endl << "e : fc egalisation" << std::endl << "r : fc specification" << std::endl << "t : fc specification glissante" << std::endl << "y : filtre median" << std::endl;
            key = cvWaitKey();
            if(key == 'a')
            {
                //fc identite
                myImage2 = myImage1;
                fc = FonctionCorrespondance::identite(myImage2.getValeurMax());
                myImage2.appliqueFC(fc);
                myImage2.exportImage(pathIdent, BINAIRE);
                img = cv::imread(pathIdent);
                cv::imshow("identite", img);
            }

            if(key == 'z')
            {
                //fc inverse
                myImage2 = myImage1;
                fc = FonctionCorrespondance::inverse(myImage2.getValeurMax());
                myImage2.appliqueFC(fc);
                myImage2.exportImage(pathInv, BINAIRE);
                img = cv::imread(pathInv);
                cv::imshow("inverse", img);
            }

            if(key == 'e')
            {
                //fc egalisation
                myImage2 = myImage1;
                fc = FonctionCorrespondance::egalisation(myImage2.getHistogramme());
                myImage2.appliqueFC(fc);
                myImage2.exportImage(pathEgal, BINAIRE);
                img = cv::imread(pathEgal);
                cv::imshow("egalisation", img);
            }

            if(key == 'r')
            {
                //fc specification
                myImage2 = myImage1;
                fc = FonctionCorrespondance::specification(myImage2.getHistogramme(), myImage2.getHistogramme().getPlat());
                myImage2.appliqueFC(fc);
                myImage2.exportImage(pathSpe, BINAIRE);
                img = cv::imread(pathSpe);
                cv::imshow("specification", img);
            }

            if(key == 't')
            {
                //fc specification glissante
                myImage2 = myImage1;
                myImage2 = myImage2.specificationGlissante(myImage2.getHistogramme().getPlat(), 21, 21);
                myImage2.exportImage(pathSpeGli, BINAIRE);
                img = cv::imread(pathSpeGli);
                cv::imshow("specification glissante", img);
            }

            if(key == 'y')
            {
                //filtre median
                myImage2 = myImage1;
                myImage2 = myImage2.filtreMedian();
                myImage2.exportImage(pathMed,BINAIRE);
                img = cv::imread(pathMed);
                cv::imshow("filtre median", img);
            }
        }

        if(key == 'n')
        {
            //nuage de points
            Nuage<int> nuage;
            int nbP = 0;
            std::cout << "combien de points dans le nuage ?" << std::endl;
            std::cin >> nbP;
            nuage.randNuage(nbP);
            Organisation<int> organisation(nuage);

            for(int i = 0; i < imgNuage.rows; i++)
                for(int j = 0; j < imgNuage.cols; j++)
                    imgNuage.at<cv::Vec3f>(i, j) = cv::Vec3f(0, 0, 0);

            for(unsigned int i = 0; i < nuage.getTaille(); i++)
            {
                cv::circle(imgNuage, cv::Point(nuage.getValeur(i).x * 3 + 1, w - nuage.getValeur(i).y * 3 + 1), 2, cv::Scalar(0, 0, 1), 0, 8);
            }
            cv::imshow("nuage de points", imgNuage);
            cvWaitKey();

            std::cout << "combien de centres ?" << std::endl;
            std::cin >> nbP;

            organisation.kMoy(nbP,1, Organisation<int>::EUCLIDIENNE);

            srand (time(NULL));
            for(int i = 0; i < organisation.getNbGroupe(); i++)
            {
                coul[0] = rand() / (float) RAND_MAX;
                coul[1] = rand() / (float) RAND_MAX;
                coul[2] = rand() / (float) RAND_MAX;

                cv::circle(imgNuage, cv::Point(organisation.getCentreGroupe(i).x * 3 + 1, w - organisation.getCentreGroupe(i).y * 3 + 1), 2, coul, -1, 8);

                for(unsigned int j = 0; j < organisation.getNuageGroupe(i).getTaille(); j++)
                {
                    cv::circle(imgNuage, cv::Point(organisation.getNuageGroupe(i).getValeur(j).x * 3 + 1, w - organisation.getNuageGroupe(i).getValeur(j).y * 3 + 1), 2, coul, 0, 8);
                }
            }
            cv::imshow("nuage de points", imgNuage);

            organisation.exportOrganisation("./images/classification.txt");
        }
    }


    cvDestroyAllWindows();


    return 0;
}
