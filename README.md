# sunfish_C

## Introduction
Sunfish_C is the result of translating the Sunfish chess engine to the C language.
The original project has been written in Python https://github.com/thomasahle/sunfish.

This C version in its current state contains just around 954 lines of source code, excluding 
header files, imports and randomUnsigned64bitIntegers.c


## Branches
The <b>master</b> branch contains the translation of the original Sunfish engine written in python. This can still be improved in terms of lines/quality of code, but the algorithm must stay the same as on the original Sunfish!

The <b>sunfish-improved</b> branch is where all improvements are merged that aren't part of the original Sunfish engine. This can be simple improvements such as endgame PST's, better transposition table usage, better move ordering, killer (non capture) heuristic, etc. 

Any <b>pull requests</b> on those 2 branches is welcome !

## Implementation
The implementation tries to mimic the original version of Sunfish as much as possible.
The only major difference with the original version is the <b>make/unmake</b> approach vs. Sunfish's <b>copy/make</b> approach.
To use transposition tables as Sunfish does, one needs to get the hash of the position. Sunfish can directly use the 'position'
object to build the hash, but this cannot be done in C. This why I have decided to use the very common Zobrist hashing method to build the hash out of the current position.
To allow incremental updates, the make/unmake approach had to be used.

## Benchmark
One sure wants to know how the C version of Sunfish compares to itself right?
Let us compare on different positions the time taken for both engines to finish the search at a depth of 8 plies.

The following basic benchmark has been conducted on the master branch at 13/11/2023 with below hardware:

    CPU 11th Gen Intel(R) Core(TM) i7-1185G7 @ 3.00GHz
	RAM 32,0 GB 4267 MHz

### Start position
Let us compare the performance of both engines.

Sunfish:

    time: 17407 ms
    nodes: 361830
    nps: 20787
    bestmove: g1f3

Sunfish-C:

    time: 1121 ms
    nodes: 396745
    nps: 353920
    bestmove: g1f3

### Middle Game position
Using below UCI position with <b>black</b> to move:

position startpos moves e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1f3 e7e6 b1c3 d5a5 f1d3 g8f6 e1g1 f8e7 c1d2 a7a6 a2a3 e8g8 c3e4 a5b6 c2c3 b6b2 e4f6 e7f6 c3c4 c6d4 f3d4

    1 ♜    ♝      ♜ ♚ 
    2    ♟ ♟      ♟ ♟ ♟
    3 ♟         ♟ ♝
    4
    5       ♙ ♘ 
    6          ♗  
    7 ♙ ♛    ♗   ♙  ♙ ♙
    8 ♖       ♕      ♖  ♔ 
      a  b  c  d  e  f  g  h

Sunfish:

    time: 53152 ms
    nodes: 1190490
    nps: 22398
    bestmove: f8d8

Sunfish-C:

    time: 2747 ms
    nodes: 1198635
    nps: 436343
    bestmove: f8d8

### Observation
The number of visited nodes in both engines is very similar.

The C version is around 20 times faster than its Python predecessor !


# License

[GNU GPL v3](https://www.gnu.org/licenses/gpl-3.0.en.html)