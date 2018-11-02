#include "GrayLevelImage2D.hpp"

// GrayLevelImage2D is an Iterator sur toutes les valeurs d'une image

// Constructor
GrayLevelImage2D::GrayLevelImage2D(unsigned int w, unsigned int h, GrayLevelImage2D::GrayLevel g) : m_width(w), m_height(h){
    m_data.resize(w*h);
    GrayLevelImage2D::fill(g);
}

GrayLevelImage2D::GrayLevelImage2D() :m_height(0), m_width(0), m_grayLevelMax(255){}




void GrayLevelImage2D::fill(GrayLevelImage2D::GrayLevel g) {
    for (unsigned int i = 0; i < w()*h(); ++i )
            m_data[i] = g; //fill le container m_data de taille w*h avec le graylevel g
}

unsigned int GrayLevelImage2D::w() const {
    return m_width;
}

unsigned int GrayLevelImage2D::h() const {
    return m_height;
}

unsigned int GrayLevelImage2D::glm() const {
    return m_grayLevelMax;
}

unsigned int GrayLevelImage2D::index(unsigned int x, unsigned int y) const {
    return (y*m_width) + x;
}

GrayLevelImage2D::GrayLevel GrayLevelImage2D::at(unsigned int i, unsigned int j) const {
    return m_data.at(GrayLevelImage2D::index(i,j));
}


GrayLevelImage2D::GrayLevel &GrayLevelImage2D::at(unsigned int i, unsigned int j) {
    return m_data.at(GrayLevelImage2D::index(i,j));
}

GrayLevelImage2D::Iterator::Iterator(GrayLevelImage2D &Image, unsigned int x, unsigned int y): Container::iterator (Image.m_data.begin()+Image.index(x,y)) {}

