#!/bin/bash

pass="crex-respin2/"


## To Hadd the files together using these runlists do: 
for (( i=1; i<=41; i++ )); do 
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_ErrorFlag.sh
  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-CREX-run-list-${i}.list CREX-Blessed-miniruns-${i}_basic.root
done
for (( i=1; i<=41; i++ )); do 
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_IncludeBMOD.sh
  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-CREX-run-list-${i}.list CREX-Blessed-miniruns-${i}_basic.root
done
for (( i=1; i<=41; i++ )); do 
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_OnlyBMOD.sh
  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-CREX-run-list-${i}.list CREX-Blessed-miniruns-${i}_basic.root
done
# AT
for (( i=1; i<=1; i++ )); do 
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_ErrorFlag.sh
  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-AT-run-list.list CREX-AT-Blessed-miniruns_basic.root
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_IncludeBMOD.sh
  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-AT-run-list.list CREX-AT-Blessed-miniruns_basic.root
  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_respin2_OnlyBMOD.sh
  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/$pass/Production/Blessed-AT-run-list.list CREX-AT-Blessed-miniruns_basic.root
done
