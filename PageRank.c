#include "PageRank.h"

/********************** Creating the adjacency matrix from the graph  ************************/
void adjacency_matrix_from_graph(int*** adjacency_matrix, int** graph, int length) {
    init_matrix_int(adjacency_matrix, length, true);
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            int target = graph[i+1][j+1];
            if(target != INDEFINI) {
                (*adjacency_matrix)[i][target] = 1;
            }
        }
    }
}


/***************Initialize all the adjacency matrix and vector to 0.0 ***************/
void init_vector(double** vector, int length, bool filled_w_zero) {
    *vector = (double*) malloc(length * sizeof(double));
    if(filled_w_zero) {
        for(int i = 0; i < length; i++) {
            (*vector)[i] = 0;
        }
    }
}    

void init_matrix_double(double*** matrix, int length, bool filled_w_zero) {
    *matrix = (double**) malloc(length * sizeof(double*));
    for(int i = 0; i < length; i++) {
        (*matrix)[i] = (double*) malloc(length * sizeof(double));
        if(filled_w_zero) {
            for(int j = 0; j < length; j++) {
                (*matrix)[i][j] = 0;
            }
        }
    }
}

void init_matrix_int(int*** matrix, int length, bool filled_w_zero) {
    *matrix = (int**) malloc(length * sizeof(int*));
    for(int i = 0; i < length; i++) {
        (*matrix)[i] = (int*) malloc(length * sizeof(int));
        if(filled_w_zero) {
            for(int j = 0; j < length; j++) {
                (*matrix)[i][j] = 0;
            }
        }
    }
}
/*************************** Filling and normalizing  **************************/
void fill_init_vector(int length, double** vector) {
    initialiseVecteur(vector, length, false);
    *vector = (double*) malloc(length * sizeof(double));
    for(int i = 0; i < length; i++) {
        char buffer[50];
        gets(buffer);
        (*vector)[i] = atof(buffer);
    }
}

double normalize_vector(double* current_vector, double* old_vector, int length) {
    double sum = 0;
    for(int i = 0; i < length; i++) {
        sum += (current_vector[i] - old_vector[i]) * (current_vector[i] - old_vector[i]);
    }
    return sqrt(sum);
}

/*************************** Getting matrix A x vector **************************/
void matrix_x_vector(double** matrix, double* vector, int length) {
    double* result = (double*) malloc(length * sizeof(double));
    for(int i = 0; i < length; i++) {
        result[i] = 0;
        for(int j = 0; j < length; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    for(int i = 0; i < length; i++) {
        vector[i] = result[i];
    }
}

	
	/*************************** PageRank LOOP  **************************/
void pageRank_loop(int** adjacency_matrix, double* initial_vector, int length, double alpha, double epsilon) {
    double** A = NULL;
    init_matrix_double(&A, length, false);
    for(int i = 0; i < length; i++) {
        int sum = 0;
        for(int j = 0; j < length; j++) {
            sum += adjacency_matrix[i][j];
        }
        for(int j = 0; j < length; j++) {
            if(sum != 0) {
                A[j][i] = (alpha * adjacency_matrix[i][j] / sum) + (1 - alpha)/length;
            } else {
                A[j][i] = 1.0/length;
            }
        }
    }

    double* current_vector = initial_vector;
    int k = 0;
    double* old_vector = NULL;
    init_vector(&old_vector, length, true);

    while(normalize_vector(current_vector, old_vector, length) > epsilon) {
        printf("Numero d'iteration : %d\n", k);
        for(int i = 0; i < length; i++) {
            old_vector[i] = current_vector[i];
        }
        matrix_x_vector(A, current_vector, length);
        k++;
    }
}
