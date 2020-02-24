#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
echo "Deleting any old aggregator files for run $1"
ls -lsatrH ~/PREX/prompt/aggRootfiles/minirun_aggregator_${1}_*.root
ls -lsatrH ~/PREX/prompt/aggRootfiles/run_aggregator_${1}.root
rm -f ~/PREX/prompt/aggRootfiles/minirun_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/run_aggregator_${1}.root
echo "Creating aggregator files for run $1"
conf="input.txt"
if [ $(($run_num)) -ge 5337 ]
then
  conf="input.5337-6490.txt"
fi
if [ $(($run_num)) -ge 6491 ]
then
  conf="input.txt"
fi
python loop-oneRun.py -r ${1} -f $conf -b prexPrompt_pass1 -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f $conf -b prexPrompt_pass1 -F 0 # Do mini runs
