#!/usr/bin/env python

import sys

if (len(sys.argv) != 7):
    print("[USAGE] Please provide 6 arguments: One for each face of the cube")
    exit()

faces = []
for i in range(1, len(sys.argv)):
    stickers = ([char for char in sys.argv[i]])
    faces.append('0')
    faces.append('x')
    for sticker in stickers:
        if (sticker == 'Y'):
            faces.append('0')
        elif (sticker == 'W'):
            faces.append('1')
        elif (sticker == 'G'):
            faces.append('2')
        elif (sticker == 'B'):
            faces.append('3')
        elif (sticker == 'O'):
            faces.append('4')
        elif (sticker == 'R'):
            faces.append('5')
        else:
            print(F"Unknown sticker color: {sticker}")
    if (i != 6):
        faces.append(' ')

print(''.join(faces))
