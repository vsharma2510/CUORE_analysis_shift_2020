{
  ifstream input_file;
  input_file.open("/nfs/cuore_ssd/scratch/vsharma/diana_ds3090_official/3MeV_channel_list_nhw.txt");
  
  int ch,run_number,i=0,input_channel=309;
  double Energy;
  string file_line;
  std::vector<int> channel;
  std::vector<int> run;
  std::vector<double> energy;
  TH1D* h = new TH1D("h","h",988,1,988);
  TH1D* h_energy = new TH1D("Energy","Energy",600,3400,4000);
  TH1D* h_run = new TH1D("Run","Run",61,303406,303467);
  TH2D* ch_E = new TH2D("ch_E","ch_E",10,1,988,10,3400,4000);
  while(getline(input_file,file_line)){
    stringstream ss(file_line);
    ss>>ch>>Energy>>run_number;
    i++;
    //if(ch==input_channel){
    cout<<"--------Channel being added is "<<ch<<"-----------"<<endl;
    if(run_number==303425){
    channel.push_back(ch);
    energy.push_back(Energy);
    run.push_back(run_number);
    h->Fill(ch);
    h_energy->Fill(Energy);
    h_run->Fill(run_number);
    ch_E->Fill(ch,Energy);
    }
    // }
  }
  cout<<"Number of channels is "<<i<<endl;
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Counts");
  h->SetTitle("Channel distribution of events between 3400 and 4000 keV");
  // h->Draw();
  
  h_energy->GetXaxis()->SetTitle("Energy");
  h_energy->GetYaxis()->SetTitle("Counts");
  h_energy->SetTitle(Form("Energy distribution for run 303425",input_channel));
  h_energy->Draw();

  h_run->GetXaxis()->SetTitle("Run Number");
  h_run->GetYaxis()->SetTitle("Counts");
  h_run->GetXaxis()->TGaxis::SetMaxDigits(7);
  h_run->SetTitle("Distribution of events among background runs");
  //h_run->Draw();
  //gStyle->SetOptStats(0);
  ch_E->GetXaxis()->SetTitle("Channel");
  ch_E->GetYaxis()->SetTitle("Energy [keV]");
  ch_E->SetTitle("Energy vs Channel");
  //ch_E->Draw("COLZ");
 
		     
}  
