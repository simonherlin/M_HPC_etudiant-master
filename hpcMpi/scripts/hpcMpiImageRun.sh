#!/bin/sh

RADIUS=20
PROCS="2 3 4 5 6 7 8"
DATAFILE="outImage.csv"

echo "radius procs time" > ${DATAFILE}

echo "running on 1 proc..."
hpcMpiImageSeq.py "${RADIUS}" >> ${DATAFILE}

for p in ${PROCS} ; do
    echo "running on ${p} procs..."
    mpirun -n "${p}" --oversubscribe hpcMpiImagePar.py "${RADIUS}" >> ${DATAFILE}
done


