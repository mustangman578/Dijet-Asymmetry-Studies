{
TFile f1("Dijet_hists_E4_withTG3_after_fit.root");
gr1_E4_ITC_TG3->Draw("AC*");
TFile f2("Dijet_hists_E4_withTG3_after_fit_2018.root");
gr1_E4_ITC_TG3->SetMarkerColor(4);
gr1_E4_ITC_TG3->Draw("CP");
gStyle->SetOptTitle(0);
TPaveLabel *title = new TPaveLabel(.11,.95,.35,.99,"new title","brndc");
title->Draw();
}

// Dijet_hists_E3_withoutTG3_after_fit_2018.root  
// Dijet_hists_E3_withoutTG3_after_fit.root
