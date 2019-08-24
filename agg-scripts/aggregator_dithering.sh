#!/bin/bash
cd ~/PREX/prompt/Aggregator/wrapper/
../setup_camguin.sh
python loop-oneRun.py -r ${1} -f dithering_input.txt -F 1 & # Do full runs
python loop-oneRun.py -r ${1} -f dithering_input.txt -F 0 & # Do miniruns
