// author : Tao Ye
// date : 05-2019
// description: A script for error code plots 

#include "DeviceErrorCounter.C"
#include "ErrorFlagDecoder.C"
#include "device_list.h"

void PlotErrorCounters(){
  TString plot_title;
  TStopwatch tsw;
  TCanvas* c1 = new TCanvas("c1","c1",2400,1200);
  TCanvas* c2 = new TCanvas("c2","c2",2400,1800);
  c2->Divide(2,2);

  c1->cd();
  tsw.Start();
  Bool_t kStatus = ErrorFlagDecoder();
  plot_title = Form("run%s_ErrorCounter_global.png",run_seg.Data());
  c1->SaveAs(output_path+ plot_title);
  cout << "--"; tsw.Print(); cout << endl;
  //  if(kStatus){
  TString maindet_array[4]={"usl","usr","dsl","dsr"};
  TString ATdet_array[4]={"atl1","atl2","atr1","atr2"};
    TString sam_array[8]={"sam1","sam2","sam3","sam4",
			  "sam5","sam6","sam7","sam8"};
    TString bcm_array[4]={"bcm_an_us","bcm_an_ds","bcm_an_diff","bcm0l02"};
  
    TString bpmTarg_array[4]={"bpm4aX","bpm4aY","bpm4eX","bpm4eY"};
    TString bpmE_array[4]={"bpm11X","bpm11Y","bpm12X","bpm12Y"};
    TString bpm1_array[4]={"bpm1XM","bpm1XP","bpm1YP","bpm1YM"};
    TString bpm4a_array[4]={"bpm4aXM","bpm4aXP","bpm4aYP","bpm4aYM"};
    TString bpm4e_array[4]={"bpm4eXM","bpm4eXP","bpm4eYP","bpm4eYM"};
    // BPM 16 was 8 before 7/16/2019
    // TString bpm8_array[4]={"bpm8XM","bpm8XP","bpm8YP","bpm8YM"};
    TString bpm11_array[4]={"bpm11XM","bpm11XP","bpm11YP","bpm11YM"};
    TString bpm12_array[4]={"bpm12XM","bpm12XP","bpm12YP","bpm12YM"};
    // BPM 11 was 14 before 7/16/2019
    // TString bpm14_array[4]={"bpm14XM","bpm14XP","bpm14YP","bpm14YM"};
    TString bpm16_array[4]={"bpm16XM","bpm16XP","bpm16YP","bpm16YM"};
  
    TString* channels[13]={maindet_array,ATdet_array,
			  sam_array,sam_array+4,bpmTarg_array,bpmE_array,
			  bpm1_array,bpm4a_array,bpm4e_array,
			  bpm11_array,bpm12_array,
			  bpm16_array};
    tsw.Start();
    for(int i=0;i<4;i++){
      c2->cd(i+1);
      DeviceErrorCounter(bcm_array[i]);
      cout << "-- Device: " << bcm_array[i] << " Done in "; tsw.Print();  tsw.Start();
    }
    plot_title = Form("run%s_ErrorCounter_bcm.png",run_seg.Data());
    c2->SaveAs(output_path+ plot_title);
    
    for(int ich=0;ich<12;ich++){
      tsw.Start();
      for(int i=0;i<4;i++){
	c2->cd(i+1);
	DeviceErrorCounter(channels[ich][i]);
	cout << "-- Device: " << channels[ich][i]<< " Done in ";
	tsw.Print(); tsw.Start();
      }
      plot_title = Form("run%s_ErrorCounter_%d.png",run_seg.Data(),ich);
      c2->SaveAs(output_path+ plot_title);
    }
    //  } // END of if there is any good event

  TString pdf_filename = Form("run%s_ErrorCounters.pdf",run_seg.Data());
  gSystem->Exec(Form("convert $(ls -rt %srun%s*ErrorCounter*.png) %s%s",
		     output_path.Data(),
		     run_seg.Data(),
		     output_path.Data(),
		     pdf_filename.Data()));
  gSystem->Exec(Form("rm %srun%s*ErrorCounter*.png",
		     output_path.Data(),
		     run_seg.Data())); 

}
