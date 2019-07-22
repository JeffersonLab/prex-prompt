
run_number=$1;
root -b -q 'japan_plot_beammod_quartz_cyc.C('$run_number')';
root -b -q 'japan_plot_beammod_BPMS_cyc.C('$run_number')';
root -b -q 'invertMatrix_maindet.C('$run_number')';
