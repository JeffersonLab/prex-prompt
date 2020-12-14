#!/bin/bash

echo -e "\n\n\n\n\n    Starting respin_agg.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting respin_agg.sh\n\n\n\n\n";

./any_aggregator.sh $1 configs/crex_ErrorFlag.sh
./any_aggregator.sh $1 configs/crex_IncludeBMOD.sh
./any_aggregator.sh $1 configs/crex_OnlyBMOD.sh
