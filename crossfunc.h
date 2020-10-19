// Luke Marushack
// Fundamentals of Computing : Lab #8
// crossfunc.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 15
#define numwords 20

void display(char [][SIZE]);
int get_input(char [][SIZE+2]);
void interactive_input(char [][SIZE+2], int *count);
int format_word(char []);
void sortwords(char [][SIZE+2], int count);
