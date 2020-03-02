void Root_PT_Dijet_Cuts_Ref_Region() 
{

	#include <iostream>
	#include <vector>

	// Initialize random number
	Double_t rnum;
    TRandom *r1=new TRandom();

	// Initialize chain and read input Ntuple
	TChain *chain = new TChain("analysis");
	chain->Add("/cluster/home/andrew.myers/dataAnalysis/data18_13TeV/data_withoutTG3/*.root");
	chain->Print();

	// Create Root output file
	TFile f("Dijet_hists_ref_2018data_after_fit.root","RECREATE");

	// Initialize Histograms 
	TH1F* h_jet1pt = new TH1F("h_jet1pt", "h_jet1pt", 100,0., 2000.);
	TH1F* h_jet2pt = new TH1F("h_jet2pt", "h_jet2pt", 100,0., 2000.);
	TH1F* h_jet3pt = new TH1F("h_jet3pt", "h_jet3pt", 100,0., 200.);
	TH1F* h_jet1pt_sel = new TH1F("h_jet1pt_sel", "h_jet1pt_sel", 100,0., 2000.);
	TH1F* h_jet2pt_sel = new TH1F("h_jet2pt_sel", "h_jet2pt_sel", 100,0., 2000.);
	TH1F* h_jet3pt_sel = new TH1F("h_jet3pt_sel", "h_jet3pt_sel", 100,0., 200.);

	TH1F* h_njets = new TH1F("h_njets", "h_njets", 20, 0., 10.);

	TH1F* h_j1j2asym_pt_300_400 = new TH1F("h_j1j2asym_pt_300_400", "h_j1j2asym_pt_300_400", 100, -1., 1.5);
	TH1F* h_j1j2asym_pt_400_500 = new TH1F("h_j1j2asym_pt_400_500", "h_j1j2asym_pt_400_500", 100, -1., 1.5);
	TH1F* h_j1j2asym_pt_500_600 = new TH1F("h_j1j2asym_pt_500_600", "h_j1j2asym_pt_500_600", 100, -1., 1.5);
	TH1F* h_j1j2asym_pt_600_800 = new TH1F("h_jDouble_t jet2_eta; //!1j2asym_pt_600_800", "h_j1j2asym_pt_600_800", 100, -1., 1.5);
	TH1F* h_j1j2asym_pt_800_1000 = new TH1F("h_j1j2asym_pt_800_1000", "h_j1j2asym_pt_800_1000", 100, -1., 1.5);
	TH1F* h_j1j2asym_pt_1000_1500 = new TH1F("h_j1j2asym_pt_1000_1500", "h_j1j2asym_pt_1000_1500", 100, -1., 1.5);
	TH1F* h_j1j2asym_pt_1500_2000 = new TH1F("h_j1j2asym_pt_1500_2000", "h_j1j2asym_pt_1500_2000", 100, -1., 1.5);

	TH2F* h_jet1vjet2 = new TH2F("h_jet1vjet2", "h_jet1vjet2", 50, 0., 500., 50, 0., 500.);
	TH2F* h_jet1_jet1_unc = new TH2F("h_jet1_jet1_unc", "h_jet1_jet1_unc", 50, 0., 500., 50, 0., 500.);

	// Initialize TBranches from Ntuple 
	TBranch        *b_JetPt_calib_1;
	TBranch        *b_JetPt_calib_2;
	TBranch        *b_JetPt_calib_3;
	TBranch        *b_JetEta_calib_1;
	TBranch        *b_JetEta_calib_2;
	TBranch        *b_JetEta_calib_3;
	TBranch        *b_JetPhi_calib_1;
	TBranch        *b_JetPhi_calib_2;
	TBranch        *b_JetPhi_calib_3;
	vector<float>  *jet1_pt;
	vector<float>  *jet2_pt;
	vector<float>  *jet3_pt;
	vector<float>  *jet1_eta;
	vector<float>  *jet2_eta;
	vector<float>  *jet3_eta;
	vector<float>  *jet1_phi;
	vector<float>  *jet2_phi;
	vector<float>  *jet3_phi;

	jet1_pt = 0;
	jet2_pt = 0;
	jet3_pt = 0;
	jet1_eta = 0;
	jet2_eta = 0;
	jet3_eta = 0;
	jet1_phi = 0;
	jet2_phi = 0;
	jet3_phi = 0;

	chain->SetBranchAddress("JetPt_calib_1", &jet1_pt,&b_JetPt_calib_1);
	chain->SetBranchAddress("JetPt_calib_2", &jet2_pt,&b_JetPt_calib_2);
	chain->SetBranchAddress("JetPt_calib_3", &jet3_pt,&b_JetPt_calib_3);
	chain->SetBranchAddress("JetEta_calib_1", &jet1_eta,&b_JetEta_calib_1);
	chain->SetBranchAddress("JetEta_calib_2", &jet2_eta,&b_JetEta_calib_2);
	chain->SetBranchAddress("JetEta_calib_3", &jet3_eta,&b_JetEta_calib_3);
	chain->SetBranchAddress("JetPhi_calib_1", &jet1_phi,&b_JetPhi_calib_1);
	chain->SetBranchAddress("JetPhi_calib_2", &jet2_phi,&b_JetPhi_calib_2);
	chain->SetBranchAddress("JetPhi_calib_3", &jet3_phi,&b_JetPhi_calib_3);

	float jet1_pt_a;
	float jet2_pt_a;
	float jet3_pt_a;
	float jet1_eta_a;
	float jet2_eta_a;
	float jet3_eta_a;
	float jet1_phi_a;
	float jet2_phi_a;
	float jet3_phi_a;
	float dphi_jet12;
	float jet_ref_a;
	float jet_probe_a;
	float j1j2asym_a[7];


	// Get number of entries 
	Long64_t nentries = chain->GetEntries();
	cout << "Number of Entries = " << nentries << endl;

	Double_t ptsum_a[7] = {0};

	Int_t npass_a[7] = {0};

	int ifound;
	float pi = 3.1415927;

	// Loop through entries and make cuts for Dijet Asymmetry 
	for (Long64_t jentry = 0; jentry<nentries; jentry++)
	{
		chain->GetEntry(jentry);

		// Count the number of jets in the event 
		int Njets = 0;
	    Njets = jet1_pt->size() + jet2_pt->size() + jet3_pt->size();
		if (Njets > 0)
		{
		//cout << "Number of jets in event = " << Njets << endl;
		}

		// Initialize the values from the vector floats 
		float JetPt1Value = 0;
		float JetPt2Value = 0;
		float JetPt3Value = 0;
		float JetEta1Value = 0;
		float JetEta2Value = 0;
		float JetEta3Value = 0;
		float JetPhi1Value = 0;
		float JetPhi2Value = 0;
		float JetPhi3Value = 0;
		jet_ref_a = 0.;
		jet_probe_a = 0.;

        // Print Event Number
		//cout << "Event Number = " << jentry << endl;

        // Get Pt Values 
		if(jet1_pt->size() == 1)
		{
			JetPt1Value = jet1_pt->at(0);
			//cout << "Jet 1 Pt = " << JetPt1Value << " GeV" << endl;
			h_jet1pt->Fill(JetPt1Value);
			jet1_pt_a = JetPt1Value;
		}

		if(jet2_pt->size() == 1)
		{
			JetPt2Value = jet2_pt->at(0);
			//cout << "Jet 2 Pt = " << JetPt2Value << " GeV" << endl;
			h_jet2pt->Fill(JetPt2Value);
			jet2_pt_a = JetPt2Value;
		}

		if(jet3_pt->size() == 1)
		{
			JetPt3Value = jet3_pt->at(0);
			//cout << "Jet 3 Pt = " << JetPt3Value << " GeV" << endl;
			h_jet3pt->Fill(JetPt3Value);
			jet3_pt_a = JetPt3Value;
		}

		// Get Eta Values 
		if(jet1_eta->size() == 1)
		{
			JetEta1Value = jet1_eta->at(0);
			jet1_eta_a = JetEta1Value;
		}

		if(jet2_eta->size() == 1)
		{
			JetEta2Value = jet2_eta->at(0);
			h_jet2pt->Fill(JetPt2Value);
			jet2_eta_a = JetEta2Value;
		}

		if(jet3_eta->size() == 1)
		{
			JetEta3Value = jet3_eta->at(0);
			jet3_eta_a = JetEta3Value;
		}

		//Get Phi Values 
		if(jet1_phi->size() == 1)
		{
			JetPhi1Value = jet1_phi->at(0);
			jet1_phi_a = JetPhi1Value;
		}

		if(jet2_phi->size() == 1)
		{
			JetPhi2Value = jet2_phi->at(0);
			jet2_phi_a = JetPhi2Value;
		}

		if(jet3_phi->size() == 1)
		{
			JetPhi3Value = jet3_phi->at(0);
			jet3_phi_a = JetPhi3Value;
		}

		Double_t PT_lim[8] = {300., 400., 500., 600., 800., 1000., 1500., 2000.};
		float PT_avg_j1j2;

		// Asymmetry for selected events 

		ifound = 0;
		Int_t in_range = -1;
		// Select jet Pt bin
		for (int ibin = 0; ibin < 7; ibin++) 
		{
			if(((jet1_pt_a >= PT_lim[ibin]) && (jet1_pt_a <= PT_lim[ibin+1]))) 
			{
				PT_avg_j1j2 = (jet1_pt_a + jet2_pt_a)/2.0;
			

				if((Njets == 2) || ((Njets > 2) && (jet3_pt_a < 30.0))) 
				{
					in_range = ibin;
				}

			}
		}

		if(in_range != -1)
		{
			// Only accept jets ~opposite in phi
        	dphi_jet12 = fabs(jet1_phi_a - jet2_phi_a);

			if(dphi_jet12 > pi) dphi_jet12 = 2*pi - dphi_jet12;

			if(dphi_jet12 >= 2.5) 
			{
				// Find a Reference jet/Probe jet combination
				if((fabs((jet1_eta_a)) < 0.8) && (fabs((jet2_eta_a)) < 0.8)) 
				{
					rnum = r1->Uniform(0,1);
					if(rnum < 0.5)
					{
						jet_ref_a = jet1_pt_a;
						jet_probe_a = jet2_pt_a;
					}
					else
					{
						jet_probe_a = jet1_pt_a;
						jet_ref_a = jet2_pt_a;
					}
					ifound = 1;
					cout << "Found Asymmetry!" << endl;
				}
			}

			// Get the dijet asymmetry 
			if(ifound == 1)
			{
				h_jet1pt_sel->Fill(jet1_pt_a);
	    		h_jet2pt_sel->Fill(jet2_pt_a);
				h_jet3pt_sel->Fill(jet3_pt_a);

				j1j2asym_a[in_range] = (jet_probe_a - jet_ref_a)/((jet_probe_a + jet_ref_a)/2.);

				if(in_range == 0) h_j1j2asym_pt_300_400->Fill(j1j2asym_a[0]);
				if(in_range == 1) h_j1j2asym_pt_400_500->Fill(j1j2asym_a[1]);
				if(in_range == 2) h_j1j2asym_pt_500_600->Fill(j1j2asym_a[2]);
				if(in_range == 3) h_j1j2asym_pt_600_800->Fill(j1j2asym_a[3]);
				if(in_range == 4) h_j1j2asym_pt_800_1000->Fill(j1j2asym_a[4]);
				if(in_range == 5) h_j1j2asym_pt_1000_1500->Fill(j1j2asym_a[5]);
				if(in_range == 6) h_j1j2asym_pt_1500_2000->Fill(j1j2asym_a[6]);

				npass_a[in_range]++;
				ptsum_a[in_range] = ptsum_a[in_range] + PT_avg_j1j2;
			}
		}

		
 
		
	}

	// Fit asymmetry plots with Gaussian

		Double_t p2 [7] = {0};
		Double_t err_sig[7];
		//Double_t new_sig[7] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
		Double_t new_sig[7] = {0.0721, 0.0653, 0.0581, 0.0534, 0.0440, 0.0413, 0.0336};
		Double_t sigfac = 3.0;

		TF1 *fit1 = new TF1("fit1", "gaus", -new_sig[0]*sigfac, new_sig[0]*sigfac);
        h_j1j2asym_pt_300_400->Fit("fit1", "R");
        TF1 *fitresult1 = h_j1j2asym_pt_300_400->GetFunction("fit1");
		p2[0] = fitresult1->GetParameter(2);
		err_sig[0] = fitresult1->GetParError(2);
		cout << "Gaussian fit, sigma =  " << p2[0] << "   +/-  " << err_sig[0] << endl;

		TF1 *fit2 = new TF1("fit2", "gaus", -new_sig[1]*sigfac, new_sig[1]*sigfac);
        h_j1j2asym_pt_400_500->Fit("fit2", "R");
        TF1 *fitresult2 = h_j1j2asym_pt_400_500->GetFunction("fit2");
		p2[1] = fitresult2->GetParameter(2);
		err_sig[1] = fitresult2->GetParError(2);

		TF1 *fit3 = new TF1("fit3", "gaus", -new_sig[2]*sigfac, new_sig[2]*sigfac);
        h_j1j2asym_pt_500_600->Fit("fit3", "R");
        TF1 *fitresult3 = h_j1j2asym_pt_500_600->GetFunction("fit3");
		p2[2] = fitresult3->GetParameter(2);
		err_sig[2] = fitresult3->GetParError(2);

		TF1 *fit4 = new TF1("fit4", "gaus", -new_sig[3]*sigfac, new_sig[3]*sigfac);
        h_j1j2asym_pt_600_800->Fit("fit4", "R");
        TF1 *fitresult4 = h_j1j2asym_pt_600_800->GetFunction("fit4");
		p2[3] = fitresult4->GetParameter(2);
		err_sig[3] = fitresult4->GetParError(2);

		TF1 *fit5 = new TF1("fit5", "gaus", -new_sig[4]*sigfac, new_sig[4]*sigfac);
        h_j1j2asym_pt_800_1000->Fit("fit5", "R");
        TF1 *fitresult5 = h_j1j2asym_pt_800_1000->GetFunction("fit5");
		p2[4] = fitresult5->GetParameter(2);
		err_sig[4] = fitresult5->GetParError(2);

		TF1 *fit6 = new TF1("fit6", "gaus", -new_sig[5]*sigfac, new_sig[5]*sigfac);
        h_j1j2asym_pt_1000_1500->Fit("fit6", "R");
        TF1 *fitresult6 = h_j1j2asym_pt_1000_1500->GetFunction("fit6");
		p2[5] = fitresult6->GetParameter(2);
		err_sig[5] = fitresult6->GetParError(2);

		TF1 *fit7 = new TF1("fit7", "gaus", -new_sig[6]*sigfac, new_sig[6]*sigfac);
        h_j1j2asym_pt_1500_2000->Fit("fit7", "R");
        TF1 *fitresult7 = h_j1j2asym_pt_1500_2000->GetFunction("fit7");
		p2[6] = fitresult7->GetParameter(2);
        err_sig[6] = fitresult7->GetParError(2);

		Double_t sigPT_PT[7];
		Double_t PT_avg[7];
		for (int k = 0; k < 7; k++) 
		{
			PT_avg[k] = ptsum_a[k]/npass_a[k];
			sigPT_PT[k] = p2[k]/sqrt(2);
			cout << k << "    npass a[k] = " << npass_a[k] << "      ptsum average a = " << PT_avg[k] << endl;
			cout << k << "    Sigma(PT)/PT = " << sigPT_PT[k] << endl;
		}

		// Graph the resulting sigma(PT ref)/PT(ref-avg).

		// Set errors for graph
		Double_t PT_lim2[8] = {300., 400., 500., 600., 800., 1000., 1500., 2000.};
	    Double_t binx[7];
		Double_t PT_mid[7];

		for (int j = 0; j < 7; j++) 
		{
			PT_mid[j] = PT_lim2[j] + (PT_lim2[j+1] - PT_lim2[j])/2.;
			// binx[j] = (PT_lim2[j+1] - PT_lim2[j])/2.;
            binx[j] = 0.;
			err_sig[j] = err_sig[j]/sqrt(2);
		}

		TGraphErrors *gr1 = new TGraphErrors(7, PT_avg, sigPT_PT, binx, err_sig);
		gr1->SetTitle("Reference Region Jet Pt Resolution 2018 Data");
		
		gr1->GetXaxis()->SetTitle("Jet Pt");
		gr1->GetYaxis()->SetTitle("sigma(Pt)/Pt");
		gr1->SetMarkerColor(4);
                gr1->SetMarkerStyle(21);
		gr1->Draw("ALP");
                gr1->Write("gr1_Ref_Region");
    

	// Write output file 
	f.Write();



}
	
