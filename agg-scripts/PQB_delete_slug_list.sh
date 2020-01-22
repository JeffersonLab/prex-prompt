#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    echo "Deleting aggregator files for run $runnum"
    rm -f ~/PREX/prompt/aggRootfiles/PQB/minirun_aggregator_${runnum}_*.root
done < $1

