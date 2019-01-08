#!/bin/sh

STEP=0.00001
PROCS="2 3 4 5 6 7 8"
DATAFILE="outIntegral.csv"

echo "step procs value time" > ${DATAFILE}

echo "running on 1 proc..."
hpcMpiIntegralSeq.py "${STEP}" >> ${DATAFILE}

for p in ${PROCS} ; do
    echo "running on ${p} procs..."
    mpirun -n "${p}" --oversubscribe hpcMpiIntegralPar.py "${STEP}" >> ${DATAFILE}
done

