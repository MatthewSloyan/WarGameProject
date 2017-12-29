#include<stdio.h>

int NewGame();

void main()
{
	int intitialGameSelection;
	int numberOfPlayers;
	int i, j, k;
	char gameName[40];
	int player[10][13] = { {2,3,4,5,6,7,8,9,10,11,12,13,14}, {14,13,12,11,10,9,8,7,6,5,4,3,2}, {2,3,4,5,6,7,8,9,10,11,12,13,14} };
	int playerScore[10][1];
	int chosenCards[10];
	int roundCounter = 0;
	int loadSelection;
	int exitSelection;
	int cardSelection;
	int largestCard = 0;
	int largestUniqueCard;
	int largestPlayerNumber;
	int currentRoundScore = 0;

	printf("Please start new game(1), load existing game(2) or exit game(0)\n");

	scanf("%d", &intitialGameSelection);

	while (intitialGameSelection != 0)
	{
		// start new game selection
		if (intitialGameSelection == 1) 
		{
			printf("Please enter a name for this new game\n"); //enter game name to save to file
			scanf("%s", gameName);

			//calls method to start new game
			numberOfPlayers = NewGame();
			
		} //if 

		//load game selection
		else if (intitialGameSelection == 2) 
		{
			//load game
			numberOfPlayers = 2;
			printf("Load game\n");

		} //else if

		else 
		{
			//error wrong value is input
			printf("The value entered is invalid, please try again.\n");
		}

		//code to play game
		if (intitialGameSelection == 1 || intitialGameSelection == 2)
		{
			for (i = 0; i < 13; i++)
			{
				printf("\n1 - Complete the next Round\n2 - Save the Game\n3 - Output games Status\n4 - Exit game without saving\n");
				scanf("%d", &loadSelection);

				switch (loadSelection)
				{
				case 1:

					break;
				case 2:

					break;
				case 3:

					break;
				case 4:
					printf("\n1 - Open a new Game\n2 - Open a Previously Saved Game\n3 - Exit application\n");
					scanf("%d", &exitSelection);

					if (exitSelection == 1) {
						printf("Please enter a name for this new game\n"); //enter game name to save to file
						scanf("%s", gameName);

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

				roundCounter++;
				printf("\nROUND %d\n", roundCounter);

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
						printf("Which card would you like to play in round %d\n", roundCounter);
						printf("Numbers from 0 - 13, e.g card 1 = 0/card 3 = 2 or card must have not been played already\n");
						scanf("%d", &cardSelection);
					} while (cardSelection < 0 || cardSelection > 13 || player[j][cardSelection] == 0); //checks to make sure player selection is between 0 and 13, also that card has not been played already

					printf("The card you selected is %d\n", player[j][cardSelection]);

					//save chosen card to scores array
					chosenCards[j] = player[j][cardSelection];
					//printf("Test %d\n", chosenCards[roundCounter][j]);

					//card is now used, so make 0
					player[j][cardSelection] = 0;
				}
				printf("\n");

				//print out all players choices
				printf("Round %d Selections and scores ============\n", roundCounter);

				for (j = 0; j < numberOfPlayers; j++)
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", chosenCards[j]);

					if (chosenCards[j] > largestCard)
					{
						largestCard = chosenCards[j];
						largestPlayerNumber = j + 1;
					}

					//count up the total round score
					currentRoundScore += chosenCards[j];
				}

				//add the score to the player score array
				playerScore[largestPlayerNumber][0] = currentRoundScore;

				printf("\nThe winner of round %d is Player %d\n", roundCounter, largestPlayerNumber);
				printf("Player %d's score is now %d\n", largestPlayerNumber, playerScore[largestPlayerNumber][0]);

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