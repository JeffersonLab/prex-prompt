#! /bin/sh
runnum=$1;

echo -e "\n\n\n\n\n    Starting prompt_sum.sh (PLOT_ONLY_MODE) \n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting prompt_sum.sh (PLOT_ONLY_MODE) \n\n\n\n\n";

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

timenow=$(date +"%Y-%m%d-%H%M");

# Make Summary Plots/Text and sync to HallA onlineWeb
# now make plots from pass1 and postpan output
$PROMPT_DIR/summary.sh $runnum;

echo "Done with plot-only mode for run $runnum";
