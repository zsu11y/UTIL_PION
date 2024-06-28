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


// cerenkov detector, SHMS Carbon runs 16738 - 16746 not including runs 16738, 16739

void Eff_34_C_SHMS_ngcer()
{


const int size = 7;

double x[size] = {1.619, 2.535, 4.670, 7.898, 12.048, 16.800, 24.126};
double y[size] = {0.94661, 0.94736, 0.94839, 0.94710, 0.94746, 0.94755, 0.94809};
double ex[size] = {0,0,0,0,0,0,0};
double ey[size] = {0.00033, 0.00027, 0.00028, 0.00027, 0.00028, 0.00032, 0.00025};



TGraphErrors *gr = new TGraphErrors(size,x,y,ex,ey);
gr->SetTitle("SHMS Carbon Noble Gas Cerenkov Efficiency vs EL-Real Trigger Rate");
gr->SetMarkerColor(4);
gr->SetMarkerStyle(21);
gr->GetXaxis()->SetTitle("EL-Real Trigger Rate (KHz)");
gr->GetYaxis()->SetTitle("Noble Gas Cerenkov Efficiency");
gr->GetYaxis()->CenterTitle();
gr->Draw("ALP");

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
gr->Draw("");
c1->Print("Eff_34_SHMS_C_ngcer.png","png");







}