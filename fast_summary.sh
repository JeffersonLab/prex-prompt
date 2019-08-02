#!/bin/sh

runnum=$1
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./japanOutput/quick_$runnum.!(*jlab.org*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    # strip out [run.seg]

    trim=${rootfile%.root}
    run_dot_seg=${trim#*ick_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    redfile='./results/quick_'${run_seg}'_regress_postpan.root';
    
    if [ ! -d ./FastPlots/run$run_seg ]; then
	mkdir ./FastPlots/run$run_seg;
    fi
    
    root -b -q -l './rootMacros/fastPlotSummary.C("'$rootfile'")';
    root -b -q -l './postpan/rootmacros/fastPlotSummary_postpan.C("'$redfile'")';

    pdfunite $(ls -rt ./FastPlots/run$run_seg/*_summary_*.pdf) \
	./FastPlots/run$run_seg/run${run_seg}_all.pdf

done


