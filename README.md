ROSS KUIPER AND GARY GRITTERS

If a 1 is returned, the .wav file that was handed was failed to read. Most likely because it had a data size <1.

If a 2 is returned, something went horribly wrong, since we never return 2.

If a 3 is returned, the program failed to malloc space for the reverse part of the code.

If a 4 is returned, the program improperly wrote a new file from reversed. It has a different size from the original .wav file, which shouldn't happen.
