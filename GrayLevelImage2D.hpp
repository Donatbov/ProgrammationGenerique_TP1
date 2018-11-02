#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères


using std::ifstream;
using std::stringstream;
using std::string;

class GrayLevelImage2D {

public:
    typedef unsigned char          GrayLevel;// le type pour les niveaux de gris.
    typedef std::vector<GrayLevel> Container;// le type pour stocker les niveaux de gris de l'image.
    typedef std::vector<std::vector<double>> Masque;// le type pour les masques de convolution


    /**
       Représente un itérateur sur toutes les valeurs d'une image.

       Model of DefaultConstructible, CopyConstructible, Assignable,
       RandomAccessIterator. */
    struct Iterator : public Container::iterator {
        // Constructeur à partir d'une image et des coordonnées d'un pixel (x,y).
        // NB: doit appeler le constructeur de la superclasse.
        Iterator( GrayLevelImage2D& Image, unsigned int x, unsigned int y );
    };

    GrayLevelImage2D();
    GrayLevelImage2D( unsigned int w, unsigned int h, GrayLevel g = 0 );
    void fill( GrayLevel g );

    //! [gli2d-sec3]
    /// @return la largeur de l'image.
    unsigned int w() const;
    /// @return la hauteur de l'image.
    unsigned int h() const;
    /// @return la borne sup des grayLevels de l'image.
    unsigned int glm() const;

    /**
       Accesseur read-only à la valeur d'un pixel.
       @return la valeur du pixel(i,j)
    */
    GrayLevel at( unsigned int i, unsigned int j ) const;

    /**
       Accesseur read-write à la valeur d'un pixel.
       @return une référence à la valeur du pixel(i,j)
    */
    GrayLevel& at( int unsigned i, unsigned int j );
    //! [gli2d-sec3]



    Iterator begin();
    Iterator end();
    Iterator start(unsigned int x, unsigned int y );

    std::pair<int,int> position( Iterator it ) const;

    bool importPGM( std::ifstream & input );
    bool exportPGM( std::ostream & output, bool ascii = true );
    bool filtrageMedian(int k);
    bool filtrageParConvolution(Masque masque);
    void genereEtConv(char c, double alpha);




private:
    // Calcule l'indice dans m_data du pixel (x,y).
    unsigned int index(unsigned int x, unsigned int y ) const;
    // Le tableau contenant les valeurs des pixels.
    Container m_data;
    // la largeur
    unsigned int       m_width;
    // la hauteur
    unsigned int       m_height;
    // le max que peut prendre graylevel
    unsigned int       m_grayLevelMax;
};
