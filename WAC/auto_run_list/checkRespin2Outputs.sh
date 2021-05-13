#!/bin/bash
cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt
source PVDB/environment.sh
cd WAC

run=0
promptPlotsExists=0
promptJAPANExists=0
promptSummaryExists=0
promptBCMExists=0
promptRatecheckExists=0
promptPostpanROOTExists=0
promptPostpanOverloadROOTExists=0
promptPostpanExists=0
aggRootFileExists=0
bmodCycleCheckExists=0
bmodCyclesExists=0
bmodSensExists=0
bmodADExists=0
bmodSlopesExists=0


# ls a file list and search it, don't look up the files index on ifarm/volatile
#ls /lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/
#ls /lustre19/expphy/volatile/halla/parity/crex-respin2/postpan_respin/
#ls /lustre19/expphy/volatile/halla/parity/crex-respin2/postpan_respin/
#ls /lustre19/expphy/volatile/halla/parity/crex-respin2/aggRootfiles/ErrorFlag/
#ls /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes_run_avg_1X/

echo "Run,Slug,Run flag,Run type,Prompt Plots Exist,Prompt JAPAN Exists,Prompt Summary Exists,Prompt BCM Exists,Prompt Ratecheck Exists,Prompt Postpan ROOT Exists,Prompt Postpan Overload ROOT Exists,Prompt Postpan Summary Exists,Agg ROOT File Exists,BMOD Cycle Check Exists,BMOD Cycles Plots Exists,BMOD Sens csv Exists,BMOD AD Plots Exists,BMOD Slopes Exists" >> data-check-respin2.csv

while IFS= read -r run; do
  run=$(printf "%d" "$run")
  slug=`rcnd $run slug`
  runtype=`rcnd $run run_type`
  runtype=`echo $runtype | xargs`
  if [[ $runtype == "" ]] ; then
    runtype="None"
  fi
  runflag=`rcnd $run run_flag`
  runflag=`echo $runflag | xargs`
  if [[ $runflag == "" ]] ; then
    runflag="None"
  fi
  echo "run ${run}, slug $slug"


  #if [ -d /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000 ] ; then
  echo "Checking /u/group/prex/analysis/www/crex/summary_respin2/all/run${run}_000"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/all/run${run}_000/summary_${run}_000.txt ] ; then
    promptPlotsExists=1
  else
    promptPlotsExists=0
    echo " FAILED "
    slug="Fail"
    runtype="Fail"
    runflag="Fail"
  fi

  echo "Test 1"
  if [ -f /lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/prexPrompt_pass2_${run}.000.root ] ; then 
  echo "Test 2"
    promptJAPANExists=1
  else
  echo "Test 3"
    promptJAPANExists=0
  fi
  #if [ "`ls /lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/prexPrompt_pass2_${run}.000.root`" != "" ] ; then 
    #promptJAPANExists=1
  #else
    #promptJAPANExists=0
    #echo `ls /lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/prexPrompt_pass2_${run}.000.root`
  #fi

  echo "Test 4"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/summary_${run}_000.txt ] ; then 
  echo "Test 5"
    promptSummaryExists=1
  else
  echo "Test 6"
    promptSummaryExists=0
  fi

  echo "Test 7"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/run${run}_000_summary_bcm.pdf ] ; then 
  echo "Test 8"
    promptBCMExists=1
  else
  echo "Test 9"
    promptBCMExists=0
  fi

  echo "Test 10"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/run${run}_000_summary_ratecheck.pdf ] ; then 
  echo "Test 11"
    promptRatecheckExists=1
  else
  echo "Test 12"
    promptRatecheckExists=0
  fi

  echo "Test 13"
  if [ -f /lustre19/expphy/volatile/halla/parity/crex-respin2/postpan_respin/prexPrompt_${run}_000_regress_postpan.root ] ; then 
  echo "Test 14"
    promptPostpanROOTExists=1
  else
  echo "Test 15"
    promptPostpanROOTExists=0
  fi

  echo "Test 16"
  if [ -f /lustre19/expphy/volatile/halla/parity/crex-respin2/postpan_respin/prexPrompt_${run}_000_regress_overload.root ] ; then 
  echo "Test 17"
    promptPostpanOverloadROOTExists=1
  else
  echo "Test 18"
    promptPostpanOverloadROOTExists=0
  fi

  echo "Test 19"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/prexPrompt_${run}_000_postpan_summary.txt ] ; then 
  echo "Test 20"
    promptPostpanExists=1
  else
  echo "Test 21"
    promptPostpanExists=0
  fi

  echo "Test 22"
  if [ -f /lustre19/expphy/volatile/halla/parity/crex-respin2/aggRootfiles/ErrorFlag/minirun_aggregator_${run}_0.root ] ; then 
  echo "Test 23"
    aggRootFileExists=1
  else
  echo "Test 24"
    aggRootFileExists=0
  fi

  echo "Test 25"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/run${run}_000_supercyle.png ] ; then 
  echo "Test 26"
    bmodCycleCheckExists=1
  else
  echo "Test 27"
    bmodCycleCheckExists=0
  fi

  echo "Test 28"
  teststr="`ls /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/run${run}_*_cyc*.pdf`"
  if [[ "$teststr" == "" ]] ; then 
  echo "Test 29"
    bmodCyclesExists=0
  else
  echo "Test 30"
    bmodCyclesExists=1
  fi

  echo "Test 31"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/BMOD_sensitivities_13746_run${run}_runwise.txt ] ; then 
  echo "Test 32"
    bmodSensExists=1
  else
  echo "Test 33"
    bmodSensExists=0
  fi

  echo "Test 34"
  if [ -f /u/group/prex/analysis/www/crex/summary_respin2/Slug${slug}/run${run}_000/dithering_slopes_13746_run${run}_runwise_alphas-deltas.pdf ] ; then 
  echo "Test 35"
    bmodADExists=1
  else
  echo "Test 36"
    bmodADExists=0
  fi

  echo "Test 37"
  if [ -f /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes_run_avg_1X/dithering_slopes_13746_slug${slug}_run${run}.root ] ; then 
  echo "Test 38"
    bmodSlopesExists=1
  else
  echo "Test 39"
    bmodSlopesExists=0
  fi

  echo "$run,$slug,$runflag,$runtype,$promptPlotsExists,$promptJAPANExists,$promptSummaryExists,$promptBCMExists,$promptRatecheckExists,$promptPostpanROOTExists,$promptPostpanOverloadROOTExists,$promptPostpanExists,$aggRootFileExists,$bmodCycleCheckExists,$bmodCyclesExists,$bmodSensExists,$bmodADExists,$bmodSlopesExists" >> data-check-respin2.csv

done < $1
