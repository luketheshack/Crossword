// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

int main(int argc, char *argv[]) {
	// initial begin
	int errorCode;
	char words[numwords][size]; // 20 words, 15 chars + null character
	char solution_board[size][size]; // 15 by fifteen?? must make display function
	char puzzle_board[size][size];
	// and stuff to check . will prob need more
	int i,j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			solution_board[i][j] = '.';
			puzzle_board[i][j] = '#';
		}
	}

	if (argc == 1) { // get user input
		display(solution_board);	
	}
	else if (argc == 2) {
		errCode = get_input(board);
		if (errCode != 0) return 1;

	}
	else if (argc == 3) {
		errCode = get_input(board);
		if (errCode != 0) return 1;
	}

	else {
		printf("\nThere was an error in your input. Please try again.\n");
		return 0;
	}

	return 0;
}
