#!/bin/bash
xterm -ls -n Prompter-${1}-${2} -T Prompter-${1}-${2} -bg black -fg white -sb -geometry 80x15+40+0 -hold -e "~/PREX/prompt/agg-scripts/login_prompt_1.sh ${1} ${2}"&
