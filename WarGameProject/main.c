#include<stdio.h>

void main()
{
	int intitialGameSelection;
	int numberOfPlayers;
	int i;
	char gameName[40];

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

			for (i = 0; i <= numberOfPlayers; i++)
			{
				printf("%d\n", i);
			}
		}

		else if (intitialGameSelection == 2) 
		{
			//load game
		}

		else 
		{
			//error wrong value is input
			printf("The value entered is invalid, please try again.\n");
		}

		printf("Please start new game(1), load existing game(2) or exit game(0)\n");
		scanf("%d", &intitialGameSelection);

	}
}