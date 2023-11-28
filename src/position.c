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
    if(position->isWhite) {
        for (int from = A8; from <= H1 ; from++) {
            char pieceFrom = position->board[from];
            if (!isupper(pieceFrom))
                continue;
            int *pieceDirections = (int *) DIRECTIONS[PIECE_INDEXES[pieceFrom]];
            for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
                int d = *(pieceDirections + dirIndex);
                for (int to = from + d; to >= 0 && to < SIZE; to += d) {
                    char pieceTo = position->board[to];
                    if (pieceTo == ' ' || (isupper(pieceTo))) // Stay inside the board, and off friendly pieces
                        break;
                    if (pieceFrom == 'P') { // Pawn move, double move and pieceTo
                        if ((d == NORTH || d == NORTHNORTH) && pieceTo != '.')
                            break;
                        if (d == NORTHNORTH && (from < A1 + NORTH || position->board[from + NORTH] != '.')) // forbidden double move (pawn is not on initial rank or obstruction mid-road
                            break;
                        if ((d == NORTHWEST || d == NORTHEAST) && pieceTo == '.' && to != position->ep
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
                    if (from == A1 && position->board[to + EAST] == 'K' &&
                        position->wc[0]) // Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + EAST, to + WEST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                    if (from == H1 && position->board[to + WEST] == 'K' &&
                        position->wc[1]) // Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + WEST, to + EAST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                }
            }
        }
    } else {
        for (int from = A8; from <= H1 ; from++) {
            char pieceFrom = position->board[from];
            if (!islower(pieceFrom))
                continue;
            int *pieceDirections = (int *) DIRECTIONS[PIECE_INDEXES[pieceFrom]];
            for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
                int d = *(pieceDirections + dirIndex);
                for (int to = from + d; to >= 0 && to < SIZE; to += d) {
                    char pieceTo = position->board[to];
                    if (pieceTo == ' ' || (islower(pieceTo))) // Stay inside the board, and off friendly pieces
                        break;
                    if (pieceFrom == 'p') { // Pawn move, double move and pieceTo
                        if ((d == SOUTH || d == SOUTHSOUTH) && pieceTo != '.')
                            break;
                        if (d == SOUTHSOUTH && (from > H8 + SOUTH || position->board[from + SOUTH] != '.'))
                            break;
                        if ((d == SOUTHWEST || d == SOUTHEAST) && pieceTo == '.' && to != position->ep
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
                    if (from == A8 && position->board[to + EAST] == 'k' && position->bc[0])// Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + EAST, to + WEST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                    if (from == H8 && position->board[to + WEST] == 'k' && position->bc[1]) // Castling, by sliding the rook next to the king, from = king's square
                        createMove(to + WEST, to + EAST, NO_PROMOTION, pieceTo, &moves[moveIndex++]);
                }
            }
        }
    }
    return moveIndex;
}

int value(const Position *position, const Move *move) {
    char fromPiece = position->board[move->from];
    char toPiece = position->board[move->to];

    int friendlyPieceIndex = PIECE_INDEXES[fromPiece];
    int score = PST[friendlyPieceIndex][move->to] - PST[friendlyPieceIndex][move->from];

    if (toPiece != '.') { // Capture
        int enemyPieceIndex = PIECE_INDEXES[toPiece];
        score += PST[enemyPieceIndex][move->to];
    }

    if (abs(move->to - position->kp) < 2) { // position->kp = square where opponent's rook is after castling, 0 if he has not just castled
        score += PST[position->isWhite ? k : K][move->to]; // Castling check detection, add king's value to score to make it >= Mate_lower because castling was illegal (king, or the 2 other adjacent squares were attacked)
    }

    if (fromPiece == 'K' && abs(move->from - move->to) == 2) { // Castling
        score += PST[R][(move->from + move->to) / 2]; // to
        score -= PST[R][move->to < move->from ? A1 : H1]; // from
    } else if (fromPiece == 'k' && abs(move->from - move->to) == 2) { // Castling
        score += PST[r][(move->from + move->to) / 2];
        score -= PST[r][move->to < move->from ? A8 : H8];
    }

    if (fromPiece == 'P') {
        if (A8 <= move->to && move->to <= H8) { // promotion
            score += PST[move->prom][move->to] - PST[P][move->to];
        }
        if (move->to == position->ep) { // en passant
            score += PST[p][move->to + SOUTH];
        }
    } else if (fromPiece == 'p') {
        if (A1 <= move->to && move->to <= H1) { // promotion
            score += PST[move->prom][move->to] - PST[p][move->to];
        }
        if (move->to == position->ep) { // en passant
            score += PST[P][move->to + NORTH];
        }
    }
    return score;
}

bool isIrreversibleMove(const Move* move, Position* position){ // to know where to start checking for threefold repetition
    return move->pieceTo != '.' || position->ep != 0 || position->kp != 0
    || toupper(position->board[move->from]) == 'P';
}


void doMove(Position* position, const Move* move) {
    char prom = ALL_PIECES[move->prom];
    char fromPiece = position->board[move->from];
    char toPiece = position->board[move->to];
    int fromPieceIndex = PIECE_INDEXES[fromPiece];

    position->currentPly++;
    position->hash ^= blackToMoveHash;

    if(move->from == NULL_MOVE){
        position->isWhite = !position->isWhite;
        position->kp = 0;
        position->ep = 0;
        position->history[position->currentPly] = position->hash;
        position->plyIrreversible = position->currentPly;
        position->score = -position->score;
        return;
    }

    position->score = position->score + move->moveValue;

    position->hash ^= pieceHashForSquares[fromPieceIndex][move->from] ^ pieceHashForSquares[fromPieceIndex][move->to];
    if(toPiece != '.') {
        position->hash ^= pieceHashForSquares[PIECE_INDEXES[toPiece]][move->to];
    }

    position->board[move->to] = position->board[move->from]; // Actual move
    position->board[move->from] = '.';

    int oldPositionEp = position->ep;
    position->ep = 0;
    position->kp = 0;

    if (position->wc[0] && ((position->isWhite && move->from == A1) || (!position->isWhite && move->to == A1))) { // Castling rights, we move the rook or capture the opponent's
        position->wc[0] = false;
        position->hash ^= castlingRightsHash[0][0];
    }
    if (position->bc[0] && ((!position->isWhite && move->from == A8) || (position->isWhite && move->to == A8))) {
        position->bc[0] = false;
        position->hash ^= castlingRightsHash[1][0];
    }
    if (position->wc[1] && ((position->isWhite && move->from == H1) || (!position->isWhite && move->to == H1))) {
        position->wc[1] = false;
        position->hash ^= castlingRightsHash[0][1];
    }
    if (position->bc[1] && ((!position->isWhite && move->from == H8) || (position->isWhite && move->to == H8))) {
        position->bc[1] = false;
        position->hash ^= castlingRightsHash[1][1];
    }

    if (fromPiece == 'K') {  // Castling
        position->wc[0] = false;
        position->wc[1] = false;
        if (abs(move->to - move->from) == 2) {
            int rookFrom = (move->to < move->from) ? A1 : H1;
            position->kp = (move->from + move->to) / 2; // square 96 if short castle, 94 if long castle
            position->board[rookFrom] = '.';
            position->board[position->kp] = 'R';
            position->hash ^= pieceHashForSquares[R][rookFrom] ^ pieceHashForSquares[R][position->kp];
        }
    } else if (fromPiece == 'k') {  // Castling
        position->bc[0] = false;
        position->bc[1] = false;
        if (abs(move->to - move->from) == 2) {
            int rookFrom = (move->to < move->from) ? A8 : H8;
            position->kp = (move->from + move->to) / 2;
            position->board[rookFrom] = '.';
            position->board[position->kp] = 'r';
            position->hash ^= pieceHashForSquares[r][rookFrom] ^ pieceHashForSquares[r][position->kp];
        }
    }

    if (fromPiece == 'P') { // Pawn promotion, double move, and en passant capture
        if (A8 <= move->to && move->to <= H8) {
            position->board[move->to] = prom;
            position->hash ^= pieceHashForSquares[P][move->to] ^ pieceHashForSquares[PIECE_INDEXES[prom]][move->to];
        } else if (move->to - move->from == 2 * NORTH) {
            position->ep = move->from + NORTH;
            position->hash ^= enPassantFileHash[move->to % 10];
        } else if (move->to == oldPositionEp) {
            position->board[move->to + SOUTH] = '.';
            position->hash ^= pieceHashForSquares[p][move->to + SOUTH];
        }
    }
    if (fromPiece == 'p') { // Pawn promotion, double move, and en passant capture
        if (A1 <= move->to && move->to <= H1) {
            position->board[move->to] = prom;
            position->hash ^= pieceHashForSquares[p][move->to] ^ pieceHashForSquares[PIECE_INDEXES[prom]][move->to];
        } else if (move->to - move->from == 2 * SOUTH) {
            position->ep = move->from + SOUTH;
            position->hash ^= enPassantFileHash[move->to % 10];
        } else if (move->to == oldPositionEp) {
            position->board[move->to + NORTH] = '.';
            position->hash ^= pieceHashForSquares[P][move->to + NORTH];
        }
    }
    position->isWhite = !position->isWhite;
    position->history[position->currentPly] = position->hash;
    if(isIrreversibleMove(move, position)){
        position->plyIrreversible = position->currentPly;
    }
    position->score = -position->score; // rotate
}

void undoMove(Position* position, Move* move, Position positionOld){
    char fromPiece = position->board[move->to];

    position->board[move->from] = fromPiece;
    position->board[move->to] = move->pieceTo; // Undo move

    if (fromPiece == 'K' && abs(move->to - move->from) == 2) {  // Castling
        position->board[(move->to < move->from) ? A1 : H1] = 'R';
        position->board[position->kp] = '.';
    } else if (fromPiece == 'k' && abs(move->to - move->from) == 2) {  // Castling
        position->board[(move->to < move->from) ? A8 : H8] = 'r';
        position->board[position->kp] = '.';
    }

    if (move->prom != NO_PROMOTION) {
        position->board[move->from] = positionOld.isWhite ? 'P' : 'p';
    }
    if (move->to == positionOld.ep) {
        if (fromPiece == 'P') { // en passant capture
            position->board[move->to + SOUTH] = 'p';
        } else if (fromPiece == 'p') { // en passant capture
            position->board[move->to + NORTH] = 'P';
        }
    }
    *position = positionOld;
}