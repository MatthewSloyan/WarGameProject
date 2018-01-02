#include<stdio.h>

//function definition
int NewGame();
void displayGameStatus(int scores[], int round, int players);

void main()
{
	FILE* filep;
	
	int intitialGameSelection;
	int numberOfPlayers;
	int i, j, k;
	char gameName[40];
	char loadGameName[40];
	int player[10][13] = { {2,3,4,5,6,7,8,9,10,11,12,13,14}, {14,13,12,11,10,9,8,7,6,5,4,3,2}, {2,3,4,5,6,7,8,9,10,11,12,13,14} };
	int playerScore[10];
	int chosenCards[10];
	int chosenCardsChecker[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int roundCounter = 0;
	int loadSelection;
	int exitSelection;
	int cardSelection;
	int largestCard = 0;
	int largestUniqueCard;
	int largestPlayerNumber;
	int currentRoundScore = 0;
	int currentRoundNumber;
	int firstRound;
	int oldValue = 0;
	int num_char;
	int input;

	printf("Please start new game(1), load existing game(2) or exit game(0)\n");

	scanf("%d", &intitialGameSelection);

	while (intitialGameSelection != 0)
	{
		// start new game selection
		if (intitialGameSelection == 1) 
		{
			printf("Please enter a name for this new game\n"); //enter game name to save to file
			scanf("%s", gameName);

			strcat(gameName, ".txt");

			//add game name to file with all names
			

			//sets the starting number for game round for loop
			currentRoundNumber = 0;
			firstRound = 0;

			//calls method to start new game
			numberOfPlayers = NewGame();

			//initalize player scores to 0
			for (i = 0; i < numberOfPlayers; i++)
			{
				playerScore[i] = 0;
			}
		} //if 

		//load game selection
		else if (intitialGameSelection == 2) 
		{
			//load game
			printf("Please enter a name of the game you would like to load\n"); 
			scanf("%s", loadGameName);

			filep = fopen(loadGameName, "r");

			if (filep == NULL)
			{
				printf("The file cannot be opened\n");
			}

			else
			{
				while (!feof(filep))
				{
					fscanf(filep, "%d", &numberOfPlayers);
					fscanf(filep, "%d", &currentRoundNumber);

					for (i = 0; i < numberOfPlayers; i++) 
					{
						for (j = 0; j < 13; j++) 
						{
							fscanf(filep, "%d", &player[i][j]);
						}
					}

					for (i = 0; i < numberOfPlayers; i++)
					{
						fscanf(filep, "%d ", &playerScore[i]);
					}
				}
			}

		} //else if

		else 
		{
			//error wrong value is input
			printf("The value entered is invalid, please try again.\n");
		}

		//code to play game
		if (intitialGameSelection == 1 || intitialGameSelection == 2)
		{
			// for loop to run for 13 rounds or from what round is loaded
			for (i = currentRoundNumber; i < 13; i++)
			{
				//if round number isn't 0 it won't display the selection code
				if (firstRound != 0)
				{
					printf("\n1 - Complete the next Round\n2 - Save the Game\n3 - Output games Status\n4 - Exit game without saving\n");
					scanf("%d", &loadSelection);

					switch (loadSelection)
					{
					case 1:

						break;
					case 2:
						//open file to write to using name input by user
						filep = fopen(gameName, "w");

						//if file not found output error.
						if (filep == NULL)
						{
							printf("The file could not be opened\n");
						}

						//print game information to player
						else
						{
							fprintf(filep, "%d\n", numberOfPlayers);
							fprintf(filep, "%d\n", roundCounter);

							//loop to print player cards to file
							for (j = 0; j < numberOfPlayers; j++)
							{
								for (k = 0; k < 13; k++)
								{
									fprintf(filep, "%d ", player[j][k]);
								}
								fprintf(filep, "\n");
							}

							//file to write player scores to file
							for (j = 0; j < numberOfPlayers; j++)
							{
								fprintf(filep, "%d ", playerScore[j]);
							}

							fclose(filep); //close the file
						}
						break;
					case 3:
						displayGameStatus(playerScore, i, numberOfPlayers);
						break;
					case 4:
						printf("\n1 - Open a new Game\n2 - Open a Previously Saved Game\n3 - Exit application\n");
						scanf("%d", &exitSelection);

						if (exitSelection == 1) {
							printf("Please enter a name for this new game\n"); //enter game name to save to file
							scanf("%s", gameName);

							//sets the starting number for game round for loop
							currentRoundNumber = 0;

							//calls method to start new game
							numberOfPlayers = NewGame();
						}
						else if (exitSelection == 2) {

						}
						else if (exitSelection == 3) {
							//exits and closes application
							exit();
						}
						else {
							printf("Value entered is invald");
						}
						break;
					default:
						printf("Value entered is invald");
						break;
					} //switch
				}

				roundCounter++;
				firstRound = 1;
				printf("\nROUND %d\n", i + 1);

				/*loop to initialize chosen cards array for later comparision*/
				for (k = 0; k < 10; k++)
				{
					chosenCards[k] = 0;
				}

				//inner for to control the go for each player per round
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
						printf("Which card would you like to play in round %d\n", i + 1);
						printf("Numbers from 0 - 13, e.g card 1 = 0/card 3 = 2 or card must have not been played already\n");
						scanf("%d", &cardSelection);
					} while (cardSelection < 0 || cardSelection >= 13 || player[j][cardSelection] == 0); //checks to make sure player selection is between 0 and 13, also that card has not been played already

					printf("The card you selected is %d\n", player[j][cardSelection]);

					//save chosen card to scores array
					chosenCards[j] = player[j][cardSelection];
					//printf("Test %d\n", chosenCards[roundCounter][j]);

					//card is now used, so make 0
					player[j][cardSelection] = 0;
				}
				printf("\n");

				//print out all players choices
				printf("Round %d Selections and scores ============\n", i + 1);

				//set the current round score to 0
				currentRoundScore = 0;

				//loop to print out player chosen cards before they are checked for duplicates, also counts up score
				for (j = 0; j < numberOfPlayers; j++)
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", chosenCards[j]);

					//count up the total round score
					currentRoundScore += chosenCards[j];
				}

				//loop to check for duplicates 
				for (j = 0; j < numberOfPlayers; j++)
				{
					oldValue = chosenCards[j];

					//loop to check if the card is unique
					for (k = j + 1; k < numberOfPlayers; k++)
					{
						if (oldValue == chosenCards[k])
						{
							chosenCards[j] = 0;
							chosenCards[k] = 0;
						}
					} 
				}

				//for to check for largest card that isn't 0
				for (j = 0; j < numberOfPlayers; j++)
				{
					if (chosenCards[j] >= largestCard)
					{
						largestCard = chosenCards[j];
						largestPlayerNumber = j + 1;
					}
				}

				//add the score to the player score array
				playerScore[largestPlayerNumber - 1] += currentRoundScore;

				printf("\nThe winner of round %d is Player %d\n", i + 1, largestPlayerNumber);
				printf("Player %d's score is now %d\n", largestPlayerNumber, playerScore[largestPlayerNumber - 1]);

				/*for (j = 0; j < numberOfPlayers; j++)
				{
					printf("\nTest cards: %d\n", chosenCards[j]);
					printf("\nTest score: %d\n", playerScore[j]);
				}*/

			} //outer for
		} //if

		//subsequent read
		printf("Please start new game(1), load existing game(2) or exit game(0)\n");
		scanf("%d", &intitialGameSelection); 
	} //while
}

int NewGame()
{
	int numberOfPlayers;

	do
	{
		printf("How many players would you like? The number of players must be between 2 and 10\n");
		scanf("%d", &numberOfPlayers);
	} while (numberOfPlayers < 2 || numberOfPlayers > 10); //checks to make sure player count is between 2 and 10

	//deals cards to number of players

	return numberOfPlayers;
}

void displayGameStatus(int scores[], int round, int players)
{
	int i;

	printf("\nRound: %d\n", round + 1);
	printf("\Number of Players: %d\n\n", players);

	printf("Scores ============\n");

	for (i = 0; i < players; i++)
	{
		printf("Player %d: %d\n", i + 1, scores[i]);
	}
}