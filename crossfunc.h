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
	char len; // length of word
	char row; // row where it starts
	char col; // col where it starts
	char dir; // direction --> d (down) or a (across)
} WordData;

void display(char [][SIZE]);
int get_input(char [][SIZE]); // 
void interactive_input(char [][SIZE], int *count); // 
int format_word(char []);
void sortwords(char [][SIZE], int count); // 
void makeclues(char [][SIZE], char [][SIZE], int count); //
void placewords(WordData [], char [][SIZE], char [][SIZE], char [][SIZE], int);