GrayLevelImage2D::Iterator GrayLevelImage2D::start(unsigned int x, unsigned int y) {
    return Iterator(*this, x, y);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin() {
    return Iterator{ *this, 0, 0 };
}

GrayLevelImage2D::Iterator GrayLevelImage2D::end() {
    return Iterator{ *this, w(), h()-1 };
}

bool GrayLevelImage2D::importPGM(std::ifstream &input) {
    unsigned int row = 0, col = 0, numrows = 0, numcols = 0, graylevel = 0;
    stringstream ss;
    string inputLine;
    string version;
    string comment;

    // entete du fichier
        // First line : version
        getline(input,inputLine);
        version = inputLine;

        // Second line : comment
        getline(input,inputLine);
        comment = inputLine;

        // Third line : size
        getline(input,inputLine);
            // on passe par un ss temporaire pour séparer num_col et num_row (c'est pas ouf mais ça marche)
            stringstream sstemp;
            sstemp << inputLine;
            sstemp >> numcols >> numrows;
            m_width = numcols;
            m_height = numrows;

        // fourth line : graylevel
        getline(input,inputLine);
        graylevel = (unsigned int)std::stoi(inputLine);
        m_grayLevelMax = graylevel;



    // Following lines : data
        // Continue with a stringstream
        ss << input.rdbuf();

        if (version == "P5"){
            unsigned char value;
            for(row = 0; row < numrows; ++row) {
                for (col = 0; col < numcols; ++col) {
                    ss >> std::noskipws >> value;
                    m_data.push_back(value);
                }
            }
        }
        else if (version == "P2"){
            unsigned int value; //on utilise un ui pour que la lecture dans le flux de '11' ne soit pas '1' '1'
            for(row = 0; row < numrows; ++row) {
                for (col = 0; col < numcols; ++col) {
                    ss >> std::skipws >> value;
                    m_data.push_back((unsigned char)value);
                }
            }
        }else{
            unsigned char value;
            for(row = 0; row < numrows; ++row) {
                for (col = 0; col < numcols; ++col) {
                    ss >> std::noskipws >> value;
                    m_data.push_back(value);
                }
            }
        }

    return true;
}

bool GrayLevelImage2D::exportPGM(std::ostream &output, bool ascii) {
    string format;
    if (ascii)
        format = "P2";
    else
        format = "P5";

    // entete du fichier
    output << format << std::endl
    << "# un commentaire" << std::endl
    << m_width << " " << m_height << std::endl
    << m_grayLevelMax << std::endl;

    // les data
    if (ascii) {
        for (Iterator i = begin(); i != end(); ++i) {
            if ((i-begin()+1) % m_width == 0)   //si on est en bout de ligne
                output << (unsigned int)*i << std::endl;
            else
                output << (unsigned int)*i << "  ";
        }
    }else{
        for (Iterator i = begin(); i != end(); ++i) {
            output << *i;
        }
    }


    return true;
}


bool GrayLevelImage2D::filtrageMedian(int k) {
    unsigned int index;
    for (Iterator i = begin(); i != end(); ++i) {   //on parcourt tous les pixels de l'image
        index = i-begin();
        //if(*i == 0 || *i == m_grayLevelMax) {   //Si on veut tricher on effectue le filtrage median uniquement si le pixel est saturé
            Container temp; // on crée un container dans lequel on va mettre les niveaux de gris des pixels voisins (d'une distance k)
            for (int y = -k; y <= k; ++y) {
                if (index + y * m_width >= 0 &&
                    index + y * m_width <= m_width * m_height - 1) {  // si c'est un voisin valide au regard des lignes
                    for (int x = -k; x <= k; ++x) {
                        if (index % m_width + x >= 0 && index % m_width + x <= m_width - 1) {     //si c'est un voisin valide au regard des colonnes
                                temp.push_back(at(index % m_width + x, index / m_width + y));   //alors on range son niveau de gris dans le container
                        }
                    }
                }
            }
            std::sort(temp.begin(), temp.end()); //on trie ensuite les niveaux de gris de l'image
            *i = temp[temp.size() / 2];   // et on réaffecte le niveau de gris median au pixel actuel
        //}
    }

    return true;
}

void GrayLevelImage2D::genereEtConv(char c, double alpha) {
    Masque masque;
    if(c == 'M'){
        for(int i = 0 ; i<3 ; i++){
            masque.push_back(std::vector<double>());
            for(int j = 0 ; j<3 ; j++){
                masque[i].push_back(1./9);
            }
        }
    }
    else if(c == 'L'){
        masque = {{0, -1./4, 0},{-1./4, 1, -1./4},{0, -1./4, 0}};
    }
    else if(c == 'R'){
        masque = {{0, -alpha/4, 0},{-alpha/4, 1+alpha, -alpha/4},{0, -alpha/4, 0}};
    }
    filtrageParConvolution(masque);
}

bool GrayLevelImage2D::filtrageParConvolution(GrayLevelImage2D::Masque masque) {
    Container data2;
    int rangeMasque = (int)(masque.size()/2); //au lieu de prendre la taille on prend la portée du voisinage (comme k)
    unsigned int index;
    for (Iterator i = begin(); i != end(); ++i) {   //on parcourt tous les pixels de l'image
        index = i-begin();
        double valeur = 0;
        for (int y = -rangeMasque; y <= rangeMasque; ++y) {
            if (index + y * m_width >= 0 &&
                index + y * m_width <= m_width * m_height - 1) {  // si c'est un voisin valide au regard des lignes
                for (int x = -rangeMasque; x <= rangeMasque; ++x) {
                    if (index % m_width + x >= 0 && index % m_width + x <= m_width - 1) {     //si c'est un voisin valide au regard des colonnes
                        valeur += at(index % m_width + x, index / m_width + y) * masque[rangeMasque + x][rangeMasque + y];
                    }
                }
            }
        }
        data2.push_back((GrayLevel) valeur);
    }
    m_data = Container(data2);
    return true;
}


