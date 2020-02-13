#!/bin/bash
# NEW CREX Run Avg slope calculation
cp ~/PREX/prompt/bmodAna/slopes_run_avg/dithering_slopes_13746_slug${1}.root ~/PREX/prompt/BMODextractor/dit_alldet_slopes_slug${1}.root
# OLD PREX Slopes from Ye Tian
#cp ~/PREX/prompt/beam-mod/rootfiles_alldet_pass2/dit_alldet_slopes_slug${1}.root ~/PREX/prompt/BMODextractor/

~/PREX/prompt/WAC/dithering/correctTree_runlist.sh ~/PREX/prompt/WAC/run_list/slug${1}.list

while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/WAC/dithering/aggregator_dithering.sh $runnum
done < ~/PREX/prompt/WAC/run_list/slug${1}.list
