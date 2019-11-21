#! /bin/sh
slug=$1
ihwp=$2
wien=$3
hrs=$4

#The first parameter points to location of accumulated minirun files.
#The second parameter points to location of output plots and text file.
#The third parameter is the slug number and needs to be entered by user.
#Enter ihwp = 1 for in, 2 for out
#Enter wein = 1 for right, 2 for left
#Enter hrs = 0 for both, 1 for right only, 2 for left only

forgetmenot=`pwd`

if [ ! -d /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug ]
then
    mkdir /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug
fi

if [ -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/grand_aggregator.root ]
then
    rm -f /chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug/grand_aggregator.root
fi

cd /chafs2/work1/apar/japan-aggregator/rootScripts/aggregator/drawPostpan
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/slugRootfiles/grandRootfile_$slug
root -l -b -q plotAgg.C'("aggRootfiles/slugRootfiles/minirun_slug","plots/summary_minirun_slug", '$slug', '$ihwp', '$wien', '$hrs')'
cp -f plots/summary_minirun_slug${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug
cp -f plots/summary_minirun_slug${slug}.pdf ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug
cp -f plots/summary_minirun_slug_linear${slug}.txt ~/PREX/prompt/hallaweb_online/slug/slug_list/slug$slug

cd $forgetmenot
