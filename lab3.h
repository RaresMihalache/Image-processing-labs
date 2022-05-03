#pragma once

#include "common.h"

/* Calculare histograma (într-un vector de întregi de dimensiune 256) 
pentru o imagine grayscale (cu 8 biți/pixel). Se afiseaza valorile in consola. */
void histogram();

/*Calculare histograma (într-un vector de întregi de dimensiune 256) 
pentru o imagine grayscale (cu 8 biți/pixel), data ca parametru. Se
returneaza valorile. */
int* histogram_values(const std::string& name);

/* functie care returneaza inaltimea unei imagini date ca parametru. */
int get_height(const std::string& name);

/* functie care returneaza latimea unei imagini date ca parametru. */
int get_width(const std::string& name);

/* Calculare FDP (într-un vector de tip float de dimensiune 256). */
void fdp();

/* Afisare histograma. */
void showHistogram(const std::string& name, int* hist, const int hist_cols, const int hist_height);

/* Calculare histograma folosind un număr redus de m ≤ 256 acumulatoare. */
void histogram_acumm(int m);
