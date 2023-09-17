#include "position.h"
#include "constants.h"
#include "chessBoard.h"
#include "move.h"
#include "pieceSquareTables.h"
#include "zobrist.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void initPosition(Position* position, char* boardToUse){
    position->board = boardToUse;
    position->score = 0;
    position->wc[0] = true;
    position->wc[1] = true;
    position->bc[0] = true;
    position->bc[1] = true;
    position->ep = 0;
    position->kp = 0;
    position->isWhite = 1;
    setInitialZobristHash(position);
}

Position* duplicatePosition(Position* source, Position* target, char* targetBoard){ // useless
    target->score = source->score;
    target->wc[0] = source->wc[0];
    target->wc[1] = source->wc[1];
    target->bc[0] = source->bc[0];
    target->bc[1] = source->bc[1];
    target->ep = source->ep;
    target->kp = source->kp;
    target->board = targetBoard;
    copyBoard(target->board, source->board);
    return target;
}

int genMoves(Position* position, Move moves[MAX_BRANCHING_FACTOR]) { // For each friendly piece, iterate through each possible 'ray' of moves as defined in the 'directions' map. The rays are broken e.g. by captures or immediately in case of pieces such as knights.
    int moveIndex = 0;
    int isWhite = position->isWhite;
    for (int from = 0; from < SIZE ; from++) {
        char pieceFrom = position->board[from];
        if ((isWhite && !isupper(pieceFrom)) || (!isWhite && !islower(pieceFrom)))
            continue;
        int* pieceDirections = (int*)DIRECTIONS[PIECE_INDEXES[pieceFrom]];
        for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
            int d = *(pieceDirections + dirIndex);
            for (int to = from + d; to >= 0 && to < SIZE; to += d) {
                char pieceTo = position->board[to];
                if (isspace(pieceTo) || ((isWhite && isupper(pieceTo)) || (!isWhite && islower(pieceTo)))) // Stay inside the board, and off friendly pieces
                    break;
                if (pieceFrom == 'P') { // Pawn move, double move and capture
                    if ((d == NORTH || d == NORTH + NORTH) && pieceTo != '.')
                        break;
                    if (d == NORTH + NORTH && (from < A1 + NORTH || position->board[from + NORTH] != '.')) // forbidden double move (pawn is not on initial rank or obstruction mid-road
                        break;
                    if ((d == NORTH + WEST || d == NORTH + EAST) && pieceTo == '.' && to != position->ep
                        && to != position->kp - 1 && to != position->kp && to != position->kp + 1) // for castling check detection
                        break;
                    if (to >= A8 && to <= H8) { // If we move to the last row, we can be anything
                        for (int promotion = Q; promotion > P ; promotion--)
                            createMove(from, to, promotion, &moves[moveIndex++]);
                        break;
                    }
                }
                if (pieceFrom == 'p') { // Pawn move, double move and capture
                    if ((d == SOUTH || d == SOUTH + SOUTH) && pieceTo != '.')
                        break;
                    if (d == SOUTH + SOUTH && (from > H8 + SOUTH || position->board[from + SOUTH] != '.'))
                        break;
                    if ((d == SOUTH + WEST || d == SOUTH + EAST) && pieceTo == '.' && to != position->ep
                        && to != position->kp - 1 && to != position->kp && to != position->kp + 1) // for castling check detection
                        break;
                    if (to >= A1 && to <= H1) { // If we move to the last row, we can be anything
                        for (int promotion = q; promotion > p ; promotion--)
                            createMove(from, to, promotion, &moves[moveIndex++]);
                        break;
                    }
                }
                createMove(from, to, NO_PROMOTION, &moves[moveIndex++]); // Move it
                if (isWhite && strchr("PNK", pieceFrom) != NULL || islower(pieceTo)) // Stop crawlers from sliding, and sliding after captures
                    break;
                if (!isWhite && strchr("pnk", pieceFrom) != NULL || isupper(pieceTo)) // Stop crawlers from sliding, and sliding after captures
                    break;
                if (
                        (isWhite && from == A1 && position->board[to + EAST] == 'K' && position->wc[0]) ||
                        (!isWhite && from == A8 && position->board[to + EAST] == 'k' && position->bc[0])
                        ) // Castling, by sliding the rook next to the king, from = king's square
                    createMove(to + EAST, to + WEST, NO_PROMOTION, &moves[moveIndex++]);
                if (
                        (isWhite && from == H1 && position->board[to + WEST] == 'K' && position->wc[1]) ||
                        (!isWhite && from == H8 && position->board[to + WEST] == 'k' && position->bc[1])
                        ) // Castling, by sliding the rook next to the king, from = king's square
                    createMove(to + WEST, to + EAST, NO_PROMOTION, &moves[moveIndex++]);
            }
        }
    }
    return moveIndex;
}

