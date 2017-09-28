void AnalSelection(double Emax= 30.){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Tue Jul  4 09:23:13 2017 by ROOT version6.06/02)
//   from TTree midas_data/MIDAS data
//   found on file: output_000311.root
//////////////////////////////////////////////////////////

  int minsample =  950;
  int maxsample = 1125;
  //  int maxsample = 3000;

  int limit= 3990; //We count the samples nsamplesgreater that are under limit


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

   Long64_t nentries = midas_data->GetEntries();

   //TH1D creates an unidimensional histogram with fixed bins of type double
   //TH2D does the same but the histogram is bidimensional 

   TH1D *Asym = new TH1D("Asym","",50,0.,1.); //Asymmetry
   TH1D *Tot  = new TH1D("Tot","",100,0.,Emax); //Total charge
   TH2D *TotvsAsym = new TH2D("TotvsAsym","",50,0.,1.,50,0.,Emax); //Charge vs Asymmetry
   TH2D *TotvsNgreater = new TH2D("TotvsNgreater","",50,0.,300,50,0.,Emax);

   TH1D *Ped1 = new TH1D("Ped1","",100,3980.,4010.); //Average pedestal, channel 1
   TH1D *Ped2 = new TH1D("Ped2","",100,3980.,4010.); //Average pedestal, channel 2


   TH1D *PedSample1 = new TH1D("PedSample1","",100,3980.,4010); //Pedestal sample by sample
   TH1D *PedSample2 = new TH1D("PedSample2","",100,3980.,4010.); 

   // Selection 

   TH2D *np1vsnp2 = new TH2D("np1vsnp2","  ",30,-0.5,100.,30,-0.5,100.);
   TH2D *pwvsnp1 = new TH2D("pwvsnp1","  ",30,-0.5,100.,50,0.,100);
   TH2D *pwvsnp2 = new TH2D("pwvsnp2","  ",30,-0.5,100.,50,0.,100);
   TH2D *pw1vspw2 = new TH2D("pw1vspw2","  ",50,0.,100,50,0.,100);
   TH2D *totvsnp1 = new TH2D("totvsnp1","  ",30,-0.5,100.,50,0.,Emax);
   TH2D *totvsnp2 = new TH2D("totvsnp2","  ",30,-0.5,100.,50,0.,Emax);
   TH2D *totvspw1 = new TH2D("totvspw1","  ",50,0.,100.,50,0.,Emax);
   TH2D *totvspw2 = new TH2D("totvspw2","  ",50,0.,100.,50,0.,Emax);
   TH2D *pw1vsevt = new TH2D("pw1vsevt","  ",50,0,nentries,50,0.,100);
   TH2D *pw2vsevt = new TH2D("pw2vsevt","  ",50,0,nentries,50,0.,100);
   TH2D *np1vsevt = new TH2D("np1vsevt","  ",50,0.,nentries,30,-0.5,100.);
   TH2D *np2vsevt = new TH2D("np2vsevt","  ",50,0.,nentries,30,-0.5,100.);
   
   //Defines wavefunctions for each channel
   TH1D *WF1;
   TH1D *WF2;

   double TSF,TS0;

   TH2D *totvsEvt = new TH2D("totvsEvt","",50,0.,nentries,50,0.,Emax);
   TH2D *asymvsEvt = new TH2D("asymvsEvt","",50,0.,nentries,50,0.,1.);

   int nselected = 0; 

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
     nbytes += midas_data->GetEntry(i);   

     if( i == 0 ) TS0 = TimeStamp; 
     if( i == nentries-1 ) TSF = TimeStamp; 


     if( i == 0 ){
       WF1 = new TH1D("WF1","",nsamples,-0.5,nsamples-0.5);
       WF2 = new TH1D("WF2","",nsamples,-0.5,nsamples-0.5);

       for(int j = 0; j < nsamples; j++ ) {
	 WF1->SetBinContent(j+1,adc_value_0[j]);
	 WF2->SetBinContent(j+1,adc_value_1[j]);
       }  
     } 

      double ped1 = 0.;
      double ped2 = 0.;

      for(int j = 0; j < 500; j++ ) {

	ped1 += adc_value_0[j];
	ped2 += adc_value_1[j];

	PedSample1->Fill(adc_value_0[j]);
	PedSample2->Fill(adc_value_1[j]);

      }     

      ped1 /= 500.;  
      ped2 /= 500.;  

      Ped1->Fill(ped1);
      Ped2->Fill(ped2);

      double sum1 = 0; 
      double sum2 = 0;

      int nsamplesgreater1=0;

      int nsamplesgreater2=0;

      for(int j=0; j<nsamples; j++) {
	if(adc_value_0[j]<limit) 
	  {
	    nsamplesgreater1++;
	  }
	
       if(adc_value_1[j]<limit) 
	 {
	   nsamplesgreater2++;
	 }
      }
      
      for(int j = minsample; j < maxsample; j++ ) {
	
	sum1 += -(adc_value_0[j]-ped1);
	sum2 += -(adc_value_1[j]-ped2);
	
      }  

      sum1 *= 1./50.*2./4096.;  //Current (R=5Oohm, ADC Voltage sensitivity)
      sum2 *= 1./50.*2./4096.;


      double tot = sum1+sum2;
      double asym = sum1/tot;

      // 

      int npeaks1 = 0; 
      int npeaks2 = 0; 

      double peakw1 = 0; 
      double peakw2 = 0; 

      int jstart1 = -1 ; 
      int jstart2 = -1; 

      for(int j = minsample; j < nsamples; j++ ) {
	
	if( TMath::Abs(adc_value_0[j]-ped1) > TMath::Abs(limit-ped1) && jstart1 == -1 ) {
	  jstart1 = j; 
	}

	if( TMath::Abs(adc_value_1[j]-ped2) > TMath::Abs(limit-ped2) && jstart2 == -1 ) {
	  jstart2 = j; 
	}

	if( jstart1 != -1 ) {
	  if( (adc_value_0[jstart1]-ped1)*(adc_value_0[j]-ped1) < 0 ) {
	    npeaks1++;
	    peakw1 += (j-jstart1); 
	    jstart1 = -1; 
	  } 
	}

	if( jstart2 != -1 ) {
	  if( (adc_value_1[jstart2]-ped2)*(adc_value_1[j]-ped2) < 0 ) {
	    npeaks2++;
	    peakw2 += (j-jstart2); 
	    jstart2 = -1; 
	  } 
	}	
      } 


      if( npeaks1 > 0 ) peakw1 /= (double) npeaks1; 
      if( npeaks2 > 0 ) peakw2 /= (double) npeaks2; 

      //      std:cout << npeaks1 <<  "  " << npeaks2 << "  " << peakw1 << "   " << peakw2 << std::endl; 


      np1vsnp2->Fill(npeaks1,npeaks2); 
      pwvsnp1->Fill(npeaks1,peakw1); 
      pwvsnp2->Fill(npeaks2,peakw2); 
      pw1vspw2->Fill(peakw1,peakw2);
      totvsnp1->Fill(npeaks1,tot);  
      totvsnp2->Fill(npeaks2,tot);  
      totvspw1->Fill(peakw1,tot);  
      totvspw2->Fill(peakw2,tot);  
      pw1vsevt->Fill(i,peakw1); 
      pw2vsevt->Fill(i,peakw2); 
      np1vsevt->Fill(i,npeaks1); 
      np2vsevt->Fill(i,npeaks2); 

      if( npeaks1 > 4 || npeaks2  > 4 ) continue; 

      //      if( tot > 2. ) std::cout << i << std::endl;


      int nsamplesgreater = nsamplesgreater1; 
      if( nsamplesgreater < nsamplesgreater2 ) nsamplesgreater = nsamplesgreater2; 

      // if( nsamplesgreater*0.02/100. > tot ) continue; // Spark

      TotvsNgreater->Fill(nsamplesgreater,tot); 

      if( tot > 0.002 )
	Asym->Fill(asym);
      if( asym > 0.2 && asym < 0.8 ) 
	Tot->Fill(tot);

      TotvsAsym->Fill(asym,tot);

      totvsEvt->Fill(i,tot);
      asymvsEvt->Fill(i,asym);

      nselected++;

   }

 
   TCanvas *cped= new TCanvas("cped","",800,800);
   cped->Divide(2,1); //Divide the window into 2 columns and 1 row
   cped->cd(1);
   Ped1->Fit("gaus"); //Plot a gaussian adjustment on the same graphic as "Ped1" 
   cped->cd(2);
   Ped2->Fit("gaus");
   cped->Update();

   TCanvas *cwf= new TCanvas("cwf","",800,800);
   cwf->Divide(1,2);  //Divides the window into 2 rows and 1 column
   cwf->cd(1);
   WF1->Draw();  //Plot (only) the waveform WF1
   cwf->cd(2);
   WF2->Draw();
   cwf->Update();

   TCanvas *cps= new TCanvas("cps","",800,800);
   cps->Divide(2,1);
   cps->cd(1);
   PedSample1->Draw();
   cps->cd(2);
   PedSample2->Draw();
   cps->Update();
   
   TCanvas *tevol= new TCanvas("tevol","",800,800);
   tevol->Divide(2,1);
   tevol->cd(1);
   totvsEvt->Draw("colz");
   tevol->cd(2);
   asymvsEvt->Draw("colz");
   tevol->Update();



  


   TCanvas *c= new TCanvas("c","",800,800);
   c->Divide(2,2);
   c->cd(1); 
   Tot->Draw();
   c->cd(2);
   Asym->Draw();

   for(int ii = 0; ii < 20; ii++ ) {
     double x = 50./2000.+(1950.-50.)/2000.*ii/19;
     
     double amax = Asym->GetMaximum();

     TLine *l = new TLine(x,0.,x,amax); 
     l->SetLineStyle(2);
     l->Draw();
   }
   c->cd(3); 
   TotvsAsym->Draw("colz");
   c->cd(4);
   TotvsNgreater->Draw("colz");
   c->Update(); 


   TCanvas *csel = new TCanvas("csel","",800,800); 
   csel->Divide(4,3); 
   csel->cd(1); 
   np1vsnp2->Draw("colz"); 
   csel->cd(2); 
   pwvsnp1->Draw("colz"); 
   csel->cd(3); 
   pwvsnp2->Draw("colz");
   csel->cd(4); 
   pw1vspw2->Draw("colz");
   csel->cd(5); 
   totvsnp1->Draw("colz");
   csel->cd(6); 
   totvsnp2->Draw("colz"); 
   csel->cd(7);
   totvspw1->Draw("colz"); 
   csel->cd(8); 
   totvspw2->Draw("colz"); 
   csel->cd(9); 
   pw1vsevt->Draw("colz"); 
   csel->cd(10); 
   pw2vsevt->Draw("colz"); 
   csel->cd(11); 
   np1vsevt->Draw("colz");
   csel->cd(12); 
   np2vsevt->Draw("colz");
   csel->Update(); 
   
   std::cout << " Rate " << (double)nselected/(TSF-TS0) << std::endl; 

}
