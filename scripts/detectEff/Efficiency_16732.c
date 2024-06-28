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

void Efficiency_16732()
{

// Run 16732 - HMS only, Carbon, 15 uA

TFile *f1 = new TFile("/u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/ROOTfiles/Analysis/Lumi/PionLT_replay_luminosity_16732_-1.root"); //open a new file for each beam current 
TTree *f1Tree = (TTree*)f1->Get("T");     
TTreeReader tr(f1Tree);

// branches that are accessed in the above root tree

TTreeReaderArray<Double_t> bcmAvg(tr,"H.bcm.bcm2.AvgCurrent");    
TTreeReaderArray<Double_t> caltr(tr,"H.cal.etottracknorm");        
TTreeReaderArray<Double_t> cerNpeSum(tr,"H.cer.npeSum");
TTreeReaderArray<Double_t> beta(tr,"H.gtr.beta");           // this, and above branches are given by outputted cut values for h_ecut_lumi when running /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/scripts/luminosity/replay_lumi.sh
TTreeReaderArray<Double_t> HgtrDP(tr,"H.gtr.dp");           // delta acceptance cut branch found in /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/DB/CUTS/general/accept.cuts

// histograms

//cerenkov hists
auto h_cer_should = new TH1D ("H.cer.npeSum", "HMS Carbon 15uA Efficiency - Run 16732", 300 , 0.1, 40);
h_cer_should -> SetLineColor(kBlack);
h_cer_should -> SetLineWidth(3);
auto h_cer_did = new TH1D ("did", "H.cer.npeSum", 300, 0.1, 40);
h_cer_did -> SetLineColor(kRed);
h_cer_did -> SetLineWidth(1);
h_cer_did -> SetLineStyle(2);

// calorimeter hists
auto h_cal_should = new TH1D ("H.cal.etottracknorm", "HMS Carbon 15uA Efficiency - Run 16732", 300, 0.1, 2);
h_cal_should -> SetLineColor(kBlack);
h_cal_should -> SetLineWidth(3);
auto h_cal_did = new TH1D ("did", "H.cal.etottracknorm", 300, 0.1, 2);
h_cal_did -> SetLineColor(kRed);
h_cal_did -> SetLineWidth(1);
h_cal_did -> SetLineStyle(2);


// cut values

auto bcmAvgCut1 = 15.0; 
auto bcmAvgCut2 = 4.0;
auto cerNpeSumCut = 3.0;
auto betaCut1 = 1;
auto betaCut2 = 0.3;
auto caltrCut = 0.7;        // this, and above pid cuts are given by outputted cut values for h_ecut_lumi when running /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/scripts/luminosity/replay_lumi.sh
auto H_del_low = -8.0;      // this, and the below acceptance cuts are were found in /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/DB/PARAM/Acceptance_Parameters.csv
auto H_del_high = 8.0;

// fill the histograms

while(tr.Next())
{   // cerenkov fill
    for (unsigned int i = 0; i <cerNpeSum.GetSize() ; i++)
    {
        if((abs(bcmAvg[i]-bcmAvgCut1)<bcmAvgCut2) && abs(beta[i]-betaCut1)<betaCut2 && caltr[i]>caltrCut && HgtrDP[i] > H_del_low && HgtrDP[i] < H_del_high)
        {                                       // ^^^"should" cuts ^^^
            h_cer_should->Fill(cerNpeSum[i]);
            if(cerNpeSum[i] > cerNpeSumCut)     // <<< "did" cut
            {
                h_cer_did->Fill(cerNpeSum[i]);
            }
        }
    }
    // calorimeter fill
    for (unsigned int i = 0; i <caltr.GetSize() ; i++)
    {
        if((abs(bcmAvg[i]-bcmAvgCut1)<bcmAvgCut2) && abs(beta[i]-betaCut1)<betaCut2 && cerNpeSum[i] > cerNpeSumCut && HgtrDP[i] > H_del_low && HgtrDP[i] < H_del_high)
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
printf(" 16732_cal Integral Should = %0.2f +/- %0.2f\n", Scal, dScal);

double dDcal= 0.0;
double Dcal = h_cal_did->IntegralAndError(1,300,dDcal,"");	
printf(" 16732_cal Integral Did = %0.2f +/- %0.2f\n",Dcal,dDcal);

double effcal = (Dcal/Scal);
double dEffcal = sqrt((effcal*(1-effcal))/Scal);
printf(" 16732_cal Efficiency = %0.5f +/- %0.5f \n\n", effcal,dEffcal);

double dScer = 0.0;
double Scer = h_cer_should->IntegralAndError(1,300,dScer,""); // "should" integral
printf(" 16732_cer Integral Should = %0.2f +/- %0.2f\n", Scer, dScer); 

double dDcer= 0.0;
double Dcer = h_cer_did->IntegralAndError(1,300,dDcer,"");  // "did" integral
printf(" 16732_cer Integral Did = %0.2f +/- %0.2f\n",Dcer,dDcer);

double effcer = (Dcer/Scer);                            // efficiency == did/should 
double dEffcer = sqrt((effcer*(1-effcer))/Scer);
printf(" 16732_cer Efficiency = %0.5f +/- %0.5f \n\n", effcer, dEffcer);

// Output the efficiency for each run number into a txt file

ifstream eff_file_in("eff_values.txt");
ofstream eff_file_out("eff_values.txt", std::ios_base::app);
string line;
bool foundcal = false;
bool foundcer = false;

while(getline(eff_file_in, line))
{ 
    if(line.find("run 16732 - cal:")!= std::string::npos)
    {
        foundcal = true;
    }
    if(line.find ("run 16732 - cer: ")!= std::string::npos)
    {
        foundcer = true;
    }
}  

if (!foundcal && !foundcer)
{
    eff_file_out << "run 16732 - cal: "<< fixed << setprecision(5) << effcal << " +/- "  << setprecision(5)<< dEffcal << endl;
    eff_file_out << "run 16732 - cer: "<< fixed << setprecision(5) << effcer << " +/- "  << setprecision(5)<< dEffcer << endl << endl;

    foundcer = true;
    foundcal = true;

    eff_file_out.close();
}


// Legend values : entered manually from terminal output


auto calLegend = new TLegend(0.55,0.5,0.9,0.75);
calLegend->AddEntry(h_cal_should,"Should","l");
calLegend->AddEntry(h_cal_should, "Integral = 325624.00 +/- 570.63 ","l"); // cal should 

calLegend->AddEntry(h_cal_did,"Did","l");
calLegend->AddEntry(h_cal_did,"Integral = 324785.00 +/- 569.90 ", "l"); // cal did 

calLegend->AddEntry( h_cal_did,"Efficiency =  0.9974 +/- 0.0035", "");
calLegend->SetTextSize(0.028);

auto cerLegend = new TLegend(0.55,0.5,0.9,0.75); // manually enter the integral and efficiency values from terminal output
cerLegend->AddEntry(h_cer_should,"Should","l");  
cerLegend->AddEntry(h_cer_should, "Integral = 325103.00 +/- 570.18","l"); // cer should

cerLegend->AddEntry(h_cer_did,"Did","l");
cerLegend->AddEntry(h_cer_did,"Integral = 324738.00 +/- 569.86", "l"); // cer did

cerLegend->AddEntry( h_cer_did,"Efficiency = 0.9989 +/- 0.0035", "");
cerLegend->SetTextSize(0.028);

TCanvas *c1 = new TCanvas("c1");
h_cer_should->Draw("");
h_cer_did->Draw("SAME");
cerLegend->Draw();

TCanvas *c2 = new TCanvas("c2");
h_cal_should->Draw("");
h_cal_did->Draw("SAME");
calLegend->Draw();

c1->Print("16732_cer_Eff.pdf","pdf");
c2->Print("16732_cal_Eff.pdf","pdf");
}