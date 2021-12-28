#!/usr/bin/env python

import sys

# use stdin if it's full
if not sys.stdin.isatty():
    moves = sys.stdin.read().strip().split(",")

# otherwise, read the given filename
else:
    if (len(sys.argv) >= 2):
        moves = sys.argv[1].split(",")
    else:
        print("[USAGE]: Please provide a string of comma-seperated rotations (Singmaster notation) either as an argument or piped from another program")
        exit()

for i in range(len(moves)):
    if (moves[i] == "U"):
        moves[i] = 0
    elif (moves[i] == "U'"):
        moves[i] = 1
    elif (moves[i] == "U2"):
        moves[i] = 2
    elif (moves[i] == "D"):
        moves[i] = 3
    elif (moves[i] == "D'"):
        moves[i] = 4
    elif (moves[i] == "D2"):
        moves[i] = 5
    elif (moves[i] == "F"):
        moves[i] = 6
    elif (moves[i] == "F'"):
        moves[i] = 7
    elif (moves[i] == "F2"):
        moves[i] = 8
    elif (moves[i] == "B"):
        moves[i] = 9
    elif (moves[i] == "B'"):
        moves[i] = 10
    elif (moves[i] == "B2"):
        moves[i] = 11
    elif (moves[i] == "R"):
        moves[i] = 12
    elif (moves[i] == "R'"):
        moves[i] = 13
    elif (moves[i] == "R2"):
        moves[i] = 14
    elif (moves[i] == "L"):
        moves[i] = 15
    elif (moves[i] == "L'"):
        moves[i] = 16
    elif (moves[i] == "L2"):
        moves[i] = 17

moves = [str(element) for element in moves]

print(",".join(moves))
