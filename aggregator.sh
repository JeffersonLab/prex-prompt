#!/bin/bash
cd Aggregator/wrapper/
../setup_camguin.sh
python loop-oneRun.py -r ${1} -f input.txt -F 1 & # Do miniruns
python loop-oneRun.py -r ${1} -f input.txt -F 0 & # Do full runs
