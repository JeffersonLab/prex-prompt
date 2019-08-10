#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/agg-scripts/aggregator.sh $runnum >& ~/PREX/prompt/LogFiles/Camguin_run$runnum\_$timenow.txt
    #./aggregator.sh $runnum 
done < $1

