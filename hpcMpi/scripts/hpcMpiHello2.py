#!/usr/bin/env python3

from mpi4py import MPI

if __name__ == '__main__':

    comm = MPI.COMM_WORLD
    worldRank = comm.Get_rank()
    worldSize = comm.Get_size()

    t0 = MPI.Wtime()

    if worldRank == 0:    # master node

        # receive messages from other nodes
        for i in range(1, worldSize):
            msg = comm.recv(source=i)
            print(i, "sent:", msg)

        t1 = MPI.Wtime()
        print('walltime: {0:.6f} s'.format(t1-t0))

    else:    # other nodes
        comm.send('hello from {}'.format(worldRank), dest=0)
