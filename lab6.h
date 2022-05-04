#pragma once

#include "common.h"

/*Implementare algoritm de urmărire a conturului şi desenare contur dintr-o imagine cu un singur obiect.*/
void border_tracing();

/*Algoritmul care construieşte codul înlănţuit, folosind algoritmul de urmarire a conturului.
Calculați și afișați intr-un fisier txt codul inlantuit. */
void construct_chain_code();

/*Algoritmul care construieşte derivata codului înlănţuit, folosind algoritmul de urmarire a conturului.
Calculați și afișați intr-un fisier txt derivata codului inlantuit. */
void construct_derivative();

/*Implementare funcţie care reconstruieşte (afişează) conturul unui obiect peste o imagine,
având ca şi date de intrare coordonatele punctului de start şi secvenţa de cod înlănţuit
utilizând vecinătate de 8. */
void construct_border(int starting_point, uchar* chain_code);