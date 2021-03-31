#!/bin/bash

pass="crex-respin2/"

## Includes Vertical(UP) AT runs...
#python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)'
#mv list.txt $pass/CREX-respin2-run-list.list
#python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)' --show=True
#mv list.txt $pass/CREX-respin2-FullInfo-run-list.list
#
## Includes Vertical(UP) AT runs...
#python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)'
#mv list.txt $pass/CREX-respin2-nonBad-run-list.list
#python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)' --show=True
#mv list.txt $pass/CREX-respin2-nonBad-FullInfo-run-list.list
#
## Includes Vertical(UP) AT runs...
#python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Test,Calibration,Pedestal,Parityscan,Production --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)'
#mv list.txt $pass/CREX-respin2-nonJunk-run-list.list
#python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Test,Calibration,Pedestal,Parityscan,Production --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)' --show=True
#mv list.txt $pass/CREX-respin2-nonJunk-FullInfo-run-list.list

# Calibration only
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Calibration
mv list.txt $pass/CREX-Calibration-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Calibration --show=True
mv list.txt $pass/CREX-Calibration-FullInfo-run-list.list

# Pedestal only
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Pedestal
mv list.txt $pass/CREX-Pedestal-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Pedestal --show=True
mv list.txt $pass/CREX-Pedestal-FullInfo-run-list.list

# Parityscan only
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Parityscan
mv list.txt $pass/CREX-Parityscan-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Parityscan --show=True
mv list.txt $pass/CREX-Parityscan-FullInfo-run-list.list

# Production GOOD only
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good --flip_state=FLIP-RIGHT,FLIP-LEFT
mv list.txt $pass/Production/Blessed-CREX-Good-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good --flip_state=FLIP-RIGHT,FLIP-LEFT --show=True
mv list.txt $pass/Production/Blessed-CREX-Good-FullInfo-run-list.list

