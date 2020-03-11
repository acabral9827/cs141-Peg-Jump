/* pegJump.cpp

   Author: Alejandro Cabral
   Program: #3, Peg Jump
   CS 141, Spring 2019

   Description:
		  This program represents a peg jumping puzzle  A
		move is made by a peg jumping over another peg into an empty
		spot, where the jumped peg is then removed from the board. The
		game ends when there are no more valid moves to make. The object
		is to eliminate as many pegs as possible.

		Sample output:

			Welcome to the peg jump puzzle!
			Enter '-' to exit, or '+' for instructions.

							A B C
							D E F
					G H I J K L M
					N O P * Q R S
					T U V W X Y Z
							1 2 3
							4 5 6

			1. Enter the peg to move: +

			Welcome to the peg jump puzzle. The board starts out with a
			single blank position, represented by the '*'.  To make a
			move, select the letter of a peg.  A peg must be able to
			jump over an adjacent peg into a blank position for a move
			to be valid.  The jumped peg is then removed from the board.
			The game is over when there are no valid moves left. At any
			point enter '-' to exit, or '+' for instructions.

			1. Enter the peg to move: E

							A B C
							D * F
					G H I * K L M
					N O P E Q R S
					T U V W X Y Z
							1 2 3
							4 5 6

			2. Enter the peg to move: w

							A B C
							D * F
					G H I W K L M
					N O P * Q R S
					T U V * X Y Z
							1 2 3
							4 5 6

			3. Enter the peg to move: 5

							A B C
							D * F
					G H I W K L M
					N O P * Q R S
					T U V 5 X Y Z
							1 * 3
							4 * 6

			4. Enter the peg to move: 2
			*** Invalid move, please retry. ***
			4. Enter the peg to move: r

							A B C
							D * F
					G H I W K L M
					N O P R * * S
					T U V 5 X Y Z
							1 * 3
							4 * 6

			5. Enter the peg to move: R

							* * *
							* 1 *
					* * * * * * *
					* * * + * * *
					* * * * * * *
							* 2 *
							* * *

			There is more than one possible move.  Which move do you want? 1

							A B C
							D R F
					G H I * K L M
					N O P * * * S
					T U V 5 X Y Z
							1 * 3
							4 * 6

			6. Enter the peg to move: -

			Exiting...

			27 pieces remaining. Ouch!
 */

 /***
  * Mallavarapu:
  * 1) Good
  * ***/

#include <iostream>
#include <cctype>     // For toupper()
using namespace std;

const int NumberOfPegs = 121;         // number of pegs on board
const int PegsPerRow = 11;            // number of pegs per row

//-------------------------------------------------------------------------------------
void displayInstructions()
{
	cout << endl
		<< "Welcome to the peg jump puzzle. The board starts out with a \n"
		<< "single blank position, represented by the '*'.  To make a \n"
		<< "move, select the letter of a peg.  A peg must be able to \n"
		<< "jump over an adjacent peg into a blank position for a move \n"
		<< "to be valid.  The jumped peg is then removed from the board. \n"
		<< "The game is over when there are no valid moves left. At any \n"
		<< "point enter '-' to exit, or '+' for instructions. \n"
		<< endl;
}

// Displays the board
void displayBoard(char board[])
{
	// Skip the first row and the last row in the array
	for (int i = 0 + PegsPerRow; i < NumberOfPegs - PegsPerRow; i++) {
		if (board[i] == '#') {
			cout << "  ";     // print a space
		}
		else {
			cout << board[i] << " ";    // print the stored character
		}
		if (((i + 1) % PegsPerRow) == 0) {
			// end of a row
			cout << endl;
		}
	}
}//end displayBoard()

// Counts the number of pieces on the board
void countPiecesOnBoard(char board[], int &piecesOnBoard)
{
	piecesOnBoard = 0;  // Resets the counter
	int i = 0;
	for (i = 0; i < NumberOfPegs; i++)
	{
		if (board[i] != '#' && board[i] != '*')
		{
			piecesOnBoard++;
		}
		else
		{
			continue;
		}
	}
}

// converts the inputed character destination to return the index of that value
int charIndexToNumberIndex(char board[], char userInput)
{
	int index;
	for (index = 0; index < NumberOfPegs; index++)
	{
		if (board[index] == userInput)
		{
			return index;
		}
	}
}

// Checks if destination index is valid
// Returns true if valid move
bool validateMove(char board[], char userInput)
{
	// Change the char value to the index of that char value
	int position = charIndexToNumberIndex(board, userInput);

	// Checks if value at 2 rows down is a '*'
	if ((board[position + 22] == '*') && (board[position + PegsPerRow] != '*'))
	{
		return true;
	}
	// Checks if value at two columns to the left is a '*'
	else if ((board[position - 2] == '*') && (board[position - 1] != '*'))
	{
		return true;
	}
	// Checks if value at two columns to the right is a '*'
	else if ((board[position + 2] == '*') && (board[position + 1] != '*'))
	{
		return true;
	}
	// Checks if value at two rows to the top is a '*'
	else if ((board[position - 22] == '*') && (board[position - PegsPerRow] != '*'))
	{
		return true;
	}
	// All moves are invalid
	else
	{
		return false;
	}
}

