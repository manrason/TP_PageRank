#include "PageRank.h"




/*************************** Obtaining graph of a social network  **************************/

void read_file(int*** graph, int* length, char file_name[FILELENGTH]) {
	FILE* file; 
	file = fopen(file_name, "r");
	if(file) {
		fscanf(file, "%d", length);
		*graph = (int**) malloc((*length + 1) * sizeof(int*));
		for(int i = 0; i < (*length) + 1; i++) {
			(*graph)[i] = (int*) malloc((*length + 1) * sizeof(int));
            if(i == 0) { 
                (*graph)[0][0] = *length;
                for(int j = 1; j < (*length) + 1; j++) {
                    (*graph)[0][j] = UNDEFINED; 
                }
            } else {
                for(int j = 0; j < (*length) + 1; j++) {
                    fscanf(file, "%d", &(*graph)[i][j]);
                }
            }
		}
		fclose(file);
	} else {
		exit(1);
	}
}


/********************** Creating the adjacency matrix from the graph  ************************/
void adjacency_matrix_from_graph(int*** adjacency_matrix, int** graph, int length) {
    init_matrix_int(adjacency_matrix, length, true);
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            int target = graph[i+1][j+1];
            if(target != UNDEFINED) {
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
            (*vector)[i] = 0.0;
        }
    }
}    

void init_matrix_double(double*** matrix, int length, bool filled_w_zero) {
    *matrix = (double**) malloc(length * sizeof(double*));
    for(int i = 0; i < length; i++) {
        (*matrix)[i] = (double*) malloc(length * sizeof(double));
        if(filled_w_zero) {
            for(int j = 0; j < length; j++) {
                (*matrix)[i][j] = 0.0;
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
    init_vector(vector, length, false);
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
        for(int i = 0; i < length; i++) {
            old_vector[i] = current_vector[i];
        }
        matrix_x_vector(A, current_vector, length);
        k++;
    }
    print_vector(current_vector, length);
}

/*************Printing result************/
//Showing result
void print_vector(double* vector, int length) {
    printf("\n");
    for(int i = 0; i < length; i++) {
        printf("%.10f  ", vector[i]);
    }
}


/***********Freeing vector and matrix*******/
void free_matrix(double** matrix){
    free(matrix);
}

void free_vector(double* vector){
    free(vector);
}



int main(int argc, char* argv[]) {
    int length = 0;
    double epsilon = 0.0001,alpha = 0.8;
    char file[FILELENGTH] = "Wiki-Vote.txt";
    int** graph;
    double* vector;
    int** adjacency_matrix;
	read_file(&graph, &length, file);
	adjacency_matrix_from_graph(&adjacency_matrix, graph, length);
    fill_init_vector(length, &vector);
    printf("test");
    pageRank_loop(adjacency_matrix, vector, length, alpha, epsilon);
    printf("after test");
    free(adjacency_matrix);
    free(vector);
    return 0;
}


