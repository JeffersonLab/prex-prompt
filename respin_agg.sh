#!/bin/bash

echo -e "\n\n\n\n\n    Starting respin_agg.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting respin_agg.sh\n\n\n\n\n";
# FIXME FIXME the input_CREX_respin2_mulc.txt input list does not include intelligent selection of data from eigenvector tree or from default BMOD in the mulc_dit tree, or any new AT combo detectors.
./any_aggregator.sh $1 configs/crex_respin2_ErrorFlag.sh
./any_aggregator.sh $1 configs/crex_respin2_IncludeBMOD.sh
./any_aggregator.sh $1 configs/crex_respin2_OnlyBMOD.sh
