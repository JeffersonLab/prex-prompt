#!/bin/tcsh

source PVDB/environment.sh

export ROOTSYS=/u/apps/root/6.18.04/root
export PATH=${ROOTSYS}/bin:${PATH}
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

export POSTPAN_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin1/postpan_respin/
export LRB_ROOTFILES=/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/LRBoutput/
export QW_ROOTFILES=/lustre19/expphy/volatile/halla/parity/crex-respin1/japanOutput/

export CAM_TYPE="ErrorFlag"
export CAM_CONFIG="input_CREX_respin1_mulc.txt"
export CAM_CUT="Default"
export CAM_OUTPUTDIR=/lustre19/expphy/volatile/halla/parity/crex-respin1/aggRootfiles/ErrorFlag
export JAPAN_DIR=/u/group/halla/parity/software/japan_offline/aggregator

export CAM_PLOTSDIR=/u/group/prex/analysis/www/crex/agg-respin1
