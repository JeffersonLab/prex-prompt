#!/bin/bash
slug=0
pass="crex-respin2/"
for (( i=100; i<=223; i++ )); do
  slug=$i
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good --flip_state=FLIP-RIGHT,FLIP-LEFT --slug=${slug}
  mv list.txt $pass/slugs/slug${slug}.list
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --target=48Ca --flag=Good,NeedCut,Suspicious --flip_state=FLIP-RIGHT,FLIP-LEFT --slug=${slug}
  mv list.txt $pass/slugs_all_production/slug${slug}.list
done
for (( i=4000; i<=4019; i++ )); do
  slug=$i
  # AT slugs 4000-4019
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --flag=Good --flip_state='Vertical(UP)' --slug=${slug}
  mv list.txt $pass/slugs/slug${slug}.list
  python /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/PVDB/prex/examples/make_run_list.py --run=5000-9000 --type=Production --flag=Good,NeedCut,Suspicious --flip_state='Vertical(UP)' --slug=${slug}
  mv list.txt $pass/slugs_all_production/slug${slug}.list
done
