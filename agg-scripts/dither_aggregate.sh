#!/bin/bash
while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/agg-scripts/aggregator_dithering.sh $runnum &
done < ~/PREX/prompt/collector/run_list/slug${1}.list
