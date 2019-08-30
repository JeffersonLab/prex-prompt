#! /bin/sh
while IFS= read -r line; do
    slug=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/agg-scripts/make_grandRootfile.sh run_list/slug${slug}.list
    sleep 1
done < $1

