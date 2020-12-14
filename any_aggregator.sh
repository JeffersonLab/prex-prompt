#!/bin/bash
source ${2}
if [[ $# -eq 1 && "$CAM_CONFIG" == "" ]]; then
  source configs/prex_regression.sh
fi
# Backup default case
if [[ "$CAM_CONFIG" == "" ]] ; then 
  export CAM_CONFIG="input.txt"
fi
if [[ "$JAPAN_DIR" == "" ]] ; then 
  export JAPAN_DIR="~/PREX/japan"
fi
cd ${JAPAN_DIR}/rootScripts/aggregator/wrapper/
echo "Deleting any old aggregator files for run $1:"
ls -lsatrH $CAM_OUTPUTDIR/minirun_aggregator_${1}_*.root
ls -lsatrH $CAM_OUTPUTDIR/run_aggregator_${1}.root
rm -f $CAM_OUTPUTDIR/minirun_aggregator_${1}_*.root
rm -f $CAM_OUTPUTDIR/run_aggregator_${1}.root
if [ ! -d $CAM_OUTPUTDIR ]; then 
  mkdir $CAM_OUTPUTDIR
fi
echo "Creating aggregator files for run $1, using config $CAM_CONFIG"
python any-loop-oneRun.py -r ${1} -f ${CAM_CONFIG} -F 1 # Do full runs # -b prexPrompt_pass2
python any-loop-oneRun.py -r ${1} -f ${CAM_CONFIG} -F 0 # Do mini runs # -b prexPrompt_pass2

