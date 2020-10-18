// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

int main(int argc, char *argv[]) {
	// initial begin
	char words[20][15]; // 20 words, 15 chars + null character
	char board[board_size][board_size]; // 15 by fifteen?? must make display function
	// and stuff to check . will prob need more
	int i,j;
	for (i = 0; i < board_size; i++) {
		for (j = 0; j < board_size; j++) {
			board[i][j] = '.';
		}
	}

	if (argc == 1) { // get user input
		display(board);	
	}
	else if (argc == 2) {

	}
	else if (argc == 3) {

	}
	else {
		printf("\nThere was an error in your input. Please try again.\n");
		return 0;
	}

	return 0;
}
