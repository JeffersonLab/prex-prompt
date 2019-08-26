# PREX-II Prompt Analysis

So far, the auto-prompt is running as a background process, checks newly finished DAQ run periodically and launches JAPAN. Therefore only a few people in this world really need to run prompt analysis by hand under certain circumstances. Just in case they need the instruction: 

### What in here
* First pass JAPAN analysis
* PostPan regression
* Second pass JAPAN analysis to apply LRB correction
* Generation of summary plots for each run
* Auto-uploading plots in online webpage


### Prompt Analysis One Single run
```
	./prompt.sh <run_number>
```

### Making Summary Plots for One Single run
```
	./summary.sh <run_number>
```

the summary.sh script uploads plots and text summary to the webpage. So be mindful when pushing this button.

###  for Multiple runs
First create a run list text with run number in each line, then run
```
	./prompt_runlist.sh <runlist_filename>
```
```
	./summary_runlist.sh <runlist_filename>
```

All the components are capable of handling splitted run. So no need to specify segment number. 


If you have any question, please contact

Tao Ye: tao.ye@stonybrook.edu
