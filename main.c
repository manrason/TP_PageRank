#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "PageRank.h"
#include "read_file.h"

int main(int argc, char* argv[]) {
    int opt;
    int length = 0;
    double epsilon = 0.0001;
    double alpha = 0.8;
    char file[FILELENGTH] = "Wiki-Vote.txt";
    int** graph;
    double* vector;
    int** adjacency_matrix;


    while((opt = getopt(argc, argv, "f:a:e:")) != -1) {
        switch(opt) {
            case 'f':
                strcpy(file, optarg);
                printf("Mise en place du file à %s\n", file);
                break;
            case 'a':
                alpha = atof(optarg);
                printf("Mise en place de alpha à %.10f\n", alpha);
                break;
            case 'e':
                epsilon = atof(optarg);
                printf("Mise en place de epsilon à %.10f\n", epsilon);
                break;
            case '?':
                printf("Option inconnue %c\n", optopt);
                break;
        }
    }

    printf("Lecture du graph depuis le fichier %s et debut d'execution avec alpha = %.10f et epsilon = %.10f..\n", file, alpha, epsilon);
	read_file(&graph, &length, file);
	//afficheMatriceEntiers(graph, length + 1);
	
	printf("Creation de la matrice d'adjacence..");
	adjacency_matrix_from_graph(&adjacency_matrix, graph, length);
    //afficheMatriceEntiers(adjacency_matrix, length);

    printf("Merci d'entrer les valeurs initiales : \n");
    fill_init_vector(length, &vector);
    //afficheVecteur(vector, length);

    printf("Execution de l'algorithme page rank ameliore");
    pageRank_loop(adjacency_matrix, vector, length, alpha, epsilon);

    return 0;
}
