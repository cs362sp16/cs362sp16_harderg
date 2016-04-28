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

//Tests buyCard
int main() {

  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador, outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  myassert(r == 0, "No duplicates, 2 players, should succeed");

  r = buyCard(0, &g);

  myassert(r == 0, "buyCard failed, player had too few coins");

  checkasserts();

  return 0;
}