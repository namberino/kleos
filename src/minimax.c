#include "minimax.h"


// evaluation function
int evaluate_board(wint_t* board)
{
    int score = 0;

    for (int i = 0; i < BOARD_SQUARE_NUM; i++)
    {
        switch (board[i])
        {
            case WHITE_PAWN:   score += PAWN_VAL; break;
            case WHITE_KNIGHT: score += KNIGHT_VAL; break;
            case WHITE_BISHOP: score += BISHOP_VAL; break;
            case WHITE_ROOK:   score += ROOK_VAL; break;
            case WHITE_QUEEN:  score += QUEEN_VAL; break;
            case WHITE_KING:   score += KING_VAL; break;

            case BLACK_PAWN:   score -= PAWN_VAL; break;
            case BLACK_KNIGHT: score -= KNIGHT_VAL; break;
            case BLACK_BISHOP: score -= BISHOP_VAL; break;
            case BLACK_ROOK:   score -= ROOK_VAL; break;
            case BLACK_QUEEN:  score -= QUEEN_VAL; break;
            case BLACK_KING:   score -= KING_VAL; break;

            default: break; // empty square or invalid piece
        }
    }

    return score;
}


// generate a list of possible moves, each item includes the new board possition, source index, and destination index
Move* generate_possible_moves(wint_t* board, bool white_turn, int* num_moves)
{
    int size = 1;
    Move* possible_moves = malloc(sizeof(Move) * size);

    for (int src_index = 0; src_index < 64; src_index++)
    {
        // check if piece is player's piece
        if (!is_opponent_piece(src_index, white_turn, board) && board[src_index] != EMPTY_SQUARE)
        {
            // loop through each possible moves
            for (int dst_index = 0; dst_index < 64; dst_index++)
            {
                Move possible_move;
                wint_t* board_copy = malloc(sizeof(wint_t) * 64);
                copy_array(board, board_copy, 64);

                // validate possible move to dest index
                if (move_piece(board_copy, src_index, dst_index, white_turn) != -1)
                {
                    // valid possible move
                    possible_move.board_position = board_copy;
                    possible_move.src_index = src_index;
                    possible_move.dst_index = dst_index;

                    // append possible move to possible moves array
                    possible_moves[size - 1] = possible_move;
                    possible_moves = realloc(possible_moves, sizeof(Move) * ++size);
                }
            }
        }
    }

    *num_moves = size;
    return possible_moves;
}


// minimax algorithm
int minimax(wint_t* board, int depth, bool max_player, int alpha, int beta, Move* best_position)
{
    if (depth == 0)
        return evaluate_board(board);

    if (max_player)
    {
        int max_eval = INT_MIN;
        int num_possible_moves;
        Move* possible_moves = generate_possible_moves(board, max_player, &num_possible_moves);

        for (int move = 0; move < num_possible_moves; move++)
        {
            int child_eval = minimax(possible_moves[move].board_position, depth - 1, false, alpha, beta, best_position);

            if (child_eval > max_eval)
            {
                max_eval = child_eval;
                *best_position = possible_moves[move];
            }

            alpha = alpha > max_eval ? alpha : max_eval;
            if (beta <= alpha)
                break;
        }

        return max_eval;
    }
    else
    {
        int min_eval = INT_MAX;
        int num_possible_moves;
        Move* possible_moves = generate_possible_moves(board, max_player, &num_possible_moves);

        for (int move = 0; move < num_possible_moves; move++)
        {
            int child_eval = minimax(possible_moves[move].board_position, depth - 1, true, alpha, beta, best_position);

            if (child_eval < min_eval)
            {
                min_eval = child_eval;
                *best_position = possible_moves[move];
            }

            beta = beta < min_eval ? beta : min_eval;
            if (beta <= alpha)
                break;
        }

        return min_eval;
    }
}


// get the best move using minimax
int get_best_move(wint_t* board, bool white_turn)
{
    
}
