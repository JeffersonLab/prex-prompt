#!/bin/bash

cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt
source PVDB/environment.sh
cd -

export ROOTSYS=/u/apps/root/6.18.04/root
export PATH=${ROOTSYS}/bin:${PATH}
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

export POSTPAN_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin1/postpan_respin/
export LRB_ROOTFILES=/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/LRBoutput/
export QW_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin1/japanOutput/

#export CAM_TYPE="ErrorFlag_dit_runwise_1X" # FIXME runwise is true, but lets leave it out for now
export CAM_TYPE="ErrorFlag_dit_run_avg_eigenvectors_sorted_part_avg_1X"
export CAM_CONFIG="input_CREX_respin1_mulc_bmod_run_avg_eigenvectors_sorted_seg_avg_1X.txt" # The _bmod version uses the CorrectTreeFast.C outputs, not JAPAN native
export CAM_CUT="Default"
export CAM_OUTPUTDIR=/lustre19/expphy/volatile/halla/parity/crex-respin1/aggRootfiles/ErrorFlag_dit_1X_part_avg
#export CAM_OUTPUTDIR=/lustre19/expphy/volatile/halla/parity/crex-respin1/aggRootfiles/ErrorFlag_dit_runwise_1X # FIXME Runwise is true, but lets leave that out for now
export JAPAN_DIR=/u/group/halla/parity/software/japan_offline/aggregator

export CAM_PLOTSDIR=/lustre19/expphy/volatile/halla/parity/crex-respin1/ifarm_plots/
#export CAM_PLOTSDIR=/u/group/prex/analysis/www/crex/agg-respin1

export DITHERING_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/DitherCorrection
export DITHERING_ROOTFILES_SLOPES=/lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/BMODextractor/
# The ${DITHERING_STUB} name is used in subsequent scripts to ammend the default "dithering" name
#export DITHERING_STUB="_run_avg_1X" # FIXME run_avg is true for this analysis... but lets leave that out for now
export DITHERING_STUB="_run_avg_eigenvectors_sorted_part_avg_1X"
