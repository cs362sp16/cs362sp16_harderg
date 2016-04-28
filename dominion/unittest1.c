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

int main() {

	struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	             outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  printf("IN UNITTEST1\n");

  myassert(r == 0, "Proper set up for a game, this should succeed");

  int k2[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	               outpost,baron,adventurer};

  r = initializeGame(2, k2, 5, &g);

  myassert(r == -1,"Duplicated cards, this should fail");

  checkasserts();

  return 0;
}
