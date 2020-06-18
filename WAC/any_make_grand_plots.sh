#!/bin/bash

# This script simplifies the producion of plots for a given slug. It runs the scripts to create plots, and copies them to the online directory.

slugfile=${1}
if [ "$#" -eq 0 ]; then
  echo ""
  echo "WAC's Aggregator slug and grand plotter"
  echo ""
  echo "Usage, 1 mandatory, 2 optional inputs: "
  echo "    ./any_make_grand_plots.sh in1 [in2 in3]"
  echo "        in1 = [path/to/slug###.list]"
  echo "        in2 (optional) = [path/to/configs/config_name.sh (script to be sourced for environment setup)] "
  echo "        in3 (optional) = [starting point slug number, -1 will utilize text file for output name base, else auto-selected]"
  exit 
fi
if [[ "$slugfile" != *".list"* && "$slugfile" != *".txt"* ]]; then
  echo "Must pass a run list .txt or .list file as input"
  exit
fi
startingpoint=-1
source ${2}
nameType=${CAM_TYPE} 
nameType_="${CAM_TYPE}_"
if [[ ${CAM_TYPE} == "" ]]; then
  nameType_=""
fi
if [ "$#" -eq 1 ]; then
  source configs/prompt_regression.sh
  nameType=""
  nameType_=""
fi
#source ~/PREX/setup_japan.sh


forgetmenot=`pwd`

firstrun=999999
lastrun=0

input="$slugfile"
while IFS= read -r line
do
  if [[ "$line" -eq "" ]]
  then 
    echo "Error, don't use empty lines in run list file"
    exit
  fi
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
#if wien1 == nothing then define it as the right thing -> also check slug number

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
wienstring="$wien1"

if [ $ihwpstring == "IN" ]
then
    ihwp=1
fi

if [ $ihwpstring == "OUT" ]
then
    ihwp=2
fi

if [ "$wienstring" == "FLIP-RIGHT" ]
then
    wien=1
fi

if [ "$wienstring" == "FLIP-LEFT" ]
then
    wien=2
fi

workingFolder=""
if [[ "${CAM_PLOTSDIR}" == "" ]] ; then
  if [ "$slug" -lt 100 ]; then
    # PREX Case
    startingpoint=0
    workingFolder=/u/group/prex/analysis/www/prex/agg-respin2
  elif [ "$slug" -lt 300 ]; then
    # CREX Case
    startingpoint=100;
    workingFolder=/u/group/prex/analysis/www/crex/agg-respin1
  elif [ "$slug" -lt 550 ]; then
    # PREX AT Case
    startingpoint=500;
    workingFolder=/u/group/prex/analysis/www/prex/agg-respin2
  elif [ "$slug" -lt 4050 ]; then
    # CREX AT Case
    startingpoint=4000;
    workingFolder=/u/group/prex/analysis/www/crex/agg-respin1
  fi
fi
# If user wants to specify the starting point, or lack of starting point for text file usage scenario (arg ${3} == -1):
if [ "$#" -eq 3 ]; then
  startingpoint=${3}
fi

if [ $startingpoint -gt $slug ]; then
  echo "starting slug number: $startingpoint larger than slug number: $slug"
  exit 1
fi

./auto_slug_list.sh $slug

# Prompt charge plots
if [[ "$nameType" == "" ]]; then
  # Default online prompt case
  cd ~/PREX/prompt/
  ./get_charge.sh 5408-${lastrun} 0
  #convert charge_mon.pdf -trim +repage charge_mon.png
  cp --force charge_plots/charge_mon.pdf ${plotFolder}/charge_mon.pdf
  cp --force charge_plots/charge_mon.pdf ${workingFolder}/charge/slugs/charge_mon_integrated_slug${slug}.pdf
  ./get_charge.sh ${firstrun}-${lastrun} 0
  #convert charge_mon.pdf -trim +repage charge_mon.png
  cp --force charge_plots/charge_mon.pdf ${plotFolder}/charge_mon_slug${slug}.pdf
  cp --force charge_plots/charge_mon.pdf ${workingFolder}/charge/slugs/charge_mon_slug${slug}.pdf
  cd $forgetmenot
fi

if [ ! -d ${workingFolder}/${nameType_}slug ]; then
  mkdir ${workingFolder}/${nameType_}slug
