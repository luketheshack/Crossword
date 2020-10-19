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

int get_input(char words[][SIZE+2]) {
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
	char line[SIZE+2];
	int ct = 0;
	while (1) {
		if (ct >= numwords) {
			printf("Too many words inputted. Stopping input retrieval...\n");
			return returnCode;
		}
		fgets(line, SIZE+2, fp);
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
	if (strlen(word) < 3 || strlen(word) > 17) {
		printf("Word does not meet length criteria.\n");
		returnCode = 1;
		return returnCode;
	}
	for (c = 0; c < strlen(word)-1; c++) {
		if (!isalpha(word[c])) {
			printf("Non-alphabetic character detected. Selected word cannot be added.\n", word);
			returnCode = 1;
			return returnCode;
		}
		else {
			word[c] = toupper(word[c]);
		}
	}
	return returnCode;
}

void interactive_input(char words[][SIZE+2], int *count) {
	char line[SIZE+2];
	int ct = 0;
	int code;
	do {
		printf("Enter a word: \n");
		fgets(line, SIZE+2, stdin);
		if (line[0] == '.') break;
		code = format_word(line);
		if (code == 0) {
			strcpy(words[ct], line);
			ct++;
		}
	}
	while (ct <= 20 && line[0] != '.');
	*count = ct;
}

void sortwords(char words[][SIZE+2], int count) {
	int i, j;
	char temp[SIZE+2];
	for (j = 0; j < count; j++) {
		for (i = 0; i < count-1; i++) {
			if (strlen(words[i]) < strlen(words[i+1])) {
				strcpy(temp, words[i]);
				strcpy(words[i], words[i+1]);
				strcpy(words[i+1], temp);
			}
		}
	}
	return;
}
