# Networked War Card Game

This project implements a modified version of the card game "War" using PThreads and socket communication for inter-process communication. Two threads play rounds of the card game, with the parent process managing the game and communicating results.

## Features

- Multi-threaded implementation using PThreads
- Inter-process communication using Unix domain sockets
- No-tie game system with suit comparison for equal cards
- Sudden death round implementation for tournament ties
- Command-line argument for specifying number of rounds
- Clean error handling and resource management

## Files

- `war_networked.c` - Main source code file
- `Makefile` - Build configuration file
- `README.md` - This documentation file

## Requirements

- GCC compiler
- POSIX-compliant operating system (Linux/Unix)
- pthread library

## Building the Program

To compile the program, use the included Makefile:

```bash
make
```

This will create the executable `war_networked`.

To clean the build files:

```bash
make clean
```

## Running the Program

Run the program by specifying the number of rounds as a command-line argument:

```bash
./war_networked <number_of_rounds>
```

Example:
```bash
./war_networked 3
```

This will run a 3-round tournament between two players.

## Game Rules

1. Each round, both players draw a card
2. Higher card value wins the round
3. If cards have equal value, suits are compared (Spades > Hearts > Diamonds > Clubs)
4. If players are tied after all rounds, a sudden death round is played
5. The player with the most rounds won is declared the tournament winner

## Output Format

The program outputs:
- Thread IDs for both players
- Card draws for each round
- Results of suit comparisons when needed
- Sudden death round (if necessary)
- Final tournament results

## Example Output
```
Child 1 TID: 123456
Child 2 TID: 123457
Beginning 3 Rounds...
Fight!
---------------------------
Round 1:
Child 1 draws 8
Child 2 draws King
Child 2 Wins!
---------------------------
[...remaining rounds...]
```