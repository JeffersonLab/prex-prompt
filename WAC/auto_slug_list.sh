#!/bin/bash
slug=0
#if [ $# -le 1 ]; then
for (( i=100; i<=223; i++ )); do
  slug=$i
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT --slug=${slug}
  mv list.txt auto_run_list/slugs/slug${slug}.list
  # AT slugs 4000-4019
  #python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --flag=Good,NeedCut,Suspicious --flip_state='Vertical(UP)' --slug=${slug}
  #mv list.txt auto_run_list/slugs/slug${slug}.list
done
#fi
