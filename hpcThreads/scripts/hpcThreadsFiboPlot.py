#!/usr/bin/env python3

import hpcThreads
from time import time
import numpy
import matplotlib.pyplot as plt


def compute_one(nb_data, nb_procs):
    '''Lance le calcul sur une valeur de data et de procs
        et retourne le temps d'exécution.'''
    t0 = time()
    hpcThreads.fiboCycliqueNFake(nb_data, nb_procs)
    t1 = time()
    return t1 - t0


def compute_all(datas, procs, nb_runs):
    '''Lance tous les calculs/mesures.'''
    times = numpy.zeros((len(datas), len(procs)))
    for kp, vp in enumerate(PROCS):
        for kd, vd in enumerate(DATAS):
            for r in range(NB_RUNS):
                t = compute_one(vd, vp)
                times[kd, kp] += t
                print("{} data on {} proc in {} s".format(vd, vp, t))
    times /= NB_RUNS
    return times


def plot_series(data, xs, zs, xlabel, ylabel, title):
    '''Fait un graphique avec plusieurs séries de donnée.
        Chaque colonne de data correspond à une série.'''
    plt.clf()
    for z_ind, z_val in enumerate(zs):
        plt.plot(xs, data[:, z_ind], label="{} procs".format(z_val))
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.grid()
    plt.title(title)
    plt.savefig('out_{}.png'.format(title))


def analyze(datas, procs, times):
    '''Fait les graphiques des temps, accélération et passage à l'échelle.'''

    # temps d'exécution
    plot_series(times, datas, procs, 'nb data', 'compute time', 'times')

    # accélérations
    speedups = numpy.zeros((len(datas), len(procs)-1))
    for i in range(len(procs)-1):
        speedups[:, i] = times[:, 0] / times[:, i+1]
    plot_series(speedups, datas, procs[1:], 'nb data', 'speed-up', 'speedups')

    # passage à l'échelle
    scalability = speedups[-1, :]
    plt.clf()
    plt.plot(procs[1:], scalability)
    plt.xlabel('nb procs')
    plt.ylabel('speed-up')
    plt.grid()
    plt.title('scalability')
    plt.savefig('out_scalability.png')


if __name__ == '__main__':

    # paramètres pour tester
    DATAS = [1000, 5000, 10000, 25000]
    PROCS = [1, 2, 4, 8]
    NB_RUNS = 2

    # paramètres pour de vrai
    # DATAS = [1000, 5000, 10000, 25000, 50000]
    # PROCS = range(1, 13)
    # NB_RUNS = 10

    # lance les calculs
    times = compute_all(DATAS, PROCS, NB_RUNS)

    # fait les graphiques
    analyze(DATAS, PROCS, times)

