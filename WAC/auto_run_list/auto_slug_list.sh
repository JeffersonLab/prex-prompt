#!/bin/bash
slug=0
pass="auto_run_list/crex-respin2/"
#if [ $# -le 1 ]; then
for (( i=100; i<=223; i++ )); do
  slug=$i
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT --slug=${slug}
  mv list.txt $pass/slugs/slug${slug}.list
done
#fi
for (( i=4000; i<=4019; i++ )); do
  slug=$i
  # AT slugs 4000-4019
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --flag=Good,NeedCut,Suspicious --flip_state='Vertical(UP)' --slug=${slug}
  mv list.txt $pass/slugs/slug${slug}.list
done