void checkMultipleMoves(char board[], char userInput, int &possibleMoves, int possibleDest[4])
{
	// Declares and resets number of possibleMoves to 0
	possibleMoves = 0;
	// Change the char value to the index of that char value
	int position = charIndexToNumberIndex(board, userInput);

	// Checks if value at 2 rows down of indexOfInput is a '*'
	// TOP CHECK of position of destination character
	if (board[position + 22] == '*')
	{
		possibleMoves++;
		possibleDest[0] = board[position + 22];
	}
	// Checks if value at two columns to the left of indexOfInput is a '*'
	// RIGHT CHECK of position of destination character
	if (board[position - 2] == '*')
	{
		possibleMoves++;
		possibleDest[1] = board[position - 2];
	}
	// Checks if value at two columns to the right of indexOfInput is a '*'
	// LEFT CHECK of position of destination character
	if (board[position + 2] == '*')
	{
		possibleMoves++;
		possibleDest[2] = board[position + 2];
	}
	// Checks if value at two rows to the top of indexOfInput is a '*'
	// DOWN CHECK of position of destination character
	if (board[position - 22] == '*')
	{
		possibleMoves++;
		possibleDest[3] = board[position - 22];
	}

}

void displayMultipleMoveBoard(char board[], char multiMoveBoard[], char userInput, int possibleMoves, int possibleDest[4])
{
	// Change the char value to the index of that char value
	int position = charIndexToNumberIndex(board, userInput);

	// Copy current board and transfer to multiMoveBoard
	int i;
	for (i = 0; i < NumberOfPegs; i++)
	{
		// multiMoveBoard[i] = board[i];
		if (multiMoveBoard[i] != '#')
		{
			multiMoveBoard[i] = '*';
		}
	}

	// Call to check how many moves
	checkMultipleMoves(board, userInput, possibleMoves, possibleDest);

	// DOWN value of position
	if (multiMoveBoard[position - 22] != '#')
	{
		multiMoveBoard[position - 22] = '1';
	}
	// RIGHT value of position
	if (multiMoveBoard[position - 2] != '#')
	{
		multiMoveBoard[position - 2] = '2';
	}
	// LEFT value of position
	if (multiMoveBoard[position + 2] != '#')
	{
		multiMoveBoard[position + 2] = '3';
	}
	// TOP value of position
	if (multiMoveBoard[position + 22] != '#')
	{
		multiMoveBoard[position + 22] = '4';
	}

	// Current position to '+'
	multiMoveBoard[position] = '+';
	displayBoard(multiMoveBoard);

}

// Makes the move: switches the values from '*' and userInput
// Also changes the value in between to a '*
void makeMove(char board[], char userInput)
{
	// Change the char value to the index of that char value
	int position = charIndexToNumberIndex(board, userInput);

	// Temp variable to store for swapping
	int temp = board[position];

	// If value at two rows under the userInput
	if (board[position + 22] == '*')
	{
		board[position + 22] = temp;
		board[position] = '*';
		board[position + PegsPerRow] = '*';
	}
	// If value at two columns to the left of userInput
	else if (board[position - 2] == '*')
	{
		board[position - 2] = temp;
		board[position] = '*';
		board[position - 1] = '*';
	}
	// If value at two columns to the right of userInput
	else if (board[position + 2] == '*')
	{
		board[position + 2] = temp;
		board[position] = '*';
		board[position + 1] = '*';
	}
	// If value at two rows to the top of userInput
	else if (board[position - 22] == '*')
	{
		board[position - 22] = temp;
		board[position] = '*';
		board[position - PegsPerRow] = '*';
	}
}

void makeMultiMove(char board[], char multiMoveBoard[], char userInput, int userChoiceForMove, int possibleDest[4])
{
	// Change the char value to the index of that char value
	int position = charIndexToNumberIndex(board, userInput);

	// Converts the integer of userChoiceForMove to a character
	char c = '0' + userChoiceForMove;
	// Get the index of the character
	int newIndex = charIndexToNumberIndex(multiMoveBoard, c);

	if (userChoiceForMove == 1)
	{
		// O: is the upper value
		board[newIndex] = board[position];
		board[position] = possibleDest[0];
		board[position - 11] = possibleDest[0];
	}
	else if (userChoiceForMove == 2)
	{
		// 1: is the left value
		board[newIndex] = board[position];
		board[position] = possibleDest[1];
		board[position - 1] = possibleDest[1];
	}
	else if (userChoiceForMove == 3)
	{
		// 2: is the right value
		board[newIndex] = board[position];
		board[position] = possibleDest[2];
		board[position + 1] = possibleDest[2];
	}
	else if (userChoiceForMove == 4)
	{
		// 3: is the down value
		board[newIndex] = board[position];
		board[position] = possibleDest[3];
		board[position + 11] = possibleDest[3];
	}

}

