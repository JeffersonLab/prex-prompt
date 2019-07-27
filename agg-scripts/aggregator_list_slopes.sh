#!/bin/bash
cd Aggregator/wrapper/
../setup_camguin.sh
python loop.py -r ${1} -f slope_input.txt -F 1 # Do miniruns
python loop.py -r ${1} -f slope_input.txt -F 0 # Do full runs
