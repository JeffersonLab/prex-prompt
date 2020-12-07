#! /bin/sh
while IFS= read -r line; do
    slug=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    #~/PREX/prompt/agg-scripts/dither_make_grand_plots.sh run_list/slug${slug}.list
    ~/PREX/prompt/agg-scripts/make_grand_plots.sh run_list/slug${slug}.list
    ~/PREX/prompt/agg-scripts/PQB_make_grand_plots.sh run_list/slug${slug}.list
    sleep 1
done < $1

