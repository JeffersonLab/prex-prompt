#!/bin/bash
# NEW CREX Run Avg slope calculation
#folder="/adaqfs/home/apar/PREX/prompt/bmodAna/slopes_run_avg"
# FIXME hardcoded paths for respin1
export QW_ROOTFILES="/lustre19/expphy/volatile/halla/parity/crex-respin1/japanOutput"
folder="/lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/slopes_run_avg"
export DITHERING_ROOTFILES_SLOPES="/lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/BMODextractor/"
outStub="_1X"
if [ "$#" -eq 0 ]; then
  echo "Usage: ./dithering/dither_correct_slug_aggregate.sh abs-path-to-RUNLIST STUB"
  exit
fi
if [ "$#" -ge 2 ]; then
  outStub="${2}" # i.e. _1X
  export DITHERING_STUB="$2"
fi
if [ -f ${folder}${outStub}/dithering_slopes_13746_runwise.root ] ; then
  /bin/cp --force ${folder}${outStub}/dithering_slopes_13746_runwise.root /lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/BMODextractor/dit_alldet_slopes${outStub}.root
fi
if [ -f ${folder}${outStub}/AT-dithering_slopes_13746_runwise.root ] ; then
  /bin/cp --force ${folder}${outStub}/AT-dithering_slopes_13746_runwise.root /lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/BMODextractor/AT-dit_alldet_slopes${outStub}.root
  #/bin/cp --force ${folder}${outStub}/AT-dithering_slopes_13746_runwise.root /lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/BMODextractor/dit_alldet_slopes${outStub}.root
fi
# OLD PREX Slopes from Ye Tian
#cp ~/PREX/prompt/beam-mod/rootfiles_alldet_pass2/dit_alldet_slopes_slug${1}.root ~/PREX/prompt/BMODextractor/

./dithering/correctTree_runlist.sh ${1} ${outStub}

while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    ~/PREX/prompt/WAC/any_aggregator.sh $runnum ~/PREX/prompt/WAC/configs/dithering${outStub}.sh
    #~/PREX/prompt/WAC/dithering/aggregator_dithering.sh $runnum ${outStub}
done < ${1}
