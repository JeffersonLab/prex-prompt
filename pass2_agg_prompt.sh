#! /bin/sh
runnum=$1;
if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi

#JAPAN Second Pass
timenow=$(date +"%Y-%m%d-%H%M");

./qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass2_ \
    --QwLog.loglevel-file 2 \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_prompt_pass2_$timenow.txt ;

# Do aggregation after the second pass of japan is done. Assume all slug aggregation is done by the WAC

#Aggregator pass 0
timenow=$(date +"%Y-%m%d-%H%M");
(./aggregator.sh $runnum > /dev/tty ) >& ./LogFiles/Camguin_run$runnum\_$timenow.txt

echo "Done with prompt for run $runnum"

# BeamMod Data Extraction (FIXME)
# BeamMod Instant Slope Calculation (FIXME)
# BeamMod Instant correction and summary (FIXME)
