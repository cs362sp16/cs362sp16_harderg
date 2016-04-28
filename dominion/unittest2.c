#include <stdio.h>

#include "dominion.h"


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

//Tests playCard
int main() {

  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador, outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  printf("IN UNITTEST2\n");

  myassert(r == 0, "No duplicates, 2 players, should succeed");

  r = playCard(baron,1,0,0,&g);

  myassert(r == 0, "playCard failed");

  checkasserts();

  return 0;
}