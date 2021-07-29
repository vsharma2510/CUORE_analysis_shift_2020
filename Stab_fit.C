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
  size_t pos;
  
  ifstream channel_file(argv[1]);
  if(!channel_file){
    cout<<"!!!!!!!! Unable to open channel list file !!!!!!!!!"<<endl;
  }

  int run_number=atoi(argv[2]);
  
  string file_line,line;
  while(getline(channel_file,file_line)){
    stringstream ss(file_line);
    ss>>x;
    cout<<"-------- channel being added is --------"<<x<<endl;
    channel.push_back(x);
  }
  
  for(it=channel.begin();it!=channel.end();it++){
    if(*it%52==0){tower=(*it)/52;}
    else{tower=((*it)/52+1);}
    cout<<"Tower being worked on is "<<tower<<endl;
    cout<<"Channel being worked on is "<<(*it)<<endl;
    
    string test1,test2,test3,test4;

    TString par_file_name = Form("/nfs/cuore_ssd/scratch/vsharma/diana_ds3090_official/stab/ds3090/stab_parameters_%d_%.3d.txt",run_number,tower);
    TString search_string = Form("chan%.4d",(*it));
    ifstream file(par_file_name);
    if(!file){
      cout<<par_file_name<<" not found!!"<<endl;
    }

    while(file.good()){
      getline(file,line);
      pos=line.find(search_string);
      if(pos!=string::npos)
	{
	  for(int j=0;j<4;j++){
	    file>>test1;
	  }
	}
	  file>>test2>>test3;
	  cout<<test2<<"   "<<test3<<endl;
    }	
    file.close();
    //cout<<test1<<"     "<test2<<endl;
    
  }
  return 0;
}
