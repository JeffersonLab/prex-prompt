#!/bin/bash

pass="crex-respin2/"

# Includes Vertical(UP) AT runs...
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --target=Home --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)'
mv list.txt $pass/CREX-HomeCheck-run-list.list
python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --flag=Good,NeedCut,Suspicious --target=Home --flip_state=FLIP-RIGHT,FLIP-LEFT,'Vertical(UP)' --show=True
mv list.txt $pass/CREX-HomeCheck-FullInfo-run-list.list

