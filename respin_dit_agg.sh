#!/bin/bash

echo -e "\n\n\n\n\n    Starting respin_agg.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting respin_agg.sh\n\n\n\n\n";

#export QW_ROOTFILES="/lustre19/expphy/volatile/halla/parity/crex-respin1/japanOutput"
export DITHERING_ROOTFILES_SLOPES="/lustre19/expphy/volatile/halla/parity/crex-respin1/bmodOutput/BMODextractor/"
export DITHERING_STUB="_1X" # Hardcoded for now, this does the basic set of BPMs and COILs analysis

# Assumes the slopes file for the whole experiment lives in BMODextractor, and has the correct segmentation information contained
cd WAC/dithering
root -l -b -q "CorrectTreeFast.C($1,\"${DITHERING_STUB}\")"
cd -



# For just aggregation stage this is all that is needed
./any_aggregator.sh $1 configs/crex_ErrorFlag_dit_1X_runwise.sh
