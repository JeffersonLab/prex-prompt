#!/bin/sh
scriptDir=`pwd`
cd $WORK_DIR

runnum=$1
level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ${scriptDir}/japanOutput/prex$level\_pass1_$runnum.!(*jlab.org*).root);
shopt -u extglob

rsync_todo_list="./prompt-tmp/rsync_todo.list"

for rootfile  in $rootfile_list
do
    # strip out [run.seg]
    echo "Starting to run summary.sh for $rootfile from "`pwd`

    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass1_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    redfile="${scriptDir}/results/prexPrompt_${run_seg}_regress_postpan.root";

    echo "****  Setting up directories"
    pwd
    ls -lrt

    if [ ! -d `pwd`/tmp/run$run_seg ]; then
	mkdir -p `pwd`/tmp/run$run_seg;
    fi
    chmod 777 `pwd`/tmp/run$run_seg;
    echo "Plots should be going to `pwd`/tmp/run$run_seg"
    echo    ls -lrt
    ls -lrt
    echo    ls -lrt `pwd`/tmp
    ls -lrt `pwd`/tmp
    my_output_path=`pwd`/tmp/run$run_seg/

    echo "****  Done setting up directories"

    root -b -q -l "${scriptDir}/rootMacros/PlotSummary.C(\"${rootfile}\",\"${my_output_path}\")";
    root -b -q -l "${scriptDir}/postpan/rootmacros/PlotSummary_postpan.C(\"${redfile}\",\"${my_output_path}\")";

    echo "****  CHECKING THE DIRECTORY STUCTURE"
    pwd
    echo "ls -lrtd `pwd`/tmp/run$run_seg"
    ls -lrtd `pwd`/tmp/run$run_seg
    echo "ls -lrt `pwd`/tmp/run$run_seg"
    ls -lrt `pwd`/tmp/run$run_seg
    echo "****  DONE CHECKING THE DIRECTORY STUCTURE"

    pdfunite $(ls -rt ${scriptDir}/tmp/run$run_seg/*_summary_*.pdf) \
     	${scriptDir}/tmp/run$run_seg/run${run_seg}_all.pdf

    if [ ! -d ${scriptDir}/hallaweb_online/summary_respin/run$run_seg ]; then
	mkdir ${scriptDir}/hallaweb_online/summary_respin/run$run_seg;
    fi
    
    mv  ./tmp/run$run_seg/* \
	${scriptDir}/hallaweb_online/summary_respin/run$run_seg/;
    rm  -rf ./tmp/run$run_seg;

    # copying prompt summary
    cp ${scriptDir}/japanOutput/summary_*$runnum*.txt \
	${scriptDir}/SummaryText/

    mv  ${scriptDir}/SummaryText/summary_$run_num.txt \
	${scriptDir}/SummaryText/summary_$level_$run_seg.txt \

    cp  ${scriptDir}/SummaryText/summary_$level_$run_seg.txt \
	${scriptDir}/hallaweb_online/summary_respin/run$run_seg/ ;
    # copying postpan summary
    cp  ${scriptDir}/results/prexPrompt_$run_seg\_postpan_summary.txt \
    	${scriptDir}/hallaweb_online/summary_respin/run$run_seg/;

    #Change user group and permission
    chgrp -R a-parity ${scriptDir}/hallaweb_online/summary_respin/run$run_seg;
    chmod -R 777 ${scriptDir}/hallaweb_online/summary_respin/run$run_seg;    
    
    bash 	${scriptDir}/hallaweb_online/summary_respin/sort_farm.sh ;

done

if [ -f $rsync_todo_list ]; then
    echo $run_num >> $rsync_todo_list;
else 
    echo $run_num > $rsync_todo_list;
fi


