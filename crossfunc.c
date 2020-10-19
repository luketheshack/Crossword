// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

void display(char board[][SIZE]) {
	printf("\nX-------------------------------X");
	int i, j;
	for (i = 0; i < SIZE; i++) {
		printf("\n| ");
		for (j = 0; j < SIZE; j++) {
			printf("%c ", board[i][j]);
		}
		printf("|");
	}
	printf("\nX-------------------------------X\n\n");
}

int get_input(char words[][SIZE]) {
	FILE *fp;
	char *fn = malloc(25*sizeof(char));
	int returnCode = 0;
	printf("What is the name of this file? ");
	scanf("%s", fn);
	free(fn);
	fp = fopen(fn, "r");
	if (!fp) {
		printf("File could not be found. Quitting program...\n");
		returnCode++;
		return returnCode;
	}
	char line[SIZE];
	int ct = 0;
	while (1) {
		if (ct >= numwords) {
			printf("Too many words inputted. Stopping input retrieval...\n");
			return returnCode;
		}
		fgets(line, SIZE, fp);
		if (feof(fp)) break;
		if (line[0] == '.') break;
		int code = format_word(line);
		if (code == 0) {
			strcpy(words[ct], line);
			++ct;	
		}
	}
	return returnCode;
	
}

int format_word(char word[]) {
	int returnCode = 0;
	int c;
	if (strlen(word) < 2) {
		printf("Word is too short.\n");
		returnCode = 1;
		return returnCode;
	}
	for (c = 0; c < strlen(word); c++) {
		if (!isalpha(word[c])) {
			printf("Non-alphabetic character detected. Word %s cannot be added.\n", word);
			returnCode = 1;
			return returnCode;
		}
		else {
			toupper(word[c]);
		}
	}
}

void interactive_input(char words[][SIZE]) {
	char line[15];
	int ct = 0;
	int code;
	do {
		printf("Enter a word: \n");
		fgets(line, SIZE, stdin);
		if (line[0] == '.') break;
		code = format_word(line);
		if (code == 0) {
			strcpy(words[ct], line);
			ct++;
		}
	}
	while (ct <= 20 && line[0] != '.');
}
