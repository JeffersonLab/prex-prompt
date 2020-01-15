#!/bin/tcsh
gojapan 
cd -
slcomment&
rcnd $1
echo "\nRun $1"
echo "Avg current = " `rcnd $1 beam_current`
echo "Target = " `rcnd $1 target_type`
promptPREXplots $1
