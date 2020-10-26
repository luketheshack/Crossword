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

void output_board(char board[][SIZE], FILE *fp) {
	fputs("\nX-------------------------------X", fp);
	int i, j;
	char c;
	for (i = 0; i < SIZE; i++) {
		fputs("\n| ", fp);
		for (j = 0; j < SIZE; j++) {
			c = board[i][j];
			fputc(c, fp);
			fputc(' ', fp);
		}
		fputc('|', fp);
	}
	fputs("\nX-------------------------------X\n\n", fp);
}

int get_input(char words[][SIZE], int *count, char *fn) {
	FILE *fp;
	int returnCode = 0;
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
	*count = ct;
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
		if (!isalpha(word[c]) && word[c] != '\n') { // cannot be the enter key or non-alphabetic character
			printf("Non-alphabetic character detected. Word cannot be added.\n");
			returnCode = 1;
			break;
		}
		else {
			if (word[c] == '\n') {
				word[c] = '\0';
			}
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

void update(WordData dataArray[], char words[][SIZE], int wordindex, int wordrow, int wordcol, char direction, int *array_index, bool seenword) {
	strcpy(dataArray[*array_index].word, words[wordindex]);
	char wrd[SIZE];
	strcpy(wrd, dataArray[*array_index].word);
	strfry(wrd); // generate clue
	strcpy(dataArray[*array_index].clue, wrd); 
	dataArray[*array_index].len = strlen(words[wordindex]);
	dataArray[*array_index].seen = seenword;
	dataArray[*array_index].row = wordrow;
	dataArray[*array_index].col = wordcol;
	dataArray[*array_index].dir = direction;
	(*array_index)++;
}

int placewords(WordData dataArray[], char words[][SIZE], char solution_board[][SIZE], char puzzle_board[][SIZE], int count) {
	int i = 0, wordrow, wordcol, array_index = 0;
	// DO FIRST WORD
	if (i >= count) return;
	wordrow = SIZE/2;
	wordcol = (SIZE - strlen(words[0]))/2;
	for (i = 0; i < strlen(words[0]); i++) {
		solution_board[wordrow][wordcol+i] = words[0][i];
		puzzle_board[wordrow][wordcol+i] = ' ';
	}	
	i++;
	
	update(dataArray, words, 0, wordrow, wordcol, 'A', &array_index, true); // change to 'A'
	
	// DO SECOND WORD
	if (i < count) return;
	int j,k,l,m;
	bool found;
	char method;

	found = false;
	for (j = 0; j < strlen(words[1]); j++) { // letter in specific word we want to place
		for (k = 0; k < dataArray[0].len; k++) { // letter in word its getting crossed with 
			if (words[1][j] == (dataArray[0].word)[k]) {
				// place word
				found = true;

				wordrow = dataArray[0].row - j;
				wordcol = dataArray[0].col + k;
				
				for (l = 0; l < strlen(words[1]); l++) {
					solution_board[wordrow+l][wordcol] = words[1][l];
					puzzle_board[wordrow+l][wordcol] = ' ';
				}
				// update data array
				update(dataArray, words, 1, wordrow, wordcol, 'D', &array_index, true); 
				break;
			}
		}
		if (found) break;
	}
	if (!found) {
		update(dataArray, words, 1, -100, -100, 'D', &array_index, false); 
		printf("Unable to place word.\n");
	}
	// DO REST OF WORDS
	//
	// error is that starting coordinates for cactus (down word) are off
	//
	for (i = 2; i < count; i++) { // for each word in word array
		found = false;
		for (j = 0; j < array_index; j++) { // for each already placed word
			if (dataArray[j].seen) { // ensure word is actually on the board

			for (k = 0; k < strlen(words[i]); k++) { // for each letter in word to be placed

				for (l = 0; l < dataArray[j].len; l++) {
					
					if (words[i][k] == (dataArray[j].word)[l]) {
						// check method: across and down
						int exceptions = 0; // for when checking if word can fit, do not include 
						bool badcond = false;
						if (dataArray[j].dir == 'A') {// new word must go down
							
							wordrow = dataArray[j].row - k;
							wordcol = dataArray[j].col + l;
							for (m = 0; m < strlen(words[i]); m++) { // should be zero start
								if ( (wordrow+m < 0) || (wordrow+m >= SIZE) || solution_board[wordrow+m][wordcol] != '.' || solution_board[wordrow+m][wordcol-1] != '.' || solution_board[wordrow+m][wordcol+1] != '.') {
									if (exceptions == 0 && (wordrow + m >= 0 && wordrow + m < SIZE)) {
										exceptions++;
									} else {
										badcond = true;
										break;	
									}	
								}	
							} 
							if (wordrow+m <= SIZE && solution_board[wordrow+m][wordcol] != '.') badcond = true; 
							if (badcond) break;
							
							//printf("%s : %c\n", dataArray[j].word, words[i][k]);
							// if we make it here, then word will fit nicely on board
							for (m = 0; m < strlen(words[i]); m++) {
								solution_board[wordrow+m][wordcol] = words[i][m];
								puzzle_board[wordrow+m][wordcol] = ' ';
							}
							found = true;
							update(dataArray, words, i, wordrow, wordcol, 'D', &array_index, true);
							printf("%c\n", dataArray[i].dir);

						}
						if (dataArray[j].dir == 'D') {// new word must go across
							
							wordrow = dataArray[j].row + l;
							wordcol = dataArray[j].col - k; // -k
							for (m = 0; m < strlen(words[i]); m++) { // should be zero start
								if ( (wordcol+m < 0) || (wordcol+m >= SIZE) || solution_board[wordrow][wordcol+m] != '.' || solution_board[wordrow+1][wordcol+m] != '.' || solution_board[wordrow-1][wordcol+m] != '.') {
									
									if (exceptions == 0 && (wordcol + m >= 0 && wordcol + m < SIZE)) {
										exceptions++;
									} else {
										badcond = true;
										break;
									}
								}	
							}
							if (wordcol+m <= SIZE && solution_board[wordrow][wordcol+m] != '.') badcond = true;
							if (badcond) break;

							// if we make it here, word fits on board
							//printf("%s : %c\n", dataArray[j].word, words[i][k]);
							for (m = 0; m < strlen(words[i]); m++) {

								solution_board[wordrow][wordcol+m] = words[i][m];
								puzzle_board[wordrow][wordcol+m] = ' ';
							}
							printf("\n");
							found = true;

							update(dataArray, words, i, wordrow, wordcol, 'A', &array_index, true);

						}
						if (found) break;
					}
					if (found) break;
				}
				if (found) break;	
			}
			if (found) break;

			}
		}
		if (!found) {
			printf("Cannot place word \"%s\" on first pass.\n", words[i]);
			update(dataArray, words, i, -100, -100, 'N', &array_index, false); // N stands for neither, -100 coordinates so that it doesn't interfere with board
		}
	}
	return array_index;
}

void try_place_again(WordData dataArray[], int array_index, char solution_board[][SIZE], char puzzle_board[][SIZE]) {
	int i, j, k, l, m, wordrow, wordcol;
	bool found;
	for (i = 0; i < array_index; i++) { // for each word in the dataArray
		found = false;
		if (!dataArray[i].seen) { // if the word hasn't been placed yet
			
		for (j = 0; j < array_index; j++) { // for each word in the dataArray
			printf("%d %d\n", i, j);	
			if ( (i != j) && dataArray[j].seen) { // if the word isn't the word we want to place, and the other word is on the board
				for (k = 0; k < dataArray[i].len; k++) {

					for (l = 0; l < dataArray[j].len; j++) {
					
					// add system to skip over words
					
					if ((dataArray[i].word)[k] == (dataArray[j].word)[l]) {
						printf("%d %d\n", i, j);
						printf("%c %s \n", dataArray[j].dir, dataArray[j].word);	
						int exceptions = 0; // for when checking if word can fit, do not include 
						bool badcond = false;
						if (dataArray[j].dir == 'A') {// new word must go down
							wordrow = dataArray[j].row - k;
							wordcol = dataArray[j].col + l;

							for (m = 0; m < dataArray[i].len; m++) { // should be zero start
								if ( (wordrow+m < 0) || (wordrow+m >= SIZE) || solution_board[wordrow+m][wordcol] != '.' || solution_board[wordrow+m][wordcol-1] != '.' || solution_board[wordrow+m][wordcol+1] != '.') {
									if (exceptions == 0 && (wordrow + m >= 0 && wordrow + m < SIZE)) {
										exceptions++;
									} else {
										badcond = true;
										break;	
									}	
								}	
							} 
							if (wordrow+m <= SIZE && solution_board[wordrow+m][wordcol] != '.') badcond = true; 
							if (badcond) break;

							// if we make it here, then word will fit nicely on board
							for (m = 0; m < dataArray[i].len; m++) {
								solution_board[wordrow+m][wordcol] = (dataArray[i].word)[m];
								puzzle_board[wordrow+m][wordcol] = ' ';
							}
							found = true;
							dataArray[i].seen = true;
							dataArray[i].row = wordrow;
							dataArray[i].col = wordcol;
							dataArray[i].dir = 'D';
						}
						if (dataArray[j].dir == 'D') {// new word must go across
							wordrow = dataArray[j].row + l;
							wordcol = dataArray[j].col - k; // -k
							for (m = 0; m < dataArray[i].len; m++) { // should be zero start
								if ( (wordcol+m < 0) || (wordcol+m >= SIZE) || solution_board[wordrow][wordcol+m] != '.' || solution_board[wordrow+1][wordcol+m] != '.' || solution_board[wordrow-1][wordcol+m] != '.') {
									
									if (exceptions == 0 && (wordcol + m >= 0 && wordcol + m < SIZE)) {
										exceptions++;
									} else {
										badcond = true;
										break;
									}
								}	
							}
							if (wordcol+m <= SIZE && solution_board[wordrow][wordcol+m] != '.') badcond = true;
							if (badcond) break;

							// if we make it here, word fits on board
							for (m = 0; m < dataArray[i].len; m++) {

								solution_board[wordrow][wordcol+m] = (dataArray[i].word)[m];
								puzzle_board[wordrow][wordcol+m] = ' ';
							}
							printf("\n");
							found = true;

							dataArray[i].seen = true;
							dataArray[i].row = wordrow;
							dataArray[i].col = wordcol;
							dataArray[i].dir = 'A';
						}
					}
					if (found) {
						printf("placed");
						break;
					}
					}
				}
				if (found) break;
			}
			if (found) break;
		}
		if (found) break;	
		}
	}
}

void showclues(WordData dataArray[], int array_index) {
	printf("\nClues: \n");
	printf("Direction |     Anagram     | Location \n");
	int i;
	for (i = 0; i < array_index; i++) {
		if (dataArray[i].seen) {
			if (dataArray[i].dir == 'A') {
				printf("Across    |");
			}
			else {
				printf("Down      |");
			}
			printf("%16s |", dataArray[i].clue);
			printf(" %d, %d \n", dataArray[i].row, dataArray[i].col);
		}
	}	
	printf("\n");
}

void output_clues(WordData dataArray[], int array_index, FILE *fp) {
	fputs("\n", fp);
	fputs("Direction |     Anagram     | Location \n", fp);
	int i;
	char *clue = malloc(18*sizeof(char));
	char c;
		
	for (i = 0; i < array_index; i++) {
		if (dataArray[i].seen) {
			if (dataArray[i].dir == 'A') {
				fputs("Across    |", fp);
			}
			else {
				fputs("Down      |", fp);
			}
			clue = dataArray[i].clue;

			fprintf(fp, "%-15s", clue);
			fputs(clue, fp);
			fputs(" |", fp);
			fputc(' ', fp);
			c = dataArray[i].row + '0';
			fputc( c , fp);
			fputs(", ", fp);
			c = dataArray[i].col + '0';
			fputc( c , fp);
			fputs(" \n", fp);
		}
	}
	fputs(" \n", fp);

}

int unplaced(WordData dataArray[], int array_index) {
	int i, ct = 0;
	for (i = 0; i < array_index; i++) {
		if (!dataArray[i].seen) ct++;
	}
	return ct;
} 
