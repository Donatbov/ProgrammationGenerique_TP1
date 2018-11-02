#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include "Histogramme.hpp"

using namespace std;
typedef GrayLevelImage2D::GrayLevel GrayLevel;
typedef GrayLevelImage2D::Iterator Iterator;

void double_brightness(GrayLevelImage2D& img);
void filtrageMedian(GrayLevelImage2D& img, int k=1);
void convolution(GrayLevelImage2D& img, char c, double alpha=0.8);
void egalise(GrayLevelImage2D& img);
int main( int argc, char** argv )
{
   /* {
       //! [tgli2d-sec3]
        GrayLevelImage2D img( 8, 8, 5 ); // imagette 8x8 remplie de 5
        for ( unsigned int y = 0; y < img.h(); ++y )
            for (unsigned int x = 0; x < img.w(); ++x ) {
                std::cout << " " << (int) img.at(x,
                                                 y); // la conversion permet de voir les caractères sous forme d'entiers non signés.
            }
        std::cout << std::endl;
        //! [tgli2d-sec3]
    }
    {
        GrayLevelImage2D img( 8, 8, 5 ); // imagette 8x8 remplie de 5
        //! [tgli2d-sec4]
        for ( GrayLevelImage2D::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
            std::cout << " " << (int) *it; // la conversion permet de voir les caractères sous forme d'entiers.
        //! [tgli2d-sec4]
    }*/

    //  import
    if(argv[1] && argv[2]) {
        GrayLevelImage2D img;
        ifstream input(argv[1]);
        try {
            img.importPGM(input);
        }
        catch (char const *msg) {
            std::cerr << "Exception: " << msg << std::endl;
        }
        catch (...) {
            std::cerr << "Exception." << std::endl;
        }
        input.close();

        if (argv[3] && std::string(argv[3]) == "double-brightness") {
            double_brightness(img);
        } else if (argv[3] && std::string(argv[3]) == "filtrage-median") {
            if (argv[4]) {
                filtrageMedian(img, atoi(argv[4]));
            } else {
                filtrageMedian(img);
            }
        } else if (argv[3] && std::string(argv[3]) == "egalisation"){
            egalise(img);
        } else if (argv[3] && std::string(argv[3]) == "convolution"){
            if (argv[4]) {
                if (argv[5]) {
                    convolution(img, argv[4][0], stod(argv[5]));
                }
                else
                    convolution(img, argv[4][0]);
            }else{
                std::cout << "Pas de argv[4], attendu :\"M\" ou \"L\" ou \"R suivi de alpha\"..."<< std::endl;
            }
        } else {
            std::cout << "Pas de argv[3], attendu : \"double-brighness\" ou \"filtrage-median {k}\" ou \"egalisation\"..."
                      << std::endl << "Image sans traitement exportée vers " << argv[2] << ".";
        }

        //  export
        ofstream output(argv[2]);
        img.exportPGM(output, false);
        output.close();
        std::cout << std::endl;

    }
    else{
        std::cout << "Pas de argv[1] et/ou argv[2], attendus : fichier_d_entree "
                  << "fichier_de_sortie \"double-brighness\" ou \"filtrage-median {k}\" ou \"egalisation\" ";
    }
    return 0;
}

void double_brightness(GrayLevelImage2D& img){
    // double la luminosité
    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    {
        *it = (2*((int)(*it))) % 256;
    }
    std::cout << "Luminosité doublée." << std::endl;
}

void filtrageMedian(GrayLevelImage2D& img, int k){
    std::cout << "Filtrage median, voisinnage k=" << k << "." << std::endl;
    img.filtrageMedian(k);
}

void convolution(GrayLevelImage2D& img, char c, double alpha){
    std::cout << "Filtrage par convolution, alpha k=" << alpha << "." << std::endl;
    img.genereEtConv(c, alpha);
}


void egalise(GrayLevelImage2D& img) {
    //egalisation d'histogramme
    Histogramme h;
    h.init(img);
    for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
        *it = (unsigned char) h.egalisation(*it);
    }
    std::cout << "Histogramme égalisé." << std::endl;

}
