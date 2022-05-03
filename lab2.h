#pragma once

#include "common.h"

/* copiază canalele R, G, B ale unei imagini RGB24 (tip CV_8UC3) în trei matrice
de tip CV_8UC1. Se afiseaza aceste matrice în 3 ferestre diferite. */
void RGB2grayscale_each_channel();

/* funcție de conversie de la o imagine color RGB24 (tip CV_8UC3) la o imagine
grayscale de tip (CV_8UC1). Se afiseaza aceasta imagine intr-o noua fereastra. */
void RGB2grayscale();

/* funcție de conversie de la o imagine grayscale (tip CV_8UC1) la o imaginare
binara de tip (CV_8UC1). Threshold-ul (pragul) se citeste din linia de comanda. */
void grayscale2binary(int threshold);

/* funcție care convertește canalele R, G, B ale unei imagini RGB24 (tip CV_8UC3) în
componente H, S, V. Memorare componente H, S, V în câte o matrice de tip CV_8UC1
corespunzătoare canalelor H, S, V. Afișare matrice în 3 ferestre diferite. */
void RGB2HSV_components();

/* verificare daca pozitia indicata de (i,j) este in interiorul imaginii img. */
bool isInside(Mat img, int i, int j);
