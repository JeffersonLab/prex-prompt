#!/bin/tcsh

source PVDB/environment.csh

setenv ROOTSYS /u/apps/root/6.18.04/root
setenv PATH ${ROOTSYS}/bin:${PATH}
setenv LD_LIBRARY_PATH "${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

setenv POSTPAN_ROOTFILES /lustre19/expphy/volatile/halla/parity/prex-respin2/postpan_respin/
setenv LRB_ROOTFILES /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/LRBoutput/
setenv QW_ROOTFILES /lustre19/expphy/volatile/halla/parity/prex-respin2/japanOutput/

setenv CAM_TYPE "ErrorFlag"
setenv CAM_CONFIG "input_PREX_respin2.txt"
setenv CAM_CUT "Default"
setenv CAM_OUTPUTDIR /lustre19/expphy/volatile/halla/parity/prex-respin2/aggRootfiles/ErrorFlag
setenv JAPAN_DIR /u/group/halla/parity/software/japan_offline/aggregator

