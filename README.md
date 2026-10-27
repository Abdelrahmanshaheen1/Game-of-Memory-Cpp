# Memory Match — C++ Card Game

A console-based, two-player memory-matching card game in C++, built around a small class hierarchy using inheritance and polymorphism.

## Design

- **`Card`** — abstract base class (face-up/down state, virtual `display()`).
- **`StandardCard`, `BonusCard`, `PenaltyCard`** — subclasses overriding `display()`, each affecting score differently when matched (bonus/penalty mechanics on top of standard matching).
- **`Deck`** — owns a 4×4 grid of `Card*`, handles shuffling and match-checking.
- **`Player`** — name and running score.
- **`Game`** — orchestrates turns between two players, coordinate-based card selection, and win condition (all cards matched).

## How to build & run

```bash
g++ -std=c++17 -o memory_match main.cpp
./memory_match
```

Compiles cleanly with `-Wall`, no warnings. Two players take turns entering grid coordinates (`x y`) to flip two cards; matches stay revealed and score points, mismatches flip back.

## Skills demonstrated

Classic OOP design in C++ — abstract base class with virtual dispatch, a clean separation between game state (`Deck`, `Player`) and game flow (`Game`), and manual memory management of a 2D array of pointers.

*Verified: compiles without warnings and runs correctly end-to-end (turn switching, match detection, flip-back on mismatch, re-prompt on invalid input).*
