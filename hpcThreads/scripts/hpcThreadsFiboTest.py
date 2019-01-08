#!/usr/bin/env python3

import hpcThreads
import sys

if __name__ == '__main__':

    # vérifie les arguments
    if len(sys.argv) != 2:
        print("usage:", sys.argv[0], "<nbData>")
        sys.exit(-1)
    NB_DATA = int(sys.argv[1])

    # lance les calculs
    print("fiboSequentiel:\n", hpcThreads.fiboSequentiel(NB_DATA))
    # TODO
