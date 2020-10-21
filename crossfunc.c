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
// 15 char problem somewhere
int format_word(char word[]) {
	int returnCode = 0;
	int c;
	if (strlen(word) < 2 || strlen(word) > SIZE) {
		printf("Word does not meet length criteria.\n");
		returnCode = 1;
		return returnCode;
	}
	for (c = 0; c < strlen(word); c++) {
		if (!isalpha(word[c])) {
			printf("Non-alphabetic character detected. Selected word cannot be added.\n", word);
			returnCode = 1;
			break;
		}
		else {
			word[c] = toupper(word[c]);
		}
	}
	return returnCode;
}

void interactive_input(char words[][SIZE], int *count) {
	char line[SIZE];
	int ct = 0;
	int code;
	do {
		printf("Enter a word: \n");
		scanf("%s", line);
		getchar();
		if (line[0] == '.') break;
		code = format_word(line);
		if (code == 0) {
			//printf("%d  ", code);
			if (strlen(line) < SIZE) {
				strcpy(words[ct], line);
				ct++;
			}
		}
	}
	while (ct <= 20 && line[0] != '.');
	*count = ct;
}

void sortwords(char words[][SIZE], int count) {
	int i, j;
	char temp[SIZE];
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

void makeclues(char words[][SIZE], char clues[][SIZE], int count) {
	int i;
	char wrd[SIZE];
	for (i = 0; i < count; i++) {
		strcpy(wrd, words[i]);
		strfry(wrd);
		strcpy(clues[i], wrd);
	}
}

typedef struct {
	char word[15]; // word itself
	char len; // length of word
	char row; // row where it starts
	char col; // col where it starts
	char dir; // direction --> d (down) or a (across)
} WordData;

void placewords(char words[][SIZE], char solution_board[][SIZE], char puzzle_board[][SIZE], int count) {
	int i = 0, wordrow, wordcol, array_index = 0;
	WordData dataArray[count];
	// DO FIRST WORD
	if (i >= count) return;
	wordrow = SIZE/2;
	wordcol = (SIZE - strlen(words[0]))/2;
	for (i = 0; i < strlen(words[0]); i++) {
		solution_board[wordrow][wordcol+i] = words[0][i];
		puzzle_board[wordrow][wordcol+i] = words[0][i];
	}	
	i++;
	
	strcpy(dataArray[array_index].word, words[0]);
	dataArray[array_index].len = strlen(words[0]);
	dataArray[array_index].row = wordrow;
	dataArray[array_index].col = wordcol;
	dataArray[array_index].dir = 'D';
	array_index++;
	
	// DO SECOND WORD
	if (i < count) return;
	int j,k,l;
	bool found;

	for (i = 0; i < array_index; i++) {
		found = false;
		for (j = 0; j < strlen(words[1]); j++) { // letter in specific word we want to place      // 1
			for (k = 0; k < dataArray[i].len; k++) { // letter in word its getting crossed with   // 0
				if (words[1][j] == (dataArray[i].word)[k]) {
					// place word
					found = true;
					for (l = 0; l < strlen(words[1]); l++) {
						wordcol = dataArray[i].col+k;
						wordrow = dataArray[i].row-j;	
						solution_board[wordrow+l][wordcol] = words[1][l]; // row vary, column stationary
							
					}
					// update data array
					break;
				}
			}
			if (found) break;
		}
		if (!found) {
			printf("Unable to place word.\n");
		}
	}
	// for each word in dataArray:
		// for each letter in spcific word
			// for each letter in word in array

	
} 
