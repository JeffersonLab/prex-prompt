#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
echo "Deleting any old PQB aggregator files for run $1"
ls -lsatrH ~/PREX/prompt/aggRootfiles/PQB/minirun_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/PQB/minirun_aggregator_${1}_*.root
echo "Creating PQB aggregator files for run $1"
#python loop-oneRun.py -r ${1} -f PQB_input.txt -F 1 & # Do full runs
python loop-oneRun.py -r ${1} -f PQB_input.txt -F 0 # Do miniruns
