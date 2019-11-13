#!/apps/python/PRO/bin/python
from subprocess import call
import sys,os,time

def main():
    
    _email="rradloff@jlab.org"
    _mssdir="/mss/halla/parity/raw"
    _source="/u/group/halla/parity/software/japan_offline/prompt/prex-prompt_merge/prex-prompt"
    _directory="/lustre/expphy/cache/halla/parity/raw"
    _rootout="/lustre/expphy/volatile/halla/parity/japanOutput"
    _nrStart=3900
    _nrStop=3905
    submit=1
    useSWIF=1 #0: uses jsub 1: uses SWIF+jsub
    
    _workflowID="Prompt_"+str(_nrStart)+"_"+str(_nrStop)

    createXMLfile(_mssdir,_source,_rootout,_nrStart,_nrStop,_email,_workflowID)

    if submit==1:
        if useSWIF==1:
            print "Submitting japan prompt analysis for runs "+str(_nrStart)+" to "+str(_nrStop)+" using designated SWIF workflow "+str(_workflowID)
            call(["swif","add-jsub","-workflow",str(_workflowID),"-create","-script",_rootout+"/"+_workflowID+".xml"])
        elif useSWIF==0:
            print "submitting position sampled with id between ",_nrStart,_nrStop
            call(["jsub","-xml",_directory+"/"+_workflowID+".xml"])
    else:
        print "NOT submitting position sampled with id between ",_nrStart,_nrStop
        
    print "I am all done"


def createXMLfile(mssdir,source,rootout,nStart,nStop,email,workflowID):

    f=open(rootout+"/"+workflowID+".xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"prex\"/>\n")
    f.write("  <Track name=\"debug\"/>\n")
#    f.write("  <Track name=\"simulation\"/>\n")
#    f.write("  <Command><![CDATA[\n")
#    f.write("    "+source+"/prompt/prex-prompt/qwparity\n")
#    f.write("  ]]></Command>\n")
    f.write("  <Name name=\""+workflowID+"\"/>\n")
    f.write("  <OS name=\"centos7\"/>\n")
    f.write("  <Memory space=\"2000\" unit=\"MB\"/>\n")

    for nr in range(nStart,nStop): # repeat for nr jobs
        f.write("  <Job>\n")
        datName="mss:"+mssdir+"/"+"parity_ALL"+"_%04d"%(nr)+".dat.0"
        f.write("    <Input src=\""+datName+"\" dest=\"parity_ALL"+"_%04d"%(nr)+".dat.0\"/>\n")
        f.write("    <Command><![CDATA[\n")
        f.write("    echo \"Setting the current directory to QW_DATA.\"\n")
        f.write("    setenv QW_DATA `pwd`\n")
        f.write("    setenv PREX_PLOT_DIR `pwd`/tmp \n")
        f.write("    cd "+source+"\n")
        f.write("    echo \"Switching to the prompt directory.\"\n")
        f.write("    setenv QW_PRMINPUT "+source+"/Parity/prminput\n")
        f.write("    setenv QW_ROOTFILES "+rootout+"\n")
#        f.write("    cd $QW_DATA\n")
#        f.write("    alias convert "+source+"/convert\n")
        f.write("    echo \"Set up these environment variables:\"\n")
        f.write("    echo \"QW_DATA = $QW_DATA\"\n")
        f.write("    echo \"QW_PRMINPUT = $QW_PRMINPUT\"\n")
        f.write("    echo \"QW_ROOTFILES = $QW_ROOTFILES\"\n")
        f.write("    echo \"PREX_PLOT_DIR = $PREX_PLOT_DIR\"\n")
#        f.write("    echo \"alias convert "+source+"/convert\"\n\n")
        f.write("    "+source+"/prompt.sh "+str(nr)+"\n")
        f.write("    ]]></Command>\n")
        f.write("    <Stdout dest=\""+source+"/LogFiles/ifarmlog"+"_%04d"%(nr)+".out\"/>\n")
        f.write("    <Stderr dest=\""+source+"/LogFiles/ifarmlog"+"_%04d"%(nr)+".err\"/>\n")
        f.write("  </Job>\n\n")

    f.write("</Request>\n")
    f.close()
    return 0

                    
if __name__ == '__main__':
    main()
                            
