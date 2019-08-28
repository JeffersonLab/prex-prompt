#!/bin/bash
cp ~/PREX/prompt/beam-mod/rootfiles_alldet_pass2/dit_alldet_slopes_slug${1}.root ~/PREX/prompt/BMODextractor/

~/PREX/prompt/beam-mod/correctTree_runlist.sh ~/PREX/prompt/collector/run_list/slug${1}.list

while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/agg-scripts/aggregator_dithering.sh $runnum &
done < ~/PREX/prompt/collector/run_list/slug${1}.list
