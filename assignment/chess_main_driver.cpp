/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Chess
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Some basic movements in chess.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

#include "chess.h"
#include "chess_printer.h"

#include "test_chess.h"

/** ui_branch handles the user interface mode of Chess.
*** @see main, test_branch.
*/
enum PlayerColor{white, black};

void ui_branch();
bool is_king_alive(ChessBoard chess_board, enum PieceColor color);
void enter_turn(ChessBoard chess_board);
void get_from_input(File* file, Rank* rank);

/** Main function evaluates the number of command line arguments.
*** If the user passed one main switches into test mode, i.e., that
*** the function test_branch() is called and the command line argument
*** is handed over to this function. If no command line argument is given
*** main switches into user interface mode and delegates the handling
*** of this to the function ui_branch().
*** @see test_branch, ui_branch.
*/
int main(int argc, char *argv[])
{
	ui_branch();
	return 0;
}

void ui_branch()
{
	ChessBoard chess_board;
	setup_chess_board(chess_board);
	print_chess_board(chess_board);
	int player = 1;
	while (is_king_alive(chess_board, white) && is_king_alive(chess_board, black)) {
		File s1_f;
		File s2_f;
		Rank s1_r;
		Rank s2_r;


	}
}

bool is_king_alive(ChessBoard chess_board, enum PieceColor color)
{
	for (int i = 0; i < 8; i++) {
		for (int u = 0; u < 8; u++) {
			if (chess_board[i][u].piece.type == King && chess_board.[i][u].piece.color == color) {
				return true
			}
		}
	}
	return false;
}

void enter_turn(struct ChessBoard chess_board){
	printf("Wich square do you want to move: ");
}

void get_from_input(File* file, Rank* rank)
{
	bool isValid = false;
	do {
		char[] input;
		scanf("%s", input);

		if (strlen(input) == 2 && input[0] >= 'a' && input[0] <= 'h' && input[1] >= '1' input[1] <= '1') {
			*File = input[0];
			*Rank = input[1];
			isValid = true;
			printf("\n");
		}
		else{
			printf("\nInvalid! Try again!\n");
		}
	} while(!isValid);
}
