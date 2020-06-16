# Making grand plots: 

## adaq computer settings
source ~/PREX/setup_japan.sh
export JAPAN_DIR=~/PREX/japan
export CAM_TYPE=""
export CAM_CONFIG="input.txt"
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/${CAM_TYPE}


# Making agg-outputs:

## adaq computer settings 
export RCDB_CONNECTION=mysql://rcdb@hallcdb.jlab.org:3306/a-rcdb
export ROOTSYS=/adaqfs/apps/ROOT/6.16-00
export PATH="${ROOTSYS}/bin:${PATH}"
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/
export POSTPAN_ROOTFILES=/chafs2/work1/apar/postpan-outputs/
export LRB_ROOTFILES=/chafs2/work1/apar/LRBoutput/
