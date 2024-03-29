WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
// escape.c
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

// Here are the public Function declarations of the puzzle
// You will need these (plus system and C library calls) 
// to solve this puzzle.
// pipe,dup2, using pthread and signal handling may be useful

void debug_shell_mp(char* besticecream); // puzzle 1
// There is no function call required for puzzle 2.
// Puzzle 2 starts as soon as puzzle 1 is finished, so be prepared
void  piping_hot();                  // puzzle 3
void* race_to_the_finish(void* argh); //puzzle 4
void  never_gonna_say_goodbye(char* lyric);// puzzle 4 (closing credits)

// author: hanxuan6

