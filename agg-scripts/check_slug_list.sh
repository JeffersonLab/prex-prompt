#! /bin/sh
while IFS= read -r line; do
    runnum=$line;
    echo "Checking aggregator files for run $runnum"
done < $1
ROOTFILEDIR="/chafs2/work1/apar/aggRootfiles"

IFS=$'\n' read -d '' -r -a lines < $1
# all lines
echo "Checking all runs: ${lines[@]}"
minirun_lines=()
run_lines=("${lines[@]}")
num_miniruns=0

# Do miniruns
for i in "${!lines[@]}"; do
  run_temp="${ROOTFILEDIR}/run_aggregator_${lines[$i]}.root"
  run_lines[$i]=$run_temp
  shopt -s nullglob
  miniarray=(${ROOTFILEDIR}/minirun_aggregator_${lines[$i]}_*.root)
  shopt -u nullglob
  #"${miniarray[@]}"
  for j in "${!miniarray[@]}"; do
    echo ${miniarray[$j]}
    minirun_lines[$num_miniruns]=${miniarray[$j]}
    let num_miniruns++
    root -l -b -q testAgg.C\(\"${miniarray[$j]}\"\)
  done
  miniarray=()
  minirunlines=()
  root -l -b -q testAgg.C\(\"${run_lines[$i]}\"\)
done
