// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

void display(char board[][size]) {
	printf("\nX-------------------------------X");
	int i, j;
	for (i = 0; i < size; i++) {
		printf("\n| ");
		for (j = 0; j < size; j++) {
			printf("%c ", board[i][j]);
		}
		printf("|");
	}
	printf("\nX-------------------------------X\n\n");
}

int get_input(char board[][size]) {
	FILE *fp;
	char *fn = malloc(25*sizeof(char));
	int returnCode = 0;
	printf("What is the name of this file? ");
	scanf("%s", p);
	free(p);
	fp = fopen(fn, "r");
	if (!fp) {
		printf("File could not be found. Quitting program...\n");
		returnCode++;
		return returnCode;
	}
	char line[size];
	int ct = 0;
	while (1) {
		if (ct == 21) {
			printf("Too many words inputted. Stopping input retrieval...\n");
			return returnCode;
		}
		fgets(line, size, fp);
		if (feof(fp)) break;
		if (line[0] == '.') break;
		strcpy(board[ct], line);
		++ct;
	}
	return returnCode;
	
}
