#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

static char board[3][3] = { '1','2','3','4','5','6','7','8','9'};

static int print_board(); //prints the board on screen, as of current status of the game
static int take_input(int playernumber, char player_character); //takes inputs from players
static int game_win_check(char playercharacter); //checks if given player has won the game
static int print_game_result(int result); //prints the final game result

int main()
{
	int game_status = 0; //0 means game in-progress. 1 means player 1 won. 2 means player 2 won. -1 means draw
	int number_moves = 0; // if this becomes 9 without a winner, then game is a draw

	print_board();

	while (1)
	{
		//player 1 moves
		take_input(1, 'X');
		print_board();
		number_moves++;
		
		//checking if player 1 has won
		if (game_win_check('X') == 1)
		{
			game_status = 1;
			break;
		}

		//checking if game is a draw
		if (number_moves == 9)
		{
			game_status = -1;
			break;
		}

		//player 2 moves
		take_input(2, 'O');
		print_board();
		number_moves++;

		//checking if player 2 has won
		if (game_win_check('O') == 1)
		{
			game_status = 2;
			break;
		}
		
		//checking if game is a draw
		if (number_moves == 9)
		{
			game_status = -1;
			break;
		}
	}

	print_game_result(game_status);

	return 0;
}

static int print_board()
{
	int row = 0, col = 0;
		
	system("cls");
	
	printf(RED "Player 1 is X." RESET GRN "Player 2 is O." RESET "\n\n");

	printf("+---+---+---+\n"); //printing top line of board

	for (row = 0; row < 3; row++)
	{
		printf("|"); //printing first vertical of first column for given row
		
		for (col = 0; col < 3; col++)
		{
			
			if (board[row][col] == 'X') printf(RED " %c " RESET "|", board[row][col]);
			else if (board[row][col] == 'O') printf(GRN " %c " RESET "|", board[row][col]);
			else printf(" %c |", board[row][col]);
		}

		printf("\n+---+---+---+\n"); //printing bottom line of given row
	}

	printf("\n\n");

	return 0;
}

static int take_input(int playernumber, char player_character)
{
	int play_pos = 0; //to capture cell number for this move
	char commit_key = 0; //to make sure user enters integer followed by enter only
	int clear_stdin_buffer = 0;
	int row = 0, col = 0;

	if (playernumber == 1) printf(RED "Player %d" RESET ", please choose cell for your next move and hit enter: ", playernumber);
	else printf(GRN "Player %d" RESET ", please choose cell for your next move and hit enter: ", playernumber);
		
	while (1)
	{
		if (scanf_s("%d%c", &play_pos, &commit_key, 2) != 2 || commit_key != '\n')
		{
			printf("\nWrong move. Please choose from one of the available cells and hit enter: ");
			
			while ((clear_stdin_buffer = getchar()) != '\n' && clear_stdin_buffer != EOF) {}
			
			continue;
		}
		
		row = (play_pos - 1) / 3;
		col = (play_pos - 1) % 3;
		
		if (play_pos < 1 || play_pos > 9 || board[row][col] == 'X' || board[row][col] == 'O')
		{
			printf("\nWrong move. Please choose from one of the available cells and hit enter: ");
			
			while ((clear_stdin_buffer = getchar()) != '\n' && clear_stdin_buffer != EOF) {}
		}
		else break;
	}
	
	board[row][col] = player_character;

	return 0;
}

static int game_win_check(char player_character)
{
	int win = 0; //will be set to 1, if given player wins
	int row = 0, col = 0;
	int win_counter = 0; //if this becomes equal to 3 during checking in this function, then given player wins

	//checking rows to see if given player has won the game
	for (row = 0; row < 3; row++)
	{
		for (col = 0, win_counter = 0; col < 3; col++)
		{
			if (board[row][col] == player_character) win_counter++;
		}

		if (win_counter == 3) 
		{
			win = 1;
			return win;
		}
	}

	//checking cols to see if given player has won the game
	for (col = 0; col < 3; col++)
	{
		for (row = 0, win_counter = 0; row < 3; row++)
		{
			if (board[row][col] == player_character) win_counter++;
		}

		if (win_counter == 3)
		{
			win = 1;
			return win;
		}
	}

	//checking diagonal to see if given player has won the game
	for (row = 0, col = 0, win_counter = 0; row < 3 && col < 3; row++, col++)
	{
		if (board[row][col] == player_character) win_counter++;

		if (win_counter == 3)
		{
			win = 1;
			return win;
		}
	}
	

	return win;

}

static int print_game_result(int result)
{

	switch (result)
	{
		case 1:
			printf(RED "Player %d " RESET "wins!!", result);
			break;

		case 2:
			printf(GRN "Player %d " RESET "wins!!", result);
			break;

		default:
			printf("It's a tie!!");
	}
	
	return 0;
}
