/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHIF
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.h
 * Author:			L. Hain
 * Due Date:		October 15, 2014
 * ----------------------------------------------------------
 * Description:
 * Basic chess functions.
 * ----------------------------------------------------------
 */

#include <stdbool.h>
#ifndef ___CHESS_H__
#define ___CHESS_H__


typedef int Rank;
typedef int File;


enum PieceType {
  NoPiece, Pawn, Bishop, Knight, Rook, Queen, King
};

enum PieceColor{White, Black};

enum MoveType { NormalMove, CaptureMove };

struct ChessPiece{
  enum PieceColor color;
  enum PieceType type;
};

struct ChessSquare{
  bool is_occupied;
  Rank rank;
  File file;
  struct ChessPiece piece;
};

typedef struct ChessSquare ChessBoard[8][8];

bool is_square_ok(File file, Rank rank);
bool 	is_piece (struct ChessPiece pc, enum PieceColor color, enum PieceType type);
void 	init_chess_board (ChessBoard chess_board);
struct ChessSquare * 	get_square (ChessBoard chess_board, File file, Rank rank);
bool 	is_square_occupied (ChessBoard chess_board, File file, Rank rank);
bool 	add_piece (ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece);
struct ChessPiece 	get_piece (ChessBoard chess_board, File file, Rank rank);
void 	setup_chess_board (ChessBoard chess_board);
bool 	remove_piece (ChessBoard chess_board, File file, Rank rank);
bool 	squares_share_file (File s1_f, Rank s1_r, File s2_f, Rank s2_r);
bool 	squares_share_rank (File s1_f, Rank s1_r, File s2_f, Rank s2_r);
bool 	squares_share_diagonal (File s1_f, Rank s1_r, File s2_f, Rank s2_r);
bool 	squares_share_knights_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r);
bool 	squares_share_pawns_move (enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r);
bool 	squares_share_queens_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r);
bool 	squares_share_kings_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r);

#endif
