#!/bin/bash
# NEW CREX Run Avg slope calculation
folder="/adaqfs/home/apar/PREX/prompt/bmodAna/slopes_run_avg"
outStub=""
if [ "$#" -eq 0 ]; then
  echo "Usage: ./dithering/dither_correct_slug_aggregate.sh SLUGNUM STUB"
  exit
fi
if [ "$#" -ge 2 ]; then
  outStub="${2}" # i.e. _1X
fi
if [ -f ${folder}${outStub}/dithering_slopes_15746_slug${1}.root ] ; then
  /bin/cp --force ${folder}${outStub}/dithering_slopes_15746_slug${1}.root ~/PREX/prompt/BMODextractor/dit_alldet_slopes${outStub}_slug${1}.root
fi
if [ -f ${folder}${outStub}/dithering_slopes_13746_slug${1}.root ] ; then
  /bin/cp --force ${folder}${outStub}/dithering_slopes_13746_slug${1}.root ~/PREX/prompt/BMODextractor/dit_alldet_slopes${outStub}_slug${1}.root
fi
# OLD PREX Slopes from Ye Tian
#cp ~/PREX/prompt/beam-mod/rootfiles_alldet_pass2/dit_alldet_slopes_slug${1}.root ~/PREX/prompt/BMODextractor/

~/PREX/prompt/WAC/dithering/correctTree_runlist.sh ~/PREX/prompt/WAC/run_list/slug${1}.list ${outStub}

while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/WAC/any_aggregator.sh $runnum ~/PREX/prompt/WAC/configs/dithering${outStub}.sh
    #~/PREX/prompt/WAC/dithering/aggregator_dithering.sh $runnum ${outStub}
done < ~/PREX/prompt/WAC/run_list/slug${1}.list
