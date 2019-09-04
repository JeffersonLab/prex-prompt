#!/bin/bash

level="Prompt"

plot_work1="/chafs2/work1/apar/SummaryPlots/";
prompt_dir="/adaqfs/home/apar/PREX/prompt/";
todo_list=$prompt_dir/prompt-tmp/rsync_todo.list;

if [ -f $todo_list ]; then 
    working_list=$prompt_dir/prompt-tmp/rsync_working.list;
    mv $todo_list $working_list; 
    while IFS= read -r line; do
	folder=$line;
	if [ ! -z "$folder" ];then
	    echo $folder;
	    rsync  -avzhP --log-file=$prompt_dir/prompt-tmp/rsync.log \
		--remove-source-files \
		--itemize-changes \
		$folder $plot_work1;
	    rmdir $folder;
	else
	    echo " -- Entry is empty ! " ;
	fi
    done < $working_list;
    rm -f $working_list;
fi
