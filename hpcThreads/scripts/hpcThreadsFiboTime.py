#!/usr/bin/env python3

import hpcThreads
import sys
from time import time


def tester_fonction(nom, fonction):
    t0 = time()
    fonction()
    t1 = time()
    print("{}: {} s".format(nom, str(t1-t0)))


if __name__ == '__main__':

    # vérifie les arguments
    if len(sys.argv) != 2:
        print("usage:", sys.argv[0], "<nbData>")
        sys.exit(-1)
    NB_DATA = int(sys.argv[1])

    # lance les calculs
    tester_fonction("sequentiel", lambda : hpcThreads.fiboSequentiel(NB_DATA))
    tester_fonction("blocs", lambda : hpcThreads.fiboBlocs(NB_DATA))
    tester_fonction("Cyclique2", lambda : hpcThreads.fiboCyclique2(NB_DATA)) 
    tester_fonction("CycliqueN", lambda : hpcThreads.fiboCycliqueN(NB_DATA, 4))
    tester_fonction("CycliqueN", lambda : hpcThreads.fiboCycliqueN(NB_DATA, 8))
    # TODO
