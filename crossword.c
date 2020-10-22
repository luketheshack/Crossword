// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

int main(int argc, char *argv[]) {
	// initial begin
	int errorCode;
	char words[numwords][SIZE]; // 20 words, 15 chars apiece
	char clues[numwords][SIZE];
	char solution_board[SIZE][SIZE]; // 15 by fifteen?? must make display function
	char puzzle_board[SIZE][SIZE];
	// and stuff to check . will prob need more
	int i,j,count;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			solution_board[i][j] = '.';
			puzzle_board[i][j] = '#';
		}
	}

	if (argc == 1) { // get user input
		display(solution_board);
		interactive_input(words, &count);
		WordData dataArray[count];
		int i;
		sortwords(words, count);
		makeclues(words, clues, count);
		placewords(dataArray, words, solution_board, puzzle_board, count);
		display(solution_board);
	}

	else if (argc == 2) {
		errorCode = get_input(words);
		if (errorCode != 0) return 1;

	}
	else if (argc == 3) {
		errorCode = get_input(words);
		if (errorCode != 0) return 1;
	}

	else {
		printf("\nThere was an error in your input. Please try again.\n");
		return 0;
	}

	return 0;
}
