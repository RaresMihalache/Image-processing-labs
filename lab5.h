#pragma once

#include "common.h"

/* Algoritm de traversare în lățime pentru etichetarea componentelor conexe.
neighbor_type = 0 -> folosim 4 vecini
neighbor_type = 1 -> folosim 8 vecini
return labels_matrix (image - Mat). */
Mat BFS_component_labeling(int neighbor_type);

/* Algoritm de traversare în adancime pentru etichetarea componentelor conexe.
neighbor_type = 0 -> folosim 4 vecini
neighbor_type = 1 -> folosim 8 vecini
return labels_matrix(image - Mat). */
Mat DFS_component_labeling(int neighbor_type);

/* Funcție care genereaza o imagine color pornind de la matricea de etichete.
Se afiseaza rezultatul. */
void colored_labels(Mat labeled_image);

/* Algoritmul de etichetare cu două treceri. Afișare rezultatele intermediare
după prima parcurgere. */
void two_pass_labeling();

Mat grayscale2binary(Mat img, int threshold);
