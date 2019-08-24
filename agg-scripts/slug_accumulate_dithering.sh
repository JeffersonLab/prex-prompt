#! /bin/sh
#gojapan
#cd ~/PREX/prompt/Aggregator/drawPostpan
while IFS= read -r line; do
    slug=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/Aggregator/drawPostpan/dithering_accumulate_mini_aggFiles_list.sh slug${slug} >& ~/PREX/prompt/LogFiles/Slug_dithering_accumulate_out_slug${slug}.txt
    sleep 3
done < $1