fi
if [ ! -d ${workingFolder}/${nameType_}slug/slug_list ]; then
  mkdir ${workingFolder}/${nameType_}slug/slug_list
fi
if [ ! -d ${workingFolder}/${nameType_}slug/slug_list/slug${slug} ]; then
  mkdir ${workingFolder}/${nameType_}slug/slug_list/slug${slug}
fi

plotFolder=${workingFolder}/${nameType_}slug/slug_list/slug${slug}
aggFolder=${CAM_OUTPUTDIR}
if [[ "${CAM_OUTPUTDIR}" != *"${CAM_TYPE}"* ]]; then
  # Case where outputdir wasn't defined correctly, fix it here
  aggFolder=${CAM_OUTPUTDIR}/${nameType}
fi

cp --force $slugfile ${plotFolder}/
if [ ! -d ${aggFolder}/slugRootfiles ] ;
then
    mkdir ${aggFolder}/slugRootfiles
fi
if [ ! -d ${aggFolder}/slugRootfiles/grandRootfile ] ;
then
    mkdir ${aggFolder}/slugRootfiles/grandRootfile
fi
if [ ! -d ${aggFolder}/slugRootfiles/grandRootfile_$slug ] ;
then
    mkdir ${aggFolder}/slugRootfiles/grandRootfile_$slug
fi

${JAPAN_DIR}/rootScripts/merger/smartHadd_miniruns_any_regression.sh `readlink -f ${slugfile}` minirun_slug${slug}.root ${aggFolder}

#~/PREX/prompt/agg-scripts/agg_prompt_list.sh ~/PREX/prompt/agg-scripts/run_list/slug${slug}.list
#sleep 900
#~/PREX/prompt/Aggregator/drawPostpan/accumulate_mini_aggFiles_list.sh slug$slug

#make aggregator plots!
#cd /chafs2/work1/apar/japan-aggregator/rootScripts/aggregator/drawPostpan
cd ${JAPAN_DIR}/rootScripts/aggregator/drawPostpan

rm -f ${aggFolder}/slugRootfiles/grandRootfile_$slug/grand_aggregator.root
# NEW Output directory for plot making
export CAM_OUTPUTDIR=${aggFolder}/slugRootfiles/grandRootfile_$slug/
root -l -b -q plotAgg.C'("'${aggFolder}'/slugRootfiles/minirun_slug","plots/summary_minirun_slug", '$slug', '$ihwp', '$wien', '$hrs')'
cp -f plots/summary_minirun_slug${slug}.txt ${plotFolder}/
cp -f plots/summary_minirun_slug${slug}.pdf ${plotFolder}/
cp -f plots/summary_minirun_slug_linear${slug}.txt ${plotFolder}/

# Do the blessed dithering alpha/delta plots for the slug
if [[ "$nameType" == "" ]]; then
  # Default online prompt case
  ~/PREX/prompt/agg-scripts/dither_slug_plots.sh ${slug}
fi

name="${startingpoint}-${slug}"
if [ $startingpoint -ge 0 ];
then
  [ -f ${forgetmenot}/grand_slug_plot_list.txt ] && rm -f ${forgetmenot}/grand_slug_plot_list.txt
  # ignore 105
  for (( i=$startingpoint; i<=$slug; i++ )); do
    [ "$i" -ne 105 ] && [ "$i" -ne 117 ] && echo $i >> ${forgetmenot}/grand_slug_plot_list.txt
  done
else
  # Pass starting point < 0 to use a local text file to pass in the name
  name="`cat ${forgetmenot}/grand_slug_plot_name.txt`"
fi
#make grand agg plots!
${JAPAN_DIR}/rootScripts/merger/smartHadd_slug_any_regression.sh ${forgetmenot}/grand_slug_plot_list.txt $name ${aggFolder}
root -l -b -q grandAgg.C'("'${aggFolder}'/slugRootfiles/grandRootfile/grand_'${name}'.root","'${plotFolder}'/grand_'${name}'",0)'
root -l -b -q grandAgg.C'("'${aggFolder}'/slugRootfiles/grandRootfile/grand_'${name}'.root","'${plotFolder}'/grand_signed_'${name}'",1)'

cp --force ${CAM_OUTPUTDIR}/grand_aggregator.root ${plotFolder}/

cd $forgetmenot

