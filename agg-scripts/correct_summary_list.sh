#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    ~/PREX/prompt/agg-scripts/correct_summary.sh $runnum
    echo "Checking aggregator files for run $runnum"
done < $1
