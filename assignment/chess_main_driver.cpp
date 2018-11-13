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

void ui_branch();
bool is_king_alive(ChessBoard chess_board, enum PieceColor color);
void enter_turn(ChessBoard chess_board, enum PieceColor player);
void get_from_input(File* file, Rank* rank);
bool piecemove_valid(ChessBoard chess_board, enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r);
void execute_move(ChessBoard chess_board, File s1_f, Rank s1_r, File s2_f, Rank s2_r);

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
	enum PieceColor player = White;
	while (is_king_alive(chess_board, White) && is_king_alive(chess_board, Black)) {
		enter_turn(chess_board, player);

		print_chess_board(chess_board);
		if (player == White) {
			player = Black;
		}
		else{
			player = White;
		}
	}
}

bool is_king_alive(ChessBoard chess_board, enum PieceColor color)
{
	for (int i = 0; i < 8; i++) {
		for (int u = 0; u < 8; u++) {
			if (chess_board[i][u].piece.type == King && chess_board[i][u].piece.color == color) {
				return true;
			}
		}
	}
	return false;
}

void enter_turn(ChessBoard chess_board, enum PieceColor player){
	File s1_f = 0;
	File s2_f = 0;
	Rank s1_r = 0;
	Rank s2_r = 0;
	bool input_valid;
	if (player == White) {
		printf("\nWhites turn\n");
	}
	else{
		printf("\nBlacks turn\n");
	}

	do {
		input_valid = true;
		printf("Wich piece do you want to move?");
		get_from_input(&s1_f, &s1_r);
		input_valid = (s1_f >= 0 && s1_f <= 7 && s1_r >= 0 && s1_r <= 7) && (chess_board[s1_r][s1_f].piece.color == player && chess_board[s1_r][s1_f].is_occupied);

		if (input_valid) {
			printf("Where do you want to move it?");
			get_from_input(&s2_f, &s2_r);
			input_valid = (s2_f >= 0 && s2_f <= 7 && s2_r >= 0 && s2_r <= 7) && (!chess_board[s2_r][s2_f].is_occupied || chess_board[s2_r][s2_f].piece.color != player) && (s1_f != s2_f && s1_r != s2_r);
		}

		if (input_valid) {

			if (chess_board[s2_r][s2_f].is_occupied) {
				input_valid = piecemove_valid(chess_board, player, CaptureMove, s1_f, s1_r, s2_f, s2_r);
			}
			else{
				input_valid = piecemove_valid(chess_board, player, NormalMove, s1_f, s1_r, s2_f, s2_r);
			}
		}

		if (!input_valid) {
			printf("Invalid!\n\n");
		}
	} while(!input_valid);
	execute_move(chess_board, s1_f, s1_r, s2_f, s2_r);
}

void get_from_input(File* file, Rank* rank)
{
	char input[2];
	scanf("%s", input);
	*file = input[0] - 'a';
	*rank = input[1] - '1';
}

bool piecemove_valid(ChessBoard chess_board, enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
	bool move_possible;

	if (chess_board[s1_r][s1_f].piece.type == Pawn) {
		move_possible = squares_share_pawns_move(color, move, s1_f, s1_r, s2_f, s2_r);
	}

	else if (chess_board[s1_r][s1_f].piece.type == Knight) {
		move_possible = squares_share_kings_move(s1_f, s1_r, s2_f, s2_r);
	}

	else if (chess_board[s1_r][s1_f].piece.type == Bishop) {
		move_possible = squares_share_diagonal(s1_f, s1_r, s2_f, s2_r);
	}

	else if (chess_board[s1_r][s1_f].piece.type == Rook) {
		move_possible = squares_share_rank(s1_f, s1_r, s2_f, s2_r) || squares_share_file(s1_f, s1_r, s2_f, s2_r);
	}

	else if (chess_board[s1_r][s1_f].piece.type == Queen) {
		move_possible = squares_share_queens_move(s1_f, s1_r, s2_f, s2_r);
	}

	else if (chess_board[s1_r][s1_f].piece.type == King) {
		move_possible = squares_share_kings_move(s1_f, s1_r, s2_f, s2_r);
	}

	return move_possible;
}

void execute_move(ChessBoard chess_board, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
	if (chess_board[s2_r][s2_f].is_occupied) {
		remove_piece(chess_board, s2_f, s2_r);
	}
	add_piece(chess_board, s2_f, s2_r, chess_board[s1_f][s1_r].piece);
	remove_piece(chess_board, s1_f, s1_r);
}
