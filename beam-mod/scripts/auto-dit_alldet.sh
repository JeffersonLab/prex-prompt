
run_number=$1;
root -b -q 'japan_plot_beammod_quartz_cyc_prompt.C('$run_number')';
root -b -q 'japan_plot_beammod_BPMS_cyc_prompt.C('$run_number')';
root -b -q 'japan_plot_beammod_at_cyc.C('$run_number')';
root -b -q 'invertMatrix_alldet.C('$run_number')';
