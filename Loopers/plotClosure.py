from ROOT import *
gROOT.SetBatch(True)
import ROOT
gROOT.SetStyle("plain")
def makeDivCan():
    gStyle.SetOptStat(111110)
    """returns a divided canvas for ratios"""
    Rcanv = ROOT.TCanvas("Rcanv","Rcanv",1500,1200)
    Rcanv.cd()
    pad1 = ROOT.TPad("pad1","pad1",0,0.2,1,1)
    pad1.SetNumber(1)
    pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.2)
    pad2.SetBottomMargin(0.4)
    #pad2.SetRightMargin(0.07)
    pad2.SetTopMargin(0.01)
    #pad2.SetLeftMargin(0.18)
    pad2.SetNumber(2)
    pad2.SetGridy()
    pad1.Draw()
    pad2.Draw()
    Rcanv.cd()
    #ROOT.SetOwnership(Rcanv,0)
    ROOT.SetOwnership(pad1,0)
    ROOT.SetOwnership(pad2,0)
    return Rcanv
def save_and_show(c):
    c.SaveAs(h.save_name)
    r = ipy_show_canv(c)
    c.Close() #Need to close to prevent ROOT crash
    return r
def makeRatio(hist1,hist2,ymax=False,ymin=False,norm=False,xtitle=''):
    """returns the ratio plot hist2/hist1
    if one of the histograms is a stack put it in as argument 2!"""
    if norm:
        print 'scaling!'
        try:
            print 'scale 1: ',1/hist1.Integral()
            print 'scale 2: ',1/hist2.Integral()
            hist1.Scale(1/hist1.Integral())
            hist2.Scale(1/hist2.Integral())
        except(ZeroDivisionError):
            pass
    retH = hist1.Clone()
    try:
        retH.Divide(hist2)
    except(TypeError):
        #this is the error you get if hist2 is a stack
        hList = hist2.GetHists()
        sumHist = hist1.Clone("sumHist")
        sumHist.Reset()
        for h in hList:
            sumHist.Add(h)
        retH.Divide(sumHist)
    except(AttributeError):
        #this is the error you get if hist1 is a stack
        print "Did you use a stack as argument 1? please use stack as argument 2!"
        raise AttributeError
    if ymax or ymin:
        retH.GetYaxis().SetRangeUser(ymin,ymax)
        retH.SetLineColor(hist2.GetLineColor())
    retH.GetYaxis().SetTitle("Prediction/MC")
    retH.GetYaxis().SetTitleSize(0.15)
    retH.GetXaxis().SetTitleSize(0.15)
    retH.GetXaxis().SetTitle(xtitle)
    retH.GetXaxis().SetLabelSize(0.15)
    retH.GetYaxis().SetLabelSize(0.15)
    retH.GetYaxis().SetNdivisions(5)
    ROOT.SetOwnership(retH,0)
    return retH

def summaryplots(lepptname,fZee):
        ptl1_el = fZee.Get('el_pTl1_Wjets').Clone()
        ptl1_el.Add(fZee.Get('el_pTl1_tt1l'))
        ptl1_el_pred = fZee.Get('el_pTl1_fakesPred_Wjets').Clone()
        ptl1_el_pred.Add(fZee.Get('el_pTl1_fakesPred_tt1l'))
        ptl1_el_closure = makeRatio(ptl1_el_pred,ptl1_el,ymin=0,ymax=2.,xtitle='Leading electron Pt[GeV]')
        pad1=c.GetPad(1)
        pad2=c.GetPad(2)
        pad1.cd()
        ptl1_el_pred.Draw()
        ptl1_el.Draw("same")
        pad2.cd()
        ptl1_el_closure.Draw()
        c.Update()
        c.SaveAs(lepptname+".pdf") 

def main():
	fZee = TFile("rootfiles/FakeRateClosureHistograms.root")
        c=makeDivCan()

	l = TLegend(.75, .7, .95, .9)
        fakePred = ['pTl1_fakesPred_bfake', 'pTl2_fakesPred_bfake', 
                    'pTl1_fakesPred_Wjets','pTl2_fakesPred_Wjets',
                    'pTl1_fakesPred_tt1l','pTl2_fakesPred_tt1l', 
                    'el_pTl1_fakesPred_Wjets','mu_pTl1_fakesPred_Wjets',
                    'el_pTl2_fakesPred_Wjets','mu_pTl2_fakesPred_Wjets',
                    'el_pTl1_fakesPred_bfake','mu_pTl1_fakesPred_bfake',
                    'el_pTl2_fakesPred_bfake','mu_pTl2_fakesPred_bfake', 
                    'el_pTl1_fakesPred_tt1l','mu_pTl1_fakesPred_tt1l',
                    'el_pTl2_fakesPred_tt1l','mu_pTl2_fakesPred_tt1l'] 

        fakefrommc = [x.replace('_fakesPred',"") for x in fakePred]

        ptl1_el = fZee.Get('el_pTl1_Wjets').Clone("ptl1_el")
        ptl1_el.Add(fZee.Get('el_pTl1_tt1l'))
        ptl1_el_pred = fZee.Get('el_pTl1_fakesPred_Wjets').Clone("ptl1_el_pred")
        ptl1_el_pred.Add(fZee.Get('el_pTl1_fakesPred_tt1l'))
        ptl1_el_closure = makeRatio(ptl1_el_pred,ptl1_el,ymin=0,ymax=2.,xtitle='Leading electron Pt[GeV]') 
        pad1=c.GetPad(1)
        pad2=c.GetPad(2)
        pad1.cd()
        ptl1_el_pred.Draw()
        ptl1_el.Draw("same")
        pad2.cd()
        ptl1_el_closure.Draw()   
	c.Update()
	c.SaveAs("el_pTl1.pdf")
   
	for i,k in enumerate(fakefrommc):
	    hZee = fZee.Get(k)
	    hWgamma = fZee.Get(fakePred[i])
	    
	    if not hZee.InheritsFrom("TH1") or not hWgamma.InheritsFrom("TH1"):
		continue

	    hZee.SetLineColor(kBlue)
	    hZee.SetMarkerColor(kBlue)
	    hZee.SetLineWidth(2)
	    hWgamma.SetLineColor(kRed)
	    hWgamma.SetMarkerColor(kRed)
	    hWgamma.SetLineWidth(2)

	    hZee.SetTitle("from MC")
	    hWgamma.SetTitle("Prediction")

            xaxislabel = k.replace('l1','LeadLep')
            xaxislabel = k.replace('l2','SubLeadLep')
            h_ratio = makeRatio(hWgamma,hZee,ymin=0,ymax=2.,xtitle=xaxislabel +' [GeV]')
            h_ratio.SetStats(kFALSE)
	    s = THStack(hZee.GetName(), hZee.GetTitle())
	    s.Add(hZee)
	    s.Add(hWgamma)
            pad1=c.GetPad(1)
            pad2=c.GetPad(2)
            pad1.cd()
	    s.Draw("nostack")
#	    s.GetXaxis().SetTitle(k +' [GeV]')
            s.GetXaxis().SetLabelSize(0)
            s.SetTitle("Closure test")
	    l.Clear()
	    l.AddEntry(hZee)
	    l.AddEntry(hWgamma)
	    l.Draw()

            pad2.cd()
            h_ratio.Draw()
	    c.Update()
	    c.SaveAs("~/public_html/ttz_z_comp/"+k.replace("_ttzjets_reco", "") + ".pdf")

if __name__ == "__main__":
    main()
