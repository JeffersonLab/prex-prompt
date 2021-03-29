#! /bin/sh
runnum=$1;


echo -e "\n\n\n\n\n    Starting prompt.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting prompt.sh\n\n\n\n\n";

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

# #  Remove the LRB output files if they exist
shopt -s extglob
# find split file
slopefile_list=$(ls -1 $PROMPT_DIR/LRBoutput/*blueR$runnum*slope.root);
shopt -u extglob

for slopefile in $slopefile_list
do
    echo "deleting "  $slopefile;
    rm -f $slopefile;
done

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");

$PROMPT_DIR/qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass0_ \
    --add-config 0.5pass.conf \
    --QwLog.loglevel-file 2 \
    --QwLog.logfile $PROMPT_DIR/LogFiles/QwLog_run$runnum\_prompt_pass0_$timenow.txt ;

mv --force $PROMPT_DIR/max_burst_index.${runnum}.conf $PROMPT_DIR/Parity/prminput/

# 1st Pass : no tree/histo rootfile output. Only to get LRB correlators
$PROMPT_DIR/qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass1_ \
    --add-config 2pass.conf \
    --disable-trees --disable-histos \
    --QwLog.loglevel-file 2 \
    --QwLog.logfile $PROMPT_DIR/LogFiles/QwLog_run$runnum\_prompt_pass1_$timenow.txt ;

# 2nd Pass: output rootfiles and beam corrections
$PROMPT_DIR/qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass2_ \
    --add-config 2pass.conf \
    --QwLog.loglevel-file 2 \
    --QwLog.logfile $PROMPT_DIR/LogFiles/QwLog_run$runnum\_prompt_pass2_$timenow.txt ;

# Postpan regression to the 2nd pass results

$PROMPT_DIR/auto_postpan.sh $runnum;
$PROMPT_DIR/overload_postpan.sh $runnum;
# FIXME these 2 need to be reconsidered/treated as offline analyses
PATH_2_3=/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/jana/0.8.0/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/gemc/2.7:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/geant4/4.10.04.p02/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/bin:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/bin:/site/12gev_phys/2.3/ce:/usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/opt/puppetlabs/bin:/site/bin
PATH_2_4=/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/root/6.20.04/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/qt/5.10.1/5.10.1/gcc_64/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/mysql/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/gemc/2.8:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/geant4/4.10.06.p02/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/evio/5.1/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/clhep/2.4.1.3/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/ccdb/ccdb-1.07.00/bin:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/banks/1.6/bin:/site/12gev_phys/2.4/ce:/apps/gcc/9.2.0/bin:/apps/cmake/cmake-3.13.4/bin:/usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/opt/puppetlabs/bin:/site/bin
LD_LIBRARY_PATH_2_3=/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/rcdb/cpp/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/xercesc/3.2.2/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib/root:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mlibrary/1.3/lib:/site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/geant4/4.10.04.p02/lib64:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/lib:/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/rcdb/cpp/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/xercesc/3.2.2/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib/root:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mlibrary/1.3/lib:/site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/geant4/4.10.04.p02/lib64:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/lib:/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/rcdb/cpp/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/xercesc/3.2.2/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib/root:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mlibrary/1.3/lib:/site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/geant4/4.10.04.p02/lib64:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/lib:/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/rcdb/cpp/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/xercesc/3.2.2/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib/root:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mlibrary/1.3/lib:/site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/geant4/4.10.04.p02/lib64:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/lib:/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/rcdb/cpp/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/xercesc/3.2.2/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib/root:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mlibrary/1.3/lib:/site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/geant4/4.10.04.p02/lib64:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/lib:/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/rcdb/cpp/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/xercesc/3.2.2/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib/root:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mysql/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/mlibrary/1.3/lib:/site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/geant4/4.10.04.p02/lib64:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/evio/5.1/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/clhep/2.4.0.4/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/ccdb/ccdb-1.06.02/lib:/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/banks/1.4/lib:
LD_LIBRARY_PATH_2_4=/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/xercesc/3.2.3/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/root/6.20.04/lib/root:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/root/6.20.04/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/qt/5.10.1/5.10.1/gcc_64/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/mysql/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/mlibrary/1.4/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/geant4/4.10.06.p02/lib64:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/evio/5.1/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/clhep/2.4.1.3/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/ccdb/ccdb-1.07.00/lib:/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/banks/1.6/lib:/apps/gcc/9.2.0/lib64:/apps/gcc/9.2.0/lib
ROOTSYS_2_3=/site/12gev_phys/2.3/Linux_CentOS7.7.1908-x86_64-gcc4.8.5/root/6.14.04
ROOTSYS_2_4=/site/12gev_phys/2.4/Linux_CentOS7.7.1908-gcc9.2.0/root/6.20.04
ROOTSYS=$ROOTSYS_2_4
PATH=$PATH_2_4
$PROMPT_DIR/auto_calcit.sh $runnum;
$PROMPT_DIR/auto_beammod.sh $runnum;
ROOTSYS=$ROOTSYS_2_3
PATH=$PATH_2_3

# Make Summary Plots/Text and sync to HallA onlineWeb
# now make plots from pass2 and postpan output
$PROMPT_DIR/summary.sh $runnum;	


#timenow=$(date +"%Y-%m%d-%H%M");
#($PROMPT_DIR/respin_agg.sh $runnum > /dev/tty ) >& $PROMPT_DIR/LogFiles/Camguin_run$runnum\_$timenow.txt
$PROMPT_DIR/respin_agg.sh $runnum;

echo "Done with prompt for run $runnum";
