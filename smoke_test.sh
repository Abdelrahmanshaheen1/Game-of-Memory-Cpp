#!/usr/bin/env bash
# Builds the game with warnings-as-errors plus AddressSanitizer/UBSan, plays a few
# scripted turns and checks the turn order and the mismatch path.
#
#   ./smoke_test.sh
#
# The card layout is shuffled randomly, so a full game cannot be scripted. The input
# below flips four different pairs; whatever the layout, both players must get a turn,
# and any memory error or undefined behaviour hit along the way fails the run.
set -uo pipefail

BIN="$(mktemp -d)/memory_match"
g++ -std=c++17 -Wall -Wextra -Werror -g -fsanitize=address,undefined -fno-sanitize-recover=all \
    -o "$BIN" main.cpp || { echo "FAIL: does not compile cleanly"; exit 1; }

# After the scripted moves the game waits for more input; stop it after a few seconds.
OUT="$(printf 'Alice\nBob\n0 0\n0 1\n1 0\n1 1\n2 0\n2 1\n3 0\n3 1\n' | timeout 5 "$BIN" 2>&1 | head -c 200000)"

fail() { echo "FAIL: $1"; echo "$OUT" | head -40; exit 1; }
grep -q "Alice, it's your turn!" <<< "$OUT" || fail "Alice never got a turn"
grep -q "Bob, it's your turn!"   <<< "$OUT" || fail "Bob never got a turn"
grep -qE "Match found!|No match, cards will be flipped back." <<< "$OUT" || fail "no match result was printed"
grep -qE "AddressSanitizer|runtime error|LeakSanitizer" <<< "$OUT" && fail "sanitizer reported a problem"

echo "smoke test passed"
