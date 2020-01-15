#!/bin/bash
cd Aggregator/wrapper/
../setup_camguin.sh
echo "Deleting any old aggregator files for run $runnum"
ls -lsatrH ~/PREX/prompt/aggRootfiles/minirun_aggregator_${runnum}_*.root
ls -lsatrH ~/PREX/prompt/aggRootfiles/run_aggregator_${runnum}.root
rm -f ~/PREX/prompt/aggRootfiles/minirun_aggregator_${runnum}_*.root
rm -f ~/PREX/prompt/aggRootfiles/run_aggregator_${runnum}.root
echo "Creating aggregator files for run $runnum"
python loop-oneRun.py -r ${1} -f input.txt -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f input.txt -F 0 # Do mini runs
