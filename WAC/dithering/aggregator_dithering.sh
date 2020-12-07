#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
source ../setup_camguin.sh
outStub=""
if [ "$#" -ge 2 ]; then
  outStub="${2}"
fi
echo "Deleting any old Dithering${outStub} aggregator files for run $1"
ls -lsatrH ~/PREX/prompt/aggRootfiles/dithering${outStub}/run_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/dithering${outStub}/run_aggregator_${1}_*.root
ls -lsatrH ~/PREX/prompt/aggRootfiles/dithering${outStub}/minirun_aggregator_${1}_*.root
rm -f ~/PREX/prompt/aggRootfiles/dithering${outStub}/minirun_aggregator_${1}_*.root
echo "Creating Dithering${outStub} aggregator files for run $1"
conf="input.txt"
if [ $(($1)) -ge 5337 ]
then
  conf="dithering${outStub}_input.5337-6490.txt"
fi
if [ $(($1)) -ge 6491 ]
then
  conf="dithering${outStub}_input.txt"
fi
python loop-oneRun.py -r ${1} -f $conf -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f $conf -F 0 # Do miniruns
