#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dominion.h"
#include "rngs.h"

#define MIN_CARD adventurer
#define MAX_CARD treasure_map

#define TREASURE_MIN copper
#define TREASURE_MAX gold

#define TRUE 1
#define FALSE 0

int is_in_array(int value, int *array, int size);
void init_gamestate(struct gameState *g, int seed);
int num_k_cards(struct gameState *g);
int count_money (struct gameState *g);
void random_play(struct gameState *g);

int main(int argc, char const *argv[]) {

	struct gameState g;
	int seed;

	seed = atoi(argv[1]);

	init_gamestate(&g, seed);
	random_play(&g);

	return 0;
}

void random_play(struct gameState *g) {
	int i, j, kcards, usekingdom, usetreasure, card, money, 
	choice1, choice2, choice3;
	int numturns = 0;

	while(!isGameOver(g)) {
		kcards = 0;

		printf("Player %d's turn\n", whoseTurn(g));

		//player will use a kingdom card 75% of the time
		if(rand() % 100 > 24) {
			usekingdom = TRUE;
		}
		else {
			usekingdom = FALSE;
		}
		kcards = num_k_cards(g);

		while (g->numActions > 0 && kcards > 0 && usekingdom) {
			card = rand() % kcards;

			i = 0;
			j = 0;

			while (j < card) {
				if (handCard(i, g) >= MIN_CARD && handCard(i, g) <= MAX_CARD) {
					j++;
				}
				i++;
			}

			choice1 = rand() % MAX_CARD;
			choice2 = rand() % MAX_CARD;
			choice3 = rand() % MAX_CARD;

			 printf( "Player %d playing kingdom card %d, handPos = %d\n",
                    whoseTurn( g ), handCard( i, g ), i );
            printf( "\tchoice1: %d \tchoice2: %d \tchoice3: %d\n", choice1, choice2, choice3 );

			playCard(i, choice1, choice2, choice3, g);

			//now only a 50% chance of playing a card
			if(rand() % 100 > 49) {
				usekingdom = TRUE;
			}
			else {
				usekingdom = FALSE;
			}
			kcards = num_k_cards(g);
		}

		money = count_money(g);
		//player will use a treasure card 75% of the time
		if(rand() % 100 > 24) {
			usetreasure = TRUE;
		}
		else {
			usetreasure = FALSE;
		}

		g->numBuys = 1;

		//75% chance of buying kingdom card 25% of buying any card
		while (g->numBuys > 0 && money > 0 && usetreasure) {
			
			do {
				if(rand() % 100 > 24) {
					card = rand() % (MAX_CARD - MIN_CARD) + MIN_CARD;;
				}
				else {
					card = rand() % MAX_CARD;
				}
			} while(buyCard(card, g) == -1);

			printf( "Player %d buying card %d\n", whoseTurn( g ), card );

			money = count_money(g);
			//lower the chance to 50%
			if(rand() % 100 > 49) {
				usetreasure = TRUE;
			}
			else {
				usetreasure = FALSE;
			}
		}

		endTurn(g);
		numturns++;
	}
}

void init_gamestate(struct gameState *g, int seed) {
	int kcards[10], numplayers, randcard, i;

	srand(seed);

	//guarantee 2-4 players
	numplayers = rand() % (MAX_PLAYERS - 2) + 2;

	//randomly pick cards
	for(i = 0; i < 10; i++) {
		do {
			randcard = rand() % (MAX_CARD - MIN_CARD) + MIN_CARD;
		} while (is_in_array(randcard, kcards, i+1));

		kcards[i] = randcard;
	}

	if (initializeGame(numplayers, kcards, seed, g) == -1) {
		printf("initializeGame failed\n");
		exit(1);
	}
}

int num_k_cards(struct gameState *g) {
	int i;
	int cards = 0;

	for (i = 0; i < numHandCards(g); i++) {
		if(handCard(i, g) >= MIN_CARD && handCard(i, g) <= MAX_CARD) {
			cards++;
		}
	}

	return cards;
}

int count_money (struct gameState *g) {
	int i;
	int money = 0;

	for(i = 0; i < numHandCards(g); i++) {
		if (handCard(i, g) == copper) {
			money += 1;
		}
		else if (handCard(i, g) == silver) {
			money += 2;
		}
		else if (handCard(i, g) == gold) {
			money += 3;
		}
		else {
			NULL;
		}
	}
	return money;
}

int is_in_array(int value, int *array, int size) {
	int i;

	for (i = 0; i < size; i++) {
		if (array[i] == value) {
			return TRUE;
		}
	}
	return FALSE;
}
