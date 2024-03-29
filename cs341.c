WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHELL (10)
#define MALLOC  (11)
#define MAPREDUCE (12)
#define DEADLOCK_DEMOLITION (13)
#define NONSTOP_NETWORKING (14)


#define BEST_MASCOT ("Rubber Mutex Duck")

// compile with: clang -pthread -O0 -Wall -Wextra -g -std=c99 -D_GNU_SOURCE -DDEBUG escape.c cs341.c

static int stage = 1; // Complete all 4 puzzles
static int completed = 0;

static int hardest_mp = SHELL;
static int leaky_barrier  = 0;
static int oops_i_did_it_again = 0;

static char* secret;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void rick_astley_says(char* mesg) {
  write(1, mesg, strlen(mesg));
  const char* never = "\n\nI just wanna tell you how I'm feeling\nGotta make you understand\n\nNever Gonna Give Up on Stage ";
  write(1, never, strlen(never));
  write(1, ((char*)"0123456789") + stage, 1);
  write(1, ".\n", 2);
  exit(1); 
}
static void check_completed() {
  if (! completed) {
    puts("\nYour attempt was incomplete. Try again?");
  } else {
    puts("Unbelievable. You, <em>{subject name}</em> must be the pride of <em>{subjecthometown}</em>!");
  }
}

static void congrats(int new_stage, char* description) {
  printf("\n\nCongrats - stage %d complete!\nUnlocking stage %d:\n%s\n", stage, new_stage, description);
  stage = new_stage;
  sleep(1);
}

static void trace(char* mesg) {
  write(1, mesg, strlen(mesg));
  write(1, "()\n", 3);
}

static void check_stage(int expected) {
   if( stage != expected) {
     printf("\nThis is puzzle #%d; you need to solve puzzle #%d first\n", expected, stage);
     exit(1);
   }
}

static char* get_textmessage(int fd) {
  printf("\nChecking fd %d ...\n", fd);
  FILE* f = fdopen(fd, "r");
  if ( ! f) {
    rick_astley_says("Could not open message; is that file descriptor valid?");
  }
  char* buffer = NULL;
  size_t capacity = 0;
  printf("Found Nokia flip phone. Waiting for message...\n");
  ssize_t result = getline(&buffer, &capacity, f);
  fclose(f);
  if( result < 0 ) { return NULL; }
  return buffer;
}

static void check_mascot() {
  trace("check_mascot");
  check_stage(2);
  char* text_message = get_textmessage(DEADLOCK_DEMOLITION);
  if ( ! text_message) {
  	perror("Failed to get message"); 
	  rick_astley_says("Did you even send a text?");
  }
  printf("Message received: '%s'\n", text_message);

  if ( strncmp(BEST_MASCOT, text_message, strlen(BEST_MASCOT)) != 0) {
    rick_astley_says("... which wont work. We need a better idea than that.");
  }
  free( text_message);

  congrats(3, "Let's make some plans - Wait for my signal then dance quickly.");
  check_stage(3);
  hardest_mp = SHELL;
  usleep(rand() % 200000);
  hardest_mp = MALLOC;
  trace("Sending signal...");
  int piper[2];
  pipe(piper);
  close(piper[0]);
  write(piper[1],"I just wanna tell you how I'm feeling", 1);
  usleep(5000);
  if( hardest_mp != MAPREDUCE) {
    rick_astley_says("Wrong sequence of events! And if you ask me how I'm feeling. Don't tell me you're too blind to see we need a U of I student to when to handle these hot signals.");
  }  
   congrats(4, "We know the game, and we're gonna play it");
}

// public API
void debug_shell_mp(char* besticecream) {
  trace("debug_shell_mp");
  check_stage(1);
  if ( strcmp(besticecream,"Altgeld DQ") && strcmp(besticecream, "Siebel") && strcmp(besticecream, "Foellinger") ) { 
    congrats(2,"Nice - Let's check the text messsages for mascot ideas");
    
    atexit(check_completed);

    check_mascot();
  }
}

void piping_hot() {
  trace( "piping_hot");
  check_stage(3);
  if( hardest_mp == MALLOC) {
    hardest_mp = MAPREDUCE;
  } else {
    rick_astley_says("Don't give up; just wait for my signal!");
  }
}

void* race_to_the_finish(void* arg) {
  if(stage == 5) return NULL;
  check_stage(4);
  if ( arg != (void*) 0x20230341 )  { rick_astley_says("So close - don't desert me"); }

  pthread_mutex_lock(&mutex);
  int success = (++ leaky_barrier ) == 20 && oops_i_did_it_again > 5;
  pthread_mutex_unlock(&mutex);
  if ( ! success) { 
    usleep(1000*( 500 + (rand() & 1023)));
    pthread_mutex_lock(&mutex);
    leaky_barrier --;
    oops_i_did_it_again ++;
    if(stage == 4) {
      printf("Leaky Barrier! %d threads escaped! (%d remain)\n", oops_i_did_it_again, leaky_barrier );
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL); 
  }
  pthread_mutex_lock(&mutex);
  if ( ! secret) {
    const char* chorus[] = {"give you up","let you down","run around and desert you","make you cry","say goodbye","tell a lie and hurt you"};
    unsigned int r = rand();
    asprintf(&secret,"%x: Never gonna %s", r, chorus[r % 6]);
    congrats(5,"Call finish with the correct lyric message to win!\n(Hint: sometimes the most important code does nothing)");
  }
  pthread_mutex_unlock(&mutex);
  char* result = strdup(secret);
  pthread_exit((void*) result);  
}

void never_gonna_say_goodbye(char* lyric) {
  trace("never_gonna_say_goodbye...");
  check_stage(5);
  alarm(1);
  sleep(2);
  if ( strcmp(secret, lyric) == 0) {
    completed = 1;
    puts( lyric );
    puts( "CS341 Puzzle Complete - thanks for playing the cs341 puzzle.\n\nYour CS341 Experience is now complete.\n\nGoodbye!" );
    exit(EXIT_SUCCESS);
  }
  rick_astley_says("Incorrect lyric");
}
