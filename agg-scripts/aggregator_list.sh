#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
python loop.py -r ${1} -f input.txt -F 1 -s ${2} # Do miniruns
python loop.py -r ${1} -f input.txt -F 0 -s ${2} # Do full runs
