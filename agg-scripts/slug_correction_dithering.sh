#! /bin/sh
while IFS= read -r line; do
    slug=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/beam-mod/correctTree_runlist.sh run_list/slug${slug}.list >& ~/PREX/prompt/LogFiles/Slug_dithering_correction_out_slug${line}.txt &
    sleep 900
done < $1

