#! /bin/sh

# This script simplifies the producion of plots for a given slug. It runs the scripts to create plots, and copies them to the online directory.
# It takes two arguments to run.
# 1: Full path to the slug list file. ~/PREX/prompt/collector/run_list/slug####.list
# 2: A single number 0, 1, or 2 for the spectrometers enabled. This is usually 0. 0 for both, 1 for right only, 2 for left only.

slugfile=$1
hrs=$2
startingpoint=60 #Default start on 60, most recent Wien
if [ "$#" -eq 3 ]; then
  startingpoint=$3
fi

source ~/PREX/setup_japan.sh

forgetmenot=`pwd`

firstrun=999999
lastrun=0

input="$slugfile"
while IFS= read -r line
do
  if [ $(echo "$line < $firstrun" | bc) == 1  ]
    then
        firstrun=$line
        #echo "firstrun $line"
    fi
    
    if [ $(echo "$line > $lastrun" | bc) == 1  ]
    then
        lastrun=$line
        #echo "lastrun $line"
    fi
done < "$input"

slug1=`rcnd $firstrun slug`
ihwp1=`rcnd $firstrun ihwp`
wien1=`rcnd $firstrun flip_state`

slug2=`rcnd $lastrun slug`
ihwp2=`rcnd $lastrun ihwp`
wien2=`rcnd $lastrun flip_state`

if [ $slug1 != $slug2 ]
then
  echo "First and last run's slugs don't equal!"
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

if [ ! -d /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug ]
then
    mkdir /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug
fi

#make aggregator plots!
cd /chafs2/work1/apar/japan-aggregator/rootScripts/aggregator/drawPostpan
#root -l -b -q copytree_auto.C'('$slug')'
rm -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/grand_aggregator.root
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/
root -l -b -q plotAgg.C'("aggRootfiles/slugRootfiles/minirun_slug","plots/summary_minirun_slug", '$slug', '$ihwp', '$wien', '$hrs')'
cp -f plots/summary_minirun_slug${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
cp -f plots/summary_minirun_slug${slug}.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
cp -f plots/summary_minirun_slug_linear${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/

rm -f grand_slug_plot_list.txt
for i in $(seq $startingpoint $slug); do echo $i>>grand_slug_plot_list.txt; done
./slug_file_accumulate_list.sh grand_slug_plot_list.txt

#make grand agg plots!
root -l -b -q grandAgg.C'("/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile/grand_'$startingpoint'-'${slug}'.root","~/PREX/prompt/hallaweb_online/slug/slug_list/slug'$slug'/grand_'$startingpoint'-'$slug'")'

cd $forgetmenot
