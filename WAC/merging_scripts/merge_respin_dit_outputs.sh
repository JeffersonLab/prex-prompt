#!/bin/bash

pass="crex-respin2/"


## To Hadd the files together using these runlists do: 
for (( i=1; i<=1; i++ )); do 
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_ErrorFlag_dit_1X_runwise.sh
  cd $JAPAN_DIR/rootScripts/merger/
  ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-AT-run-list.list respin2_AT_dithering_slopes_run_avg_basic.root /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes${DITHERING_STUB}/
  ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-CREX-run-list.list respin2_CREX_dithering_slopes_run_avg_basic.root /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes${DITHERING_STUB}/
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_ErrorFlag_dit_1X_cyclewise.sh
  cd $JAPAN_DIR/rootScripts/merger/
  ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-AT-run-list.list respin2_AT_dithering_slopes_cyclewise_basic.root /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes${DITHERING_STUB}/
  ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-CREX-run-list.list respin2_CREX_dithering_slopes_cyclewise_basic.root /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes${DITHERING_STUB}/ # 3rd argument overwrites the write-location
done

##### BMOD merging
###for (( i=1; i<=13; i++ )); do 
  ###cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  ###source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
  ###cd $JAPAN_DIR/rootScripts/merger/
  ###./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Blessed-CREX-run-list-\${i}.list dithering-slopes-runwise-\${i}.root
  ###cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  ###source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_cyclewise.sh
  ###cd $JAPAN_DIR/rootScripts/merger/
  ###./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Blessed-CREX-run-list-\${i}.list dithering-slopes-cyclewise-\${i}.root
###done

## To Hadd the files together using these runlists do: 
#for (( i=1; i<=13; i++ )); do 
  #cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  #source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
  #cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  #./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/repo-simple-lists/all_crex_${i}.list CREX-All-miniruns-${i}.root
  #./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-CREX-run-list-${i}.list CREX-Blessed-miniruns-${i}.root
#done

## To Hadd the files together using these runlists do: 
#for (( i=1; i<=13; i++ )); do 
  #cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  #source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise_eigen_part_avg.sh
  #cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  #./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/repo-simple-lists/all_crex_${i}.list CREX-All-miniruns-${i}.root
#done
