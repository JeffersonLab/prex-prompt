#!/bin/bash

level="Prompt"

plot_work1="/chafs2/work1/apar/SummaryPlots/";
prompt_dir="/adaqfs/home/apar/PREX/prompt/";
todo_list=$prompt_dir/prompt-tmp/rsync_todo.list;

if [ -f $todo_list ]; then 
    while IFS= read -r line; do
	runnum=$line;
	if [ ! -z "$runnum" ];then
	    shopt -s extglob
	    folder_list=$(ls -1d $prompt_dir/tmp/run${runnum}_*);    
	    shopt -u extglob;

	    for folder  in $folder_list
	    do
		echo $folder;
		rsync  -avzhP --log-file=$prompt_dir/prompt-tmp/rsync.log \
		    --remove-source-files \
		    --itemize-changes \
		    $folder $plot_work1;
		rmdir $folder;
	    done
	else
	    echo "Run Number is empty ! " ;
	fi
    done < $todo_list;
    rm -f $todo_list;
fi



