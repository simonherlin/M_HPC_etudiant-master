#!/usr/bin/env python3

import hpcMpi
import sys
import time as t


if __name__ == '__main__':

    # parse command line arguments
    step = 1e-3
    if len(sys.argv) == 2:
        step = float(sys.argv[1])

    t0 = t.time()

    # compute
    value = hpcMpi.compute(hpcMpi.fPi, 0, 1, step)

    t1 = t.time()

    # output result
    time = t1 - t0
    print(step, "1", value, time)
