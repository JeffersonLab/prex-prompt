#!/bin/bash

pass="auto_run_list/crex-respin2/"

python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --current=5 --target=48Ca --flag=Good,NeedCut,Suspicious
mv list.txt $pass/full-run-list-curentcut.list

## Produces the RCND run list for non-Bad and production runs.
## Includes Vertical(UP) AT runs...
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --type=Production,Calibration,Pedestal,Parityscan
mv list.txt $pass/CREX-All-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --type=Production,Calibration,Pedestal,Parityscan --show=True
mv list.txt $pass/CREX-All-FullInfo-run-list.list

## Produces the RCND run list for non-Bad and production runs.
## Skips Vertical(UP) AT runs... which is fine since the target is a mess anyway
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT --show=True
mv list.txt $pass/Production/Blessed-CREX-FullInfo-run-list.list

## Bad, etc.
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Good-CREX-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Bad --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Bad-CREX-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=NeedCut --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/NeedCut-CREX-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Suspicious-CREX-run-list.list

## Small enough to survive the smartHadd.C memory limit (I guess)
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-6000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-1.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=6001-6500 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-2.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=6501-7000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-3.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=7001-7250 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-4.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=7251-7500 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-5.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=7501-7750 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-6.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=7751-8000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-7.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=8001-8250 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-8.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=8251-9000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-run-list-9.list

## To Hadd the files together using these runlists do: 
#for (( i=1; i<=9; i++ )); do 
#  cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
#  source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag.sh
#  cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
#  ./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/Blessed-CREX-run-list-\${i}.list CREX-Blessed-miniruns-\${i}.root
#done


## AT 
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flip_state='Vertical(UP)'
mv list.txt $pass/All-AT-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flip_state='Vertical(UP)' --show==True
mv list.txt $pass/All-AT-FullInfo-run-list.list

## To Hadd the files together using these runlists do: 
#for (( i=1; i<=1; i++ )); do 
  #cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  #source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
  #cd $JAPAN_DIR/rootScripts/merger/
  #./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/Blessed-AT-run-list.list dithering_slopes_AT_CREX.root
  #cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  #source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_cyclewise.sh
  #cd $JAPAN_DIR/rootScripts/merger/
  #./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/Blessed-AT-run-list.list dithering_slopes_AT_CREX.root
#done

python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --flag=Good,NeedCut,Suspicious --flip_state='Vertical(UP)'
mv list.txt $pass/Production/Blessed-AT-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --flag=Good,NeedCut,Suspicious --flip_state='Vertical(UP)' --show==True
mv list.txt $pass/Production/Blessed-AT-FullInfo-run-list.list
#
## Carbon 1%
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production,Calibration,Pedestal --target=Carbon --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Blessed-Carbon-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production,Calibration,Pedestal --target=Carbon --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT --show=True
mv list.txt $pass/Blessed-Carbon-FullInfo-run-list.list
# Ca40
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production,Calibration,Pedestal --target=40Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Blessed-Ca40-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production,Calibration,Pedestal --target=40Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT --show=True
mv list.txt $pass/Blessed-Ca40-FullInfo-run-list.list


##### BMOD merging
###for (( i=1; i<=9; i++ )); do 
  ###cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  ###source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
  ###cd $JAPAN_DIR/rootScripts/merger/
  ###./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/Blessed-CREX-run-list-\${i}.list dithering-slopes-runwise-\${i}.root
  ###cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  ###source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_cyclewise.sh
  ###cd $JAPAN_DIR/rootScripts/merger/
  ###./smartHadd_dit_slopes_by_run.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/Blessed-CREX-run-list-\${i}.list dithering-slopes-cyclewise-\${i}.root
###done

## To Hadd the files together using these runlists do: 
#for (( i=1; i<=11; i++ )); do 
  #cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  #source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise.sh
  #cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  #./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/repo-simple-lists/all_crex_${i}.list CREX-All-miniruns-${i}.root
  #./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/Blessed-CREX-run-list-${i}.list CREX-Blessed-miniruns-${i}.root
#done

## To Hadd the files together using these runlists do: 
#for (( i=1; i<=11; i++ )); do 
  #cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/
  #source /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/configs/crex_ErrorFlag_dit_1X_runwise_eigen_part_avg.sh
  #cd /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/merger
  #./smartHadd_miniruns_any_regression.sh /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/WAC/$pass/repo-simple-lists/all_crex_${i}.list CREX-All-miniruns-${i}.root
#done
