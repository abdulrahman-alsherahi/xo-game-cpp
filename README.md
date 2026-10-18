# XO Game (Tic Tac Toe) - C++

A simple console-based Tic Tac Toe game for two players, written in C++.

The in-game messages are in German (for example `Aktueller Spieler` = current player, `Gewinner` = winner, `Unentschieden` = draw).

## Features

- Two-player mode (X and O on the same keyboard)
- Input validation (out-of-range numbers, occupied fields, and non-numeric input)
- Automatic win detection for rows, columns, and diagonals
- Draw detection after 9 moves

## Technologies

- C++
- Standard Library (iostream)

## How to Run

Compile:

```bash
g++ xo-game.cpp -o xo
```

Run:

```bash
./xo
```

## Example

Players choose a field by entering its number:

```
1 | 2 | 3
4 | 5 | 6
7 | 8 | 9
```
