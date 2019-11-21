#!/bin/bash

level="Prompt"

japan_work1=""$PROMPT_DIR"/japanOutput/";
todo_list=""$PROMPT_DIR"/prompt-tmp/rsync_todo.list";

if [ -f $todo_list ]; then 
    while IFS= read -r line; do
	runnum=$line;
	shopt -s extglob
	rootfile_list=$(ls -1t $PROMPT_DIR/tmp/prex$level\_pass1_$runnum.!(*jlab.org*).root);    
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
		$PROMPT_DIR/tmp/summary_$run_num.txt \
		$japan_work1;

	    rsync  -avzhP --log-file=$PROMPT_DIR/prompt-tmp/rsync.log \
		--remove-source-files \
		--itemize-changes \
		$rootfile $japan_work1;
	done
    done < $todo_list;
    rm -f $todo_list;
fi



