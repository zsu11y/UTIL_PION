#include <iostream>
#include <TH1D.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TROOT.h>
#include <TFile.h> 
#include <TH2D.h>

using namespace std;

void Efficiency_16764()
{

// Run 16764 - SHMS only, LH2, 60 uA

TFile *f1 = new TFile("/u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/ROOTfiles/Analysis/Lumi/PionLT_replay_luminosity_16764_-1.root"); //open a new file for each beam current 
TTree *f1Tree = (TTree*)f1->Get("T");     
TTreeReader tr(f1Tree);

// branches that are accessed in the above root tree

TTreeReaderArray<Double_t> bcmAvg(tr,"H.bcm.bcm2.AvgCurrent");    
TTreeReaderArray<Double_t> caltr(tr,"P.cal.etottracknorm");        
TTreeReaderArray<Double_t> hgcerNpeSum(tr,"P.hgcer.npeSum");
TTreeReaderArray<Double_t> ngcerNpeSum(tr,"P.ngcer.npeSum");
TTreeReaderArray<Double_t> aeroNpeSum(tr,"P.aero.npeSum");
TTreeReaderArray<Double_t> beta(tr,"P.gtr.beta");           // this, and above branches are given by outputted cut values for h_ecut_lumi when running /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/scripts/luminosity/replay_lumi.sh
TTreeReaderArray<Double_t> HgtrDP(tr,"P.gtr.dp");           // delta acceptance cut branch found in /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/DB/CUTS/general/accept.cuts

// histograms

// hg cerenkov hists
auto h_hgcer_should = new TH1D ("P.hgcer.npeSum", "SHMS LH2 60uA Efficiency - Run 16764", 300 , 0.1, 40);
h_hgcer_should -> SetLineColor(kBlack);
h_hgcer_should -> SetLineWidth(3);
auto h_hgcer_did = new TH1D ("did", "P.hgcer.npeSum", 300, 0.1, 40);
h_hgcer_did -> SetLineColor(kRed);
h_hgcer_did -> SetLineWidth(1);
h_hgcer_did -> SetLineStyle(2);

// ng cerenkov hists
auto h_ngcer_should = new TH1D ("P.ngcer.npeSum", "SHMS LH2 60uA Efficiency - Run 16764", 300 , 0.1, 40);
h_ngcer_should -> SetLineColor(kBlack);
h_ngcer_should -> SetLineWidth(3);
auto h_ngcer_did = new TH1D ("did", "P.ngcer.npeSum", 300, 0.1, 40);
h_ngcer_did -> SetLineColor(kRed);
h_ngcer_did -> SetLineWidth(1);
h_ngcer_did -> SetLineStyle(2);

// aerogel hists
auto h_aero_should = new TH1D ("P.aero.npeSum","SHMS LH2 60uA Efficiency - Run 16764", 300, 0.1, 50);
h_aero_should -> SetLineColor(kBlack);
h_aero_should -> SetLineWidth(3);
auto h_aero_did = new TH1D ("did", "P.aero.npeSum", 300, 0.1, 50);
h_aero_did -> SetLineColor(kRed);
h_aero_did -> SetLineWidth(1);
h_aero_did -> SetLineStyle(2);


// calorimeter hists
auto h_cal_should = new TH1D ("P.cal.etottracknorm", "SHMS LH2 60uA Efficiency - Run 16764", 300, 0.1, 2);
h_cal_should -> SetLineColor(kBlack);
h_cal_should -> SetLineWidth(3);
auto h_cal_did = new TH1D ("did", "P.cal.etottracknorm", 300, 0.1, 2);
h_cal_did -> SetLineColor(kRed);
h_cal_did -> SetLineWidth(1);
h_cal_did -> SetLineStyle(2);


// cut values

auto bcmAvgCut1 = 60; // run replay lumi to figure out cut values for this run
auto bcmAvgCut2 = 10.0;
auto hgcerNpeSumCut = 2.0;
auto ngcerNpeSumCut = 3.0;
auto aeroNpeSumCut = 1.5;
auto betaCut1 = 1;
auto betaCut2 = 0.3;
auto caltrCut = 0.7;        // this, and above pid cuts are given by outputted cut values for h_ecut_lumi when running /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/scripts/luminosity/replay_lumi.sh
auto H_del_low = -10.0;      // this, and the below acceptance cuts are were found in /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/DB/PARAM/Acceptance_Parameters.csv
auto H_del_high = 20.0;      // values for del low and del high taken from /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/DB/PARAM/Acceptance_Parameters.csv

// fill the histograms

while(tr.Next())
{   // hg cerenkov fill
    for (unsigned int i = 0; i <hgcerNpeSum.GetSize() ; i++)
    {
        if((abs(bcmAvg[i]-bcmAvgCut1)<bcmAvgCut2) && abs(beta[i]-betaCut1)<betaCut2 && caltr[i]>caltrCut && ngcerNpeSum[i] > ngcerNpeSumCut && aeroNpeSum[i] > aeroNpeSumCut && HgtrDP[i] > H_del_low && HgtrDP[i] < H_del_high)
        {                                       // ^^^"should" cuts ^^^
            h_hgcer_should->Fill(hgcerNpeSum[i]);
            if(hgcerNpeSum[i] > hgcerNpeSumCut)     // <<< "did" cut
            {
                h_hgcer_did->Fill(hgcerNpeSum[i]);
            }
        }
    }
    // ng cerenkov fill
    for (unsigned int i = 0; i <ngcerNpeSum.GetSize() ; i++)
    {
        if((abs(bcmAvg[i]-bcmAvgCut1)<bcmAvgCut2) && abs(beta[i]-betaCut1)<betaCut2 && caltr[i]>caltrCut && hgcerNpeSum[i] > hgcerNpeSumCut && aeroNpeSum[i] > aeroNpeSumCut && HgtrDP[i] > H_del_low && HgtrDP[i] < H_del_high)
        {                                       // ^^^"should" cuts ^^^
            h_ngcer_should->Fill(ngcerNpeSum[i]);
            if(ngcerNpeSum[i] > ngcerNpeSumCut)     // <<< "did" cut
            {
                h_ngcer_did->Fill(ngcerNpeSum[i]);
            }
        }
    }
    // aerogel fill
    for (unsigned int i = 0; i <aeroNpeSum.GetSize() ; i++)
    {
        if((abs(bcmAvg[i]-bcmAvgCut1)<bcmAvgCut2) && abs(beta[i]-betaCut1)<betaCut2 && caltr[i]>caltrCut && ngcerNpeSum[i] > ngcerNpeSumCut && hgcerNpeSum[i] > hgcerNpeSumCut && HgtrDP[i] > H_del_low && HgtrDP[i] < H_del_high)
        {                                       // ^^^"should" cuts ^^^
            h_aero_should->Fill(aeroNpeSum[i]);
            if(aeroNpeSum[i] > aeroNpeSumCut)     // <<< "did" cut
            {
                h_aero_did->Fill(aeroNpeSum[i]);
            }
        }
    }

    // calorimeter fill
    for (unsigned int i = 0; i <caltr.GetSize() ; i++)
    {
        if((abs(bcmAvg[i]-bcmAvgCut1)<bcmAvgCut2) && abs(beta[i]-betaCut1)<betaCut2 && hgcerNpeSum[i] > hgcerNpeSumCut && HgtrDP[i] > H_del_low && HgtrDP[i] < H_del_high)
        {                                   // ^^^ "should" cuts ^^^
            h_cal_should->Fill(caltr[i]);   
            if(caltr[i]>caltrCut)           // <<< "did" cut
            {
                h_cal_did->Fill(caltr[i]);
            }
        }
    }
}


// calculate integrals and efficiencies and print to terminal so I can put them in the legend


double dScal = 0.0;
double Scal = h_cal_should->IntegralAndError(1,300,dScal,"");
printf(" 16764_cal Integral Should = %0.2f +/- %0.2f\n", Scal, dScal);

double dDcal= 0.0;
double Dcal = h_cal_did->IntegralAndError(1,300,dDcal,"");	
printf(" 16764_cal Integral Did = %0.2f +/- %0.2f\n",Dcal,dDcal);

double effcal = (Dcal/Scal);
double dEffcal = sqrt((effcal*(1-effcal))/Scal);
printf(" 16764_cal Efficiency = %0.5f +/- %0.5f \n\n", effcal,dEffcal);


double dShgcer = 0.0;
double Shgcer = h_hgcer_should->IntegralAndError(1,300,dShgcer,""); // "should" integral
printf(" 16764_hgcer Integral Should = %0.2f +/- %0.2f\n", Shgcer, dShgcer); 

double dDhgcer= 0.0;
double Dhgcer = h_hgcer_did->IntegralAndError(1,300,dDhgcer,"");  // "did" integral
printf(" 16764_hgcer Integral Did = %0.2f +/- %0.2f\n",Dhgcer,dDhgcer);

double effhgcer = (Dhgcer/Shgcer);                            // efficiency == did/should 
double dEffhgcer = sqrt((effhgcer*(1-effhgcer))/Shgcer);
printf(" 16764_hgcer Efficiency = %0.5f +/- %0.5f \n\n", effhgcer, dEffhgcer);


double dSngcer = 0.0;
double Sngcer = h_ngcer_should->IntegralAndError(1,300,dSngcer,""); // "should" integral
printf(" 16764_ngcer Integral Should = %0.2f +/- %0.2f\n", Sngcer, dSngcer); 

double dDngcer= 0.0;
double Dngcer = h_ngcer_did->IntegralAndError(1,300,dDngcer,"");  // "did" integral
printf(" 16764_ngcer Integral Did = %0.2f +/- %0.2f\n",Dngcer,dDngcer);

double effngcer = (Dngcer/Sngcer);                            // efficiency == did/should 
double dEffngcer = sqrt((effngcer*(1-effngcer))/Sngcer);
printf(" 16764_ngcer Efficiency = %0.5f +/- %0.5f \n\n", effngcer, dEffngcer);

double dSaero = 0.0;
double Saero = h_hgcer_should->IntegralAndError(1,300,dSaero,""); // "should" integral
printf(" 16764_aero Integral Should = %0.2f +/- %0.2f\n", Saero, dSaero); 

double dDaero= 0.0;
double Daero = h_hgcer_did->IntegralAndError(1,300,dDaero,"");  // "did" integral
printf(" 16764_aero Integral Did = %0.2f +/- %0.2f\n",Daero,dDaero);

double effaero = (Daero/Saero);                            // efficiency == did/should 
double dEffaero = sqrt((effaero*(1-effaero))/Saero);
printf(" 16764_aero Efficiency = %0.5f +/- %0.5f \n\n", effaero, dEffaero);

// Output the efficiency for each run number into a txt file

ifstream eff_file_in("eff_values.txt");
ofstream eff_file_out("eff_values.txt", std::ios_base::app);
string line;
bool foundcal = false;
bool foundhgcer = false;
bool foundngcer = false;
bool foundaero = false;

while(getline(eff_file_in, line))
{ 
    if(line.find("run 16764 - cal:")!= std::string::npos)
    {
        foundcal = true;
    }
    if(line.find ("run 16764 - hgcer: ")!= std::string::npos)
    {
        foundhgcer = true;
    }
    if(line.find("run 16764 - ngcer:")!= std::string::npos)
    {
        foundcal = true;
    }
    if(line.find ("run 16764 - aero: ")!= std::string::npos)
    {
        foundhgcer = true;
    }
}  

if (!foundcal && !foundhgcer && !foundngcer && !foundaero)
{
    eff_file_out << "run 16764 - cal: "<< fixed << setprecision(5) << effcal << " +/- "  << setprecision(5)<< dEffcal << endl;
    eff_file_out << "run 16764 - hgcer: "<< fixed << setprecision(5) << effhgcer << " +/- "  << setprecision(5)<< dEffhgcer << endl;
    eff_file_out << "run 16764 - ngcer: "<< fixed << setprecision(5) << effngcer << " +/- "  << setprecision(5)<< dEffngcer << endl;
    eff_file_out << "run 16764 - aero: "<< fixed << setprecision(5) << effaero << " +/- "  << setprecision(5)<< dEffaero << endl << endl;
    foundhgcer = true;
    foundngcer = true;
    foundcal = true;
    foundaero = true;

    eff_file_out.close();
}


// Legend values : entered manually from terminal output


auto calLegend = new TLegend(0.55,0.5,0.9,0.75);
calLegend->AddEntry(h_cal_should,"Should","l");
calLegend->AddEntry(h_cal_should, "Integral = 422499.00 +/- 650.00 ","l"); // cal should 

calLegend->AddEntry(h_cal_did,"Did","l");
calLegend->AddEntry(h_cal_did,"Integral = 405367.00 +/- 636.68", "l"); // cal did 

calLegend->AddEntry( h_cal_did,"Efficiency = 0.9595 +/- 0.0030 ", "");
calLegend->SetTextSize(0.028);

auto hgcerLegend = new TLegend(0.55,0.5,0.9,0.75); // manually enter the integral and efficiency values from terminal output
hgcerLegend->AddEntry(h_hgcer_should,"Should","l");  
hgcerLegend->AddEntry(h_hgcer_should, "Integral = 379090.00 +/- 615.70","l"); // hgcer should

hgcerLegend->AddEntry(h_hgcer_did,"Did","l");
hgcerLegend->AddEntry(h_hgcer_did,"Integral = 369559.00 +/- 607.9", "l"); // hgcer did

hgcerLegend->AddEntry( h_hgcer_did,"Efficiency = 0.9749 +/- 0.0032", "");
hgcerLegend->SetTextSize(0.028);

auto ngcerLegend = new TLegend(0.55,0.5,0.9,0.75); // manually enter the integral and efficiency values from terminal output
ngcerLegend->AddEntry(h_ngcer_should,"Should","l");  
ngcerLegend->AddEntry(h_ngcer_should, "Integral = 397174.00 +/- 630.22","l"); // ngcer should

ngcerLegend->AddEntry(h_ngcer_did,"Did","l");
ngcerLegend->AddEntry(h_ngcer_did,"Integral = 378092.00 +/- 614.89", "l"); // ngcer did

ngcerLegend->AddEntry( h_ngcer_did,"Efficiency = 0.9520 +/- 0.0031", "");
ngcerLegend->SetTextSize(0.028);

auto aeroLegend = new TLegend(0.55,0.5,0.9,0.75); // manually enter the integral and efficiency values from terminal output
aeroLegend->AddEntry(h_aero_should,"Should","l");  
aeroLegend->AddEntry(h_aero_should, "Integral = 379090.00 +/- 615.70","l"); // aero should

aeroLegend->AddEntry(h_aero_did,"Did","l");
aeroLegend->AddEntry(h_aero_did,"Integral = 369559.00 +/- 607.91", "l"); // aero did

aeroLegend->AddEntry( h_aero_did,"Efficiency = 0.9749 +/- 0.0032", "");
aeroLegend->SetTextSize(0.028);

// draw + print the histograms

TCanvas *c1 = new TCanvas("c1");
h_hgcer_should->Draw("");
h_hgcer_did->Draw("SAME");
hgcerLegend->Draw();


TCanvas *c2 = new TCanvas("c2");
h_cal_should->Draw("");
h_cal_did->Draw("SAME");
calLegend->Draw();

TCanvas *c3 = new TCanvas("c3");
h_ngcer_should->Draw("");
h_ngcer_did->Draw("SAME");
ngcerLegend->Draw();

TCanvas *c4 = new TCanvas("c4");
h_aero_should->Draw("");
h_aero_did->Draw("SAME");
aeroLegend->Draw();


c1->Print("16764_hgcer_Eff.pdf","pdf");
c2->Print("16764_cal_Eff.pdf","pdf");
c3->Print("16764_ngcer_Eff.pdf","pdf");
c4->Print("16764_aero_Eff.pdf", "pdf");
}