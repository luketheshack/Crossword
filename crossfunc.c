// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

void display(char board[][board_size]) {
	printf("\nX-------------------------------X");
	int i, j;
	for (i = 0; i < board_size; i++) {
		printf("\n| ");
		for (j = 0; j < board_size; j++) {
			printf("%c ", board[i][j]);
		}
		printf("|");
	}
	printf("\nX-------------------------------X\n\n");
}
