#!/bin/bash

./any_aggregator.sh $1 configs/prex_ErrorFlag.sh
./any_aggregator.sh $1 configs/prex_IncludeBMOD.sh
./any_aggregator.sh $1 configs/prex_OnlyBMOD.sh
