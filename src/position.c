#include "position.h"
#include "constants.h"
#include "chessBoard.h"
#include "move.h"
#include "pieceSquareTables.h"
#include "zobrist.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void initPosition(Position *position, char *boardCopy, char *boardToUse, uint64_t* history) {
    copyBoard(boardCopy, boardToUse);
    position->board = boardCopy;
    position->score = 0;
    position->wc[0] = true;
    position->wc[1] = true;
    position->bc[0] = true;
    position->bc[1] = true;
    position->ep = 0;
    position->kp = 0;
    position->isWhite = 1;
    setInitialZobristHash(position);
    position->history = history;
    position->history[0] = position->hash;
    position->plyIrreversible = 0;
    position->currentPly = 0;
}

Position* duplicatePosition(Position* source, Position* target){
    target->board = source->board; // shallow copy!
    target->score = source->score;
    target->wc[0] = source->wc[0];
    target->wc[1] = source->wc[1];
    target->bc[0] = source->bc[0];
    target->bc[1] = source->bc[1];
    target->ep = source->ep;
    target->kp = source->kp;
    target->isWhite = source->isWhite;
    target->hash = source->hash;
    target->history = source->history; // shallow copy!
    target->plyIrreversible = source->plyIrreversible;
    target->currentPly = source->currentPly;
    return target;
}