// Checks if game is not finished
// Returns true is finished
bool gameFinished(char board[])
{
	int i;
	for (i = 0; i < NumberOfPegs; i++)
	{
		if ((board[i] != '#') && (board[i] != '*'))
		{
			if ((board[i - 11] == '*') &&
				(board[i - 1] == '*') &&
				(board[i + 1] == '*') &&
				(board[i + 11] == '*'))
			{
				return true;
			}
			else
			{
				return false;
			}
		}// end if()
	}// end for()
}// end gameFinished

//-------------------------------------------------------------------------------------
int main()
{
	//Variable declarations
	char board[] =
	{
	  '#','#','#','#','#','#','#','#','#','#','#',
	  '#','#','#','#','#','#','#','#','#','#','#',
	  '#','#','#','#','A','B','C','#','#','#','#',
	  '#','#','#','#','D','E','F','#','#','#','#',
	  '#','#','G','H','I','J','K','L','M','#','#',
	  '#','#','N','O','P','*','Q','R','S','#','#',
	  '#','#','T','U','V','W','X','Y','Z','#','#',
	  '#','#','#','#','1','2','3','#','#','#','#',
	  '#','#','#','#','4','5','6','#','#','#','#',
	  '#','#','#','#','#','#','#','#','#','#','#',
	  '#','#','#','#','#','#','#','#','#','#','#'
	};

	// Secondary board to display the possible moves if more than 1
	char multiMoveBoard[] =
	{
	  '#','#','#','#','#','#','#','#','#','#','#',
	  '#','#','#','#','#','#','#','#','#','#','#',
	  '#','#','#','#','A','B','C','#','#','#','#',
	  '#','#','#','#','D','E','F','#','#','#','#',
	  '#','#','G','H','I','J','K','L','M','#','#',
	  '#','#','N','O','P','*','Q','R','S','#','#',
	  '#','#','T','U','V','W','X','Y','Z','#','#',
	  '#','#','#','#','1','2','3','#','#','#','#',
	  '#','#','#','#','4','5','6','#','#','#','#',
	  '#','#','#','#','#','#','#','#','#','#','#',
	  '#','#','#','#','#','#','#','#','#','#','#'
	};

	cout << "Welcome to the peg jump puzzle! \n"
		<< "Enter '-' to exit, or '+' for instructions. "
		<< endl;

	// Display the initial board
	displayBoard(board);

	int moveNumber = 1;     // counter for moveNumber
	char userInput;         // userInput for character destination
	int pieces = 0;         // total number of pieces
	int possibleMoves;      // total number of possible moves
	int userChoiceForMove;  // user choice for which move to make from multiple move options

	// Array holding the index locations of the 4 possible moves
	// 0: up
	// 1: left
	// 2: right
	// 3: down
	int possibleDest[4];

	// Main loop to play the game
	while (gameFinished(board) != true)
	{
		// Prompt for and get move
		cout << moveNumber << ". Enter the peg to move: ";
		cin >> userInput;

		// Make sure userInput is accepted as lowercase if not uppercase
		userInput = toupper(userInput);

		// Check for '-' to exit, and '+' for displaying instructions
		if (userInput == '+')
		{
			cout << endl;
			displayInstructions();
			continue;
		}
		if (userInput == '-')
		{
			cout << endl << "Exiting..." << endl << endl;
			break;
		}

		// Validate the move for destination
		if (validateMove(board, userInput) == false)
		{
			cout << "*** Invalid move, please retry. *** " << endl;
			continue;
		}

		// Checks possible moves;
		checkMultipleMoves(board, userInput, possibleMoves, possibleDest);
		// Based on how many possibleMoves, give error, makeMove, or makeMultiMove
		if (possibleMoves == 0)
		{
			break;
		}
		// Normal move
		if (possibleMoves == 1)
		{
			makeMove(board, userInput);
		}
		// Multiple move options
		if (possibleMoves > 1)
		{
			// Display the board showing the possible multiple moves
			displayMultipleMoveBoard(board, multiMoveBoard, userInput, possibleMoves, possibleDest);

			// Determine which move the user wants
			cout << "There is more than one possible move.  Which move do you want? ";
			cin >> userChoiceForMove;

			// Given userChoiceForMove, change the value at that position
			makeMultiMove(board, multiMoveBoard, userInput, userChoiceForMove, possibleDest);
		}

		// Increment move number and display the board
		moveNumber++;
		displayBoard(board);
	}

	// Display appropriate message depending on number of remaining pegs
	countPiecesOnBoard(board, pieces);
	switch (pieces)
	{
	case 1:
		cout << pieces << " piece remaining. Excellent!" << endl;
		break;
	case 2:
		cout << pieces << " pieces remaining. Good!" << endl;
		break;
	case 3:
		cout << pieces << " pieces remaining. OK." << endl;
		break;
	case 4:
		cout << pieces << " pieces remaining. Needs Improvement." << endl;
		break;
	default:
		cout << pieces << " pieces remaining. Ouch! " << endl;
	}

	return 0;
}//end main()