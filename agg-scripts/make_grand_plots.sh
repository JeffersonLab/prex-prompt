#!/bin/bash

# This script simplifies the producion of plots for a given slug. It runs the scripts to create plots, and copies them to the online directory.
# It takes two arguments to run.
# 1: Full path to the slug list file. ~/PREX/prompt/collector/run_list/slug####.list
# 2: A single number 0, 1, or 2 for the spectrometers enabled. This is usually 0. 0 for both, 1 for right only, 2 for left only.

slugfile=$1
#hrs=$2
startingpoint=100
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

slug2=`rcnd $lastrun slug`
arm2=`rcnd $lastrun arm_flag`
ihwp2=`rcnd $lastrun ihwp`
wien2=`rcnd $lastrun flip_state`

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

mkdir ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}
cp --force $1 ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/

cd ~/PREX/prompt/
./get_charge.sh 5408-${lastrun} 0
#convert charge_mon.pdf -trim +repage charge_mon.png
/bin/cp --force charge_plots/charge_mon.pdf hallaweb_online/slug/slug_list/slug${slug}/charge_mon.pdf
/bin/cp --force charge_plots/charge_mon.pdf hallaweb_online/charge/slugs/charge_mon_integrated_slug${slug}.pdf
./get_charge.sh ${firstrun}-${lastrun} 0
#convert charge_mon.pdf -trim +repage charge_mon.png
/bin/cp --force charge_plots/charge_mon.pdf hallaweb_online/slug/slug_list/slug${slug}/charge_mon_slug${slug}.pdf
/bin/cp --force charge_plots/charge_mon.pdf hallaweb_online/charge/slugs/charge_mon_slug${slug}.pdf

if [ ! -d /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug ]
then
    mkdir /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug
fi

#make aggregator plots!
cd /chafs2/work1/apar/japan-aggregator/rootScripts/aggregator/drawPostpan

#~/PREX/prompt/agg-scripts/agg_prompt_list.sh ~/PREX/prompt/agg-scripts/run_list/slug${slug}.list
#sleep 900
~/PREX/prompt/Aggregator/drawPostpan/accumulate_mini_aggFiles_list.sh slug$slug


#root -l -b -q copytree_auto.C'('$slug')'
rm -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/grand_aggregator.root
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/
root -l -b -q plotAgg.C'("aggRootfiles/slugRootfiles/minirun_slug","plots/summary_minirun_slug", '$slug', '$ihwp', '$wien', '$hrs')'
cp -f plots/summary_minirun_slug${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
cp -f plots/summary_minirun_slug${slug}.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
cp -f plots/summary_minirun_slug_linear${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/

# Do the blessed dithering alpha/delta plots for the slug
~/PREX/prompt/agg-scripts/dither_slug_plots.sh ${slug}

rm -f grand_slug_plot_list.txt
# ignore 105
if [[ $slug < 105 ]]
then
  for i in $(seq $startingpoint $slug); do echo $i>>grand_slug_plot_list.txt; done
else
  for i in $(seq $startingpoint 104); do echo $i>>grand_slug_plot_list.txt; done
fi
if [[ $slug > 105 ]]
then
  if [[ $startingpoint > 105 ]]
  then
    for i in $(seq $startingpoint $slug); do echo $i>>grand_slug_plot_list.txt; done
  else
    for i in $(seq 106 $slug); do echo $i>>grand_slug_plot_list.txt; done
  fi
fi

#make grand agg plots!
./slug_file_accumulate_list.sh grand_slug_plot_list.txt
root -l -b -q grandAgg.C'("/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile/grand_'$startingpoint'-'${slug}'.root","~/PREX/prompt/hallaweb_online/slug/slug_list/slug'$slug'/grand_'$startingpoint'-'$slug'",0)'
cp --force ${CAM_OUTPUTDIR}/grand_aggregator.root ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
./slug_file_accumulate_list.sh grand_slug_plot_list.txt
root -l -b -q grandAgg.C'("/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile/grand_'$startingpoint'-'${slug}'.root","~/PREX/prompt/hallaweb_online/slug/slug_list/slug'$slug'/grand_signed_'$startingpoint'-'$slug'",1)'

cd $forgetmenot
