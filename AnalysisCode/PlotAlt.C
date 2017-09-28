void PlotAlt(int i, int max_delta_adc, int delta_samples) {
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Tue Jul  4 08:57:05 2017 by ROOT version6.06/02)
//   from TTree midas_data/MIDAS data
//   found on file: output_000306.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();


//Declaration of leaves types
   Int_t           TimeStamp;
   Int_t           event;
   Int_t           nchannels;
   Int_t           nsamples;
   Int_t           TimeSample;
   Int_t           adc_value_0[4000];
   Int_t           adc_value_1[4000];

   // Set branch addresses.
   midas_data->SetBranchAddress("TimeStamp",&TimeStamp);
   midas_data->SetBranchAddress("event",&event);
   midas_data->SetBranchAddress("nchannels",&nchannels);
   midas_data->SetBranchAddress("nsamples",&nsamples);
   midas_data->SetBranchAddress("TimeSample",&TimeSample);
   midas_data->SetBranchAddress("adc_value_0",adc_value_0);
   midas_data->SetBranchAddress("adc_value_1",adc_value_1);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// midas_data->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = midas_data->GetEntries();

   Long64_t nbytes = 0;
   
   nbytes += midas_data->GetEntry(i);

   TH1D *wf1 = new TH1D("wf1"," ",nsamples,0.,nsamples*TimeSample);
   TH1D *wf2 = new TH1D("wf2"," ",nsamples,0.,nsamples*TimeSample);

   for(int j = 0;j < nsamples; j++) {

     wf1->SetBinContent(j+1,adc_value_0[j]);
     wf2->SetBinContent(j+1,adc_value_1[j]);

   }


      double ped1 = 0.;
      double ped2 = 0.;

      for(int j = 0; j < 500; j++ ) {

	ped1 += adc_value_0[j];
	ped2 += adc_value_1[j];

      }     

      ped1 /= 500.;  
      ped2 /= 500.;  

   int minsample = 925; 
   int limit = 3990; 

   // int npeaks1 = 0; 
   // int npeaks2 = 0; 
   
   // double peakw1 = 0; 
   // double peakw2 = 0; 
   
   // int jstart1 = -1 ; 
   // int jstart2 = -1; 

   // for(int j = minsample; j < nsamples; j++ ) {
     
   //   if( TMath::Abs(adc_value_0[j]-ped1) > TMath::Abs(limit-ped1) && jstart1 == -1 ) {
   //     jstart1 = j; 
   //   }
     
   //   if( TMath::Abs(adc_value_1[j]-ped2) > TMath::Abs(limit-ped2) && jstart2 == -1 ) {
   //     jstart2 = j; 
   //   }
     
   //   if( jstart1 != -1 ) {
   //     if( (adc_value_0[jstart1]-ped1)*(adc_value_0[j]-ped1) < 0 ) {
   // 	 npeaks1++;
   // 	 peakw1 += (j-jstart1); 
   // 	 jstart1 = -1; 
   //     } 
   //   }
     
   //   if( jstart2 != -1 ) {
   //     if( (adc_value_1[jstart2]-ped2)*(adc_value_1[j]-ped2) < 0 ) {
   // 	 npeaks2++;
   // 	 peakw2 += (j-jstart2); 
   // 	 jstart2 = -1; 
   //     } 
   //   }	
   // } 
   

   // if( npeaks1 > 0 ) peakw1 /= (double) npeaks1; 
   // if( npeaks2 > 0 ) peakw2 /= (double) npeaks2; 
   
   // std:cout << npeaks1 <<  "  " << npeaks2 << "  " << peakw1 << "   " << peakw2 << std::endl;

   int delta_adc0 = 0;
   int delta_adc1 = 0;
   double diff0   = 0;
   double diff1   = 0;

   //printf("%d, %d\n", minsample, delta_samples+minsample);

   for (int j = minsample; j < (delta_samples+minsample); ++j) {
     delta_adc0 += adc_value_0[j]-ped1;
     delta_adc1 += adc_value_1[j]-ped2;
     //printf("%d, %d\n", delta_adc0, delta_adc1);
     
   }
   diff0 = delta_adc0/delta_samples;
   diff1 = delta_adc1/delta_samples;

   printf("%f, %f\n", diff0, diff0);

   wf1->Draw();
   wf2->Draw("same");
   wf2->SetLineColor(2);

}
