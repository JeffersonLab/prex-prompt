#!/bin/tcsh

source PVDB/environment.sh

export ROOTSYS=/u/apps/root/6.18.04/root
export PATH=${ROOTSYS}/bin:${PATH}
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

export POSTPAN_ROOTFILES=/lustre19/expphy/volatile/halla/parity/prex-respin2/postpan_respin/
export LRB_ROOTFILES=/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/LRBoutput/
export QW_ROOTFILES=/lustre19/expphy/volatile/halla/parity/prex-respin2/japanOutput/

export CAM_TYPE="OnlyBMOD"
export CAM_CONFIG="input_PREX_respin2_mulc.txt"
export CAM_CUT="OnlyBMOD"
export CAM_OUTPUTDIR=/lustre19/expphy/volatile/halla/parity/prex-respin2/aggRootfiles/OnlyBMOD
export JAPAN_DIR=/u/group/halla/parity/software/japan_offline/aggregator

