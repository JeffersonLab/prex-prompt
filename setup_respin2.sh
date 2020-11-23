setenv PATH `echo $PATH | sed 's/:/\n/g' | grep -v "5.34.36" |grep -v ROOT | awk 'NR==1{printf"%s",$1}; NR>1{printf":%s",$1}'`
setenv LD_LIBRARY_PATH `echo $LD_LIBRARY_PATH | sed 's/:/\n/g' | grep -v "5.34.36" | grep -v ROOT | awk 'NR==1{printf"%s",$1}; NR>1{printf":%s",$1}'`

setenv ROOTSYS /site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/root/6.14.04/

setenv PATH "${ROOTSYS}/bin:${PATH}"
setenv LD_LIBRARY_PATH "${ROOTSYS}/lib:${LD_LIBRARY_PATH}"

setenv QW_ROOTFILES /lustre/expphy/volatile/halla/parity/prex-respin2/japanOutput/
setenv QW_DATA /lustre/expphy/cache/halla/parity/raw/
setenv QW_PRMINPUT /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/Parity/prminput/
