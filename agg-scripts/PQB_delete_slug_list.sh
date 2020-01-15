#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    echo "Deleting aggregator files for run $runnum"
    rm -f ~/PREX/prompt/aggRootfiles/PQB/minirun_aggregator_${runnum}_*.root
    rm -f ~/PREX/prompt/aggRootfiles/PQB/run_aggregator_${runnum}.root
done < $1

