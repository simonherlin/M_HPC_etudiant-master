#!/usr/bin/env python3

import hpcMpi
import sys
from time import time


if __name__ == '__main__':

    if len(sys.argv) != 2:
        print("usage:", sys.argv[0], "<radius>")
        sys.exit(-1)

    RADIUS = int(sys.argv[1])

    # read image
    image1 = hpcMpi.readPnm("backloop.pnm")
    if image1.size == 0:
        if worldRank == 0:
            print("error: failed to read pnm file")
        sys.exit(-1)
    height, width = image1.shape

    t0 = time()

    # compute blur
    x0, x1, y0, y1 = 0, width, 0, height  # the whole image
    # x0, x1, y0, y1 = 400, 1000, 100, 400  # only the guy doing backloop
    image2 = hpcMpi.blur(image1, RADIUS, x0, x1, y0, y1)

    t1 = time()

    # outputs
    hpcMpi.writePnm("output.pnm", image2)
    print(RADIUS, 1, t1-t0)
