#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
echo "Deleting any old aggregator files for run $1"
ls -lsatrH ~/PREX/prompt/aggRootfiles/SAMs/minirun_aggregator_${1}_*.root
ls -lsatrH ~/PREX/prompt/aggRootfiles/SAMs/run_aggregator_${1}.root
rm -f ~/PREX/prompt/aggRootfiles/SAMs/minirun_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/SAMs/run_aggregator_${1}.root
echo "Creating aggregator files for run $1"
python loop-oneRun.py -r ${1} -f SAMs_input.txt -b testSAMs_pass2 -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f SAMs_input.txt -b testSAMs_pass2 -F 0 # Do mini runs