int genActualMoves(Position *position, Move moves[MAX_BRANCHING_FACTOR]) { // For each friendly piece, iterate through each possible 'ray' of moves as defined in the 'directions' map. The rays are broken e.g. by captures or immediately in case of pieces such as knights.
    int moveIndex = 0;
    char* board = position->board;
    for (int from = A8; from <= H1 ; from++) {
        if(position->isWhite) {
            char pieceFrom = board[from];
            if (!isupper(pieceFrom))
                continue;
            int *pieceDirections = (int *) DIRECTIONS[PIECE_INDEXES[pieceFrom]];
            for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
                int d = *(pieceDirections + dirIndex);
                for (int to = from + d; to >= 0 && to < SIZE; to += d) {
                    char pieceTo = board[to];
                    if (isspace(pieceTo) || (isupper(pieceTo))) // Stay inside the board, and off friendly pieces
                        break;
                    if (pieceFrom == 'P') { // Pawn move, double move and pieceTo
                        if ((d == NORTH || d == NORTH + NORTH) && pieceTo != '.')
                            break;
                        if (d == NORTH + NORTH && (from < A1 + NORTH || board[from + NORTH] !='.')) // forbidden double move (pawn is not on initial rank or obstruction mid-road
                            break;
                        if ((d == NORTH + WEST || d == NORTH + EAST) && pieceTo == '.' && to != position->ep
                            && to != position->kp - 1 && to != position->kp &&
                            to != position->kp + 1) // for castling check detection
                            break;
                        if (to >= A8 && to <= H8) { // If we move to the last row, we can be anything
                            for (int promotion = Q; promotion > P; promotion--) {
                                createMove(from, to, promotion, pieceTo, &moves[moveIndex++]);
                                break;  // only consider queen promotions for efficiency reasons
                            }
                            break;
                        }
                    }
                    createMove(from, to, NO_PROMOTION, pieceTo, &moves[moveIndex++]); // Move it
                    if (strchr("PNK", pieceFrom) != NULL || islower(pieceTo)) // Stop crawlers from sliding, and sliding after captures
                        break;
                    if (from == A1 && board[to + EAST] == 'K' &&
                        position->wc[0]) // Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + EAST, to + WEST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                    if (from == H1 && board[to + WEST] == 'K' &&
                        position->wc[1]) // Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + WEST, to + EAST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                }
            }
        } else {
            char pieceFrom = board[from];
            if (!islower(pieceFrom))
                continue;
            int *pieceDirections = (int *) DIRECTIONS[PIECE_INDEXES[pieceFrom]];
            for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
                int d = *(pieceDirections + dirIndex);
                for (int to = from + d; to >= 0 && to < SIZE; to += d) {
                    char pieceTo = board[to];
                    if (isspace(pieceTo) || (islower(pieceTo))) // Stay inside the board, and off friendly pieces
                        break;
                    if (pieceFrom == 'p') { // Pawn move, double move and pieceTo
                        if ((d == SOUTH || d == SOUTH + SOUTH) && pieceTo != '.')
                            break;
                        if (d == SOUTH + SOUTH && (from > H8 + SOUTH || board[from + SOUTH] != '.'))
                            break;
                        if ((d == SOUTH + WEST || d == SOUTH + EAST) && pieceTo == '.' && to != position->ep
                            && to != position->kp - 1 && to != position->kp &&
                            to != position->kp + 1) // for castling check detection
                            break;
                        if (to >= A1 && to <= H1) { // If we move to the last row, we can be anything
                            for (int promotion = q; promotion > p; promotion--) {
                                createMove(from, to, promotion, pieceTo, &moves[moveIndex++]);
                                break; // only consider queen promotions for efficiency reasons
                            }
                            break;
                        }
                    }
                    createMove(from, to, NO_PROMOTION, pieceTo, &moves[moveIndex++]); // Move it
                    if (strchr("pnk", pieceFrom) != NULL || isupper(pieceTo)) // Stop crawlers from sliding, and sliding after captures
                        break;
                    if (from == A8 && board[to + EAST] == 'k' && position->bc[0])// Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + EAST, to + WEST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                    if (from == H8 && board[to + WEST] == 'k' && position->bc[1]) // Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + WEST, to + EAST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                }
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

    if (toPiece != '.') { // Capture
        int enemyPieceIndex = PIECE_INDEXES[toPiece];
        score += PST[enemyPieceIndex][to];
    }

    if (abs(to - position->kp) < 2) { // position->kp = square where opponent's rook is after castling, 0 if he has not just castled
        score += PST[isWhite ? k : K][to]; // Castling check detection, add king's value to score to make it >= Mate_lower because castling was illegal (king, or the 2 other adjacent squares were attacked)
    }

    if (fromPiece == 'K' && abs(from - to) == 2) { // Castling
        score += PST[R][(from + to) / 2]; // to
        score -= PST[R][to < from ? A1 : H1]; // from
    } else if (fromPiece == 'k' && abs(from - to) == 2) { // Castling
        score += PST[r][(from + to) / 2];
        score -= PST[r][to < from ? A8 : H8];
    }

    if (fromPiece == 'P') {
        if (A8 <= to && to <= H8) { // promotion
            score += PST[prom][to] - PST[P][to];
        }
        if (to == position->ep) { // en passant
            score += PST[p][to + SOUTH];
        }
    } else if (fromPiece == 'p') {
        if (A1 <= to && to <= H1) { // promotion
            score += PST[prom][to] - PST[p][to];
        }
        if (to == position->ep) { // en passant
            score += PST[P][to + NORTH];
        }
    }
    return score;
}

bool isIrreversibleMove(const Move* move, Position* position){ // to know where to start checking for threefold repetition
    return move->pieceTo != '.' || position->ep != 0 || position->kp != 0
    || toupper(position->board[move->from]) == 'P';
}


void doMove(Position* position, const Move* move) {
    int from = move->from, to = move->to;
    char prom = ALL_PIECES[move->prom];
    char fromPiece = position->board[from];
    char toPiece = position->board[to];
    int fromPieceIndex = PIECE_INDEXES[fromPiece];
    int isWhite = position->isWhite;

    position->currentPly++;
    position->hash ^= blackToMoveHash;

    if(move->from == NULL_MOVE){
        position->isWhite = !isWhite;
        position->kp = 0;
        position->ep = 0;
        position->history[position->currentPly] = position->hash;
        position->plyIrreversible = position->currentPly;
        position->score = -position->score;
        return;
    }

    position->score = position->score + move->moveValue;

    position->hash ^= pieceHashForSquares[fromPieceIndex][from] ^ pieceHashForSquares[fromPieceIndex][to];
    if(toPiece != '.') {
        position->hash ^= pieceHashForSquares[PIECE_INDEXES[toPiece]][to];
    }

    position->board[to] = position->board[from]; // Actual move
    position->board[from] = '.';

    int oldPositionEp = position->ep;
    position->ep = 0;
    position->kp = 0;

    if (position->wc[0] && ((isWhite && from == A1) || (!isWhite && to == A1))) { // Castling rights, we move the rook or capture the opponent's
        position->wc[0] = false;
        position->hash ^= castlingRightsHash[0][0];
    }
    if (position->bc[0] && ((!isWhite && from == A8) || (isWhite && to == A8))) {
        position->bc[0] = false;
        position->hash ^= castlingRightsHash[1][0];
    }
    if (position->wc[1] && ((isWhite && from == H1) || (!isWhite && to == H1))) {
        position->wc[1] = false;
        position->hash ^= castlingRightsHash[0][1];
    }
    if (position->bc[1] && ((!isWhite && from == H8) || (isWhite && to == H8))) {
        position->bc[1] = false;
        position->hash ^= castlingRightsHash[1][1];
    }

    if (fromPiece == 'K') {  // Castling
        position->wc[0] = false;
        position->wc[1] = false;
        if (abs(to - from) == 2) {
            int rookFrom = (to < from) ? A1 : H1;
            position->kp = (from + to) / 2; // square 96 if short castle, 94 if long castle
            position->board[rookFrom] = '.';
            position->board[position->kp] = 'R';
            position->hash ^= pieceHashForSquares[R][rookFrom] ^ pieceHashForSquares[R][position->kp];
        }
    } else if (fromPiece == 'k') {  // Castling
        position->bc[0] = false;
        position->bc[1] = false;
        if (abs(to - from) == 2) {
            int rookFrom = (to < from) ? A8 : H8;
            position->kp = (from + to) / 2;
            position->board[rookFrom] = '.';
            position->board[position->kp] = 'r';
            position->hash ^= pieceHashForSquares[r][rookFrom] ^ pieceHashForSquares[r][position->kp];
        }
    }

    if (fromPiece == 'P') { // Pawn promotion, double move, and en passant capture
        if (A8 <= to && to <= H8) {
            position->board[to] = prom;
            position->hash ^= pieceHashForSquares[P][to] ^ pieceHashForSquares[PIECE_INDEXES[prom]][to];
        } else if (to - from == 2 * NORTH) {
            position->ep = from + NORTH;
            position->hash ^= enPassantFileHash[to % 10];
        } else if (to == oldPositionEp) {
            position->board[to + SOUTH] = '.';
            position->hash ^= pieceHashForSquares[p][to + SOUTH];
        }
    }
    if (fromPiece == 'p') { // Pawn promotion, double move, and en passant capture
        if (A1 <= to && to <= H1) {
            position->board[to] = prom;
            position->hash ^= pieceHashForSquares[p][to] ^ pieceHashForSquares[PIECE_INDEXES[prom]][to];
        } else if (to - from == 2 * SOUTH) {
            position->ep = from + SOUTH;
            position->hash ^= enPassantFileHash[to % 10];
        } else if (to == oldPositionEp) {
            position->board[to + NORTH] = '.';
            position->hash ^= pieceHashForSquares[P][to + NORTH];
        }
    }
    position->isWhite = !isWhite;
    position->history[position->currentPly] = position->hash;
    if(isIrreversibleMove(move, position)){
        position->plyIrreversible = position->currentPly;
    }
    position->score = -position->score; // rotate
}

void undoMove(Position* position, Move* move, Position positionOld){
    int from = move->from, to = move->to;
    char fromPiece = position->board[to];

    position->board[from] = fromPiece;
    position->board[to] = move->pieceTo; // Undo move

    if (fromPiece == 'K' && abs(to - from) == 2) {  // Castling
        position->board[(to < from) ? A1 : H1] = 'R';
        position->board[position->kp] = '.';
    } else if (fromPiece == 'k' && abs(to - from) == 2) {  // Castling
        position->board[(to < from) ? A8 : H8] = 'r';
        position->board[position->kp] = '.';
    }

    if (move->prom != NO_PROMOTION) {
        position->board[from] = positionOld.isWhite ? 'P' : 'p';
    }
    if (to == positionOld.ep) {
        if (fromPiece == 'P') { // en passant capture
            position->board[to + SOUTH] = 'p';
        } else if (fromPiece == 'p') { // en passant capture
            position->board[to + NORTH] = 'P';
        }
    }
    *position = positionOld;
}