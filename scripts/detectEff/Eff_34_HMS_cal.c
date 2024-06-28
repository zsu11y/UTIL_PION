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
#include <fstream>
using namespace std;


// calorimeter detector, HMS only, Carbon, runs 16727 - 16737 not including runs: 16728, 16733, 16736, 16737

void Eff_34_HMS_cal()
{



// LH2, runs 16703 - 16712 not including runs 16705, 16707, 16711, 16712


const int sizeh = 6;
double hx[sizeh] = {80.208, 78.125, 55.124, 34.256, 21.107, 12.048, };
double hy[sizeh] = {0.99651, 0.99697, 0.99706, 0.99722, 0.99735, 0.99743, };
double hex[sizeh] = {0,0,0,0,0,0};
double hey[sizeh] = {0.00007, 0.00008, 0.00007, 0.00007, 0.00007, 0.00007};


TGraphErrors *grh = new TGraphErrors(sizeh,hx,hy,hex,hey);
grh->SetTitle("HMS LH2 Calorimeter Efficiency vs EL-Real Trigger Rate");
grh->SetMarkerColor(kBlue);
grh->SetMarkerStyle(21);
grh->GetXaxis()->SetTitle("EL-Real Trigger Rate (KHz)");
grh->GetYaxis()->SetTitle("Calorimeter Efficiency");
grh->GetYaxis()->CenterTitle();
grh->Draw("ALP");




// Carbon, runs 16727 - 16737 not including runs: 16728, 16733, 16736, 16737


const int sizec = 7;

double cx[sizec] = {18.644 ,14.796, 10.260, 7.052, 3.540, 2.056, 1.409};
double cy[sizec] = {0.99748, 0.99743, 0.99761, 0.99748, 0.99742, 0.99770, 0.99757};
double cex[sizec] = {0,0,0,0,0,0,0};
double cey[sizec] = {0.0008, 0.0005, 0.0005, 0.0005, 0.0009, 0.0005, 0.0005};



TGraphErrors *grc = new TGraphErrors(sizec,cx,cy,cex,cey);
grc->SetTitle("HMS Carbon Calorimeter Efficiency vs EL-Real Trigger Rate");
grc->SetMarkerColor(kBlue);
grc->SetMarkerStyle(21);
grc->GetXaxis()->SetTitle("EL-Real Trigger Rate (KHz)");
grc->GetYaxis()->SetTitle("Calorimeter Efficiency");
grc->GetYaxis()->CenterTitle();
grc->Draw("ALP");







/*
TF1 *f1 = new TF1("f1", "pol1", 0, 20);
f1->SetLineColor(kRed);
f1->SetLineWidth(2);
f1->GetParameters();
grc->Fit("f1","R");
grc->Draw("SAME");

*/

TCanvas *c1 = new TCanvas("c1");
c1->SetGrid();
c1->SetLeftMargin(0.15);
grh->Draw("");
c1->Print("Eff_34_HMS_cal_LH2.png","png");

TCanvas *c2 = new TCanvas("c2");
c2->SetGrid();
c2->SetLeftMargin(0.15);
grc->Draw("");
c2->Print("Eff_34_HMS_cal_C.png","png");






}