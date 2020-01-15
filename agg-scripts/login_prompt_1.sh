#!/bin/bash
#ssh -Y apar@${1} 'tcsh -s' < ~/scripts/do_prompt_1.sh ${2}
#command="~/PREX/prompt/agg-scripts/do_prompt_1.sh ${2} ;exec $SHELL -1"
ssh apar@${1} -X -tt "echo '~/PREX/prompt/agg-scripts/do_prompt_1.sh ${2}'|$SHELL -l"
