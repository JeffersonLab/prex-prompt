#!/bin/tcsh

# Ifarm needs this
#source PVDB/environment.sh
#export ROOTSYS=/u/apps/root/6.18.04/root
#export PATH=${ROOTSYS}/bin:${PATH}
#export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

# Adaq computers need this
source ~/PREX/setup_japan.sh
export RCDB_CONNECTION=mysql://rcdb@hallcdb.jlab.org:3306/a-rcdb
export ROOTSYS=/adaqfs/apps/ROOT/6.16-00
export PATH="${ROOTSYS}/bin:${PATH}"
export LD_LIBRARY_PATH="${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

# Aggregator script needs these
export POSTPAN_ROOTFILES=/lustre/expphy/volatile/halla/parity/prex-respin2/postpan_respin/
export LRB_ROOTFILES=/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/LRBoutput/
export QW_ROOTFILES=/lustre/expphy/volatile/halla/parity/prex-respin2/japanOutput/

# Name of aggregator and plots output sub-folder
export CAM_TYPE="IncludeBMOD"
# Aggregator script's input device list (unneeded for the grand plots)
export CAM_CONFIG="input_PREX_respin2_mulc.txt"
# Aggregator script's cut type (unneeded for the grand plots)
export CAM_CUT="IncludeBMOD" # "IncludeBMOD", "BMODonly" and "Burp" are alternate options
# Aggregator script's output destination - note you could replace "IncludeBMOD" with ${CAM_TYPE} if you are feeling efficient
export CAM_OUTPUTDIR=/lustre/expphy/volatile/halla/parity/prex-respin2/aggRootfiles/IncludeBMOD
# The install directory for finding the merger and aggregator scripts, can be any July 1st 2020 or onward copy or branch based off of develop or operations.
export JAPAN_DIR=/u/group/halla/parity/software/japan_offline/aggregator

# Stub folder for ${CAM_TYPE} plot folders to be placed in
export CAM_PLOTSDIR=/u/group/prex/analysis/www/prex2/agg-respin2
