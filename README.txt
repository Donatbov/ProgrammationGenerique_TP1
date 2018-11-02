======================================
compilation:
Nous avons remarqué qu'en compilant sous Windows les pixels se retrouvaient décalés dans le processus d'importation/exportation (même avec std::ios::binary)...
Par-contre, en compilant sous Linux il n'y a aucun soucis.
Ne trouvant pas de solution nous avons continué le TP sous Linux.


Instructions de compilation : 

Pour les parties 1 à 8 :
g++ -std=c++11 GrayLevelImage2D.cpp Histogramme.cpp testGrayLevelImage2D.cpp

Pour la partie A :
g++ -std=c++11 GrayLevelImage2D.cpp Bruit_gaussien.cpp


======================================
Instructions de lancement :

Pour utiliser double_brightness :
./a.out <image-source.pgm> <image-exportée.pgm> double-brightness

Pour utiliser le filtrage médian :
./a.out <image-source.pgm> <image-exportée.pgm> filtrage-median {k}

Pour utiliser l'égalisation :
./a.out <image-source.pgm> <image-exportée.pgm> egalisation

Pour utiliser la convolution avec masque de convolution "moyenne" :
./a.out <image-source.pgm> <image-exportée.pgm> convolution M

Pour utiliser la convolution avec masque de convolution "Laplacien" :
./a.out <image-source.pgm> <image-exportée.pgm> convolution L

Pour utiliser la convolution avec masque de convolution "R" (Laplacien avec un alpha) :
./a.out <image-source.pgm> <image-exportée.pgm> convolution R {alpha}


Pour utiliser le bruit gaussien :
./a.out <image-source.pgm> <image-exportée.pgm> <probabilité d'avoir du bruit>

