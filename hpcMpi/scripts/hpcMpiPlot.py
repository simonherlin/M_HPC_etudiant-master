#!/usr/bin/env python3

import matplotlib as mpl
mpl.use('TkAgg')
import matplotlib.pyplot as plt

import pandas
import sys


if __name__ == '__main__':

    if len(sys.argv) != 2:
        print("usage:", sys.argv[0], "<datafile>")
        sys.exit(-1)
    DATAFILE = sys.argv[1]

    df = pandas.read_csv(DATAFILE, delimiter=" ")

    # trouve le temps en séquentiel
    df1 = df.loc[df['procs'] == 1]
    time1 = df1['time'][0]

    # calcule les accélérations
    dfs = df.loc[df['procs'] != 1].sort_values('procs')
    dfs['speedup'] = dfs.apply(lambda row: time1/row.time, axis=1)

    # trace les accélérations
    plt.plot(dfs['procs'], dfs['speedup'])
    plt.xlabel('nb procs')
    plt.ylabel('speed-up')
    plt.grid()
    plt.title('scalability')
    # plt.savefig('out_scalability.png')
    plt.show()
