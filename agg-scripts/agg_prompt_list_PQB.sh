#! /bin/sh
./PQB_delete_slug_list.sh $1
while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    #~/PREX/prompt/agg-scripts/aggregator_dithering.sh $runnum >& ~/PREX/prompt/LogFiles/Camguin_dithering_run$runnum\_$timenow.txt
    ~/PREX/prompt/agg-scripts/aggregator_PQB.sh $runnum
done < $1

