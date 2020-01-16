#!/bin/bash
cd Aggregator/wrapper/
../setup_camguin.sh
echo "Deleting any old aggregator files for run $1"
ls -lsatrH ~/PREX/prompt/aggRootfiles/minirun_aggregator_${1}_*.root
ls -lsatrH ~/PREX/prompt/aggRootfiles/run_aggregator_${1}.root
rm -f ~/PREX/prompt/aggRootfiles/minirun_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/run_aggregator_${1}.root
echo "Creating aggregator files for run $1"
python loop-oneRun.py -r ${1} -f input.txt -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f input.txt -F 0 # Do mini runs
