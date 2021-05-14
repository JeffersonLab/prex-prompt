#!/bin/bash

cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
./hadd_eigen_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-CREX-run-list.list Full_mini_eigen_reg_allbpms_CREX.root _vectors_basic
./hadd_eigen_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/auto_run_list/Blessed-AT-run-list.list Full_mini_eigen_reg_allbpms_AT.root _vectors_basic # Third argument is the alternate path suffix for eigen rootfiles

