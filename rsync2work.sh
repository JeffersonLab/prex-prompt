#!/bin/bash

level="Prompt"

japan_work1="/chafs2/work1/apar/japanOutput/";
prompt_dir="/adaqfs/home/apar/PREX/prompt";
todo_list=""$prompt_dir"/tmp-test/rsync_todo.list";

if [ -f $todo_list ]; then 
    while IFS= read -r line; do
	runnum=$line;
	shopt -s extglob
	rootfile_list=$(ls -1t $prompt_dir/tmp/prex$level\_pass1_$runnum.!(*jlab.org*).root);    
	shopt -u extglob;

	for rootfile  in $rootfile_list
	do
	    echo $rootfile;
	    trim=${rootfile%.root}
	    run_dot_seg=${trim#*pass1_}
	    run_num=${run_dot_seg%.*}
	    run_seg=${run_dot_seg/./_}

	    rsync -avzP \
		--remove-source-files \
		$prompt_dir/tmp/summary_$run_num.txt \
		$japan_work1;

	    rsync  -avzP --log-file=rsync.log \
		--remove-source-files \
		--itemize-changes \
		$rootfile $japan_work1;

	    exit ;
	done
    done < $todo_list;
    rm -f $todo_list;
fi



