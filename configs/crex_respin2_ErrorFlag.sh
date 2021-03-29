#!/bin/bash

cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt
source PVDB/environment.sh
cd -

export ROOTSYS=/u/apps/root/6.18.04/root
export PATH=${ROOTSYS}/bin:${PATH}
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

export POSTPAN_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin2/postpan_respin/
export LRB_ROOTFILES=/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/LRBoutput/
export QW_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/

export CAM_TYPE="ErrorFlag"
export CAM_CONFIG="input_CREX_respin2_mulc.txt"
export CAM_CUT="Default"
export CAM_OUTPUTDIR=/lustre19/expphy/volatile/halla/parity/crex-respin2/aggRootfiles/ErrorFlag
export JAPAN_DIR=/u/group/halla/parity/software/japan_offline/aggregator

export CAM_PLOTSDIR=/u/group/prex/analysis/www/crex/agg-respin2
export DITHERING_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/DitherCorrection
export DITHERING_ROOTFILES_SLOPES=/lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/BMODextractor/
# The ${DITHERING_STUB} name is used in subsequent scripts to ammend the default "dithering" name
#export DITHERING_STUB="_run_avg_1X" # FIXME run_avg is true for this analysis... but lets leave that out for now
export DITHERING_STUB="_1X"
