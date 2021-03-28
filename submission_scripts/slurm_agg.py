#!/apps/python/PRO/bin/python
from subprocess import call
import subprocess
import sys,os,time
import argparse
import pandas as pd
import numpy as np


parser = argparse.ArgumentParser(description="Submit array jobs using slurm scheduler for PREX-II aggregator analysis.")

parser.add_argument("-o", dest="out", action="store", required=True, help = "Enter location of output rootfiles for this respin")
#parser.add_argument("-w", dest="web", action="store", required=True, help = "Enter location of web directory for plots")
parser.add_argument("-t", dest="tmp", action="store", required=True, help = "Enter location where the slurm error logs will be written")
parser.add_argument("-n", dest="name", action="store", required=False, default="respin1", help= "Enter job name")
parser.add_argument("-j", dest="jsub", action="store", required=True, help ="Enter location to write the job submission script")
parser.add_argument("-p", dest="prompt", action="store", required=False, default="/u/group/halla/parity/software/japan_offline/prompt/prex-prompt", help= "Enter location of prompt directory")
parser.add_argument("-l", dest="runlist", action="store", required=True, help= "Give location of runlist to process")
parser.add_argument("--time", dest="time", action="store", required=False, default="2:00:00", help="Enter the wall time requested. Default is set to 2:00:00.")
args=parser.parse_args()

df_run=pd.read_csv(os.path.realpath(args.runlist), header=None)
runlist=(df_run.iloc[:,0]).tolist()
runs=",".join(map(str,runlist))

print(runs)
print("\n")


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
for i in range(0, len(runlist)):     
     jsubf.write("RUN["+str(i)+"]="+str(runlist[i])+"\n")
jsubf.write("export QW_ROOTFILES=\""+os.path.realpath(args.out)+"\" \n")
#jsubf.write("export WEB_DIR=\""+os.path.realpath(args.web)+"\" \n")
jsubf.write("echo \"Set up these environment variables:\"\n")
jsubf.write("echo \"QW_ROOTFILES = $QW_ROOTFILES\"\n")
jsubf.write("cd "+os.path.realpath(args.prompt)+"\n")
jsubf.write("source /site/12gev_phys/softenv.sh 2.3\n")
jsubf.write(args.prompt+"/respin_agg.sh ${RUN[${SLURM_ARRAY_TASK_ID}-1]}\n")

jsubf.close()


#os.system("sbatch --array=1-"+str(len(runlist))+" "+args.jsub+"/"+args.name+".sh")

