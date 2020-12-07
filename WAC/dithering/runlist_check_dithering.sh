#!/bin/bash
cd ~/PREX/prompt/bmodAna/
if [ "$#" -ne 1 ]; then
  echo "Error: just give the slug number directly"
  exit;
fi
slug=$1
if [ ! -d "/adaqfs/home/apar/PREX/prompt/hallaweb_online/dithering_1X_slug/slug_list/slug${slug}/" ]
then
  echo "Invalid slug number: $slug"
  exit;
fi 
root -l -b -q runlist_check_dithering.C\(\"slopes_run_avg_1X/dithering_slopes_13746_slug${slug}.root\",\"run_list/slug${slug}.list\"\);
echo ""
echo ""
echo "Made: ~/PREX/prompt/bmodAna/checks/run-checks.txt" #slug${slug}_dithering_slopes_check.txt"
echo ""
cd -
