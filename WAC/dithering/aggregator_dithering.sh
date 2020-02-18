#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
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
python loop-oneRun.py -r ${1} -f dithering${outStub}_input.txt -F 1 # Do full runs
python loop-oneRun.py -r ${1} -f dithering${outStub}_input.txt -F 0 # Do miniruns
