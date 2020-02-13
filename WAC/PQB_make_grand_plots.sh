#!/bin/bash

# This script simplifies the producion of plots for a given slug. It runs the scripts to create plots, and copies them to the online directory.
# It takes two arguments to run.
# 1: Full path to the slug list file. ~/PREX/prompt/collector/run_list/slug####.list
# 2: A single number 0, 1, or 2 for the spectrometers enabled. This is usually 0. 0 for both, 1 for right only, 2 for left only.

slugfile=$1
#hrs=$2
#startingpoint=4 #Default start on 60, most recent Wien
#startingpoint=60 #Default start on 60, most recent Wien
startingpoint=100 #Default start on 60, most recent Wien
if [ "$#" -eq 2 ]; then
  startingpoint=$2
fi

source ~/PREX/setup_japan.sh

forgetmenot=`pwd`

firstrun=999999
lastrun=0

input="$slugfile"
while IFS= read -r line
do
  if [ $(echo "$line < $firstrun" | bc) -eq 1  ]
    then
        firstrun=$line
        #echo "firstrun $line"
    fi
    
    if [ $(echo "$line > $lastrun" | bc) -eq 1  ]
    then
        lastrun=$line
        #echo "lastrun $line"
    fi
done < "$input"

slug1=`rcnd $firstrun slug`
arm1=`rcnd $firstrun arm_flag`
ihwp1=`rcnd $firstrun ihwp`
wien1=`rcnd $firstrun flip_state`
if [[ ! "$wien1" =~ FLIP-(LEFT|RIGHT) ]]; then
  wien1="FLIP-RIGHT"
fi

slug2=`rcnd $lastrun slug`
arm2=`rcnd $lastrun arm_flag`
ihwp2=`rcnd $lastrun ihwp`
wien2=`rcnd $lastrun flip_state`
if [[ ! "$wien2" =~ FLIP-(LEFT|RIGHT) ]]; then
  wien2="FLIP-RIGHT"
fi

if [ $slug1 != $slug2 ]
then
  echo "First and last run's slugs don't equal!"
  exit
fi

if [[ (($arm1 -ne 0) && ($arm2 -ne 0)) && ($arm1 -ne $arm2) ]]
then
  echo "First and last run's good HRS don't equal!"
  exit
fi

if [ $ihwp1 != $ihwp2 ]
then
  echo "First and last run's ihwp don't equal!"
  exit
fi

if [ $wien1 != $wien2 ]
then
  echo "First and last run's wien don't equal!"
  exit
fi

slug=$slug1
hrs=$arm2
ihwpstring=$ihwp1
wienstring=$wien1

if [ $ihwpstring == "IN" ]
then
    ihwp=1
fi

if [ $ihwpstring == "OUT" ]
then
    ihwp=2
fi

if [ $wienstring == "FLIP-RIGHT" ]
then
    wien=1
fi

if [ $wienstring == "FLIP-LEFT" ]
then
    wien=2
fi

if [ $startingpoint -gt $slug ]; then
  echo "starting slug number: $startingpoint larger than slug number: $slug"
  exit 1
fi

mkdir ~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug${slug}
cp --force $1 ~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug${slug}/
if [ ! -d /chafs2/work1/apar/aggRootfiles/slugRootfiles/PQB/grandRootfile_$slug ]
then
    mkdir /chafs2/work1/apar/aggRootfiles/slugRootfiles/PQB/grandRootfile_$slug
fi

#make aggregator plots!
cd /chafs2/work1/apar/japan-aggregator/rootScripts/aggregator/drawPostpan

#~/PREX/prompt/agg-scripts/agg_prompt_list.sh ~/PREX/prompt/agg-scripts/run_list/slug${slug}.list
#sleep 900
~/PREX/prompt/Aggregator/drawPostpan/PQB_accumulate_mini_aggFiles_list.sh slug$slug



#root -l -b -q copytree_auto.C'('$slug')'
rm -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/PQB/grandRootfile_$slug/grand_aggregator.root
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/slugRootfiles/PQB/grandRootfile_$slug/
root -l -b -q plotAgg.C'("aggRootfiles/slugRootfiles/PQB/minirun_slug","plots/PQB/summary_minirun_slug", '$slug', '$ihwp', '$wien', '$hrs')'
cp -f plots/PQB/summary_minirun_slug${slug}.txt ~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug${slug}/
cp -f plots/PQB/summary_minirun_slug${slug}.pdf ~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug${slug}/
cp -f plots/PQB/summary_minirun_slug_linear${slug}.txt ~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug${slug}/

[ -f grand_slug_plot_list.txt ] && rm -f grand_slug_plot_list.txt
# ignore 105
for (( i=$startingpoint; i<=$slug; i++ )); do
  [ "$i" -ne 105 ] && echo $i >> grand_slug_plot_list.txt
done
./PQB_slug_file_accumulate_list.sh grand_slug_plot_list.txt
#cat grand_slug_plot_list.txt  # debugging

#make grand agg plots!
root -l -b -q grandAgg.C'("/chafs2/work1/apar/aggRootfiles/slugRootfiles/PQB/grandRootfile/grand_'$startingpoint'-'${slug}'.root","~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug'$slug'/grand_'$startingpoint'-'$slug'",0)'
root -l -b -q grandAgg.C'("/chafs2/work1/apar/aggRootfiles/slugRootfiles/PQB/grandRootfile/grand_'$startingpoint'-'${slug}'.root","~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug'$slug'/grand_signed_'$startingpoint'-'$slug'",1)'

cp --force ${CAM_OUTPUTDIR}/grand_aggregator.root ~/PREX/prompt/hallaweb_online/PQB_slug/slug_list/slug${slug}/

cd $forgetmenot
