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

## Tests

`./smoke_test.sh` builds the game with `-Wall -Wextra -Werror` and AddressSanitizer + UBSan, plays four scripted turns and checks that both players get a turn and a match/no-match result is printed. Any warning, memory error or undefined behaviour fails it. The deck is shuffled at random, so a whole game cannot be scripted; this checks the build and the turn loop, not every rule. GitHub Actions runs it on each push.

## Known limitations

- Input is read with plain `cin >> x >> y` and is not validated beyond the 0-3 range check, so typing a non-number (or closing the input stream) makes the prompt loop repeat instead of exiting.
- Shuffling uses `rand()` seeded from the clock, so two games started in the same second get the same layout.

## Skills demonstrated

Classic OOP design in C++ — abstract base class with virtual dispatch, a clean separation between game state (`Deck`, `Player`) and game flow (`Game`), and manual memory management of a 2D array of pointers.

*Verified: compiles without warnings and runs correctly end-to-end (turn switching, match detection, flip-back on mismatch, re-prompt on invalid input).*
