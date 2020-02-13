#!/bin/tcsh
gojapan 
cd -
slcomment&
promptPREXplots $1
rcnd $1
echo "\nRun         = \e[1;34m$1\e[0m"
echo "Slug number = "'\e[1;34m'`rcnd $1 slug`'\e[0m'
echo "Avg current = "'\e[1;34m'`rcnd $1 beam_current` "uA"'\e[0m'
echo "Target type = "'\e[1;34m'`rcnd $1 target_type` '\e[0m'
