# sunfish_c
This project's goal is to rewrite the Sunfish chess engine in the C language.
The original project has been written in Python https://github.com/thomasahle/sunfish.

The .exe file produced by CMakeLists.txt can directly be used to run the engine that implements the UCI protocol.

The project in its current state contains just around 954 lines of source code, excluding header files and the random 64 bit unsigned integers used for zobrist hashing.
Any pull requests to further optimize the search and improve the code is welcome.