{
  ifstream input_file;
  input_file.open("/nfs/cuore_ssd/scratch/vsharma/diana_ds3090_official/3MeV_channel_list_nhw.txt");
  
  int ch,temp,i=0;
  double Energy;
  string file_line;
  std::vector<int> channel;
  TH1D* h = new TH1D("h","h",988,1,988);
  while(getline(input_file,file_line)){
    stringstream ss(file_line);
    ss>>ch>>Energy>>temp;
    i++;
    cout<<"--------Channel being added is "<<ch<<"-----------"<<endl;
    channel.push_back(ch);
    h->Fill(ch);    
  }
  cout<<"Number of channels is "<<i<<endl;
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Counts");
  h->SetTitle("Channel distribution of events between 3400 and 4000 keV");
  h->Draw();
}
