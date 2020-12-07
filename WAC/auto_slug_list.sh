#!/bin/bash
slug=0
if [ $# -le 1 ]; then
  slug=$1
  python /adaqfs/home/apar/pvdb/prex/examples/make_run_list.py --run=5000-8000 --type=Production --current=20 --target=48Ca --slug=${slug}
  mv list.txt auto_run_list/slug${slug}.list
fi
