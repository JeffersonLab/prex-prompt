#! /bin/sh

run_num=$1;

echo -e "\n\n\n\n\n    Starting auto_beammod.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting auto_beammod.sh\n\n\n\n\n";

if [ -z "$run_num" ] 
then
    echo "Run Number is empty";
    >&2 echo "Run Number is empty";
    exit 1;
fi    


if  [ $(($run_num)) -ge  3130 ] && [ $(($run_num)) -le  3403 ]
then
    root -b -q '$PROMPT_DIR/beam-mod/scripts/japan_plot_beammod_BPMS_cyc_12X.C('$run_num')';
fi
if  [ $(($run_num)) -ge  3404 ] && [ $(($run_num)) -le  4980 ]
then
    root -b -q '$PROMPT_DIR/beam-mod/scripts/japan_plot_beammod_BPMS_cyc_prompt.C('$run_num')';
fi

root -b -q '$PROMPT_DIR/beam-mod/scripts/japan_plot_beammod_quartz_cyc_prompt.C('$run_num')';

if  [ $(($run_num)) -ge  3803 ]
then
    root -b -q '$PROMPT_DIR/beam-mod/scripts/japan_plot_beammod_at_cyc_prompt.C('$run_num')';
fi

if  [ $(($run_num)) -ge  3130 ] && [ $(($run_num)) -le  3403 ]
then
    root -b -q '$PROMPT_DIR/beam-mod/scripts/invertMatrix_alldet.C('$run_num')';
fi
if  [ $(($run_num)) -ge  3404 ] && [ $(($run_num)) -le  4734 ]
then
    root -b -q '$PROMPT_DIR/beam-mod/scripts/invertMatrix_alldet_1346.C('$run_num')';
fi
if  [ $(($run_num)) -ge  4735 ] && [ $(($run_num)) -le  4980 ]
then
    root -b -q '$PROMPT_DIR/beam-mod/scripts/invertMatrix_alldet_3546.C('$run_num')';
fi
