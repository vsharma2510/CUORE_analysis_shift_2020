#include <iostream>
#include <fstream>
#include <getopt.h>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <cstdlib>

#include <TH2.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TLegend.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TPad.h>


#include "QCuore.hh"
#include "QError.hh"
#include "QObject.hh"
#include "QGlobalHandle.hh"
#include "QMessage.hh"
#include "QGlobalDataManager.hh"
#include "QDetChannelCollectionHandle.hh"
#include "QDetChannelCollection.hh"
#include "QHeader.hh"
#include "QPulseInfo.hh"
#include "QChain.hh"
#include "QTObject.hh"
#include "QTObjectHandle.hh"

using namespace std;
using namespace Cuore;

int main(int argc, char* argv[]){

  std::vector<int> channel;
  std::vector<int>::iterator it;
  int tower,x;
  int run_number [14];
  run_number[0]=303396;
  run_number[1]=303398;
  run_number[2]=303399;
  run_number[3]=303400;
  run_number[4]=303406;
  run_number[5]=303408;
  run_number[6]=303409;
  run_number[7]=303410;
  run_number[8]=303411;
  run_number[9]=303413;
  run_number[10]=303414;
  run_number[11]=303415;
  run_number[12]=303416;
  run_number[13]=303417;

  ifstream channel_file(argv[1]);
  if(!channel_file){
    cout<<"!!!!!!!! Unable to open channel list file !!!!!!!!!"<<endl;
  }

  string file_line;
  while(getline(channel_file,file_line)){
    stringstream ss(file_line);
    ss>>x;
    cout<<"-------- channel being added is --------"<<x<<endl;
    channel.push_back(x);
  }

  TString listname;
  QChain ch("qtree");
  TString cut_baseline,cut_heater;

  for(it=channel.begin();it!=channel.end();it++){
    if(*it%52==0){tower=(*it)/52;}  
    else{tower=((*it)/52+1);}
    cout<<"Tower being worked on is "<<tower<<endl;
    cout<<"Channel being worked on is "<<(*it)<<endl;
    for(int i=0;i<4;i++){
      if(run_number[i]<303401){
	listname.Form("/nfs/cuore_ssd/scratch/vsharma/diana_ds3090_official/output/ds3090/Production_%d_%.3d_C.list",run_number[i],tower);
      }
      if(run_number[i]>303401){
	listname.Form("/nfs/cuore_ssd/scratch/vsharma/diana_ds3090_official/output/ds3090/Production_%d_%.3d_B.list",run_number[i],tower);
      }
      
      int nAdded=ch.Add(listname.Data());
      if(nAdded==0){cout<<"Failed to add list file for run "<<run_number<<" and channel "<<channel<<endl;}
    }
    
    cut_baseline.Form("Channel==%d && IsStabPulser",(*it)); //IsSignal?
    cut_heater.Form("Channel==%d && IsStabPulser",(*it));
    
    /*unsigned int sizeArr1=ch.Draw("Baseline:OF_Amplitude",cut_baseline.Data(),"GOFF");
    
    double* baseline = ch.GetV1();
    double* amplitude = ch.GetV2();
    double* Baseline = new double [sizeArr1];
    double* Amplitude = new double [sizeArr1];
    
    cout<<"BASELINE VS AMPLITUDE"<<endl;
    
    for(int i=0;i<sizeArr1;i++){
      Baseline[i]=baseline[i];
      Amplitude[i]=amplitude[i];
      if(i%10==0){cout<<Baseline[i]<<"   "<<Amplitude[i]<<endl;}
    }
    
    cout<<"Data copy finished"<<endl;
    
    TH2D* h_baseline = new TH2D("h_baseline","Baseline vs Amplitude",10000,0,-10000,5000,0,5000); 
    //h_baseline->FillN(sizeArr1,Baseline,0,Amplitude,1);
    for(int i=0;i<sizeArr1;i++){
      h_baseline->Fill(Baseline[i],Amplitude[i]);
    }
    TString baseline_histo_title = Form("Baseline vs Amplitude {Channel==%d && IsPulser}",(*it));
    h_baseline->GetXaxis()->SetTitle("Baseline [mV]");
    h_baseline->GetYaxis()->SetTitle("OF_Amplitude");
    h_baseline->SetTitleOffset(1.3,"y");
    h_baseline->SetTitle(baseline_histo_title);
    h_baseline->SetMarkerStyle(2);
    h_baseline->SetMarkerSize(0.6);*/
    TCanvas* c1 = new TCanvas("c1"," ",800,600);
    c1->cd();
    c1->SetLogy();
    /*h_baseline->Draw();
    TString baseline_title = Form("baseline_vs_amplitude_ch%d_C.pdf",(*it));
    c1->SaveAs(baseline_title);
    */
    unsigned int sizeArr2=ch.Draw("BaselineSlope",cut_heater.Data(),"GOFF");
    
    double* baseline_slope = ch.GetV1();
    double* Baseline_slope = new double [sizeArr2];
    
    cout<<"BASELINE SLOPE"<<endl;
    
    for(int i=0;i<sizeArr2;i++){
      Baseline_slope[i]=baseline_slope[i];
      if(i%10==0){cout<<Baseline_slope[i]<<endl;}
    }
    
    cout<<"Data copy finished"<<endl;
    
    TH1D* h_baseline = new TH1D("h_baseline_slope","Baseline Slope",100,-2,2);
    for(int i=0;i<sizeArr2;i++){
      h_baseline->Fill(Baseline_slope[i]);
    }
    h_baseline->Draw();
    TString baseline_slope_title = Form("Baseline_slope_ch%d_C.pdf",(*it));
    TString baseline_slope_histo_title = Form("Baseline Slope {Channel==%d && IsStabPulser}",(*it));
    h_baseline->GetXaxis()->SetTitle("Counts");
    h_baseline->GetYaxis()->SetTitle("baseline slope");
    h_baseline->SetTitle(baseline_slope_histo_title);
    c1->SaveAs(baseline_slope_title);
  }
  return 0;
}
