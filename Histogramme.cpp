#include "Histogramme.hpp"

//constructor
Histogramme::Histogramme(){
    m_histogramme.fill(0);
    m_histogramme_cummule.fill(0);
}

void Histogramme::init(GrayLevelImage2D &img){
    unsigned int nbPixel = img.w()*img.h();

    for (GrayLevelImage2D::Iterator i = img.begin(); i != img.end(); ++i) {   //on parcourt tous les pixels de l'image
        m_histogramme[*i] += 1.0/nbPixel;   //on incrémente la proportion au bon indice
    }
    // on crée ensuite l'histogramme cummulé
    m_histogramme_cummule = m_histogramme;
    for (int j = 1; j <= m_histogramme.size()-1; ++j) {
        m_histogramme_cummule[j] += m_histogramme_cummule[j-1];
    }

}

unsigned int Histogramme::egalisation(int j) const {
    return (unsigned int)(255*m_histogramme_cummule[j]);
}
