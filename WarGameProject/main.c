#include<stdio.h>

void main()
{
	int intitialGameSelection;
	int numberOfPlayers;
	int i, j, k;
	char gameName[40];
	int player[10][13] = { { 2,3,4,5,6,7,8,9,10,11,12,13,14 }, { 14,13,12,11,10,9,8,7,6,5,4,3,2 } };
	int chosenCards[13][10];
	int roundCounter = 0;
	int cardSelection;

	printf("Please start new game(1), load existing game(2) or exit game(0)\n");

	scanf("%d", &intitialGameSelection);

	while (intitialGameSelection != 0)
	{
		// start new game selection
		if (intitialGameSelection == 1) 
		{
			printf("Please enter a name for this new game\n"); //enter game name to save to file
			scanf("%s", gameName);

			do
			{
				printf("How many players would you like? The number of players must be between 2 and 10\n");
				scanf("%d", &numberOfPlayers);
			} while (numberOfPlayers < 2 || numberOfPlayers > 10); //checks to make sure player count is between 2 and 10

			//deals cards to number of players

			//test player arrays
			/*for (i = 0; i < 2; i++)
			{
				for (j = 0; j < 13; j++)
				{
					printf("%d\t", player[i][j]);
				}
				printf("\n");
			}*/

			//test number of players 
			/*for (i = 0; i <= numberOfPlayers; i++)
			{
				printf("%d\n", i);
			}*/

			//outer for to control the 13 rounds of the game
			for (i = 0; i < 13; i++)
			{
				roundCounter++;

				//inner for to controle the go for each player per round
				for (j = 0; j < numberOfPlayers; j++)
				{
					//display the current players cards
					printf("\nPlayer %d: Your cards =====================\n", j + 1);

					for (k = 0; k < 13; k++)
					{
						printf("%d  ", player[j][k]);
					}
					printf("\n");
					printf("==========================================\n\n");

					//allows current player to select card from array to use
					do
					{
						printf("Which card would you like to play in round %d\n", roundCounter);
						printf("Numbers from 0 - 13, e.g card 1 = 0/card 3 = 2 or card must have not been played already\n");
						scanf("%d", &cardSelection);
					} while (cardSelection < 0 || cardSelection > 13 || player[j][cardSelection] == 0); //checks to make sure player selection is between 0 and 13, also that card has not been played already

					printf("The card you selected is %d\n", player[j][cardSelection]);

					//save chosen card to scores array
					chosenCards[roundCounter][j] = player[j][cardSelection];
					//printf("Test %d\n", chosenCards[roundCounter][j]);

					//card is now used, so make 0
					player[j][cardSelection] = 0;
				}
				printf("\n");

				//print out all players choices
				printf("Round %d Selections and scores ", roundCounter);
				printf("============\n");

				for (j = 0; j < numberOfPlayers; j++)
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", chosenCards[roundCounter][j]);
				}
			} //outer for
		} //if 

		else if (intitialGameSelection == 2) 
		{
			//load game
		}

		else 
		{
			//error wrong value is input
			printf("The value entered is invalid, please try again.\n");
		}

		//subsequent read
		printf("Please start new game(1), load existing game(2) or exit game(0)\n");
		scanf("%d", &intitialGameSelection); 
	}
}