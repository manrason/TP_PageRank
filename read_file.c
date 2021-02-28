#include "read_file.h"

/*************************** Obtaining graph of a social network  **************************/

void read_file(int*** graph, int* length, char file[FILELENGTH]) {
	FILE* file; 
	file = fopen(file, "r");
	if(file) {
		fscanf(file, "%d", length);
		*graph = (int**) malloc((*length + 1) * sizeof(int*));
		for(int i = 0; i < (*length) + 1; i++) {
			(*graph)[i] = (int*) malloc((*length + 1) * sizeof(int));
            if(i == 0) { 
                (*graph)[0][0] = *length;
                for(int j = 1; j < (*length) + 1; j++) {
                    (*graph)[0][j] = UNDIFINED; 
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
