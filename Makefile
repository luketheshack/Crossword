crossword: crossword.o crossfunc.o
	gcc crossword.o crossfunc.o -o crossword

crossword.o: crossfunc.h crossword.c
	gcc -c crossword.c -o crossword.o

crossfunc.o: crossfunc.c crossfunc.h
	gcc -c crossfunc.c -o crossfunc.o

clean:
	rm *.o
	rm crossword
