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
		if (ct >= numwords) {
			printf("Too many words inputted. Stopping input retrieval...\n");
			return returnCode;
		}
		fgets(line, size, fp);
		if (feof(fp)) break;
		if (line[0] == '.') break;
		int code = format_word(line);
		if (code == 0) {
			strcpy(board[ct], line);	
		}
		++ct;
	}
	return returnCode;
	
}

int format_word(char *word) {
	int returnCode = 0;
	int c;
	for (c = 0; c < (*word).size(); c++) {
		if (!isalpha((*word)[c])) {
			printf("Non-alphabetic character detected. Word %s cannot be added.\n", word);
			returnCode = 1;
			return returnCode;
		}
		else {
			toupper((*word)[c]);
		}
	}
}
