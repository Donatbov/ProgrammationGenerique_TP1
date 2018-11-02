#include "Bruit_gaussien.hpp"


int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator Iterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: bruit-impulsionnel <input.pgm> <output.pgm> <prob>" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    double prob = (argc > 3) ? atof( argv[ 3 ] ) : 0.01; // récupère la probabilité de bruit
    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    {
        if ( rand01() < prob ){
            int noise = (int)generateGaussianNoise(0, 256/2) ;    //génere un nombre aléatoire selon la loi normale centrée réduite N(0,256) remarquez que 256/2 correspond à l'espérance d'un tirage d'une loi uniforme entre 0 et 256
            if (*it+noise > 255){
                *it = 255;
            }else if(*it + noise <0){
                *it = 0;
            }else {
                *it = (*it + (unsigned char)noise);
            }
       }
    }
    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img.exportPGM( output, false );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}

double rand01() {
    return (double)random() / (double)RAND_MAX;
}

double generateGaussianNoise(double mu, double sigma) {
    static const double epsilon = std::numeric_limits<double>::min();
    static const double two_pi = 2.0*3.14159265358979323846;

    thread_local double z1;
    thread_local bool generate;
    generate = !generate;

    if (!generate)
        return z1 * sigma + mu;

    double u1, u2;
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    }
    while ( u1 <= epsilon );

    double z0;
    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}
