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


// calorimeter detector, SHMS Carbon runs 16738 - 16746 not including runs 16738, 16739

void Eff_34_SHMS_cal()
{


const int sizec = 7;

double cx[sizec] = {1.619, 2.535, 4.670, 7.898, 12.048, 16.800, 24.126};
double cy[sizec] = {0.96709, 0.96665, 0.96638, 0.96608, 0.96551, 0.96558, 0.96574};
double cex[sizec] = {0,0,0,0,0,0,0};
double cey[sizec] = {0.00025, 0.00021, 0.00022, 0.00021, 0.00022, 0.00025, 0.00020};



TGraphErrors *grc = new TGraphErrors(sizec,cx,cy,cex,cey);
grc->SetTitle("SHMS Carbon Calorimeter Efficiency vs EL-Real Trigger Rate");
grc->SetMarkerColor(4);
grc->SetMarkerStyle(21);
grc->GetXaxis()->SetTitle("EL-Real Trigger Rate (KHz)");
grc->GetYaxis()->SetTitle("Calorimeter Efficiency");
grc->GetYaxis()->CenterTitle();
grc->Draw("ALP");


// LH2 Runs 16759 - 16764


const int sizeh = 6;

double hx[sizeh] = {122.374, 96.537,66.414, 44.098, 26.766, 14.198};
double hy[sizeh] = {0.95958,0.95945,0.96031, 0.96066, 0.96106, 0.96108};
double hex[sizeh] = {0,0,0,0,0,0};
double hey[sizeh] = {0.00029,0.00030, 0.00027, 0.00023, 0.00019, 0.00027};



TGraphErrors *grh = new TGraphErrors(sizeh,hx,hy,hex,hey);
grh->SetTitle("SHMS LH2 Calorimeter Efficiency vs EL-Real Trigger Rate");
grh->SetMarkerColor(4);
grh->SetMarkerStyle(21);
grh->GetXaxis()->SetTitle("EL-Real Trigger Rate (KHz)");
grh->GetYaxis()->SetTitle("Calorimeter Efficiency");
grh->GetYaxis()->CenterTitle();
grh->Draw("ALP");

/*
TF1 *f1 = new TF1("f1", "pol1", 0, 20);
f1->SetLineColor(kRed);
f1->SetLineWidth(2);
f1->GetParameters();
gr->Fit("f1","R");
gr->Draw("SAME");

*/

TCanvas *c1 = new TCanvas("c1");
c1->SetGrid();
c1->SetLeftMargin(0.15);
grc->Draw("");
c1->Print("Eff_34_SHMS_cal_C.png","png");

TCanvas *c2 = new TCanvas("c2");
c2->SetGrid();
c2->SetLeftMargin(0.15);
grh->Draw("");
c2->Print("Eff_34_SHMS_cal_LH2.png","png");





}