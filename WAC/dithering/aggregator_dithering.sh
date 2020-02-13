#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
echo "Deleting any old Dithering aggregator files for run $1"
ls -lsatrH ~/PREX/prompt/aggRootfiles/dithering/run_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/dithering/run_aggregator_${1}_*.root
ls -lsatrH ~/PREX/prompt/aggRootfiles/dithering/minirun_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/dithering/minirun_aggregator_${1}_*.root
echo "Creating Dithering aggregator files for run $1"
python loop-oneRun.py -r ${1} -f dithering_input.txt -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f dithering_input.txt -F 0 # Do miniruns
