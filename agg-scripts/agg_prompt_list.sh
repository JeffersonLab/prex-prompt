#! /bin/sh
./delete_slug_list.sh $1
while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/aggregator.sh $runnum >& ~/PREX/prompt/LogFiles/Camguin_run$runnum\_$timenow.txt
    sleep 120
    #./aggregator.sh $runnum 
done < $1

