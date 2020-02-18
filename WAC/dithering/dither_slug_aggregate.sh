#!/bin/bash
# NEW CREX Run Avg slope calculation
outStub=""
if [ "$#" -ge 2 ]; then
  outStub="${2}" # i.e. _1X
fi
while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/WAC/dithering/aggregator_dithering.sh $runnum ${outStub}
done < ~/PREX/prompt/WAC/run_list/slug${1}.list
