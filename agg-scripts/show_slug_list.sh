#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    echo "Showing aggregator files for run $runnum"
    ls -lsatrh ~/PREX/prompt/aggRootfiles/minirun_aggregator_${runnum}*.root
    ls -lsatrh ~/PREX/prompt/aggRootfiles/run_aggregator_${runnum}*.root
done < $1

