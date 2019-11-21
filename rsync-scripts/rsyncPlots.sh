#!/bin/bash

level="Prompt"

todo_list=$PROMPT_DIR/rsync-scripts/rsync_todo.list;
plot_work1=$PROMPT_DIR/SummaryPlots/;

if [ -f $todo_list ]; then 
    working_list=$PROMPT_DIR/rsync-scripts/rsync_working.list;
    mv $todo_list $working_list; 
    while IFS= read -r line; do
	folder=$line;
	if [ ! -z "$folder" ];then
	    echo $folder;
	    rsync  -avzhP --log-file=$prompt_dir/rsync-scripts/rsync.log \
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
