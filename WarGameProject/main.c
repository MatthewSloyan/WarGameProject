#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>

// Matthew Sloyan - G00348036
// https://github.com/MatthewSloyan/WarGameProject

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
	int roundCounter = 0;
	int cardSelection;
	int largestCard = 0;
	int largestPlayerNumber;
	int largestOverallScore = 0;
	int winningPlayer;
	int currentRoundScore = 0;
	int nextRoundChecker;
	int nextRoundScore = 0;
	int oldValue = 0;

	//allow the user to select wheter to start a new game, load game or exit the application (intitial read)
	printf("Please start new game(1), load existing game(2) or exit game(0)\n");
	scanf("%d", &intitialGameSelection);

	//while loop until 0 is encountered
	while (intitialGameSelection != 0) 
	{
		// start new game selection
		if (intitialGameSelection == 1) 
		{
			NewGame(); //calls method to start new game
		}
		
		//load game selection
		else if (intitialGameSelection == 2) 
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
			// for loop to run for 13 rounds or from what round is loaded
			for (i = currentRoundNumber; i < 13; ++i) 
			{
				roundCounter++;
				printf("\nROUND %d\n", i + 1);

				//loop to initialize chosen cards array for later comparision
				for (j = 0; j < 10; j++) 
				{
					chosenCards[j] = 0;
				}

				//inner for to control the go for each player per round
				for (j = 0; j < numberOfPlayers; j++) 
				{
					//display the current players cards
					printf("\nPlayer %d: ", j + 1);
					printf("\n=========================================================");
					printf("\nCards: ");

					for (k = 0; k < 13; k++)
					{
						printf("%-4d", player[j][k]);
					}
					printf("\n");
					printf("=========================================================\n");
					printf("Input: 1   2   3   4   5   6   7   8   9   10  11  12  13\n");
					printf("=========================================================\n\n");

					//allows current player to select card from array to use
					do
					{
						printf("Which card would you like to play in round %d\n", i + 1);
						printf("The number below your card is the value you input to select the card, however the card must have not been played already\n");
						scanf("%d", &cardSelection);

						//checks to make sure player selection is between 0 and 13, also that card has not been played already
					} while (cardSelection < 0 || cardSelection > 13 || player[j][cardSelection - 1] == 0);

					//print the selected card
					printf("The card you selected is %d\n", player[j][cardSelection - 1]);

					//save chosen card to scores array
					chosenCards[j] = player[j][cardSelection - 1];

					//card is now used, so make 0
					player[j][cardSelection - 1] = 0; 
				} //for

				printf("\n");

				//print out all players choices
				printf("Round %d Selections and scores ============\n", i + 1);

				// Round winners and scores =====================================================

				//loop to print out player chosen cards before they are checked for duplicates, also counts up score
				for (j = 0; j < numberOfPlayers; j++)
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", chosenCards[j]);

					currentRoundScore += chosenCards[j]; //count up the total round score
				}

				//loop to check for duplicates 
				for (j = 0; j < numberOfPlayers; j++) 
				{
					//sets the oldvalue to the iteration value E.g 
					oldValue = chosenCards[j]; 

					//loop to check if the card is unique
					for (k = 0; k < numberOfPlayers; k++) 
					{
						//if k == j then value will be equal as it's the same value in array, so it skips over it
						if (k == j) 
						{
							continue;
						}

						//if the card value equals the oldvalue then it and the old value is changed to 0, removing the duplicates.
						if (oldValue == chosenCards[k]) 
						{
							chosenCards[j] = 0;
							chosenCards[k] = 0;
						}
					}
				} //outer for

				//variable to determine if all values are equal
				nextRoundChecker = 0; 

				//for to check for largest card that isn't 0
				for (j = 0; j < numberOfPlayers; j++) 
				{
					if (chosenCards[j] >= largestCard)
					{
						largestCard = chosenCards[j];
						largestPlayerNumber = j + 1;
					}

					//check if chosen card is greater than 0, which would mean that all the values aren't equal
					if (chosenCards[j] > 0)
					{
						nextRoundChecker = 1;
					}
				}

				//if it still equals to 0 then all values must be equal, so the score is added to the next round
				if (nextRoundChecker == 0)
				{
					nextRoundScore = currentRoundScore;
					printf("\nThe Round is a draw, %d points will carry over to the next round\n", nextRoundScore);
				}
				else
				{
					//if game was a draw in the last round, the score is added if the round is won.
					if (nextRoundScore > 0)
					{
						currentRoundScore += nextRoundScore;
					}

					//add the score to the player score array
					playerScore[largestPlayerNumber - 1] += currentRoundScore;

					printf("\nThe winner of round %d is Player %d\n", i + 1, largestPlayerNumber);
					printf("Player %d's score is now %d\n", largestPlayerNumber, playerScore[largestPlayerNumber - 1]);
				}

				//call the function to allow players to select a number of options, e.g play the next round, view the game status, exit without saving etc.
				if(i < 12)
				{
					gameSelectionOptions();
				}
				
				currentRoundScore = 0; //set the current round score back to 0

			} //for

			// End of game ==================================

			//loop that runs trough scores array to check for the winnner
			for (i = 0; i < numberOfPlayers; i++) 
			{
				if (playerScore[i] > largestOverallScore)
				{
					largestOverallScore = playerScore[i];
					winningPlayer = i + 1;
				}
			}

			printf("\nThe winner of the War is Player %d with a total score of %d\n", winningPlayer, largestOverallScore);

			printf("\n\nThe War has ended!\n\n\n");

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

	//enter game name to save to file
	printf("Please enter a name for this new game, please don't include file extension\n");
	scanf("%s", gameName);

	//adds the file extension to name
	strcat(gameName, ".txt");

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

		//for loop that takes a random card from each suit in order 1-4, till it fills the 13 cards. 
		//E.g first iteration, it takes a random diamond, then a random heart and so on.
		for (j = 0; j < 13; j++)
		{
			randomCardPos = rand() % 13; //gets a random array position between 0-12
			player[i][j] = cards[suit][randomCardPos]; //deals random card to player of suit one E.g Spades

			suit++; //increments suit to move to suit two E.g Hearts
			if (suit == 3) // once the number of suits reaches it's end (all four suits) it starts over
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
		printf("The file cannot be opened\n\n");
	}

	else
	{
		while (!feof(filep))
		{
			//if the file contains values it will print out the game names
			num_char = fscanf(filep, "%s", gameNameAll);
			if (num_char > 0)
			{
				printf("%s\n", gameNameAll);
			}
		}
		printf("\n");
		fclose(filep); //close the file
	}
	
	//load game
	printf("Please enter a name of the game you would like to load, please included .txt extension\n");
	scanf("%s", loadGameName);

	//set name entered to game name for saving
	strcpy(gameName, loadGameName);

	//open the that the player has entered if found
	filep = fopen(loadGameName, "r");

	if (filep == NULL)
	{
		printf("The file cannot be opened\n");
	}

	else
	{
		while (!feof(filep))
		{
			//read in the number of players and the current round
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
	printf("Number of Players: %d\n\n", players);

	printf("Scores ============\n");

	//print out the scores of the game
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
		//open file to write to using name input by user
		filep = fopen(gameName, "w"); 

		//if file not found output error.
		if (filep == NULL) 
		{
			printf("The file could not be opened\n");
		}

		else //print game information to player
		{
			fprintf(filep, "%d\n", numberOfPlayers);
			fprintf(filep, "%d\n", i + 1); //prints the round to file

			//loop to print player cards to file
			for (j = 0; j < numberOfPlayers; j++)
			{
				for (k = 0; k < 13; k++)
				{
					fprintf(filep, "%d ", player[j][k]);
				}
				fprintf(filep, "\n");
			}

			//for to write player scores to file
			for (j = 0; j < numberOfPlayers; j++) 
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