#!/bin/sh

runnum=$1
level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./japanOutput/prex$level\_pass1_$runnum.!(*jlab.org*).root);
shopt -u extglob
echo " -- summary.sh: checking PREX_PLOT_DIR=" $PREX_PLOT_DIR
rsync_todo_list="./rsync-scripts/rsync_todo.list"

for rootfile  in $rootfile_list
do
    # strip out [run.seg]

    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass1_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    redfile='./results/prexPrompt_'${run_seg}'_regress_postpan.root';
    
    if [ ! -d $PREX_PLOT_DIR/run$run_seg ]; then
      mkdir $PREX_PLOT_DIR/run$run_seg;
    fi

    root -b -q -l './rootMacros/PlotSummary.C("'$rootfile'","'$PREX_PLOT_DIR'")';
    root -b -q -l './postpan/rootmacros/PlotSummary_postpan.C("'$redfile'","'$PREX_PLOT_DIR'")';

    if [ ! -d ./hallaweb_online/summary/run$run_seg ]; then
	mkdir ./hallaweb_online/summary/run$run_seg;
    fi

    cp  $PREX_PLOT_DIR/run$run_seg/* \
    	./hallaweb_online/summary/run$run_seg/;

    cp ./japanOutput/summary_*$runnum*.txt \
	./SummaryText/

    mv  ./SummaryText/summary_$run_num.txt \
	./SummaryText/summary_$level_$run_seg.txt \

    cp  ./SummaryText/summary_$level_$run_seg.txt \
	./hallaweb_online/summary/run$run_seg/ ;

    cp  ./results/prexPrompt_$run_seg\_postpan_summary.txt \
    	./hallaweb_online/summary/run$run_seg/;

    chgrp -R a-parity ./hallaweb_online/summary/run$run_seg;
    chmod -R 755 ./hallaweb_online/summary/run$run_seg;    
    
    bash 	./hallaweb_online/summary/sort.sh ;

    if [ -f $rsync_todo_list ]; then
	echo $PREX_PLOT_DIR/run$run_seg >> $rsync_todo_list;
    else 
	echo $PREX_PLOT_DIR/run$run_seg > $rsync_todo_list;
    fi

done


