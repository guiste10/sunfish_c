# sunfish_c
This project's goal is to rewrite the Sunfish chess engine in the C language.
The original project has been written in Python https://github.com/thomasahle/sunfish.

The .exe file produced by CMakeLists.txt can directly be used to run the engine that implements the UCI protocol.
This engine has been successfully tested with the Arena Chess GUI. 

At the time of writing, the search still needs to be adapted to match the behaviour of the original Sunfish implementation. 
The project in its current state contains just under 600 lines of source code, excluding header files and 'includes'.
Any pull requests to further optimize the search and the number of lines of code is welcome.