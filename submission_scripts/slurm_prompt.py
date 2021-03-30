#!/apps/python/PRO/bin/python
from subprocess import call
import subprocess
import sys,os,time
import argparse
import pandas as pd
import numpy as np

parser = argparse.ArgumentParser(description="Submit array jobs using slurm scheduler for PREX-II transverse running")

parser.add_argument("-s", dest="src", action="store", required=False, default="/mss/halla/parity/raw", help = "Enter location of raw root files")
parser.add_argument("-o", dest="out", action="store", required=True, help = "Enter location of output rootfiles for this respin")
parser.add_argument("-w", dest="web", action="store", required=True, help = "Enter location of web directory for plots")
parser.add_argument("-t", dest="tmp", action="store", required=True, help = "Enter location where the slurm error logs will be written")
parser.add_argument("-n", dest="name", action="store", required=False, default="respin1", help= "Enter job name")
parser.add_argument("-j", dest="jsub", action="store", required=True, help ="Enter location to write the job submission script")
parser.add_argument("-p", dest="prompt", action="store", required=False, default="/u/group/halla/parity/software/japan_offline/prompt/prex-prompt", help= "Enter location of prompt directory")
parser.add_argument("-l", dest="runlist", action="store", required=True, help= "Give location of runlist to process")
parser.add_argument("--time", dest="time", action="store", required=False, default="24:00:00", help="Enter the wall time requested. Default is set to 24:00:00.")
args=parser.parse_args()

df_run=pd.read_csv(os.path.realpath(args.runlist), header=None)
runlist=(df_run.iloc[:,0]).tolist()
runs=",".join(map(str,runlist))
armflaglist=(df_run.iloc[:,2]).tolist()
armflags=",".join(map(str, armflaglist))
armname={}
armname["ALL_PREX"]="ALL"
armname["CH_LHRS"]="CH_LHRS"
armname["ALLminusR"]="ALL"
armname["INJ"]="INJ"
armname["CH_INJ"]="CH_INJ"

print(runs)
print("\n")
print(armflags)


if not os.path.exists(args.out):
     os.system("mkdir -p "+args.out)
if not os.path.exists(args.tmp):
     os.system("mkdir -p "+args.tmp)
if not os.path.exists(args.jsub):
     os.system("mkdir -p "+args.jsub)
if not os.path.exists(args.web):
     os.system("mkdir -p "+args.web)


jsubf=open(args.jsub+"/"+args.name+".sh", "w")
jsubf.write("#!/bin/bash\n")
jsubf.write("#SBATCH --account=halla\n")
jsubf.write("#SBATCH --partition=production\n")
jsubf.write("#SBATCH --job-name="+args.name+"\n")
jsubf.write("#SBATCH --time="+args.time+"\n")
jsubf.write("#SBATCH --nodes=1\n")
jsubf.write("#SBATCH --ntasks=1\n")
jsubf.write("#SBATCH --cpus-per-task=1\n")
jsubf.write("#SBATCH --mem=4G\n")
jsubf.write("#SBATCH --output="+args.tmp+"/"+args.name+"_%A_%a.out\n")
jsubf.write("#SBATCH --error="+args.tmp+"/"+args.name+"_%A_%a.err\n")
for i in range(0, len(runlist)):     # Ugly hack. This won't be necessary if admin allows slurm task id >1000.
     jsubf.write("RUN["+str(i)+"]="+str(runlist[i])+"\n")
     jsubf.write("ARM["+str(i)+"]="+str(armname[armflaglist[i]])+"\n")
jsubf.write("export QW_DATA=\""+os.path.realpath("/scratch")+"\"\n")
jsubf.write("cd $QW_DATA\n")
jsubf.write("echo \"Started copying file\"\n")
jsubf.write("export split_no=$(ls /mss/halla/parity/raw/parity_${ARM[${SLURM_ARRAY_TASK_ID}-1]}_${RUN[${SLURM_ARRAY_TASK_ID}-1]}.dat.* | sort -t'.' -n -k3 | tail -n 1 | awk -F. '{print $3}')\n")
jsubf.write("export i=0\n")
jsubf.write("while [ $i -le $split_no ]\n")
jsubf.write("do\n")
jsubf.write(" jget "+args.src+"/parity_${ARM[${SLURM_ARRAY_TASK_ID}-1]}_${RUN[${SLURM_ARRAY_TASK_ID}-1]}.dat.$i \n")
jsubf.write(" i=$[$i+1]\n")
jsubf.write("done\n")
jsubf.write("ls -lh *${RUN[${SLURM_ARRAY_TASK_ID}-1]}.dat*\n")
jsubf.write("export PREX_PLOT_DIR=\"$QW_DATA/tmp\"\n")
jsubf.write("export QW_PRMINPUT=\""+os.path.realpath(args.prompt)+"/Parity/prminput\" \n")
jsubf.write("export QW_ROOTFILES=\""+os.path.realpath(args.out)+"\" \n")
jsubf.write("export WEB_DIR=\""+os.path.realpath(args.web)+"\" \n")
jsubf.write("echo \"Set up these environment variables:\"\n")
jsubf.write("echo \"QW_DATA = $QW_DATA\"\n")
jsubf.write("echo \"QW_PRMINPUT = $QW_PRMINPUT\"\n")
jsubf.write("echo \"QW_ROOTFILES = $QW_ROOTFILES\"\n")
jsubf.write("echo \"PREX_PLOT_DIR = $PREX_PLOT_DIR\"\n")
jsubf.write("echo \"WEB_DIR = $WEB_DIR\"\n")

jsubf.write("cd "+os.path.realpath(args.prompt)+"\n")
jsubf.write("source /site/12gev_phys/softenv.sh 2.3\n")
jsubf.write(args.prompt+"/prompt_chainrootfile_test.sh ${RUN[${SLURM_ARRAY_TASK_ID}-1]}\n")

jsubf.close()


os.system("sbatch --array=1-"+str(len(runlist))+" "+args.jsub+"/"+args.name+".sh")
