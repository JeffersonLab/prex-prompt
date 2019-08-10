#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/agg-scripts/aggregator_nonstandardInput.sh $runnum >& ~/PREX/prompt/LogFiles/Camguin_run$runnum\_$timenow.txt
done < $1
