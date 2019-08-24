#! /bin/sh
while IFS= read -r line; do
    slug=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/agg-scripts/agg_prompt_list_dithering.sh run_list/slug${slug}.list >& ~/PREX/prompt/LogFiles/Slug_dithering_out.txt
    sleep 240
done < $1

