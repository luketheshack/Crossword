// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define SIZE 15
#define numwords 20

typedef struct {
	char word[15]; // word itself
	char clue[15];
	int len; // length of word
	bool seen; // has word been placed?
	int row; // row where it starts
	int col; // col where it starts
	char dir; // direction --> d (down) or a (across)
} WordData;

void display(char [][SIZE]);
int get_input(char [][SIZE], int *, char *); // 
void interactive_input(char [][SIZE], int *count); // 
int format_word(char []);
void sortwords(char [][SIZE], int count); // 
void update(WordData [], char [][SIZE], int, int, int, char, int *, bool);
int placewords(WordData [], char [][SIZE], char [][SIZE], char [][SIZE], int);
void try_place_again(WordData [], int, char [][SIZE], char [][SIZE]);
void showclues(WordData [], int);
void to_text_file(WordData [], char [][SIZE], char [][SIZE]);
void output_board(char [][SIZE], FILE *);
void output_clues(WordData [], int, FILE *);
int unplaced(WordData [], int);
