#!/bin/bash
cd ~/PREX/prompt/bmodAna/
if [ "$#" -lt 2 ]; then
  echo "Arguments must be slug number, cycle number to begin the new segment at, and the segment index (defaults to 2 if not given, the original segments are always = 1)"
  exit
fi
segment=$3
if [ "$#" -lt 3 ]; then
  segment=2
fi
# Assume 1X analysis applies to both for now
root -l -b -q SegmentTree.C'("slopes_run_avg/dithering_slopes_13746_slug'$1'.root",'${2}','${segment}')'
root -l -b -q SegmentTree.C'("slopes_run_avg_1X/dithering_slopes_13746_slug'$1'.root",'${2}','${segment}')'