int value(const Position *position, const Move *move) {
    int from = move->from;
    int to = move->to;
    int prom = move->prom;
    char fromPiece = position->board[from];
    char toPiece = position->board[to];
    int isWhite = position->isWhite;

    int friendlyPieceIndex = PIECE_INDEXES[fromPiece];
    int score = PST[friendlyPieceIndex][to] - PST[friendlyPieceIndex][from];

    if (isalpha(toPiece)) { // Capture
        int enemyPieceIndex = PIECE_INDEXES[toPiece];
        score -= PST[enemyPieceIndex][to];
    }

    if (abs(to - position->kp) < 2) { // position->kp = square where opponent's rook is after castling, 0 if he has not just castled
        score -= PST[isWhite ? k : K][to]; // Castling check detection, add king's value to score to make it >= Mate_lower because castling was illegal (king, or the 2 other adjacent squares were attacked)
    }

    if (fromPiece == 'K' && abs(from - to) == 2) { // Castling
        score += PST[R][(from + to) / 2];
        score -= PST[R][to < from ? A1 : H1];
    } else if (fromPiece == 'k' && abs(from - to) == 2) { // Castling
        score += PST[r][(from + to) / 2];
        score -= PST[r][to < from ? A8 : H8];
    }

    if (fromPiece == 'P') {
        if (A8 <= to && to <= H8) { // promotion
            score += PST[prom][to] - PST[P][to];
        }
        if (to == position->ep) { // en passant
            score -= PST[p][to + SOUTH];
        }
    } else if (fromPiece == 'p') {
        if (A1 <= to && to <= H1) { // promotion
            score += PST[prom][to] - PST[p][to];
        }
        if (to == position->ep) { // en passant
            score -= PST[P][to + NORTH];
        }
    }

    return score;
}

void doMove(Position* position, Move* move) {
    int from = move->from, to = move->to;
    char prom = PIECES[move->prom];
    char fromPiece = position->board[from];
    int isWhite = position->isWhite;

    position->ep = 0;
    position->kp = 0;
    if(to == NULL_MOVE){
        position->isWhite = !isWhite;
        return;
    }

    position->score = position->score + value(position, move);

    position->board[to] = position->board[from]; // Actual move
    position->board[from] = '.';

    if (isWhite && from == A1) { // Castling rights, we move the rook or capture the opponent's
        position->wc[0] = false;
    }
    if (!isWhite && from == A8) {
        position->bc[0] = false;
    }
    if (isWhite && from == H1) {
        position->wc[1] = false;
    }
    if (!isWhite && from == H8) {
        position->bc[1] = false;
    }
    if (isWhite && to == A8) {
        position->bc[0] = false;
    }
    if (!isWhite && to == A1) {
        position->wc[0] = false;
    }
    if (isWhite && to == H8) {
        position->bc[1] = false;
    }
    if (!isWhite && to == H1) {
        position->wc[1] = false;
    }

    if (fromPiece == 'K') {  // Castling
        position->wc[0] = false;
        position->wc[1] = false;
        if (abs(to - from) == 2) {
            position->kp = (from + to) / 2; // 96 if short castle, 94 if long castle
            position->board[(to < from) ? A1 : H1] = '.';
            position->board[position->kp] = 'R';
        }
    } else if (fromPiece == 'k') {  // Castling
        position->bc[0] = false;
        position->bc[1] = false;
        if (abs(to - from) == 2) {
            position->kp = (from + to) / 2;
            position->board[(to < from) ? A8 : H8] = '.';
            position->board[position->kp] = 'r';
        }
    }

    if (fromPiece == 'P') { // Pawn promotion, double move, and en passant capture
        if (A8 <= to && to <= H8) {
            position->board[to] = prom;
        }
        if (to - from == 2 * NORTH) {
            position->ep = from + NORTH;
        }
        if (to == position->ep) {
            position->board[to + SOUTH] = '.';
        }
    }
    if (fromPiece == 'p') { // Pawn promotion, double move, and en passant capture
        if (A1 <= to && to <= H1) {
            position->board[to] = prom;
        }
        if (to - from == 2 * SOUTH) {
            position->ep = from + SOUTH;
        }
        if (to == position->ep) {
            position->board[to + NORTH] = '.';
        }
    }
    position->isWhite = !isWhite;
}