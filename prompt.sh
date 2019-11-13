#! /bin/sh
runnum=$1;
if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi

promptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
export PROMPT_DIR=$promptdir;
echo "Prompt directory is PROMPT_DIR = $PROMPT_DIR"

#MACHINE_NAME=${HOSTNAME%%.*}
#echo " -- prompt.sh: MACHINE_NAME=" $MACHINE_NAME
#export PREX_PLOT_DIR=$PWD/tmp_$MACHINE_NAME
#echo " -- prompt.sh: set PREX_PLOT_DIR=" $PREX_PLOT_DIR

if [ -z ${PREX_PLOT_DIR+x} ];
then 
    echo "PREX_PLOT_DIR is unset";
    echo "Setting it to `pwd`"
    export PREX_PLOT_DIR=`pwd`
else
    echo "PREX_PLOT_DIR is set to '$PREX_PLOT_DIR'";
fi

if [ ! -d $PREX_PLOT_DIR ]; then
    mkdir $PREX_PLOT_DIR;
fi

#  Remove the LRB output files if they exist
shopt -s extglob
# find split file
slopefile_list=$(ls -1 $PROMPT_DIR/LRBoutput/blueR$runnum*slope.root);
shopt -u extglob

for slopefile in $slopefile_list
do
    echo "deleting "  $slopefile;
    rm -f $slopefile;
done

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");

$PROMPT_DIR/qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass1_ \
    --QwLog.loglevel-file 2 \
    --QwLog.logfile $PROMPT_DIR/LogFiles/QwLog_run$runnum\_prompt_pass1_$timenow.txt ;

# Postpan regression to the first pass results
$PROMPT_DIR/auto_postpan.sh $runnum;
$PROMPT_DIR/overload_postpan.sh $runnum;
$PROMPT_DIR/auto_calcit.sh $runnum;

# Make Summary Plots/Text and sync to HallA onlineWeb
# now make plots from pass1 and postpan output
$PROMPT_DIR/summary.sh $runnum;

# Do aggregation after the second pass of japan is done. Assume all slug aggregation is done by the WAC
#Aggregator pass 0
# timenow=$(date +"%Y-%m%d-%H%M");
# (./aggregator.sh $runnum > /dev/tty ) >& ./LogFiles/Camguin_run$runnum\_$timenow.txt

echo "Done with prompt for run $runnum";
