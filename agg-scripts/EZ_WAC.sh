#! /bin/sh

# This script simplifies the producion of plots for a given slug. It runs the scripts to create plots, and copies them to the online directory.
# It takes two arguments to run.
# 1: Full path to the slug list file. ~/PREX/prompt/collector/run_list/slug####.list
# 2: A single number 0, 1, or 2 for the spectrometers enabled. This is usually 0. 0 for both, 1 for right only, 2 for left only.

slugfile=$1
hrs=$2

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

if [ ! -d /u/group/halla/www/hallaweb/html/parity/prex/onlinePlots/slug/slug_list/slug$slug ]
then
    mkdir /u/group/halla/www/hallaweb/html/parity/prex/onlinePlots/slug/slug_list/slug$slug
fi

#copy current slug list to online plots
cp -f ~/PREX/prompt/collector/run_list/slug${slug}.list ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug/

#do the collector!
#cd ~/PREX/prompt/collector
#~/PREX/prompt/collector/do_agg_slug.sh $slug

#make collector plots
cd ~/PREX/prompt/collector
./collector -d ../results/ -l run_list/slug${slug}.list 
./aggregate
cp -f ./plots/aggregate_maindet_slug${slug}.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug/

#make postpan plots
cd ~/PREX/prompt/collector/drawPostpan/
root -l -b -q drawPostPan.C'("~/PREX/prompt/collector/rootfiles/prexPrompt_slug'$slug'.root","slug'$slug'","list.txt")'
cp -f y_*slug${slug}.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug/
cp -f o_*slug${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug/

#do the hadd'ing!
cd ~/PREX/prompt/Aggregator/drawPostpan/
~/PREX/prompt/Aggregator/drawPostpan/accumulate_mini_aggFiles_list.sh slug$slug

if [ ! -d /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug ]
then
    mkdir /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug
fi

if [ -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/grand_aggregator.root ]
then
    rm -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/grand_aggregator.root
fi

#make aggregator plots!
cd /chafs2/work1/apar/japan-aggregator/rootScripts/aggregator/drawPostpan
#root -l -b -q copytree_auto.C'('$slug')'
#cp -f plots/grand_prototype.root /chafs2/work1/apar/aggRootfiles/slugRootfiles/grand_aggregator.root
#export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile
rm grand_aggregator.root
export CAM_OUTPUTDIR=./
root -l -b -q plotAgg.C'("aggRootfiles/slugRootfiles/minirun_slug","plots/summary_minirun_slug", '$slug', '$ihwp', '$wien', '$hrs')'
cp -f plots/summary_minirun_slug${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
cp -f plots/summary_minirun_slug${slug}.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/
cp -f plots/summary_minirun_slug_linear${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug${slug}/

#make grand agg plots!
#root -l -b -q grandAgg.C'("/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile/grand_aggregator.root","~/PREX/prompt/hallaweb_online/slug/slug_list/slug'$slug'/grand_26-'$slug'")'

cd $forgetmenot

source /apps/root/5.34.36/setroot_CUE.bash

#make charge monitor plots!
cp -f ~/pvdb/prex/examples/acc_charge.py ./

python acc_charge.py --list ~/PREX/prompt/collector/run_list/slug${slug}.list
root -b -q /adaqfs/home/apar/pvdb/prex/examples/DrawChargeMon.C
mv -f ./charge_mon.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug/slug_charge_mon.pdf
rm out.txt

python acc_charge.py --run=3103-`cat ~/PREX/prompt/collector/run_list/slug${slug}.list | tail -1`
root -b -q /adaqfs/home/apar/pvdb/prex/examples/DrawChargeMon.C
mv -f ./charge_mon.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug/total_charge_mon.pdf
rm out.txt

rm acc_charge.py

