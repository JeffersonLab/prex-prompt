#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh #input the run list as 1, slug number as 2, for safety
python loop.py -r ${1} -f input.txt -F 0 -s ${2} # Do miniruns
python loop.py -r ${1} -f input.txt -F 1 -s ${2} # Do full runs
