#include "Conf.h"
#include "CentUtil.h"

CentUtil::CentUtil() {
    nTofMatchUpperPoly3 = new TF1("nTofMatchUpperPoly3", "pol3", 0, 850);
    nTofMatchLowerPoly3 = new TF1("nTofMatchLowerPoly3", "pol3", 0, 850);
    betaEta1UpperPoly3 = new TF1("betaEta1UpperPoly3", "pol3", 0, 850);
    betaEta1LowerPoly3 = new TF1("betaEta1LowerPoly3", "pol3", 0, 850);
    for (int i=0; i<3; i++) {
        nTofMatchUpperPars[i] = 0;
        nTofMatchLowerPars[i] = 0;
        betaEta1UpperPars[i] = 0;
        betaEta1LowerPars[i] = 0;
    }
    nTofMatchUpperPoly3->SetParameters(nTofMatchUpperPars);
    nTofMatchLowerPoly3->SetParameters(nTofMatchLowerPars);
    betaEta1UpperPoly3->SetParameters(betaEta1UpperPars);
    betaEta1LowerPoly3->SetParameters(betaEta1LowerPars);

    for (int i=0; i<MAX_TRG; i++) {
        kLumi[i] = 0;
        bLumi[i] = 0;
    }
    
    funcVz = new TF1("funcVz", "pol6", -70, 70);
    for (int i=0; i<9; i++) {
        centSplitEdge[i] = 0;
    }
    doPileUp = doLumi = doVz = true;
    doSplit = false;
}

void CentUtil::ReadParams() {
    nTrg = cent_conf::nTrg; 
    std::cout << "[LOG] - ReadParams: The parameter list is named as [" << cent_conf::Name << "] version [" << cent_conf::Mode << "]." << std::endl;
    std::cout << "[LOG] - ReadParams: Number of triggers: " << nTrg << ", list: ";
    for (int i=0; i<nTrg; i++) {
        std::cout << cent_conf::trgList[i] << "\t";
    }
    std::cout << std::endl;

    SetPileUpNTofMatchUpperParam(cent_conf::nTofMatch_upper_pars);
    SetPileUpNTofMatchLowerParam(cent_conf::nTofMatch_lower_pars);
    SetPileUpBetaEta1UpperParam(cent_conf::beta_eta1_upper_pars);
    SetPileUpBetaEta1LowerParam(cent_conf::beta_eta1_lower_pars);

    for (int i=0; i<nTrg; i++) {
        SetLumiParam(cent_conf::trgList[i], cent_conf::lumi_par[i][0], cent_conf::lumi_par[i][1]);
    }

    for (int i=0; i<nTrg; i++) {
        SetVzParam(cent_conf::trgList[i], &cent_conf::vz_par[i][0]);
    }

    SetCentEdge(cent_conf::cent_edge);
}

int CentUtil::ConvertTrg(int trg) {
    for (int i=0; i<nTrg; i++) {
        if (trg == cent_conf::trgList[i]) { 
            return i;
        }
    }
    return -1;
}

int CentUtil::LumiCorrection(int trg, int ref3, int zdcx) {
    // trg means converted trgid
    // like: 0 for 610001, 0 is trg and 610001 is trgid 
    double f = zdcx * kLumi[trg] + bLumi[trg];
    double factor = f == 0 ? 0.0 : bLumi[trg] / f;
    return (int)(factor * ref3);
}

int CentUtil::VzCorrection(int trg, int ref3, double vz) {
    double factor = parVz[trg][0] / funcVz->Eval(vz);
    return (int)(factor * ref3);
}

int CentUtil::GetRefMult3Corr(int ref3, int beta_eta1, int nTofMatch, int TofMult, double zdcx, double vz, int trgid) {
    int trg = ConvertTrg(trgid);
    if (trg >= nTrg || trg < 0) {
        return -1;
    }
    if (fabs(vz) > 70.0) {
        return -1;
    }
    if (doPileUp && IsPileUp(ref3, beta_eta1, nTofMatch)) {
        return -1;
    }
    if (doLumi) {
        ref3 = LumiCorrection(trg, ref3, zdcx);
    }
    if (doVz) {
        ref3 = VzCorrection(trg, ref3, vz);
    }
    return ref3;

}

int CentUtil::GetCentrality9(int ref3) {
    if (!doSplit) {
        std::cout << "[WARNING] - GetCentrality9: Centrality bin edge not set yet." << std::endl;
        return -1;
    }
    for (int i=0; i<9; i++) {
        if (ref3 > centSplitEdge[i]) {
            return i;
        }
    }
    return -1;
}

bool CentUtil::IsBetaEta1PileUp(int ref3, int beta_eta1) {
    return betaEta1UpperPoly3->Eval(beta_eta1) < ref3 || betaEta1LowerPoly3->Eval(beta_eta1) > ref3 || beta_eta1 <= 1;
}

bool CentUtil::IsNTofMatchPileUp(int ref3, int nTofMatch) {
    return nTofMatchUpperPoly3->Eval(nTofMatch) < ref3 || nTofMatchLowerPoly3->Eval(nTofMatch) > ref3 || nTofMatch <= 1;
}
