#!/bin/sh
runnum=$1

echo -e "\n\n\n\n\n    Starting summary.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting summary.sh\n\n\n\n\n";

level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 $PROMPT_DIR/japanOutput/prex$level\_pass2_$runnum.!(*jlab.org*).root);
shopt -u extglob
echo " -- summary.sh: checking PREX_PLOT_DIR=" $PREX_PLOT_DIR
rsync_todo_list="$PROMPT_DIR/rsync-scripts/rsync_todo.list"

for rootfile  in $rootfile_list
do
    # strip out [run.seg]
    echo "Starting to run summary.sh for $rootfile from "`pwd`

    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass2_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    redfile="$PROMPT_DIR/results/prexPrompt_${run_seg}_regress_postpan.root";
    
    if [ ! -d $PREX_PLOT_DIR/run$run_seg ]; then
      mkdir $PREX_PLOT_DIR/run$run_seg;
    fi

    root -b -q -l "$PROMPT_DIR/rootMacros/PlotSummary.C(\"${rootfile}\",\"$PREX_PLOT_DIR\")";
    root -b -q -l "$PROMPT_DIR/postpan/rootmacros/PlotSummary_postpan.C(\"${redfile}\",\"$PREX_PLOT_DIR\")";

    echo "****  CHECKING THE DIRECTORY STUCTURE"
    pwd
    echo "ls -lrtd $PREX_PLOT_DIR/run$run_seg"
    ls -lrtd $PREX_PLOT_DIR/run$run_seg
    echo "ls -lrt $PREX_PLOT_DIR/run$run_seg"
    ls -lrt $PREX_PLOT_DIR/run$run_seg
    echo "****  DONE CHECKING THE DIRECTORY STUCTURE"

    #pdfunite $(ls -rt $PREX_PLOT_DIR/run$run_seg/*_summary_*.pdf) \
    # 	$PREX_PLOT_DIR/run$run_seg/run${run_seg}_all.pdf

    if [ ! -d $PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg ]; then
	mkdir $PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg;
    fi

    cp  $PREX_PLOT_DIR/run$run_seg/* \
    	$PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg/;

    cp $PROMPT_DIR/japanOutput/summary_*$runnum*.txt \
	$PROMPT_DIR/SummaryText/

    # copying prompt summary
    cp $PROMPT_DIR/japanOutput/summary_*$runnum*.txt \
	$PROMPT_DIR/SummaryText/

    mv  $PROMPT_DIR/SummaryText/summary_$run_num.txt \
	$PROMPT_DIR/SummaryText/summary_$level_$run_seg.txt \

    cp  $PROMPT_DIR/SummaryText/summary_$level_$run_seg.txt \
	$PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg/ ;
    # copying postpan summary
    cp  $PROMPT_DIR/results/prexPrompt_$run_seg\_postpan_summary.txt \
    	$PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg/;

    #Change user group and permission
    chgrp -R a-parity $PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg;
    chmod -R 775 $PROMPT_DIR/hallaweb_online/prex2/summary_respin/run$run_seg;    
    
    bash $PROMPT_DIR/hallaweb_online/prex2/summary_respin/sort_farm.sh "run$run_seg";

    if [ -f $rsync_todo_list ]; then
	echo $PREX_PLOT_DIR/run$run_seg >> $rsync_todo_list;
    else 
	echo $PREX_PLOT_DIR/run$run_seg > $rsync_todo_list;
    fi

done


