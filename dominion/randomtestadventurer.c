#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int failed = 0;

void myassert(int b,char* msg) {
    if (b == 0) {
      printf("FAILED ASSERTION: %s\n",msg);
      failed = 1;
    }
}

void checkasserts() {
    if (!failed) {
      printf ("TEST SUCCESSFULLY COMPLETED.\n");
    }
}


//Tests the adventurer card by feeding it randomly generated
//input 2000 times
int main(int argc, char const *argv[])
{
  
  int x, r, i;
  struct gameState g;
  int j = 0;
  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador, outpost,baron,tribute};

  x = (int)argv[1];
  srand(x);
  printf("IN RANDOMCARDTEST\n");

  for (i = 0; i < 2000; i++) {  
    r = initializeGame((rand() % MAX_PLAYERS), k, rand(), &g);

    r = cardEffect(adventurer, (rand() % 3), (rand() % 3), (rand() % 3), &g, 0, &j);

    myassert(r == 0, "adventurer failed");

    if(failed) {
      break;
    }
  }

    checkasserts();

  return 0;
}