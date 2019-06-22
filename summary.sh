#!/bin/sh

runnum=$1
level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./japanOutput/prex$level\_pass2_$runnum.!(*jlab.org*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    # strip out [run.seg]

    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass2_}

    run_seg=${run_dot_seg/./_}
    if [ ! -d ./SummaryPlots/run$run_seg ]; then
	mkdir ./SummaryPlots/run$run_seg;
    fi

    root -b -q -l './rootMacros/PlotSummary.C("'$rootfile'")';

    if [ ! -d ./hallaweb_online/summary/run$run_seg ]; then
	mkdir ./hallaweb_online/summary/run$run_seg;
    fi

    cp  ./SummaryPlots/run$run_seg/* \
	./hallaweb_online/summary/run$run_seg/;

    mv  ./SummaryText/summary_$run_dot_seg.txt \
	./SummaryText/summary_$level_$run_seg.txt \

    cp  ./SummaryText/summary_$level_$run_seg.txt \
	./hallaweb_online/summary/run$run_seg/ ;

    #Change user group and permission
    chgrp -R a-parity ./hallaweb_online/summary/run$run_seg;
    chmod -R 755 ./hallaweb_online/summary/run$run_seg;    

done


