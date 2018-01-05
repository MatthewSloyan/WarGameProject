#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>

//function definition
void NewGame();
void displayGameStatus(int scores[], int round, int players);
void loadGame();
void shuffleDeck();
void gameSelectionOptions();

//Global variable for file loading function
FILE* filep;

char gameName[40];
char loadGameName[40];
char gameNameAll[40];

int player[10][13] = { 0 }; //player cards and number
int cards[4][13] = { { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, }, { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, }, { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, }, { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, } };
int playerScore[10];
int numberOfPlayers;
int currentRoundNumber;
int i, j, k;
int num_char;
int ifNewGame = 0;
int loadSelection;
int exitSelection;

void main()
{
	//local variables
	int intitialGameSelection;
	int chosenCards[10];
	int chosenCardsChecker[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int roundCounter = 0;
	int cardSelection;
	int largestCard = 0;
	int largestUniqueCard;
	int largestPlayerNumber;
	int currentRoundScore = 0;
	int oldValue = 0;
	int input;

	//allow the user to select wheter to start a new game, load game or exit the application (intitial read)
	printf("Please start new game(1), load existing game(2) or exit game(0)\n");
	scanf("%d", &intitialGameSelection);

	while (intitialGameSelection != 0) //while loop until 0 is encountered
	{
		if (intitialGameSelection == 1) // start new game selection
		{
			NewGame(); //calls method to start new game
		}

		else if (intitialGameSelection == 2) //load game selection
		{
			loadGame(); //calls the load game function
		}

		else 
		{
			printf("The value entered is invalid, please try again.\n"); //error wrong value is input
		}

		// Play Game =====================================================

		if (intitialGameSelection == 1 || intitialGameSelection == 2)
		{
			for (i = currentRoundNumber; i < 13; ++i) // for loop to run for 13 rounds or from what round is loaded
			{
				roundCounter++;
				printf("\nROUND %d\n", i + 1);

				for (j = 0; j < 10; j++) //loop to initialize chosen cards array for later comparision
				{
					chosenCards[j] = 0;
				}

				for (j = 0; j < numberOfPlayers; j++) //inner for to control the go for each player per round
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

						//checks to make sure player selection is between 0 and 13, also that card has not been played already
					} while (cardSelection < 0 || cardSelection >= 13 || player[j][cardSelection] == 0);

					printf("The card you selected is %d\n", player[j][cardSelection]);

					chosenCards[j] = player[j][cardSelection]; //save chosen card to scores array

					player[j][cardSelection] = 0; //card is now used, so make 0
				} //for

				printf("\n");

				//print out all players choices
				printf("Round %d Selections and scores ============\n", i + 1);

				//set the current round score to 0
				//currentRoundScore = 0;

				// Round winners and scores =====================================================

				for (j = 0; j < numberOfPlayers; j++) //loop to print out player chosen cards before they are checked for duplicates, also counts up score
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", chosenCards[j]);

					currentRoundScore += chosenCards[j]; //count up the total round score
				}

				for (j = 0; j < numberOfPlayers; j++) //loop to check for duplicates 
				{
					oldValue = chosenCards[j];

					for (k = j + 1; k < numberOfPlayers; k++) //loop to check if the card is unique
					{
						if (oldValue == chosenCards[k])
						{
							chosenCards[j] = 0;
							chosenCards[k] = 0;
						}
					} 
				} //outer for

				for (j = 0; j < numberOfPlayers; j++) //for to check for largest card that isn't 0
				{
					if (chosenCards[j] > largestCard)
					{
						largestCard = chosenCards[j];
						largestPlayerNumber = j + 1;
					}
				}

				playerScore[largestPlayerNumber - 1] += currentRoundScore; //add the score to the player score array

				printf("\nThe winner of round %d is Player %d\n", i + 1, largestPlayerNumber);
				printf("Player %d's score is now %d\n", largestPlayerNumber, playerScore[largestPlayerNumber - 1]);

				/*for (j = 0; j < numberOfPlayers; j++)
				{
					printf("\nTest cards: %d\n", chosenCards[j]);
					printf("\nTest score: %d\n", playerScore[j]);
				}*/	

				//call the function to allow players to select a number of options, e.g play the next round, view the game status, exit without saving etc.
				gameSelectionOptions(); 

			} //for
		} //if 

		//subsequent read
		printf("Please start new game(1), load existing game(2) or exit game(0)\n");
		scanf("%d", &intitialGameSelection); 
	} //while
}

// FUNCTIONS ==========================================

// New game Function ==================================

