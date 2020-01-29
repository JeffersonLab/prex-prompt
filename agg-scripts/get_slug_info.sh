#!/bin/bash
cat ~/PREX/prompt/agg-scripts/run_list/slug${1}.list | tail -1
rcnd `cat ~/PREX/prompt/agg-scripts/run_list/slug${1}.list | tail -1` | grep -i IHWP
rcnd `cat ~/PREX/prompt/agg-scripts/run_list/slug${1}.list | tail -1` | grep -i STATE
#rcnd `cat ~/PREX/prompt/agg-scripts/run_list/slug${1}.list | tail -1` | grep -i wac
#echo "HRS = `csv=$(echo \`grep "slug${1}," hrs_list.txt\`|tr "slug${1}," " "); echo ${csv}`"
echo "HRS = `csv=$(echo \`grep "slug${1}," ~/PREX/prompt/agg-scripts/hrs_list.txt\`); echo ${csv}`"
echo "WAC_Comment = `rcnd \`cat ~/PREX/prompt/agg-scripts/run_list/slug${1}.list | tail -1\` wac_comment`"
