#! /bin/sh
runnum=$1;
if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi

#  Remove the LRB output files if they exist
shopt -s extglob
# find split file
slopefile_list=$(ls -1 ./LRBoutput/blueR$runnum*slope.root);
shopt -u extglob

for slopefile in $slopefile_list
do
    echo "deleting "  $slopefile;
    rm -f $slopefile;
done

if[ ! -d ./tmp ]; then
    mkdir ./tmp;
fi

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");

./qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass1_ \
    --rootfiles ./tmp \
    --QwLog.loglevel-file 2 \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_prompt_pass1_$timenow.txt ;

./prompt-tmp/auto_postpan.sh $runnum;
./prompt-tmp/summary.sh $runnum;

echo "Done with prompt for run $runnum";
