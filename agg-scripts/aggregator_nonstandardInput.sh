#!/bin/bash
cd $PROMPT_DIR/Aggregator/wrapper/
../setup_camguin.sh
python loop-oneRun.py -r ${1} -f repair_input.txt -F 0 & # Do miniruns
python loop-oneRun.py -r ${1} -f repair_input.txt -F 1 & # Do full runs
