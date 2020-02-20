#!/bin/bash
cd ~/PREX/prompt/bmodAna/
if [ "$#" -lt 2 ]; then
  echo "Arguments must be slug number and cycle number to remove"
  exit
fi
# Assume 1X analysis applies to both for now
root -l -b -q CopyTree.C'("slopes_run_avg/dithering_slopes_13746_slug'$1'.root",'${2}')'
root -l -b -q CopyTree.C'("slopes_run_avg_1X/dithering_slopes_13746_slug'$1'.root",'${2}')'
