# Making grand plots: 

## adaq computer settings
source ~/PREX/setup_japan.sh
export JAPAN_DIR=~/cameronc/analyses/ifarm-aggregator/japan-ifarm-aggregator
export CAM_PLOTSDIR=/u/group/prex/analysis/www/prex2/agg-respin2
# CHANGE THIS
export CAM_TYPE="test"


# Aggregator needed stuff
# The ${CAM_TYPE} name is used in subsequent scripts to ammend the ${CAM_OUTPUTDIR} path for convenience
export CAM_OUTPUTDIR=/chafs2/work1/apar/aggRootfiles/${CAM_TYPE}
# CHANGE THIS
export CAM_CONFIG="input.txt"


# Making agg-outputs:

## adaq computer settings 
export RCDB_CONNECTION=mysql://rcdb@hallcdb.jlab.org:3306/a-rcdb

export ROOTSYS=/adaqfs/apps/ROOT/6.16-00
export PATH="${ROOTSYS}/bin:${PATH}"
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"
export POSTPAN_ROOTFILES=/chafs2/work1/apar/postpan-outputs/
export LRB_ROOTFILES=/chafs2/work1/apar/LRBoutput/
# CHANGE THIS
export CAM_CUT="Default"

# CHANGE THIS for Dithering
export DITHERING_ROOTFILES=/chafs2/work1/apar/DitherCorrection/
export DITHERING_ROOTFILES_SLOPES=/chafs2/work1/apar/BMODextractor/
### The ${DITHERING_STUB} name is used in subsequent scripts to ammend the default "dithering" name
export DITHERING_STUB="_test"
