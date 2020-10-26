# Crossword

This crossword generating program takes in words provided by the user or provided from a file and puts them on the crossword board. The crossword is then displayed on the board. For more information, visit https://www3.nd.edu/~rbualuan/courses/fundcomp20/lab8/ 

I completed both the first and second extra credit assignment for this program as well. The first extra credit assignment is located in the "placewords" (crossfunc.c, line 149) function. Instead of quitting after it cannot place a word, the program continues trying to place words. The second extra credit assignment is the "try_place_again" function (crossfunc.c, line 294), which attempts to place the words that couldn't be initially placed after all the others have been placed. The try_place_again function runs one more time for each word that couldn't be placed on the first pass throughout (see crossword.c). Both extra credit systems are fully functional.  
