#!/bin/bash

level="Prompt"

japan_work1="/chafs2/work1/apar/japanOutput/";
prompt_dir="/u/group/halla/parity/software/japan_offline/prompt/prex-prompt_merge/prex-prompt";
todo_list=""$prompt_dir"/prompt-tmp/rsync_todo.list";

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

	    rsync -avzhP \
		--remove-source-files \
		$prompt_dir/tmp/summary_$run_num.txt \
		$japan_work1;

	    rsync  -avzhP --log-file=$prompt_dir/prompt-tmp/rsync.log \
		--remove-source-files \
		--itemize-changes \
		$rootfile $japan_work1;
	done
    done < $todo_list;
    rm -f $todo_list;
fi



