// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h

#include "crossfunc.h"

int main(int argc, char *argv[]) {
	// initial begin
	int errorCode;
	char words[numwords][SIZE]; // 20 words, 15 chars apiece
	char solution_board[SIZE][SIZE]; // 15 by fifteen?? must make display function
	char puzzle_board[SIZE][SIZE];
	// and stuff to check . will prob need more
	int i,j,count = 0;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			solution_board[i][j] = '.';
			puzzle_board[i][j] = '#';
		}
	}

	if (argc == 1) { // get user input
		interactive_input(words, &count);
		WordData dataArray[count];
		sortwords(words, count);
		int array_index = placewords(dataArray, words, solution_board, puzzle_board, count);
		display(solution_board);
		display(puzzle_board);
		showclues(dataArray, array_index);
	}

	else if (argc == 2) {
		errorCode = get_input(words, &count, argv[1]);
		if (errorCode != 0) return 1;
		WordData dataArray[count];
		sortwords(words, count);
		int array_index = placewords(dataArray, words, solution_board, puzzle_board, count);
		display(solution_board);
		display(puzzle_board);
		showclues(dataArray, array_index);
	}
	else if (argc == 3) {
		FILE *fp = fopen(argv[2], "w+");
		errorCode = get_input(words, &count, argv[1]);
		if (errorCode != 0) return 1;
		WordData dataArray[count];
		sortwords(words, count);
		int array_index = placewords(dataArray, words, solution_board, puzzle_board, count);
		output_board(solution_board, fp);
		output_board(puzzle_board, fp);
	}

	else {
		printf("\nThere was an error in your input. Please try again.\n");
		return 0;
	}

	return 0;
}
