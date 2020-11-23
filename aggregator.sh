#!/bin/bash
cd ./Aggregator/wrapper/
../setup_camguin.sh
python3 loop-oneRun.py -r ${1} -f input.txt -F 1 # Do full runs
python3 loop-oneRun.py -r ${1} -f input.txt -F 0 # Do mini runs
