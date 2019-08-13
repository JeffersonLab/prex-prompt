#!/bin/sh

runnum=$1
level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./japanOutput/prex$level\_pass1_$runnum.!(*jlab.org*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    # strip out [run.seg]

    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass1_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    redfile='./results/prexPrompt_'${run_seg}'_regress_postpan.root';
    
    if [ ! -d ./tmp/run$run_seg ]; then
	mkdir ./tmp/run$run_seg;
    fi
    
    root -b -q -l './rootMacros/PlotSummary.C("'$rootfile'")';
    root -b -q -l './postpan/rootmacros/PlotSummary_postpan.C("'$redfile'")';

    # pdfunite $(ls -rt ./tmp/run$run_seg/*_summary_*.pdf) \
    # 	./tmp/run$run_seg/run${run_seg}_all.pdf

    if [ ! -d ./hallaweb_online/summary/run$run_seg ]; then
	mkdir ./hallaweb_online/summary/run$run_seg;
    fi
    
    mv  ./tmp/run$run_seg/* \
	./hallaweb_online/summary/run$run_seg/;
    rm  -rf ./tmp/run$run_seg;
    # copying prompt summary
    cp ./japanOutput/summary_*$runnum*.txt \
	./SummaryText/

    mv  ./SummaryText/summary_$run_num.txt \
	./SummaryText/summary_$level_$run_seg.txt \

    cp  ./SummaryText/summary_$level_$run_seg.txt \
	./hallaweb_online/summary/run$run_seg/ ;
    # copying postpan summary
    cp  ./results/prexPrompt_$run_seg\_postpan_summary.txt \
    	./hallaweb_online/summary/run$run_seg/;

    #Change user group and permission
    chgrp -R a-parity ./hallaweb_online/summary/run$run_seg;
    chmod -R 755 ./hallaweb_online/summary/run$run_seg;    
    
    bash 	./hallaweb_online/summary/sort.sh ;
done


