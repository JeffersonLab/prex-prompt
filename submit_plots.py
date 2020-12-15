#!/apps/python/PRO/bin/python
from subprocess import call
import subprocess
import sys,os,time

def main():
    
    _email="rradloff@jlab.org"
    _mssdir="/mss/halla/parity/raw"
    _source="/u/group/halla/parity/software/japan_offline/prompt/prex-prompt"
    _directory="/lustre/expphy/cache/halla/parity/raw"
    _rootout="/lustre/expphy/volatile/halla/parity/crex-respin1/japanOutput/"
    _webout="/u/group/prex/analysis/www/crex/summary_respin1/" #Modify this to port the webplots into a custom directory (Sakib)
    _nrStart=8400
    _nrStop=8404
    submit=1
    useSWIF=1 #0: uses jsub 1: uses SWIF+jsub

    firstrun=9999
    lastrun=0
    _runlist=[]
    _runlist.append(int(_nrStart))
    # runfile=open(_source+"/prex-runlist/simple_list/extra_march9.list","r")
    # runfile=open(_source+"/prex-runlist/good_list/test.list","r")
    #runfile=open(_source+"/prex-runlist/simple_list/extra_feb28.list","r")
    #runfile=open(_source+"/prex-runlist/simple_list/all.list","r")
    runfile=open(_source+"/crex-runlist/simple_list/all_crex.list","r")
    for line in runfile:
        if (len(line) < 4):
            continue
        if int(_nrStart) != int(line):
          _runlist.append(int(line))
        if (firstrun >= int(line) and _nrStart <= int(line)):
          firstrun=int(line)
        if (lastrun <= int(line) and _nrStop >= int(line)):
          lastrun=int(line)
    runfile.close()

    _workflowID="SummaryPlots_"+str(firstrun)+"_"+str(lastrun)

    createXMLfile(_mssdir,_source,_rootout,_webout,_nrStart,_nrStop,_email,_workflowID,_runlist)

    if submit==1:
        if useSWIF==1:
            print "Submitting plots analysis for runs "+str(firstrun)+" to "+str(lastrun)+" using designated SWIF workflow "+str(_workflowID)
            call(["swif","add-jsub","-workflow",str(_workflowID),"-create","-script",_rootout+"/"+_workflowID+".xml"])
        elif useSWIF==0:
            print "submitting position sampled with id between ",firstrun,lastrun
            call(["jsub","-xml",_directory+"/"+_workflowID+".xml"])
        else:
            print "NOT submitting position sampled with id between ",firstrun,lastrun
            
    print "I am all done"


def createXMLfile(mssdir,source,rootout,webout,nStart,nStop,email,workflowID,runlist):

    f=open(rootout+"/"+workflowID+".xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"prex\"/>\n")
    f.write("  <Track name=\"debug\"/>\n")
    #f.write("  <Track name=\"one_pass\"/>\n")
    f.write("  <Name name=\""+workflowID+"\"/>\n")
    f.write("  <OS name=\"centos77\"/>\n")
    f.write("  <Memory space=\"2000\" unit=\"MB\"/>\n")
    f.write("  <TimeLimit time=\"6\" unit=\"hours\"/>\n")

    # for nr in range(nStart,nStop+1): # repeat for nr jobs
    # print "    <Stdout dest=\""+source+"/LogFiles/postpan_ifarmlog"+"_%04d"%(runlist[0])+".out\"/>\n"
    # print "    <Stderr dest=\""+source+"/LogFiles/postpan_ifarmlog"+"_%04d"%(runlist[0])+".err\"/>\n"
    for nr in runlist:
        if (nr < nStart or nr > nStop):
            continue
        f.write("  <Job>\n")
        #cmd = "ls /mss/halla/parity/raw/parity_ALL_"+str(nr)+".dat.* | sort -t'.' -n -k3 | tail -n 1 | awk -F. '{print $3}'"
        #ps = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        #output = ps.communicate()[0]
        # for partfile in range(0,int(output)+1):
        #     datName="mss:"+mssdir+"/"+"parity_ALL"+"_%04d"%(nr)+".dat."+str(partfile)
        # f.write("    <Input src=\""+datName+"\" dest=\"parity_ALL"+"_%04d"%(nr)+".dat."+str(partfile)+"\"/>\n")
        f.write("    <Command><![CDATA[\n")
        f.write("    source /site/12gev_phys/softenv.csh 2.3\n")
        f.write("    echo \"Setting the current directory to QW_DATA.\"\n")
        f.write("    setenv QW_DATA `pwd`\n")
        f.write("    setenv PREX_PLOT_DIR `pwd`/tmp \n")
        f.write("    cd "+source+"\n")
        f.write("    echo \"Switching to the prompt directory.\"\n")
        #f.write("    setenv QW_PRMINPUT "+source+"/Parity/prminput\n")
        f.write("    setenv QW_ROOTFILES "+rootout+"\n")
        f.write("    setenv WEB_DIR      "+webout+"\n")
        f.write("    echo \"Set up these environment variables:\"\n")
        f.write("    echo \"QW_DATA = $QW_DATA\"\n")
        #f.write("    echo \"QW_PRMINPUT = $QW_PRMINPUT\"\n")
        f.write("    echo \"QW_ROOTFILES = $QW_ROOTFILES\"\n")
        f.write("    echo \"PREX_PLOT_DIR = $PREX_PLOT_DIR\"\n")
        f.write("    echo \"WEB_DIR= $WEB_DIR\"\n")
#        f.write("    printenv \n")
        f.write("    "+source+"/prompt_sum.sh "+str(nr)+"; \n")
        f.write("    ]]></Command>\n")
        f.write("    <Stdout dest=\""+source+"/LogFiles/summary_ifarmlog"+"_%04d"%(nr)+".out\"/>\n")
        f.write("    <Stderr dest=\""+source+"/LogFiles/summary_ifarmlog"+"_%04d"%(nr)+".err\"/>\n")
        f.write("  </Job>\n\n")

    f.write("</Request>\n")
    f.close()
    return 0
                    
if __name__ == '__main__':
    main()
