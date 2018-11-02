#ifndef TP1_HISTOGRAMME_HPP
#define TP1_HISTOGRAMME_HPP

#include <array>
#include "GrayLevelImage2D.hpp"

class Histogramme {
public:
    typedef std::array<double, 256> tabValue;

    Histogramme();
    void init(GrayLevelImage2D &img);
    /**
    @param j prend une valeur de niveau de gris en entrée
    @return et retourne une autre valeur de niveau de gris basée sur l'histogramme cummulé croissant
    */
    unsigned int egalisation( int j ) const;

private:
    tabValue m_histogramme;
    tabValue m_histogramme_cummule;
};


#endif
