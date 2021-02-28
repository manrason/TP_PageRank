#ifndef PAGERANK
#define PAGERANK

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define FILELENGTH 256
#define UNDEFINED -1


void adjacency_matrix_from_graph(int*** adjacency_matrix, int** graph, int length);
void init_vector(double** vector, int length, bool filled_w_zero);
void init_matrix_double(double*** matrix, int length, bool filled_w_zero);
void init_matrix_int(int*** matrix, int length, bool filled_w_zero);
void fill_init_vector(int length, double** vector);
double normalize_vector(double* current_vector, double* old_vector, int length);
void matrix_x_vector(double** matrix, double* vector, int length);
void pageRank_loop(int** adjacency_matrix, double* initial_vector, int length, double alpha, double epsilon);
void print_vector(double* vector, int length);

#endif