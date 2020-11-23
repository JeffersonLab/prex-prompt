#!/apps/python/PRO/bin/python
from subprocess import call
import subprocess
import sys,os,time

def main():
    
    _email="cameronc@jlab.org"
    _mssdir="/mss/halla/parity/raw"
    _source="/u/group/halla/parity/software/japan_offline/prompt/prex-prompt"
    _directory="/lustre/expphy/cache/halla/parity/raw"
    _rootout="/lustre19/expphy/volatile/halla/parity/prex-respin2/japanOutput/"
    _nrStart=3349
    _nrStop=4872
    submit=1
    useSWIF=1 #0: uses jsub 1: uses SWIF+jsub

    firstrun=9999
    lastrun=1
    _runlist=[]
    #runfile=open(_source+"/prex-runlist/simple_list/test.list","r")
    runfile=open(_source+"/prex-runlist/simple_list/failed_agg_runs.list","r")
    #runfile=open(_source+"/prex-runlist/rerun/rerun2_sim.list","r")
    for line in runfile:
        if (len(line) < 4):
            continue
        _runlist.append(int(line))
        if (firstrun >= int(line) and _nrStart <= int(line)):
            firstrun=int(line)
        if (lastrun <= int(line) and _nrStop >= int(line)):
            lastrun=int(line)
    runfile.close()
    
    _workflowID="Aggregator_"+str(firstrun)+"_"+str(lastrun)

    createXMLfile(_source,_rootout,_nrStart,_nrStop,_email,_workflowID,_runlist)

    if submit==1:
        if useSWIF==1:
            print "Submitting japan prompt analysis for runs "+str(firstrun)+" to "+str(lastrun)+" using designated SWIF workflow "+str(_workflowID)
            call(["swif","add-jsub","-workflow",str(_workflowID),"-create","-script",_rootout+"/"+_workflowID+".xml"])
        elif useSWIF==0:
            print "submitting position sampled with id between ",firstrun,lastrun
            call(["jsub","-xml",_directory+"/"+_workflowID+".xml"])
    else:
        print "NOT submitting position sampled with id between ",firstrun,lastrun
        
    print "I am all done"


def createXMLfile(source,rootout,nStart,nStop,email,workflowID,runlist):

    f=open(rootout+"/"+workflowID+".xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"prex\"/>\n")
#    f.write("  <Track name=\"debug\"/>\n")
    f.write("  <Track name=\"analysis\"/>\n")
    f.write("  <Name name=\""+workflowID+"\"/>\n")
    f.write("  <OS name=\"centos7\"/>\n")
    f.write("  <Memory space=\"2000\" unit=\"MB\"/>\n")

    #for nr in range(nStart,nStop+1): # repeat for nr jobs
    #print "    <Stdout dest=\""+source+"/LogFiles/ifarmlog"+"_%04d"%(runlist[0])+".out\"/>\n"
    #print "    <Stderr dest=\""+source+"/LogFiles/ifarmlog"+"_%04d"%(runlist[0])+".err\"/>\n"
    for nr in runlist:
        if (nr < nStart or nr > nStop):
            continue
        f.write("  <Job>\n")
        f.write("    <Command><![CDATA[\n")
        f.write("    cd "+source+"\n")
        f.write("    echo \"Switching to the prompt directory.\"\n")
        f.write("    setenv QW_ROOTFILES "+rootout+"\n")
        f.write("    echo \"Set up these environment variables:\"\n")
        f.write("    echo \"QW_ROOTFILES = $QW_ROOTFILES\"\n")
        f.write("    printenv \n")
        f.write("    "+source+"/respin_agg.sh "+str(nr)+"\n")
        f.write("    ]]></Command>\n")
        f.write("    <Stdout dest=\""+source+"/LogFiles/respinAggregator_ifarmlog"+"_%04d"%(nr)+".out\"/>\n")
        f.write("    <Stderr dest=\""+source+"/LogFiles/respinAggregator_ifarmlog"+"_%04d"%(nr)+".err\"/>\n")
        f.write("  </Job>\n\n")

    f.write("</Request>\n")
    f.close()
    return 0

                    
if __name__ == '__main__':
    main()
                            
