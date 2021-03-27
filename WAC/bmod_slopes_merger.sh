#!/bin/bash

## BMOD merging
#for (( i=1; i<=9; i++ )); do 
#  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
#  cd $JAPAN_DIR/rootScripts/merger/
#  ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list-${i}.list dithering-slopes-runwise-${i}.root
#  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_cyclewise.sh
#  cd $JAPAN_DIR/rootScripts/merger/
#  ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list-${i}.list dithering-slopes-cyclewise-${i}.root
#done
#
#cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
#cd $JAPAN_DIR/rootScripts/merger/
#./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-AT-run-list.list AT-dithering-slopes-runwise.root
#cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_cyclewise.sh
#cd $JAPAN_DIR/rootScripts/merger/
#./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-AT-run-list.list AT-dithering-slopes-cyclewise.root
#cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
#cd $JAPAN_DIR/rootScripts/merger/
#./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list.list dithering-slopes-runwise.root
#cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_cyclewise.sh
#cd $JAPAN_DIR/rootScripts/merger/
#./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list.list dithering-slopes-cyclewise.root

# Eigenvector version - test 
cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise_eigen_part_avg.sh
#source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise_eigen_seg_avg.sh
cd $JAPAN_DIR/rootScripts/merger/
# third argument here is to specify a non-standard input/output folder
./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list.list dithering-slopes-runwise.root 
# ./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-AT-run-list.list AT-dithering-slopes-runwise.root 
#./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list.list dithering-slopes-cyclewise.root /lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/eigenvector_slopes/slopes_run_avg_1X_eigenvectors_sorted_seg_avg/