void NewGame()
{
	int suit = 0;
	int randomCardPos;

	printf("Please enter a name for this new game\n"); //enter game name to save to file
	scanf("%s", gameName);

	strcat(gameName, ".txt"); //adds the file extension to name

	do
	{
		printf("How many players would you like? The number of players must be between 2 and 10\n");
		scanf("%d", &numberOfPlayers);
	} while (numberOfPlayers < 2 || numberOfPlayers > 10); //checks to make sure player count is between 2 and 10

	//initalize player scores to 0
	for (i = 0; i < numberOfPlayers; i++)
	{
		playerScore[i] = 0;
	}

	//sets the starting number for game round for loop
	currentRoundNumber = 0;
	ifNewGame = 1;

	// Dealing of Cards ==========================================

	srand(time(NULL)); /* seeds with the time of day */

	for (i = 0; i < numberOfPlayers; i++)
	{
		shuffleDeck(); //calls the shuffle deck function

		for (j = 0; j < 13; j++)
		{
			randomCardPos = rand() % 13; //gets a random array position between 0-12=
			player[i][j] = cards[suit][randomCardPos]; //deals random card to player of suit one E.g Spades

			suit++; //increments suit to move to suit two E.g Hearts
			if (suit == 3) // once the number of suits reaches it's end (all four suits) it starts over for the last card.
			{
				suit = 0;
			}
		}
	} //outer for
}

// Shuffling of Cards function ==========================================

void shuffleDeck()
{
	int randomNum;
	int oldCardValue;
	int i;

	// loop to run through card array shuffling it radomly
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 13; j++)
		{
			randomNum = rand() % 13; //gets a random array position between 0-12
			oldCardValue = cards[i][randomNum]; // saves the value in random number position
			cards[i][randomNum] = cards[i][j]; // card array gets updated with loop position
			cards[i][j] = oldCardValue; //card array gets updated with old card value E.g 12
		}
	}
}

// Load Game Function function ==========================================

void loadGame()
{
	printf("Game selection =====================\n");

	//open file with all the possible game selections
	filep = fopen("allGameNames.txt", "r");

	if (filep == NULL)
	{
		printf("The file cannot be opened\n");
	}

	else
	{
		while (!feof(filep))
		{
			num_char = fscanf(filep, "%s", gameNameAll);
			if (num_char > 0)
			{
				printf("%s\n", gameNameAll);
			}
		}
		printf("\n");

	}
	fclose(filep); //close the file
	
	//load game
	printf("Please enter a name of the game you would like to load\n");
	scanf("%s", loadGameName);

	//set name entered to game name for saving
	strcpy(gameName, loadGameName);

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

			//scan in the each players cards into array
			for (i = 0; i < numberOfPlayers; i++)
			{
				for (j = 0; j < 13; j++)
				{
					fscanf(filep, "%d", &player[i][j]);
				}
			}

			//scan in the each players scores into array
			for (i = 0; i < numberOfPlayers; i++)
			{
				fscanf(filep, "%d ", &playerScore[i]);
			}

			printf("\nGame %s is loaded\n", gameName);
		} //while
		fclose(filep); //close the file

		displayGameStatus(playerScore, i, numberOfPlayers); //display the status of the game
	} //else
}

// Display Game status Function ==========================================

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

// Game Selection options Function =====================================================

void gameSelectionOptions()
{
	printf("\n1 - Complete the next Round\n2 - Save the Game\n3 - Output games Status\n4 - Exit game without saving\n");
	scanf("%d", &loadSelection);

	switch (loadSelection)
	{
	case 1:
		//complete the next round
		break;
	case 2:
		//Save the game selection
		filep = fopen(gameName, "w"); //open file to write to using name input by user

		if (filep == NULL) //if file not found output error.
		{
			printf("The file could not be opened\n");
		}

		else //print game information to file
		{
			fprintf(filep, "%d\n", numberOfPlayers);
			fprintf(filep, "%d\n", i);

			for (j = 0; j < numberOfPlayers; j++) //loop to print player cards to file
			{
				for (k = 0; k < 13; k++)
				{
					fprintf(filep, "%d ", player[j][k]);
				}
				fprintf(filep, "\n");
			}

			for (j = 0; j < numberOfPlayers; j++) //for to write player scores to file
			{
				fprintf(filep, "%d ", playerScore[j]);
			}

			fclose(filep); //close the file
		}

		//if it's a new game it will add the name to all games file
		//if it's not a new game then it won't add it as the name will already exist in the file
		if (ifNewGame == 1)
		{
			//add game name to file with all names
			filep = fopen("allGameNames.txt", "a");

			if (filep == NULL)
			{
				printf("The file could not be opened\n");
			}

			else
			{
				fprintf(filep, "%s\n", gameName); //appends game name to file
				fclose(filep);
			}
		}
		break;
	case 3:
		displayGameStatus(playerScore, i, numberOfPlayers); //diplays the game status to players
		break;
	case 4:
		//Allows the user to open a new game,  Open a Previously Saved Game or exit application
		printf("\n1 - Open a new Game\n2 - Open a Previously Saved Game\n3 - Exit application\n");
		scanf("%d", &exitSelection);

		if (exitSelection == 1) {
			NewGame(); //calls method to start new game
			i = -1; //sets the round back to 1
		}
		else if (exitSelection == 2)
		{
			loadGame(); //calls the load game function
			i = currentRoundNumber - 1; //sets the round back to the round in the file
		}
		else if (exitSelection == 3) {
			//exits and closes application
			exit(0);
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